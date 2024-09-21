#include "common.h"

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", _iosAssert);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400121D0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosIopRead);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCdStStart);

void iosCdStStop(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCdStRead);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCdStSkip);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCdStSectorAlignSkip);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCdSetErrorCallback);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCdSetMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCdStInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCdInit);

void iosInitDebPc(void) {
}

void iosStopPc(void) {
}

void iosDebPcVsyncCounterCheck(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetCnt0Pc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetCnt1Pc);

void InitDebPc(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosWaitIdleThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreateIdleThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetClock);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetClockSecond);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40012A78);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosAddIntcHandler);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreateSema);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDeleteSema);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInitIntrSystem);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetTCount);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetTCountExtension);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetSecondFromTCount);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosResetCpuRapCounter);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetCpuRapCountPar1Int);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDI);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosEI);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosLoaderResetEntry);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40013058);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40013090);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosEE2IopRequest);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosEE2IopEndChk);

void iosCreateIopMgr(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40013160);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400133C8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400135C8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40013A78);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMallocInGarbagePtn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400142E0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40014770);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40014AF8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40014D48);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40014F88);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40015210);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400152B8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400155C0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosWaitMalloc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSignalMalloc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMallocGarbageTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMallocAlign);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMallocAlignNoCheck);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMallocSetExecGarbageCallback);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosReallocAlign);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFree);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFreeParts);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreatePartition);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreatePartitionWithPc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInitMallocSystem);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetMallocPtn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetMallocRootPtnRemainSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFollowAllLink);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDebugPartitionDump);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDebugPartitionFileDump);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40015F18);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", addMemoryDebugCallback);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getMemorySafetyLockFlag);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40015F58);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcGetInfo);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcChDir);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcMkDir);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcCreateFile);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcDeleteFile);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcReadFile);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcWriteFile);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcFormat);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcUnformat);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMcGetDir);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400167B0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSendMsg);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRecvMsg);

void iosInitMessageSystem(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreateMsgQueue);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40016BB8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40016BD0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40016C10);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40016E20);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosNetRecvMsg);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitNet);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosNetRecv);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosNetSend);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosNetRecvMsgWithStateCallback);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosNetClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosNetOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadGetXZInputL);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadGetXZInputLwithThreshold);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadGetXZInputLwithThresholdIndepAxis);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadGetXZInputR);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadEntryTickFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadRead);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadChkConnect);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPadInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSPrintf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosUsbSerialPrintf);

void iosCreatePrintMgr(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetPrintfMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSrpWaitDMA);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMemToSprDmaAdrCopy);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSprToMemDmaAdrCopy);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreateThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40018530);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInitThreadSystem);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreateThreadS);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosStartThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSleepThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosWakeupThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosiWakeupThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosChangeThreadPriority);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetThreadPriority);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDeleteThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCallBackThreadMgr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", ioskernel);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosJumpRecoverPoint);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosResetKernel);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40018D30);

void endSCEDemo(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40018D88);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40019018);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400192E0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Init_ShockVoiceSet);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Init_Shock);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Shock_SetShockVoiceSet);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Init_Player);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Init_Controler);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Shock_Request);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Shock_Decode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Shock_SetMotor);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40019958);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40019960);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400199A8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400199B0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40019A00);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40019B58);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40019D68);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40019FF0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001A170);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001A2F8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysMoveModuleObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysCreateModuleObjExisted);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysResolveAllModuleObjHasUndefSymbol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001A918);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001AB68);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001AD58);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001AE88);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysLaunchModule);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", IosCdvdManagerSimulation);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetXffEntryPointPreRelocation);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitDld);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", IosLoadIrxSimulation);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", IosGetMergeDataFileName);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysSearchSymbol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysSearchModuleFuncNameByAddr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDumpExecutableModules);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysSearchModuleSymbolByGroup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysRemoveModuleObjGroup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysResolveOneModuleObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysResolveAllProgramModule);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysLaunchExecModule);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysInitModuleObjExisted);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysFlushModuleObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetSymbolByIndex);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysRelocateModuleObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetXffWorkSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetModuleObjMallocSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDisposeModuleObjRelocationElement);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetExecModuleSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getModuleSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C220);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C248);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetUndefModuleObjNum);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetSymdefModuleObjNum);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C350);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C3B0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C3F8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C440);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C468);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C4F8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C5E8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysResolveAllModuleObjOfGroup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", readEModule);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysWriteLinkerScriptFile);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001C8F0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", loadtest);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosLoaderGetFileSizeName);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFileRead);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosLoaderFOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosLoaderFClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosLoaderFRead);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosLoaderGetFileSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", initDldSys);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001CDD8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001CFE0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001D120);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", DldExceptionByOriginAdr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysSearchCalledModuleFuncNameByAddr);

