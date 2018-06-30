#ifndef _BUTTON_H
#define _BUTTON_H

/**
 *return non-zero if button is pressed; zero otherwise.
 */

 typedef enum {
   BUTTON_PRESSED = 1,
   BUTTON_RELEASED = 0,
 } ButtonState;

int getButtonState(void);

#endif // _BUTTON_H
