#ifndef _CONFIG_h
#define _CONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

#define PI 3.14159265
#define timer_freq 10
#define std_pulse_delay 5
#define min_pwm_period 1000
#define max_pwm_period 10000000
#define steps_in_mm 40
#define steps_in_angle 0.5556
#define std_steps_for_acc 10
#define msec 1000000

const uint8_t _MAX_TOOLS = 10;
const uint8_t _MAX_MOTORS = 9;
const uint8_t _MAX_AXIS_MOTORS = 6;
const char axis_labels[_MAX_AXIS_MOTORS] = { 'X','Y','Z','A','B','C' };
const uint8_t axis_pins[_MAX_AXIS_MOTORS][3] = { { 2,3,4 },{ 5,6,7 },{ 8,9,10 },{ 11,12,13 },{ 26,27,28 },{ 29,30,31 } };
const uint8_t axis_microsteps_pins[_MAX_AXIS_MOTORS][3] = { { 32,33,34 },{ 32,33,34 },{ 32,33,34 },{ 32,33,34 },{ 32,33,34 },{ 32,33,34 } };
#endif