void isysCreateExceptionThread(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001D3A8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCubicBezier);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCubicInterVectorXYZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFourthBezier);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCubicBezierVectorXYZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitMath);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001D5E0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", CompareString16);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInitCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosUnitCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPushCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPopCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPushVu0RegistersToWork);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPopVu0RegistersFromWork);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosTransCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetTransCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosClearTransCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetRotXVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetRotYVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRotCurrentMatrixX);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRotCurrentMatrixY);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRotCurrentMatrixZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosScaleCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetCurrentMatrixTrans);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMulCurrentMatrixR);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMulCurrentMatrixL);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosApplyCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosApplyRotCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRotTransPersCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosTransposeCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosTransposeRotationCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInverseCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPushVu0Registers);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPopVu0Registers);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInitPushPosVuSema);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCopyMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosApplyRotMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosUnitMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosUnitRotation);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosTransposeMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInverseMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInverseMatrixPerfect);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosScaleMatrixV);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFloatModulo);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetCameraMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMakeNormalLightMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosScaleNormalLightMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMakeLightColorMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosTransMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosTransMatrixF);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosScaleMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMulRotMatrixXInt16);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRotMatrixX);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRotMatrixY);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRotMatrixZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDumpMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetScaleMatrixV);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetYDirXYZFromMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetXDirXYZFromMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFmodf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosRotTransCurrentMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMvecZero);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMvecAllOnes);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMvecAllOne);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosAddMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosClampSW_AddMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosClampUW_AddMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSubMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMulMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosApplyM_Mat);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCalcIcolorToBrightness);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosIColScale);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosIColAddVec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSwClip255Mvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosIColAddVecXYZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosUcharColClampAdd);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSWToMmColMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMmColToSWMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosITOF15ToMmColMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMmColToITOF15Mvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFvecToMmColMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMmColToFvecMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSwClipMvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFvecToICol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosIColToMvecSl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosIColToFvec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPowf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFastPowf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetDifferencialQuaternionWithNoRegularize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4001FCA8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetEulerYXZFromQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetEulerZXYFromQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetEulerXYZFromQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetRotLimitationQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetLimitationQuaternionWithBaseAxis);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetCurrentQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetLastQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", MultiCurrentQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", MultiCurrentQuaternionL);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InvertCurrentQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetCurrentQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", RotCurrentQuaternionX);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", RotCurrentQuaternionY);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", RotCurrentQuaternionZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", PushQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", PushQuaternionWithNoCopy);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", PopQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitQuaternionDrive);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetQuaternionByAxisRotate);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetQuaternionByAxisRotateWithNoRegularize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetQuaternionByAxisRotateV);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetQuaternionByAxisRotateVExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetQuaternionByAxisRotateVWithNoRegularize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", DivQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetInverseMatrixFromQuaternionPos);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", MultiMatrixByQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetMirrorQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", RotQuaternionXExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", RotQuaternionYExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", RotQuaternionZExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionFromMatrix);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", CopyMultiQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByAxisDirZY);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByAxisDirZYExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByAxisDirZX);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetQuaternionByCosineAxisRotateVWithNoRegularize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetQuaternionByAxisRotateVWithNoRegularizeRadian);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetYRotQuaternionFromDir);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetStabYRotQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", StabilizeToYRotQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByEulerYXZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByEulerYXZExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetEulerYXZFromQuaternionZHalfPI);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByEulerZXY);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByEulerZXYExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByEulerXYZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByEulerXYZExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetLimitationQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetZDirFromQuaternion);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionByDegEulerYXZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetQuaternionAxisRotInfo);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SetQuaternionByCosineAxisRotateV);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetAlignSinCosf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetSinCosf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetSinf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetCosf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetTanf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetSinCos);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetSin);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetCos);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetTan);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetACosf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetACos);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetACosfExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetASinfExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetATanfExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetATan2fExact);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetASin);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetATan2);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", resetArcFuncCall);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetTableSin);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetTableCos);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitTableSinCos);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFTOI15Vector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFTOI12Vector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFTOI4Vector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFTOI0Vector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosITOF15Vector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosITOF12Vector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosITOF4Vector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosITOF0Vector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetStabXZVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInitRandom);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetRandom);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetRandomVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetDRandomVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetRandomVector0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosAbsVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetReflectVector);

