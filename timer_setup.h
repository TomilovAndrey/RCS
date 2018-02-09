#include <inttypes.h>
#include <p32xxxx.h>
#include <sys\attribs.h>
#include <pins_arduino.h>

#ifndef _TIMER_SETUP_h
#define _TIMER_SETUP_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "wprogram.h"
#else
#include "WProgram.h"
#endif

#define TIMER3 0
#define TIMER4 1
#define TIMER5 2


#define TIMER_PRESCALAR_1_1   0x0000
#define TIMER_PRESCALAR_1_2   0x0010
#define TIMER_PRESCALAR_1_4   0x0020
#define TIMER_PRESCALAR_1_8   0x0030
#define TIMER_PRESCALAR_1_16  0x0040
#define TIMER_PRESCALAR_1_32  0x0050
#define TIMER_PRESCALAR_1_64  0x0060
#define TIMER_PRESCALAR_1_256 0x0070


void initTimerISR(int timer, int prescalar, int period);
void stopTimerISR(int timer);
void handle_pwm(int timer);
#endif