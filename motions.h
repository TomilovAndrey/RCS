#ifndef _MOTIONS_h
#define _MOTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

#include <Motor_driver\handle_pwm.h>
#include <Parse\parse.h>

void motion_error(uint8_t);

void init_frame();
void init_motors();
void init_motion(uint8_t , uint8_t, uint8_t, bool, float, float, float, uint8_t);
void motion_run(uint8_t);
void motion_stop(uint8_t);
#endif