void iosDumpFVector(void) {
}

void iosDumpIVector(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetArbitraryUpVectorElement);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetScaleInverseVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetStabXYVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetStabYZVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetLengthPointToLine);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetInverseVectorXYZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetExceptAxisVector);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCalcFColorToBrightness);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosITOF15VectorXYZ);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosScaleColorTo255);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosScaleColorToONE);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40024218);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreateDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosReleaseDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetDCParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetDCClearParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetDCViewPort);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetDCViewPortCenter);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPushDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPopDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetRootDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetRootDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetCurrentDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetCurrentDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosResetDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosInitDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetDCGroup);

void func_40024A30(void) {
}

void func_40024A38(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetDCWithClear);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", _iosPushDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosPushDCWithClear);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40024B90);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlPopLayer);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40024FB0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosUsedPacketBufferSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCreateIVArbitrationSema);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlGetTransAdrs);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetPacketPtrPath1);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetPacketPtrPath1);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosAllocPacketPtrPath1);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlChainHead);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlChainTail);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlChainHeadCurrent);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlChainTailCurrent);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlSwap);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlTrans);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlLockObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlGetWorkBufId);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlGetTransBufId);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlGetEndAdrs);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlGetLayer);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlSetLayer);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlPushLayer);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlGetLayerNum);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlRelease);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitDL);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlCheckAdrs);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlCheckSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlGetCreateAdrs);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosAllocPacketPtrPath1UnCachedA);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDlTransNow);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDumpDMAStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDumpVIF1Status);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDumpGIFStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSyncPath);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400268A8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40026BE0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGsResizeRootDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGsSetMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGsSetDrawContext);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCopyFrameBuffer);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getDispScreenWidth);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getDispScreenHeight);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getDrawScreenWidth);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getDrawScreenHeight);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getFrameBufferSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getFrameBufferSizeFBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getFrameBufferSizeTBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getDispBufferAddressTBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getDispBufferAddressFBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getDrawBufferAddressTBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getDrawBufferAddressFBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getZBufferAddressTBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getZBufferAddressFBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getTextureAreaAddressTBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getTextureAreaAddressFBP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getScreenOffsetX);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getScreenOffsetY);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getAntiAlias);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getProgressiveMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosResetGraph);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDmaSendPath1);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDmaSendPath2);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDmaSendPath3);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDmaSendSChainPath1);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDmaSendSChainPath2);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosDmaSendSChainPath3);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosResetPath);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSyncV);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetField);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGsChangeMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetBGColor);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGsResetCRTC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetSyncNoReturnFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetScreenEnv);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosCheckDrawFinish);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGsInitDC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitGp);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosWaitDMA);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosWaitVU1);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getCRTCoffsetU);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getCRTCoffsetV);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGsChangeScreenOffset);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSyncGP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", bootGPThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosTransGP);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosChkGpDlTransExec);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGPFrameInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetIStartFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetGpFinishFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetIFinishFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getIntrGpCount);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetDlTransFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetVSchedulerFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosWaitGPFinish);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40028600);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iStart);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iFinish);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400286E8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsRegBegin);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsRegEnd);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsRegEndWithPtr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsReglistBegin);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsReglistEnd);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsBox);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsBox2);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsBoxLine);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", spriteNoTexFast);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", spriteTexFast);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", gsReg);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getSpriteDrawFirst);

