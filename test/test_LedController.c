#include "unity.h"
#include <stdarg.h>
#include <malloc.h>
#include "LedController.h"
#include "mock_Button.h"
#include "mock_Led.h"

int turnLedCallNumbers = 0;
int expectedGetButtonStateMaxCalls = 0;
int expectedTurnLedMaxCalls = 0;
ButtonState *expectedButtonStates = NULL;
LedState *expectedLedStates = NULL;

void setUp(void){}

void tearDown(void){}

void *createMsg(char *format, ...){
	va_list valist;
	int neededSize;
	char *buffer;

	va_start(valist,format);
	neededSize = vsnprintf(NULL,0,format,valist) + 1;
	buffer = malloc(neededSize);
	vsnprintf(buffer,neededSize,format,valist);
	va_end(valist);

	return buffer;
}

void freeMsg(char *msg)
{
	if(msg)
	{
		free(msg);
	}
}

char *getLedStateName(LedState state)
{
	switch(state){
		case LED_ON:
			return "LED_ON";
		case LED_OFF:
			return "LED_OFF";
		default:
			return "(unknown LED state)";
	}
}

void fake_turnLed(LedState state, int NumCalls)
{
	turnLedCallNumbers++;
	char *msg;

	if(NumCalls < expectedTurnLedMaxCalls){
		LedState expectedState = expectedLedStates[NumCalls];
		if(state !=  expectedState)
		{
			msg = createMsg("turnLed() was called with %s, but expect %s",
								      getLedStateName(state), getLedStateName(expectedState));
			TEST_FAIL_MESSAGE(msg);
		}
	}
	else{
		msg = createMsg("turnLed() was called with %s, but expect %s",
						        getLedStateName(state));
		TEST_FAIL_MESSAGE("turnLed() was called with ???, but expect ???");
	}
}

ButtonState fake_getButtonState(int NumCalls)
{
	if(NumCalls < expectedGetButtonStateMaxCalls){
		return expectedButtonStates[NumCalls];
	}
	else
		TEST_FAIL_MESSAGE("Recieved extra getButtonStete() calls");
}

void setupFake(LedState expLedStates[], int ledMaxCalls ,ButtonState buttStates[], int buttonMaxCalls)
{
	turnLedCallNumbers =  0;
	turnLed_StubWithCallback(fake_turnLed);
	expectedLedStates = expLedStates;
	expectedTurnLedMaxCalls = ledMaxCalls;
	getButtonState_StubWithCallback(fake_getButtonState);
	expectedGetButtonStateMaxCalls = buttonMaxCalls;
	expectedButtonStates = buttStates;
}

void verifyTurnLedCalls(int numCalls)
{
	if(turnLedCallNumbers != numCalls)
		TEST_FAIL_MESSAGE("turnLed() was not calld at all.But 1 call is expected.");
}

void test_xxx(void)
{
  LedButtonInfo info = {LED_OFF,BUTTON_RELEASED};
  ButtonState expectedButtonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};
  LedState expectedLedStates[] = {LED_ON};

  setupFake(expectedLedStates,1,expectedButtonStates,3);

	getButtonState();       // it should return released
	getButtonState();       // it should return released
	turnLed(LED_ON);
	getButtonState();       // it should return released

  verifyTurnLedCalls(1);
}

void xtest_doTapTurnOnTapTurnOffLed_given_led_is_off_and_button_is_pressed_and_released_expect_led_to_turn_on(void)
{
  LedButtonInfo info = {LED_OFF,BUTTON_RELEASED};
  ButtonState expectedButtonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};
  LedState expectedLedStates[] = {LED_ON};

  //turnLedCallNumbers = 0;
  setupFake(expectedLedStates,1,expectedButtonStates,3);
  //turnLed_StubWithCallback(fake_turnLed);
  //getButtonState_StubWithCallback(fake_getButtonStateReleasedPressedReleased);

  doTapTurnOnTapTurnOffLed(&info);
  doTapTurnOnTapTurnOffLed(&info);
  doTapTurnOnTapTurnOffLed(&info);

  verifyTurnLedCalls(1);

  TEST_ASSERT_EQUAL(LED_ON, info.currentLedState);
}

void xtest_doTapTurnOnTapTurnOffLed_given_led_is_on_and_button_is_pressed_and_released_expect_led_to_turn_off(void)
{
  LedButtonInfo info = {LED_ON,BUTTON_RELEASED};
  ButtonState expectedButtonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};
  LedState expectedLedStates[] = {LED_OFF};

  turnLed_StubWithCallback(fake_turnLed);
  setupFake(expectedLedStates,1,expectedButtonStates,3);

  doTapTurnOnTapTurnOffLed(&info);
  doTapTurnOnTapTurnOffLed(&info);
  doTapTurnOnTapTurnOffLed(&info);

  verifyTurnLedCalls(1);

  TEST_ASSERT_EQUAL(LED_OFF, info.currentLedState);
}

/*void xtest_doTapTurnOnTapTurnOffLed_given_led_is_on_and_button_is_released__expect_led_to_turn_on(void)
{
  LedButtonInfo info = {LED_ON,BUTTON_RELEASED};

  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  doTapTurnOnTapTurnOffLed(&info); // released and on
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  doTapTurnOnTapTurnOffLed(&info); // pressed and on
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  turnLed_Expect(LED_ON);
  doTapTurnOnTapTurnOffLed(&info);  //released and on

  TEST_ASSERT_EQUAL(LED_ON, info.currentLedState);
}

void xtest_doTapTurnOnTapTurnOffLed_given_led_is_off_and_button_is_pressed__expect_led_to_turn_off(void)
{
  LedButtonInfo info = {LED_OFF,BUTTON_PRESSED};

  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  doTapTurnOnTapTurnOffLed(&info); // released and on
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  doTapTurnOnTapTurnOffLed(&info); // pressed and on
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_OFF);
  doTapTurnOnTapTurnOffLed(&info);  //released and on

  TEST_ASSERT_EQUAL(LED_OFF, info.currentLedState);
}

void xtest_doTapTurnOnTapTurnOffLed_given_button_is_pressed_and_released_expect_led_to_turn_on(void)
{
  LedState currentLedState;
  currentLedState = LED_OFF;
  doTapTurnOnTapTurnOffLed1(&currentLedState);

  TEST_ASSERT_EQUAL(LED_ON,currentLedState);
}

void xtest_doTapTurnOnTapTurnOffLed_given_button_is_pressed_and_released_expect_led_to_turn_off(void)
{
  LedState currentLedState;
  currentLedState = LED_ON;
  doTapTurnOnTapTurnOffLed1(&currentLedState);

  TEST_ASSERT_EQUAL(LED_OFF,currentLedState);
}

void xtest_LedController_given_led_is_pressed_expect_led_is_turn_on(void)
{
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);

  turnOnledIfButtonIsPressed();
}

void xtest_LedController_given_led_is_not_pressed_expect_led_is_turn_off(void)
{
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  turnLed_Expect(LED_OFF);

  turnOnledIfButtonIsPressed();
}*/
