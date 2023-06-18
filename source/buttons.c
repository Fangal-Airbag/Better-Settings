#include "buttons.h"
#include <stdbool.h>

const uint32_t BUTTON_A = WPAD_CLASSIC_BUTTON_A | WPAD_PRO_BUTTON_A;
const uint32_t BUTTON_B = WPAD_CLASSIC_BUTTON_B | WPAD_PRO_BUTTON_B;
const uint32_t BUTTON_X = WPAD_CLASSIC_BUTTON_X | WPAD_PRO_BUTTON_X;
const uint32_t BUTTON_Y = WPAD_CLASSIC_BUTTON_Y | WPAD_PRO_BUTTON_Y;
const uint32_t BUTTON_R = WPAD_CLASSIC_BUTTON_R | WPAD_PRO_TRIGGER_R;
const uint32_t BUTTON_L = WPAD_CLASSIC_BUTTON_L | WPAD_PRO_TRIGGER_L;
const uint32_t BUTTON_ZR = WPAD_CLASSIC_BUTTON_ZR | WPAD_PRO_TRIGGER_ZR;
const uint32_t BUTTON_ZL = WPAD_CLASSIC_BUTTON_ZL | WPAD_PRO_TRIGGER_ZL;
const uint32_t BUTTON_UP = WPAD_CLASSIC_BUTTON_UP | WPAD_CLASSIC_STICK_L_EMULATION_UP | WPAD_PRO_BUTTON_UP | WPAD_PRO_STICK_L_EMULATION_UP;
const uint32_t BUTTON_DOWN = WPAD_CLASSIC_BUTTON_DOWN | WPAD_CLASSIC_STICK_L_EMULATION_DOWN | WPAD_PRO_BUTTON_DOWN | WPAD_PRO_STICK_L_EMULATION_DOWN;
const uint32_t BUTTON_RIGHT = WPAD_CLASSIC_BUTTON_RIGHT | WPAD_CLASSIC_STICK_L_EMULATION_RIGHT | WPAD_PRO_BUTTON_RIGHT | WPAD_PRO_STICK_L_EMULATION_RIGHT;
const uint32_t BUTTON_LEFT = WPAD_CLASSIC_BUTTON_LEFT | WPAD_CLASSIC_STICK_L_EMULATION_LEFT | WPAD_PRO_BUTTON_LEFT | WPAD_PRO_STICK_L_EMULATION_LEFT;

bool aIsPressed = false;
bool aIsHeld = false;
bool bIsPressed = false;
bool bIsHeld = false;
bool xIsPressed = false;
bool xIsHeld = false;
bool yIsPressed = false;
bool yIsHeld = false;
bool rIsPressed = false;
bool rIsHeld = false;
bool lIsPressed = false;
bool lIsHeld = false;
bool zrIsPressed = false;
bool zrIsHeld = false;
bool zlIsPressed = false;
bool zlIsHeld = false;
bool upIsPressed = false;
bool upIsHeld = false;
bool downIsPressed = false;
bool downIsHeld = false;
bool leftIsPressed = false;
bool leftIsHeld = false;
bool rightIsPressed = false;
bool rightIsHeld = false;

float x, y;

uint32_t buttonPressed(KPADStatus kStatus) {
    return kStatus.classic.trigger | kStatus.pro.trigger;
}

uint32_t buttonHeld(KPADStatus kStatus) {
    return kStatus.classic.hold | kStatus.pro.hold;
}

uint32_t buttonReleased(KPADStatus kStatus) {
    return kStatus.classic.release | kStatus.pro.release;
}

