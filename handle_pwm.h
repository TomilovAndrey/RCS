#ifndef _HANDLE_PWM_h
#define _HANDLE_PWM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

#include <config.h>
#include <Motor_driver\timer_setup.h>
#include <Motor_driver\motor_driver.h>

void start_cycle();
void stop_cycle();
void set_pwm_obj(motor_driver*);
void set_pwm_data(uint, uint, int, uint8_t, uint8_t);
void set_pwm_flags(bool, bool, bool, uint8_t);
void handle_pwm(int);
#endif