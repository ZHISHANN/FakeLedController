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

  if(State->currentLedState == LED_OFF && State->previousButtonState == BUTTON_RELEASED)
  {
    if(button == BUTTON_PRESSED){
      State->currentLedState = LED_ON;
      turnLed(LED_ON);
      State->previousButtonState = BUTTON_PRESSED;
    }
  }
  else if (State->currentLedState == LED_ON && State->previousButtonState == BUTTON_PRESSED)
  {
    if(getButtonState() == BUTTON_RELEASED){
      State->currentLedState = LED_OFF;
      turnLed(LED_OFF);
      State->previousButtonState = BUTTON_RELEASED;
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