void calcVPAD(VPADStatus *vStatus) {
    if (aIsPressed) vStatus->trigger |= VPAD_BUTTON_A;
    if (aIsHeld) vStatus->hold |= VPAD_BUTTON_A;
    if (bIsPressed) vStatus->trigger |= VPAD_BUTTON_B;
    if (bIsHeld) vStatus->hold |= VPAD_BUTTON_B;
    if (xIsPressed) vStatus->trigger |= VPAD_BUTTON_X;
    if (xIsHeld) vStatus->hold |= VPAD_BUTTON_X;
    if (yIsPressed) vStatus->trigger |= VPAD_BUTTON_Y;
    if (yIsHeld) vStatus->hold |= VPAD_BUTTON_Y;
    if (rIsPressed) vStatus->trigger |= VPAD_BUTTON_R;
    if (rIsHeld) vStatus->hold |= VPAD_BUTTON_R;
    if (lIsPressed) vStatus->trigger |= VPAD_BUTTON_L;
    if (lIsHeld) vStatus->hold |= VPAD_BUTTON_L;
    if (zrIsPressed) vStatus->trigger |= VPAD_BUTTON_ZR;
    if (zrIsHeld) vStatus->hold |= VPAD_BUTTON_ZR;
    if (zlIsPressed) vStatus->trigger |= VPAD_BUTTON_ZL;
    if (zlIsHeld) vStatus->hold |= VPAD_BUTTON_ZL;
    if (upIsPressed) vStatus->trigger |= VPAD_BUTTON_UP;
    if (upIsHeld) vStatus->hold |= VPAD_BUTTON_UP;
    if (downIsPressed) vStatus->trigger |= VPAD_BUTTON_DOWN;
    if (downIsHeld) vStatus->hold |= VPAD_BUTTON_DOWN;
    if (leftIsPressed) vStatus->trigger |= VPAD_BUTTON_LEFT;
    if (leftIsHeld) vStatus->hold |= VPAD_BUTTON_LEFT;
    if (rightIsPressed) vStatus->trigger |= VPAD_BUTTON_RIGHT;
    if (rightIsHeld) vStatus->hold |= VPAD_BUTTON_RIGHT;
}

void calcKPAD(KPADStatus *kStatus) {
    if (buttonPressed(*kStatus) & BUTTON_A) aIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_A) aIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_A) {
        aIsPressed = false;
        aIsHeld = false;
    }

    if (buttonPressed(*kStatus) & BUTTON_B) bIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_B) bIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_B) {
        bIsPressed = false;
        bIsHeld = false;
    }

    if (buttonPressed(*kStatus) & BUTTON_X) xIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_X) xIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_X) {
        xIsPressed = false;
        xIsHeld = false;
    }
    
    if (buttonPressed(*kStatus) & BUTTON_Y) yIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_Y) yIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_Y) {
        yIsPressed = false;
        yIsHeld = false;
    }
    
    if (buttonPressed(*kStatus) & BUTTON_R) rIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_R) rIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_R) {
        rIsPressed = false;
        rIsHeld = false;
    }

    if (buttonPressed(*kStatus) & BUTTON_L) lIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_L) lIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_L) {
        lIsPressed = false;
        lIsHeld = false;
    }

    if (buttonPressed(*kStatus) & BUTTON_ZR) zrIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_ZR) zrIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_ZR) {
        zrIsPressed = false;
        zrIsHeld = false;
    }

    if (buttonPressed(*kStatus) & BUTTON_ZL) zlIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_ZL) zlIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_ZL) {
        zlIsPressed = false;
        zlIsHeld = false;
    }
    
    if (buttonPressed(*kStatus) & BUTTON_UP) upIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_UP) upIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_UP) {
        upIsPressed = false;
        upIsHeld = false;
    }
    
    if (buttonPressed(*kStatus) & BUTTON_DOWN) downIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_DOWN) downIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_DOWN) {
        downIsPressed = false;
        downIsHeld = false;
    }
    
    if (buttonPressed(*kStatus) & BUTTON_LEFT) leftIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_LEFT) leftIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_LEFT) {
        leftIsPressed = false;
        leftIsHeld = false;
    }

    if (buttonPressed(*kStatus) & BUTTON_RIGHT) rightIsPressed = true;
    if (buttonHeld(*kStatus) & BUTTON_RIGHT) rightIsHeld = true;
    if (buttonReleased(*kStatus) & BUTTON_RIGHT) {
        rightIsPressed = false;
        rightIsHeld = false;
    }
}