void gsReglist(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosTransTex);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getTWH);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDeleteObjManager);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002AF90);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002B218);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysAddGroupWithLinkParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysAddGroupRelativeWithLinkParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", _isysDeleteGroup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDeleteGroupWithLinkParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDeleteGroupAllObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDeleteAllGroup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGroupForFirst);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGroupForFirstForce);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGroupGetObjNumForce);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", _isysCreateObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysSetObjImmediateDeleteFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysRequestDeleteObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysInitGroup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysAddGroupWithLinkParamNoWait);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysObjDeleteLock);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysObjDeleteUnLock);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGroupForNext);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGroupForNextForce);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGroupForExit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysInitObjSystem);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetLinkNum);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetLinkMax);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetObjIdentifierByObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetGroupSrhNext);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysObjWaitSema);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysObjSignalSema);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002C8F0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getVIntrCnt);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", waitVscheduler);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", bootSchedulerThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosAddISchedulerTaskList);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetISchedulerExecCnt);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", ischedStop);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", ischedRestart);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetISchedulerSubthreadTask);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSetIVSyncMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetIVSyncMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vschedSetNextFrameForceGarbage);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetGarbageTime);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002CD88);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002CDB0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002CEA0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysInitISYSLetterObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysFlushISYSLetterObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetLetterObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysLetterObjDiscardLetterAll);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", create_letter);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", init_letter);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", is_hope_letter_type);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", get_letter_contents_data);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002D1E0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", increment_letter_refcount);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", decrement_letter_refcount);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", is_letter_reach_time);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", is_init_letter_called);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", get_reference_letter_type);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", get_letter_receiver_obj_group);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", get_letter_receiver_data);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", doit_letter_manager);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", init_letter_manager);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", send_letter);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002D480);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", create_letter_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", check_free_letter_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", discard_all_letter_in_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", get_total_letter_in_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", open_letter_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", get_next_letter_in_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", close_letter_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002D638);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", push_back_letter_in_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", discard_selecting_letter_in_post);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", constructor_letter_type);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", entry_new_letter_type);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", init_letter_type_store);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", get_letter_type);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002D888);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosConvertStringSJIStoEUC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosConvertStringEUCtoSJIS);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosConvertStringEUCtoID);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetDataSizeOfFont);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetFontDataWithID);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetFontDataWithJIS);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetFontDataWithSJIS);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetFontDataWithEUC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetFontIDWithJIS);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetFontIDWithSJIS);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetFontIDWithEUC);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosEntryLocaleFontNoLoad);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetFontInfo);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGet2ByteCharCode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", _isysCreateSubMsgQueue);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", _isysRecvSubMsg);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", _isysSendSubMsg);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitSubThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysInitSubThreadExecEnv);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysStartSubThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDeleteSubThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDumpSubThreadStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysWakeupSubThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysSleepSubThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SubThreadTerminateRestorePoint);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetThisSubThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysInitSubThreadObj);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysCreateSubThreadS);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysSleepSubThreadM);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysJumpSubThread);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002F17C);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetSubThreadWorkSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetSubThreadStackUse);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysGetSubThreadStackSize);

void isysDumpSubThreadPC(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isysDebugSetSubThreadSleepProtection);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4002F2A8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepReq);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepPlayerSrh);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepPlayerSrh2);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepStopReq);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepSetVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepSetPan);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepSetDefaultParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepPauseAll);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepPause);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepCont);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepStopTypeAll);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepInitTickParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndSepInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndVabCreate);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndVabDelete);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndVabHDOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndVabHDClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndBDOpen);

