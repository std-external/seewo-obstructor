// Dll Hijacking
// This file is generated by blook
// Neither touch/modify nor include this file in your project!

#include "Windows.h"

// blook: USE_STATIC_INITIALIZATION_TO_INIT_EXPORTS
void (*blookHijackFuncs[82])() = {};
const char* blookHijackFuncNames[] = {
 "DllCanUnloadNow",
 "DllGetClassObject",
 "Private1",
 "SvchostPushServiceGlobals",
 "WinHttpAddRequestHeaders",
 "WinHttpAddRequestHeadersEx",
 "WinHttpAutoProxySvcMain",
 "WinHttpCheckPlatform",
 "WinHttpCloseHandle",
 "WinHttpConnect",
 "WinHttpConnectionDeletePolicyEntries",
 "WinHttpConnectionDeleteProxyInfo",
 "WinHttpConnectionFreeNameList",
 "WinHttpConnectionFreeProxyInfo",
 "WinHttpConnectionFreeProxyList",
 "WinHttpConnectionGetNameList",
 "WinHttpConnectionGetProxyInfo",
 "WinHttpConnectionGetProxyList",
 "WinHttpConnectionOnlyConvert",
 "WinHttpConnectionOnlyReceive",
 "WinHttpConnectionOnlySend",
 "WinHttpConnectionSetPolicyEntries",
 "WinHttpConnectionSetProxyInfo",
 "WinHttpConnectionUpdateIfIndexTable",
 "WinHttpCrackUrl",
 "WinHttpCreateProxyResolver",
 "WinHttpCreateUrl",
 "WinHttpDetectAutoProxyConfigUrl",
 "WinHttpFreeProxyResult",
 "WinHttpFreeProxyResultEx",
 "WinHttpFreeProxySettings",
 "WinHttpFreeProxySettingsEx",
 "WinHttpFreeQueryConnectionGroupResult",
 "WinHttpGetDefaultProxyConfiguration",
 "WinHttpGetIEProxyConfigForCurrentUser",
 "WinHttpGetProxyForUrl",
 "WinHttpGetProxyForUrlEx",
 "WinHttpGetProxyForUrlEx2",
 "WinHttpGetProxyForUrlHvsi",
 "WinHttpGetProxyResult",
 "WinHttpGetProxyResultEx",
 "WinHttpGetProxySettingsEx",
 "WinHttpGetProxySettingsResultEx",
 "WinHttpGetProxySettingsVersion",
 "WinHttpGetTunnelSocket",
 "WinHttpOpen",
 "WinHttpOpenRequest",
 "WinHttpPacJsWorkerMain",
 "WinHttpProbeConnectivity",
 "WinHttpQueryAuthSchemes",
 "WinHttpQueryConnectionGroup",
 "WinHttpQueryDataAvailable",
 "WinHttpQueryHeaders",
 "WinHttpQueryHeadersEx",
 "WinHttpQueryOption",
 "WinHttpReadData",
 "WinHttpReadDataEx",
 "WinHttpReadProxySettings",
 "WinHttpReadProxySettingsHvsi",
 "WinHttpReceiveResponse",
 "WinHttpRegisterProxyChangeNotification",
 "WinHttpResetAutoProxy",
 "WinHttpSaveProxyCredentials",
 "WinHttpSendRequest",
 "WinHttpSetCredentials",
 "WinHttpSetDefaultProxyConfiguration",
 "WinHttpSetOption",
 "WinHttpSetProxySettingsPerUser",
 "WinHttpSetSecureLegacyServersAppCompat",
 "WinHttpSetStatusCallback",
 "WinHttpSetTimeouts",
 "WinHttpTimeFromSystemTime",
 "WinHttpTimeToSystemTime",
 "WinHttpUnregisterProxyChangeNotification",
 "WinHttpWebSocketClose",
 "WinHttpWebSocketCompleteUpgrade",
 "WinHttpWebSocketQueryCloseStatus",
 "WinHttpWebSocketReceive",
 "WinHttpWebSocketSend",
 "WinHttpWebSocketShutdown",
 "WinHttpWriteData",
 "WinHttpWriteProxySettings",
};

int blookInit = ([] {
    char system_dir_path[MAX_PATH];
    GetSystemDirectoryA(system_dir_path, MAX_PATH);
    strcat_s(system_dir_path, "\\winhttp.dll");
    HMODULE lib = LoadLibraryA(system_dir_path);

    if (!lib) {
        MessageBoxA(NULL, "Failed to load winhttp.dll", "Error", MB_ICONERROR);
        return 1;
    }

    for (int i = 0; i < sizeof(blookHijackFuncs) / sizeof(blookHijackFuncs[0]); i++) {
        blookHijackFuncs[i] = (void (*)()) GetProcAddress(lib, blookHijackFuncNames[i]);
    }

    return 0;
})();

