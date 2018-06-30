#ifndef _LEDCONTROLLER_H
#define _LEDCONTROLLER_H

#include "Led.h"
#include "Button.h"

typedef struct  LedButtonInfo LedButtonInfo;
struct LedButtonInfo {
  LedState currentLedState;
  ButtonState previousButtonState;
};

void turnOnledIfButtonIsPressed(void);
//void checkButtonAndDoLedForever();
void doTapTurnOnTapTurnOffLed1(LedState *ledState);
void doTapTurnOnTapTurnOffLed(LedButtonInfo *State);
void doTurnOnLedOnButtonPressedAndHoldController();
void doTapTapLedController();

#endif // _LEDCONTROLLER_H