void sndBDClose(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sndVabInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", initSound);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", tickProcSound);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", addAdpcmTickProcFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", setPcmTickProcFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", soundGetTickProcCnt);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", soundSetRevMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", soundGetRevMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", getSlotInfo);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", setSoundMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosAllocIopHeap);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosFreeIopHeap);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosLoadIopModule);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetIopTotalFreeMemSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosGetIopTotalMemSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosWaitIopSema);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosSignalIopSema);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitIopDev);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400303A8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosKeybdInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosKeybdSetCallBackFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40030620);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosKeybdGetInfo);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400306A8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMouseInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", iosMouseSetCallBackFunc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40030970);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", GetStrHashWorkBuffer);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", InitStrHash);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", AddStrHashKey);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", MakeStrHashValue);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", SearchStrHashKey);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", ReleaseStrHashKeyAll);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", DeleteStrHashKey);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ChipSetDigitalOutputMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ChipInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ChipInitHot);

void func_40030D00(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlEntryTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlEntryTickProcById);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlRemoveTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlSetTickMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlGetTickMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlSetTickTime);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlGetTickTime);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2CtrlInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DmaTransVoice);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DmaTransStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DmaInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspEffectSetEndAdr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspEffectSetType);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspEffectSetDepth);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspEffectSetDepth2);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspEffectSetDelay);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspEffectSetFeedBack);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspEffectChange);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspEffectSetSwitch);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspSetMasterVolume);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspSetMasterVolumeMax);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspGetMasterVolume);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2DspInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmStopMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmQuit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmSlotMalloc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmSlotReserv);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmSlotFree);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmWorkClear);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40031728);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmOpenFake);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmSetFd);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmGetFd);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmSetLsn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmGetLsn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmGetTargetLsn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmSetUserParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmGetUserParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40031C08);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmVolumePercent);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmTrkVolumeDirect);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmTrkVolumePercent);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmTrkDspSw);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", ____VolReflection);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", ____VolPerBackup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmPitchPercent);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmPlay);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmPause);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmCont);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmStop);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmIopReadAdr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmSetOutputMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmLoopSecNum);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmGetBuffer);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmSetSignal);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40032420);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400324D0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40032608);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400327D0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmPreLoad);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExStAdpcmTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40032AC0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40032C10);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", all_keyoff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", all_soundoff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", all_soundpause);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", all_soundmute);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModMidiout1);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModMidiout1Exclusive);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModMidiout);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModOpenBgm);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModOpenSe);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModCheckSndOn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModSetParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModGetParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModSetOutputMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ModInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", debug_mod_config);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40034800);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40034838);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035408);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035A50);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035A88);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035B28);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035BC8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035C68);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035D10);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035D80);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035F80);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035FB8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40035FF0);

void func_40036028(void) {
}

void func_40036030(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036038);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400360C0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400360F8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036148);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400361A0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400361F8);

void func_40036250(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036258);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036290);

void func_40036330(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036338);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036370);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400363A8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036450);

void func_400364E8(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400364F0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036528);

void func_400365B0(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400365B8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036660);

void func_40036BE0(void) {
}

void func_40036BE8(void) {
}

void func_40036BF0(void) {
}

void func_40036BF8(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40036C00);

void func_40036CE0(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteSend);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteSendDmaCom);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteDmaTransStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteGetAdpStmAdr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteGetPcmStmTransOffset);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteGetSlotReleaseLv);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteGetDspChangeStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteSyncStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2RemoteInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40037188);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepPlay);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepPlaySelectCore);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepStop);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepStopSndOff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepPause);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepCont);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepVabStopSndOff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepAllStopSndOff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepCheckSndOn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepSetParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepMidiOut);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepMasterVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SepInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", debug_sep_config);

