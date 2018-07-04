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

  if(State->currentLedState == LED_OFF)  //if led is off
  {
      if(State->previousButtonState == BUTTON_RELEASED)  //if previous button is released
      {
          if(button == BUTTON_PRESSED) //current button is pressed
          {
            State->currentLedState = LED_OFF;
            turnLed(LED_ON);
            State->previousButtonState = button;
          }
          else // current button is released
          {
            State->currentLedState = LED_OFF;
            State->previousButtonState = button;
          }
       }
      else  // if previous button is pressed
      {
          if(button == BUTTON_RELEASED) //current button is released
          {
            State->currentLedState = LED_ON;
            State->previousButtonState = button;
          }
      }
   }
   else // led is on
   {
      if(State->previousButtonState == BUTTON_RELEASED) //previous button is released
      {
          if(button == BUTTON_PRESSED) //current button is pressed
          {
            State->currentLedState = LED_ON;
            State->previousButtonState = button;
          }
          else  // current button is released
          {
            State->currentLedState = LED_ON;
            State->previousButtonState = button;
          }
      }
      else //previous button is pressed
      {
          if(button == BUTTON_RELEASED)  // current button is released
          {
            turnLed(LED_OFF);
            State->currentLedState = LED_OFF;
            State->previousButtonState = button;
          }
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