// blook: GENERATED_PLACEHOLDER_FUNCTION_EXPORTS
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_BLOOK_PLACEHOLDER_1")
extern "C" void BLOOK_PLACEHOLDER_1() { return (blookHijackFuncs[0])(); }

#pragma comment(linker, "/EXPORT:DllGetClassObject=_BLOOK_PLACEHOLDER_2")
extern "C" void BLOOK_PLACEHOLDER_2() { return (blookHijackFuncs[1])(); }

#pragma comment(linker, "/EXPORT:Private1=_BLOOK_PLACEHOLDER_3")
extern "C" void BLOOK_PLACEHOLDER_3() { return (blookHijackFuncs[2])(); }

#pragma comment(linker, "/EXPORT:SvchostPushServiceGlobals=_BLOOK_PLACEHOLDER_4")
extern "C" void BLOOK_PLACEHOLDER_4() { return (blookHijackFuncs[3])(); }

#pragma comment(linker, "/EXPORT:WinHttpAddRequestHeaders=_BLOOK_PLACEHOLDER_5")
extern "C" void BLOOK_PLACEHOLDER_5() { return (blookHijackFuncs[4])(); }

#pragma comment(linker, "/EXPORT:WinHttpAddRequestHeadersEx=_BLOOK_PLACEHOLDER_6")
extern "C" void BLOOK_PLACEHOLDER_6() { return (blookHijackFuncs[5])(); }

#pragma comment(linker, "/EXPORT:WinHttpAutoProxySvcMain=_BLOOK_PLACEHOLDER_7")
extern "C" void BLOOK_PLACEHOLDER_7() { return (blookHijackFuncs[6])(); }

#pragma comment(linker, "/EXPORT:WinHttpCheckPlatform=_BLOOK_PLACEHOLDER_8")
extern "C" void BLOOK_PLACEHOLDER_8() { return (blookHijackFuncs[7])(); }