void func_40038100(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40038108);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400381B8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40038720);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotGetSlotClassIdx);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFreeSearch);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFreeSearchTerm);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSearchPriority);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSearchPriorityOlder);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSearchParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSearchParamOlder0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSearchParamOlder1);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSearchTypeOlder);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotBlock);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFree);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotCheckSlotClass);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindLoop);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindVab);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindVabCh);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindVabChNote);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindVabChSsaBaseNote);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindSlotClass);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindSlotClassCh);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindSlotClassChNote);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotFindSlotClassChSsaBaseNote);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetBasicParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetSsa);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetGroup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetMute);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetMasVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetSeMasVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetBaseVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetMasPan);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetBasePan);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetPan);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetBendRange);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetBendValue);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetPitch);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetPause);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetDirectPitch);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetMasTune);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetAdsr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetVolPhase);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetLoop);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetDumperOn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetLfoPitchTbl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetLfoPitchSpeed);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetLfoPitchDepth);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetLfoVolTbl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetLfoVolSpeed);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetLfoVolDepth);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetTimeVolParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetTimePitchParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetTimePanParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetPoltamentParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotGetVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotGetPan);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetDumperOff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotModKeyOff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotVabKeyOff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotVabKeyOffGroup);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetKeyOnBit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetKeyOffBit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetReverbOnBit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetReverbOffBit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetNoiseOnBit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetNoiseOffBit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetOutputMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotSetVolShiftDownParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotGetVolShiftDownParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotTbl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SlotEnvTbl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003CE68);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003CF28);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpOpenSelCore);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpVabStopSndOff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpPlay);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpStop);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpStopSndOff);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpPause);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpCont);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpCheckSndOn);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpSetParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpGetParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpMidiOut);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpSetSignal);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2SmfpInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", debug_smfp_mod_config);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", debug_set_smfp_time_count_delta_per);

void func_4003E2A0(void) {
}

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003E2A8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003E338);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003E4C8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003E548);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmSetVolume);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmSetPitch);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmPlay);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmStop);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmIopReadAdr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StAdpcmQuit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", get_vabid);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003EBE0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003ED58);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_check_alive);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_get_info);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_get_seseq);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_get_seprogchunk);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_get_progchunk);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_get_splitchunk);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_get_veltbl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_get_lfotbl_param);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_set_semastervol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", vab_get_semastervol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2VabHdOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2VabGetBdSize);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2VabBdOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2VabClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2VabHdClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2VabInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F3C8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F3E8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F468);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F528);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F5D0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F6A0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F788);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F7E8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F8F0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003F928);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003FAD0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003FBD8);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003FC78);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003FD60);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_4003FF10);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400400A0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_400400F0);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40040118);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40040350);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40040398);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputOpenDoubleBuffer);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputCtrl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputGetLipFrame);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputGetRealPlayFrameCount);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40040710);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputSetVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputSetPan);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputSetPhase);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputSetOutputMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputAutoFilterInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputSetAutoFilterDirect);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputSetAutoFilter);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInputAutoFilterCtrl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputOpen);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputClose);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputBufferClear);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputSetVol);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputSetEffect);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputSetOutputMode);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputCtrl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputGetLipFrame);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputAutoFilterInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputSetAutoFilterDirect);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputSetAutoFilter);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmOutputAutoFilterCtrl);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmCheckAutoFilterSeq);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmTickProc);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmSetSignal);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2ExPcmInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40041048);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40041148);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40041248);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40041370);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40041538);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", IirInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", IirParam);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", IirFilter);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StPcmStart);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StPcmStop);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StPcmSetVolume);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StPcmSetEffect);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StPcmIopTransOffset);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StPcmInit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", Sg2StPcmQuit);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", func_40041A98);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", mktime);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", strstr);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", div);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", atanf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", cosf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", fabsf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sinf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sqrt);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", acosf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", asinf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", atan2f);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", fmodf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", powf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sqrtf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __ieee754_sqrt);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __ieee754_acosf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __ieee754_asinf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __ieee754_atan2f);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __ieee754_fmodf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __ieee754_powf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __ieee754_rem_pio2f);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __ieee754_sqrtf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __kernel_cosf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __kernel_rem_pio2f);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", __kernel_sinf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", floorf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", scalbnf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", copysignf);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sceGsPutIMR);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sceGsGetIMR);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", isceGsPutIMR);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sceCdRead);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sceCdReadIOPm);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sceCdGetError);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sceCdStatus);

INCLUDE_ASM("asm/kernel/nonmatchings/21A0", sceCdReadClock);
