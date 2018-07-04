#ifndef _LEDCONTROLLER_H
#define _LEDCONTROLLER_H

#include "Led.h"
#include "Button.h"

typedef struct  LedButtonInfo LedButtonInfo;
struct LedButtonInfo {
  LedState currentLedState;
  ButtonState previousButtonState;
  //LedState previousledState;
};

void turnOnledIfButtonIsPressed(void);
//void checkButtonAndDoLedForever();
void doTapTurnOnTapTurnOffLed1(LedState *ledState);
void doTapTurnOnTapTurnOffLed(LedButtonInfo *State);
void doTurnOnLedOnButtonPressedAndHoldController();
void doTapTapLedController();
void doTapTurnOnTapTurnOffLed_1(LedButtonInfo *State);

#endif // _LEDCONTROLLER_H
