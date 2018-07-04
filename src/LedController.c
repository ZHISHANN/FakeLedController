#include "unity.h"
#include "LedController.h"
#include "mock_Button.h"
#include "mock_Led.h"

void turnOnledIfButtonIsPressed(void){

  if(getButtonState())
    turnLed(LED_ON);
  else
    turnLed(LED_OFF);
}

void doTapTurnOnTapTurnOffLed1(LedState *ledState)
{
    if(*ledState == LED_OFF)
      *ledState = LED_ON;
    else
      *ledState = LED_OFF;
}

void doTapTurnOnTapTurnOffLed(LedButtonInfo *State)
{
  ButtonState button;
  button = getButtonState();

  if(State->currentLedState == LED_OFF)
  {
    if(button == BUTTON_PRESSED && button != State->previousButtonState)
    {
      State->currentLedState = LED_ON;
      turnLed(LED_ON);
      State->previousButtonState = button;
    }
    else
      State->previousButtonState = button;
    }
  else
  {
    if(button == BUTTON_RELEASED && button != State->previousButtonState)
      State->previousButtonState = button;
    else
    {
      if(button == BUTTON_RELEASED && button != State->previousButtonState)
      {
        State->currentLedState = LED_OFF;
        turnLed(LED_OFF);
        State->previousButtonState = button;
      }
      else
        State->previousButtonState = button;
    }
  }
}


void doTurnOnLedOnButtonPressedAndHoldController(){
  while(1){
    turnOnledIfButtonIsPressed();
  }
}

void doTapTapLedController(){
  //LedState currentLedState;

  while(1){
    //turnOnledIfButtonIsPressed();
  }
}
