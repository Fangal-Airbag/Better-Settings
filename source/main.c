#include <wups.h>
#include <wups/config/WUPSConfigItemBoolean.h>

#include <whb/log.h>
#include <whb/log_udp.h>
#include <sysapp/title.h>
#include <sysapp/launch.h>
#include <coreinit/title.h>
#include <gx2/surface.h>
#include <vpad/input.h>
#include <padscore/kpad.h>

#include "buttons.h"

WUPS_PLUGIN_NAME("Better Settings");
WUPS_PLUGIN_DESCRIPTION("An aroma plugin that improves the System Settings user experience!");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("Fangal");
WUPS_PLUGIN_LICENSE("GPLv3");

#define MIRROR_SCREENS_CONFIG_ID "mirrorScreens"
#define INPUT_REDIRECTION_CONFIG_ID "inputRedirection"

WUPS_USE_STORAGE("Better_Settings");

bool mirrorScreens = true;
bool inputRedirection = true;
bool isConfigOpen = false;

uint64_t sysTID;

INITIALIZE_PLUGIN() {
    WHBLogUdpInit();
    WHBLogPrintf("Hola from Better Settings!");

    sysTID = _SYSGetSystemApplicationTitleId(SYSTEM_APP_ID_SYSTEM_SETTINGS);

    WUPS_OpenStorage();
    WUPS_GetBool(NULL, MIRROR_SCREENS_CONFIG_ID, &mirrorScreens);
    WUPS_StoreBool(NULL, MIRROR_SCREENS_CONFIG_ID, mirrorScreens);
    WUPS_GetBool(NULL, INPUT_REDIRECTION_CONFIG_ID, &inputRedirection);
    WUPS_StoreBool(NULL, INPUT_REDIRECTION_CONFIG_ID, inputRedirection);
    WUPS_CloseStorage();
}

void mirrorScreensChanged(ConfigItemBoolean *item, bool newVal) {
    mirrorScreens = newVal;
    WUPS_StoreBool(NULL, MIRROR_SCREENS_CONFIG_ID, mirrorScreens);
}

void inputRedirectionChanged(ConfigItemBoolean *item, bool newVal) {
    inputRedirection = newVal;
    WUPS_StoreBool(NULL, INPUT_REDIRECTION_CONFIG_ID, inputRedirection);
}

WUPS_GET_CONFIG() {
    WUPS_OpenStorage();

    isConfigOpen = true;

    WUPSConfigHandle config;
    WUPSConfig_CreateHandled(&config, "Better Settings");

    WUPSConfigCategoryHandle cat;
    WUPSConfig_AddCategoryByNameHandled(config, "Options", &cat);

    WUPSConfigItemBoolean_AddToCategoryHandled(config, cat, MIRROR_SCREENS_CONFIG_ID, "Mirror Gamepad screen to the TV", mirrorScreens, &mirrorScreensChanged);
    WUPSConfigItemBoolean_AddToCategoryHandled(config, cat, INPUT_REDIRECTION_CONFIG_ID, "Redirect inputs", inputRedirection, &inputRedirectionChanged);

    return config;
}

WUPS_CONFIG_CLOSED() {
    WUPS_CloseStorage();

    isConfigOpen = false;
}

DECL_FUNCTION(void, GX2CopyColorBufferToScanBuffer, GX2ColorBuffer *colorBuffer, GX2ScanTarget scan_target) {
    if (OSGetTitleID() == sysTID) {
        if (mirrorScreens) {
            if(scan_target == GX2_SCAN_TARGET_DRC) {
               real_GX2CopyColorBufferToScanBuffer(colorBuffer, GX2_SCAN_TARGET_DRC | GX2_SCAN_TARGET_TV);
            }
        }
        else {
            real_GX2CopyColorBufferToScanBuffer(colorBuffer, scan_target);
        }
    }
    else {
        real_GX2CopyColorBufferToScanBuffer(colorBuffer, scan_target);
    }        
}

DECL_FUNCTION(int32_t, VPADRead, VPADChan chan, VPADStatus *vStatus, uint32_t size, VPADReadError *err) {
    int32_t res = real_VPADRead(chan, vStatus, size, err);

    if (!isConfigOpen) {
        if (inputRedirection) {
            calcVPAD(vStatus);
        }
    }

    return res;
}

DECL_FUNCTION(int32_t, KPADReadEx, KPADChan chan, KPADStatus *kStatus, uint32_t size, KPADError *err) {
    int32_t res = real_KPADReadEx(chan, kStatus, size, err);
    
    if (OSGetTitleID() == sysTID) {
        calcKPAD(kStatus);
    }

    return res;
}

WUPS_MUST_REPLACE(GX2CopyColorBufferToScanBuffer, WUPS_LOADER_LIBRARY_GX2, GX2CopyColorBufferToScanBuffer);
WUPS_MUST_REPLACE(KPADReadEx, WUPS_LOADER_LIBRARY_PADSCORE, KPADReadEx);
WUPS_MUST_REPLACE(VPADRead, WUPS_LOADER_LIBRARY_VPAD, VPADRead);
