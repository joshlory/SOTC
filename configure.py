import argparse
import os
import shutil
import subprocess
import sys
import re

from   pathlib import Path
from   typing  import Dict, List, Set, Union

import ninja_syntax

import splat
import splat.scripts.split as split
from   splat.segtypes.linker_entry import LinkerEntry

ROOT = Path(__file__).parent
TOOLS_DIR = ROOT / "tools"

YAML_FILE = "config/sotc_preview.yaml"
BASENAME = "SCPS_150.97"
LD_PATH = f"{BASENAME}.ld"
ELF_PATH = f"build/{BASENAME}"
MAP_PATH = f"build/{BASENAME}.map"
PRE_ELF_PATH = f"build/{BASENAME}.elf"

COMMON_INCLUDES = "-Iinclude -Isrc -isystem include/sdk/ee -isystem include/sdk -isystem include/gcc -isystem include/gcc/gcc-lib"
COMPILER_DIR = f"{TOOLS_DIR}/cc/ee-gcc2.96/bin"

COMPILER_FLAGS     = "-O2 -G8 -gstabs"
COMPILER_FLAGS_CPP = "-O2 -G8 -x c++ -fno-exceptions -gstabs"

COMPILE_CMD = (
    f"{COMPILER_DIR}/ee-gcc -c {COMMON_INCLUDES} {COMPILER_FLAGS}"
)
COMPILE_CMD_CPP = (
    f"{COMPILER_DIR}/ee-gcc -c {COMMON_INCLUDES} {COMPILER_FLAGS_CPP}"
)


def exec_shell(command: List[str], stdout = subprocess.PIPE) -> str:
    ret = subprocess.run(
        command, stdout=stdout, stderr=subprocess.PIPE, text=True
    )
    return ret.stdout


def clean():
    if os.path.exists(".splache"):
        os.remove(".splache")
    shutil.rmtree("asm", ignore_errors=True)
    shutil.rmtree("assets", ignore_errors=True)
    shutil.rmtree("build", ignore_errors=True)


def write_permuter_settings():
    with open("permuter_settings.toml", "w") as f:
        f.write(
            f"""compiler_command = "tools/cc/ee-gcc2.96/bin/ee-gcc.exe -c -Iinclude -Iinclude/sdk/ee -Iinclude/gcc -Iinclude/gcc/gcc-lib -O2 -G8 -gstabs -D__GNUC__"
assembler_command = "mips-linux-gnu-as -march=r5900 -mabi=eabi -Iinclude"
compiler_type = "gcc"

[preserve_macros]

[decompme.compilers]
"tools/cc/ee-gcc2.96/bin/ee-gcc" = "ee-gcc2.9-991111-01"
"""
        )


def build_stuff(linker_entries: List[LinkerEntry]):
    built_objects: Set[Path] = set()

    def build(
        object_paths: Union[Path, List[Path]],
        src_paths: List[Path],
        task: str,
        variables: Dict[str, str] = {},
        implicit_outputs: List[str] = [],
    ):
        if not isinstance(object_paths, list):
            object_paths = [object_paths]

        object_strs = [str(obj) for obj in object_paths]

        for object_path in object_paths:
            if object_path.suffix == ".o":
                built_objects.add(object_path)
            ninja.build(
                outputs=object_strs,
                rule=task,
                inputs=[str(s) for s in src_paths],
                variables=variables,
                implicit_outputs=implicit_outputs,
            )

    ninja = ninja_syntax.Writer(open(str(ROOT / "build.ninja"), "w"), width=9999)

    # Rules
    cross = "mips-linux-gnu-"
    ld_args = f"-EL -T config/undefined_syms_auto.txt -T config/undefined_funcs_auto.txt -T config/undefined_syms.txt -Map $mapfile -T $in -o $out"

    ninja.rule(
        "as",
        description="as $in",
        command=f"cpp {COMMON_INCLUDES} $in | iconv -f=UTF-8 -t=EUC-JP $in | {cross}as -no-pad-sections -EL -march=5900 -mabi=eabi -Iinclude -o $out",
    )

    ninja.rule(
        "cpp",
        description="cpp $in",
        command=f"{COMPILE_CMD_CPP} $in -o $out && {cross}strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "cc",
        description="cc $in",
        command=f"{COMPILE_CMD} $in -o $out && {cross}strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "ld",
        description="link $out",
        command=f"{cross}ld {ld_args}",
    )

    ninja.rule(
        "sha1sum",
        description="sha1sum $in",
        command="sha1sum -c $in && touch $out",
    )

    ninja.rule(
        "elf",
        description="elf $out",
        command=f"{cross}objcopy $in $out -O binary",
    )

    for entry in linker_entries:
        seg = entry.segment

        if seg.type[0] == ".":
            continue

        if entry.object_path is None:
            continue

        if isinstance(seg, splat.segtypes.common.asm.CommonSegAsm) or isinstance(
            seg, splat.segtypes.common.data.CommonSegData
        ):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.cpp.CommonSegCpp):
            build(entry.object_path, entry.src_paths, "cpp")
        elif isinstance(seg, splat.segtypes.common.c.CommonSegC):
            build(entry.object_path, entry.src_paths, "cc")
        elif isinstance(seg, splat.segtypes.common.databin.CommonSegDatabin) or isinstance(seg, splat.segtypes.common.rodatabin.CommonSegRodatabin):
            build(entry.object_path, entry.src_paths, "as")
        else:
            print(f"ERROR: Unsupported build segment type {seg.type}")
            sys.exit(1)

    ninja.build(
        PRE_ELF_PATH,
        "ld",
        LD_PATH,
        implicit=[str(obj) for obj in built_objects],
        variables={"mapfile": MAP_PATH},
    )

    ninja.build(
        ELF_PATH,
        "elf",
        PRE_ELF_PATH,
    )

    ninja.build(
        ELF_PATH + ".ok",
        "sha1sum",
        "checksum.sha1",
        implicit=[ELF_PATH],
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Configure the project")
    parser.add_argument(
        "-c",
        "--clean",
        help="Clean extraction and build artifacts",
        action="store_true",
    )
    parser.add_argument(
        "-csrc",
        "--cleansrc",
        help="Clean the 'src' folder",
        action="store_true",
    )
    parser.add_argument(
        "-nogp",
        "--no-gprel-removing",
        help="Do not remove gp_rel references on the disassembly",
        action="store_true",
    )
    parser.add_argument(
        "-noconvert",
        "--no-eucjp-converting",
        help="Do not convert to EUC-JP the disassembly strings",
        action="store_true",
    )
    args = parser.parse_args()

    if args.clean:
        clean()
    
    if args.cleansrc:
        shutil.rmtree("src", ignore_errors=True)

    split.main([YAML_FILE], modes="all", verbose=False)

    linker_entries = split.linker_writer.entries

    build_stuff(linker_entries)

    write_permuter_settings()

    if not os.path.isfile("compile_commands.json"):
        exec_shell(["ninja", "-t", "compdb"], open("compile_commands.json", "w"))