#pragma comment(linker, "/EXPORT:WinHttpCloseHandle=_BLOOK_PLACEHOLDER_9")
extern "C" void BLOOK_PLACEHOLDER_9() { return (blookHijackFuncs[8])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnect=_BLOOK_PLACEHOLDER_10")
extern "C" void BLOOK_PLACEHOLDER_10() { return (blookHijackFuncs[9])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionDeletePolicyEntries=_BLOOK_PLACEHOLDER_11")
extern "C" void BLOOK_PLACEHOLDER_11() { return (blookHijackFuncs[10])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionDeleteProxyInfo=_BLOOK_PLACEHOLDER_12")
extern "C" void BLOOK_PLACEHOLDER_12() { return (blookHijackFuncs[11])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionFreeNameList=_BLOOK_PLACEHOLDER_13")
extern "C" void BLOOK_PLACEHOLDER_13() { return (blookHijackFuncs[12])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionFreeProxyInfo=_BLOOK_PLACEHOLDER_14")
extern "C" void BLOOK_PLACEHOLDER_14() { return (blookHijackFuncs[13])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionFreeProxyList=_BLOOK_PLACEHOLDER_15")
extern "C" void BLOOK_PLACEHOLDER_15() { return (blookHijackFuncs[14])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionGetNameList=_BLOOK_PLACEHOLDER_16")
extern "C" void BLOOK_PLACEHOLDER_16() { return (blookHijackFuncs[15])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionGetProxyInfo=_BLOOK_PLACEHOLDER_17")
extern "C" void BLOOK_PLACEHOLDER_17() { return (blookHijackFuncs[16])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionGetProxyList=_BLOOK_PLACEHOLDER_18")
extern "C" void BLOOK_PLACEHOLDER_18() { return (blookHijackFuncs[17])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionOnlyConvert=_BLOOK_PLACEHOLDER_19")
extern "C" void BLOOK_PLACEHOLDER_19() { return (blookHijackFuncs[18])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionOnlyReceive=_BLOOK_PLACEHOLDER_20")
extern "C" void BLOOK_PLACEHOLDER_20() { return (blookHijackFuncs[19])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionOnlySend=_BLOOK_PLACEHOLDER_21")
extern "C" void BLOOK_PLACEHOLDER_21() { return (blookHijackFuncs[20])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionSetPolicyEntries=_BLOOK_PLACEHOLDER_22")
extern "C" void BLOOK_PLACEHOLDER_22() { return (blookHijackFuncs[21])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionSetProxyInfo=_BLOOK_PLACEHOLDER_23")
extern "C" void BLOOK_PLACEHOLDER_23() { return (blookHijackFuncs[22])(); }

#pragma comment(linker, "/EXPORT:WinHttpConnectionUpdateIfIndexTable=_BLOOK_PLACEHOLDER_24")
extern "C" void BLOOK_PLACEHOLDER_24() { return (blookHijackFuncs[23])(); }

#pragma comment(linker, "/EXPORT:WinHttpCrackUrl=_BLOOK_PLACEHOLDER_25")
extern "C" void BLOOK_PLACEHOLDER_25() { return (blookHijackFuncs[24])(); }

#pragma comment(linker, "/EXPORT:WinHttpCreateProxyResolver=_BLOOK_PLACEHOLDER_26")
extern "C" void BLOOK_PLACEHOLDER_26() { return (blookHijackFuncs[25])(); }

#pragma comment(linker, "/EXPORT:WinHttpCreateUrl=_BLOOK_PLACEHOLDER_27")
extern "C" void BLOOK_PLACEHOLDER_27() { return (blookHijackFuncs[26])(); }

#pragma comment(linker, "/EXPORT:WinHttpDetectAutoProxyConfigUrl=_BLOOK_PLACEHOLDER_28")
extern "C" void BLOOK_PLACEHOLDER_28() { return (blookHijackFuncs[27])(); }

#pragma comment(linker, "/EXPORT:WinHttpFreeProxyResult=_BLOOK_PLACEHOLDER_29")
extern "C" void BLOOK_PLACEHOLDER_29() { return (blookHijackFuncs[28])(); }

#pragma comment(linker, "/EXPORT:WinHttpFreeProxyResultEx=_BLOOK_PLACEHOLDER_30")
extern "C" void BLOOK_PLACEHOLDER_30() { return (blookHijackFuncs[29])(); }

#pragma comment(linker, "/EXPORT:WinHttpFreeProxySettings=_BLOOK_PLACEHOLDER_31")
extern "C" void BLOOK_PLACEHOLDER_31() { return (blookHijackFuncs[30])(); }

#pragma comment(linker, "/EXPORT:WinHttpFreeProxySettingsEx=_BLOOK_PLACEHOLDER_32")
extern "C" void BLOOK_PLACEHOLDER_32() { return (blookHijackFuncs[31])(); }

#pragma comment(linker, "/EXPORT:WinHttpFreeQueryConnectionGroupResult=_BLOOK_PLACEHOLDER_33")
extern "C" void BLOOK_PLACEHOLDER_33() { return (blookHijackFuncs[32])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetDefaultProxyConfiguration=_BLOOK_PLACEHOLDER_34")
extern "C" void BLOOK_PLACEHOLDER_34() { return (blookHijackFuncs[33])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetIEProxyConfigForCurrentUser=_BLOOK_PLACEHOLDER_35")
extern "C" void BLOOK_PLACEHOLDER_35() { return (blookHijackFuncs[34])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxyForUrl=_BLOOK_PLACEHOLDER_36")
extern "C" void BLOOK_PLACEHOLDER_36() { return (blookHijackFuncs[35])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxyForUrlEx=_BLOOK_PLACEHOLDER_37")
extern "C" void BLOOK_PLACEHOLDER_37() { return (blookHijackFuncs[36])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxyForUrlEx2=_BLOOK_PLACEHOLDER_38")
extern "C" void BLOOK_PLACEHOLDER_38() { return (blookHijackFuncs[37])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxyForUrlHvsi=_BLOOK_PLACEHOLDER_39")
extern "C" void BLOOK_PLACEHOLDER_39() { return (blookHijackFuncs[38])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxyResult=_BLOOK_PLACEHOLDER_40")
extern "C" void BLOOK_PLACEHOLDER_40() { return (blookHijackFuncs[39])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxyResultEx=_BLOOK_PLACEHOLDER_41")
extern "C" void BLOOK_PLACEHOLDER_41() { return (blookHijackFuncs[40])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxySettingsEx=_BLOOK_PLACEHOLDER_42")
extern "C" void BLOOK_PLACEHOLDER_42() { return (blookHijackFuncs[41])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxySettingsResultEx=_BLOOK_PLACEHOLDER_43")
extern "C" void BLOOK_PLACEHOLDER_43() { return (blookHijackFuncs[42])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetProxySettingsVersion=_BLOOK_PLACEHOLDER_44")
extern "C" void BLOOK_PLACEHOLDER_44() { return (blookHijackFuncs[43])(); }

#pragma comment(linker, "/EXPORT:WinHttpGetTunnelSocket=_BLOOK_PLACEHOLDER_45")
extern "C" void BLOOK_PLACEHOLDER_45() { return (blookHijackFuncs[44])(); }

#pragma comment(linker, "/EXPORT:WinHttpOpen=_BLOOK_PLACEHOLDER_46")
extern "C" void BLOOK_PLACEHOLDER_46() { return (blookHijackFuncs[45])(); }

#pragma comment(linker, "/EXPORT:WinHttpOpenRequest=_BLOOK_PLACEHOLDER_47")
extern "C" void BLOOK_PLACEHOLDER_47() { return (blookHijackFuncs[46])(); }

#pragma comment(linker, "/EXPORT:WinHttpPacJsWorkerMain=_BLOOK_PLACEHOLDER_48")
extern "C" void BLOOK_PLACEHOLDER_48() { return (blookHijackFuncs[47])(); }

#pragma comment(linker, "/EXPORT:WinHttpProbeConnectivity=_BLOOK_PLACEHOLDER_49")
extern "C" void BLOOK_PLACEHOLDER_49() { return (blookHijackFuncs[48])(); }

#pragma comment(linker, "/EXPORT:WinHttpQueryAuthSchemes=_BLOOK_PLACEHOLDER_50")
extern "C" void BLOOK_PLACEHOLDER_50() { return (blookHijackFuncs[49])(); }

#pragma comment(linker, "/EXPORT:WinHttpQueryConnectionGroup=_BLOOK_PLACEHOLDER_51")
extern "C" void BLOOK_PLACEHOLDER_51() { return (blookHijackFuncs[50])(); }

#pragma comment(linker, "/EXPORT:WinHttpQueryDataAvailable=_BLOOK_PLACEHOLDER_52")
extern "C" void BLOOK_PLACEHOLDER_52() { return (blookHijackFuncs[51])(); }

#pragma comment(linker, "/EXPORT:WinHttpQueryHeaders=_BLOOK_PLACEHOLDER_53")
extern "C" void BLOOK_PLACEHOLDER_53() { return (blookHijackFuncs[52])(); }

#pragma comment(linker, "/EXPORT:WinHttpQueryHeadersEx=_BLOOK_PLACEHOLDER_54")
extern "C" void BLOOK_PLACEHOLDER_54() { return (blookHijackFuncs[53])(); }

#pragma comment(linker, "/EXPORT:WinHttpQueryOption=_BLOOK_PLACEHOLDER_55")
extern "C" void BLOOK_PLACEHOLDER_55() { return (blookHijackFuncs[54])(); }

#pragma comment(linker, "/EXPORT:WinHttpReadData=_BLOOK_PLACEHOLDER_56")
extern "C" void BLOOK_PLACEHOLDER_56() { return (blookHijackFuncs[55])(); }

#pragma comment(linker, "/EXPORT:WinHttpReadDataEx=_BLOOK_PLACEHOLDER_57")
extern "C" void BLOOK_PLACEHOLDER_57() { return (blookHijackFuncs[56])(); }

#pragma comment(linker, "/EXPORT:WinHttpReadProxySettings=_BLOOK_PLACEHOLDER_58")
extern "C" void BLOOK_PLACEHOLDER_58() { return (blookHijackFuncs[57])(); }

#pragma comment(linker, "/EXPORT:WinHttpReadProxySettingsHvsi=_BLOOK_PLACEHOLDER_59")
extern "C" void BLOOK_PLACEHOLDER_59() { return (blookHijackFuncs[58])(); }

#pragma comment(linker, "/EXPORT:WinHttpReceiveResponse=_BLOOK_PLACEHOLDER_60")
extern "C" void BLOOK_PLACEHOLDER_60() { return (blookHijackFuncs[59])(); }

#pragma comment(linker, "/EXPORT:WinHttpRegisterProxyChangeNotification=_BLOOK_PLACEHOLDER_61")
extern "C" void BLOOK_PLACEHOLDER_61() { return (blookHijackFuncs[60])(); }

#pragma comment(linker, "/EXPORT:WinHttpResetAutoProxy=_BLOOK_PLACEHOLDER_62")
extern "C" void BLOOK_PLACEHOLDER_62() { return (blookHijackFuncs[61])(); }

#pragma comment(linker, "/EXPORT:WinHttpSaveProxyCredentials=_BLOOK_PLACEHOLDER_63")
extern "C" void BLOOK_PLACEHOLDER_63() { return (blookHijackFuncs[62])(); }

#pragma comment(linker, "/EXPORT:WinHttpSendRequest=_BLOOK_PLACEHOLDER_64")
extern "C" void BLOOK_PLACEHOLDER_64() { return (blookHijackFuncs[63])(); }

#pragma comment(linker, "/EXPORT:WinHttpSetCredentials=_BLOOK_PLACEHOLDER_65")
extern "C" void BLOOK_PLACEHOLDER_65() { return (blookHijackFuncs[64])(); }

#pragma comment(linker, "/EXPORT:WinHttpSetDefaultProxyConfiguration=_BLOOK_PLACEHOLDER_66")
extern "C" void BLOOK_PLACEHOLDER_66() { return (blookHijackFuncs[65])(); }

#pragma comment(linker, "/EXPORT:WinHttpSetOption=_BLOOK_PLACEHOLDER_67")
extern "C" void BLOOK_PLACEHOLDER_67() { return (blookHijackFuncs[66])(); }

#pragma comment(linker, "/EXPORT:WinHttpSetProxySettingsPerUser=_BLOOK_PLACEHOLDER_68")
extern "C" void BLOOK_PLACEHOLDER_68() { return (blookHijackFuncs[67])(); }

#pragma comment(linker, "/EXPORT:WinHttpSetSecureLegacyServersAppCompat=_BLOOK_PLACEHOLDER_69")
extern "C" void BLOOK_PLACEHOLDER_69() { return (blookHijackFuncs[68])(); }

#pragma comment(linker, "/EXPORT:WinHttpSetStatusCallback=_BLOOK_PLACEHOLDER_70")
extern "C" void BLOOK_PLACEHOLDER_70() { return (blookHijackFuncs[69])(); }

#pragma comment(linker, "/EXPORT:WinHttpSetTimeouts=_BLOOK_PLACEHOLDER_71")
extern "C" void BLOOK_PLACEHOLDER_71() { return (blookHijackFuncs[70])(); }

#pragma comment(linker, "/EXPORT:WinHttpTimeFromSystemTime=_BLOOK_PLACEHOLDER_72")
extern "C" void BLOOK_PLACEHOLDER_72() { return (blookHijackFuncs[71])(); }

#pragma comment(linker, "/EXPORT:WinHttpTimeToSystemTime=_BLOOK_PLACEHOLDER_73")
extern "C" void BLOOK_PLACEHOLDER_73() { return (blookHijackFuncs[72])(); }

#pragma comment(linker, "/EXPORT:WinHttpUnregisterProxyChangeNotification=_BLOOK_PLACEHOLDER_74")
extern "C" void BLOOK_PLACEHOLDER_74() { return (blookHijackFuncs[73])(); }

#pragma comment(linker, "/EXPORT:WinHttpWebSocketClose=_BLOOK_PLACEHOLDER_75")
extern "C" void BLOOK_PLACEHOLDER_75() { return (blookHijackFuncs[74])(); }

#pragma comment(linker, "/EXPORT:WinHttpWebSocketCompleteUpgrade=_BLOOK_PLACEHOLDER_76")
extern "C" void BLOOK_PLACEHOLDER_76() { return (blookHijackFuncs[75])(); }

#pragma comment(linker, "/EXPORT:WinHttpWebSocketQueryCloseStatus=_BLOOK_PLACEHOLDER_77")
extern "C" void BLOOK_PLACEHOLDER_77() { return (blookHijackFuncs[76])(); }

#pragma comment(linker, "/EXPORT:WinHttpWebSocketReceive=_BLOOK_PLACEHOLDER_78")
extern "C" void BLOOK_PLACEHOLDER_78() { return (blookHijackFuncs[77])(); }

#pragma comment(linker, "/EXPORT:WinHttpWebSocketSend=_BLOOK_PLACEHOLDER_79")
extern "C" void BLOOK_PLACEHOLDER_79() { return (blookHijackFuncs[78])(); }

#pragma comment(linker, "/EXPORT:WinHttpWebSocketShutdown=_BLOOK_PLACEHOLDER_80")
extern "C" void BLOOK_PLACEHOLDER_80() { return (blookHijackFuncs[79])(); }

#pragma comment(linker, "/EXPORT:WinHttpWriteData=_BLOOK_PLACEHOLDER_81")
extern "C" void BLOOK_PLACEHOLDER_81() { return (blookHijackFuncs[80])(); }

#pragma comment(linker, "/EXPORT:WinHttpWriteProxySettings=_BLOOK_PLACEHOLDER_82")
extern "C" void BLOOK_PLACEHOLDER_82() { return (blookHijackFuncs[81])(); }
