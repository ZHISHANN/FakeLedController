#include "unity.h"
#include "LedController.h"
#include "mock_Button.h"
#include "mock_Led.h"

void setUp(void){}

void tearDown(void){}

void xtest_doTapTurnOnTapTurnOffLed_given_led_is_off_and_button_is_pressed_and_released_expect_led_to_turn_on(void)
{
  LedButtonInfo info = {LED_OFF,BUTTON_RELEASED};

  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  doTapTurnOnTapTurnOffLed(&info);

  TEST_ASSERT_EQUAL(LED_ON, info.currentLedState);
}

void test_doTapTurnOnTapTurnOffLed_given_led_is_on_and_button_is_pressed_and_released_expect_led_to_turn_off(void)
{
  LedButtonInfo info = {LED_ON,BUTTON_RELEASED};

  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  turnLed_Expect(LED_OFF);
  doTapTurnOnTapTurnOffLed(&info);

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
}
