#pragma once

#include <stdint.h>
#include <vpad/input.h>
#include <padscore/kpad.h>

uint32_t buttonPressed(KPADStatus kStatus);
uint32_t buttonHeld(KPADStatus kStatus);
uint32_t buttonReleased(KPADStatus kStatus);

void calcVPAD(VPADStatus *vStatus);
void calcKPAD(KPADStatus *kStatus);