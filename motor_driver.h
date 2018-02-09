#ifndef _MOTOR_DRIVER_h
#define _MOTOR_DRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

/*
bool flags: -enable_flag---stop_flag---error_flag-
______________________________________________________________
010 - start initialization / off mode
100 - run mode
110 - on/stop/idle mode
111 - error with stop mode 
101 - error without stop mode
011 - error with deenergysing mode
*/

void motor_error(uint8_t);

class motor_driver
{
protected:

	bool enable_flag;
	bool stop_flag;
	bool error_flag;
	bool mstep_correction_flag;
	uint8_t error_code;

	char label;
	uint8_t number;
	uint8_t priority;

	uint8_t pin_enable;
	uint8_t pin_step;
	uint8_t pin_dir;

public:

	bool direction;
	uint counter;
	uint period;
	int acceleration;
	uint8_t steps_for_acc;
	uint8_t pulse_delay;

	motor_driver()
	{
		this->enable_flag = false;
		this->stop_flag = true;
		this->error_flag = false;
		this->mstep_correction_flag = false;
		this->error_code = 255;
		this->label = ' ';
		this->number = 255;
		this->priority = 255;
		this->pin_enable = 255;
		this->pin_step = 255;
		this->pin_dir = 255;
		this->counter = 0;
		this->period = 0;
		this->acceleration = 0;
		this->steps_for_acc = 1;
		this->steps_for_acc = 0;
		this->pulse_delay = 0;
	}
	motor_driver(char lbl, uint8_t nbr, uint8_t p_e, uint8_t p_s, uint8_t p_d)
	{
		if (nbr > _MAX_MOTORS)
			motor_error(1);
		else
		{
			this->enable_flag = false;
			this->stop_flag = true;
			this->error_flag = false;
			this->mstep_correction_flag = false;
			this->error_code = 255;
			this->label = lbl;
			this->number = nbr;
			this->priority = 255;
			this->pin_enable = p_e;
			this->pin_step = p_s;
			this->pin_dir = p_d;
			this->counter = 0;
			this->period = 0;
			this->acceleration = 0;
			this->steps_for_acc = 1;
			this->steps_for_acc = 0;
			this->pulse_delay = 0;
		}
	}

	const bool get_enable_flag();
	const bool get_stop_flag();
	const bool get_error_flag();
	const bool get_msteps_correction_flag();
	const uint8_t get_error_code();
	const char get_label();
	const uint8_t get_number();
	const uint8_t get_priority();
	const uint8_t get_pin_enable();
	const uint8_t get_pin_step();
	const uint8_t get_pin_dir();

	void set_enable_flag(bool);
	void set_stop_flag(bool);
	void set_error_flag(bool);
	void set_msteps_correction_flag(bool);
	void set_flags(uint8_t);
	void set_label(char);
	void set_number(uint8_t);
	void set_priority(uint8_t);
	void set_pin_enable(uint8_t);
	void set_pin_step(uint8_t);
	void set_pin_dir(uint8_t);
	void set_pins(uint8_t, uint8_t, uint8_t);

	virtual void enable();
	virtual void on();
	virtual void off();
	virtual void init(bool, uint, uint, int, uint8_t);
	virtual void init_data(bool, uint, uint, int, uint8_t);
	virtual void run();
	virtual void stop(); 
	virtual void error(uint8_t);
};
extern motor_driver Stepper_motor;

class motor_driver_A4988: public motor_driver
{
private:

	uint8_t pin_MS1;
	uint8_t pin_MS2;
	uint8_t pin_MS3;

public:

	motor_driver_A4988()
	{
		this->enable_flag = false;
		this->stop_flag = true;
		this->error_flag = false;
		this->mstep_correction_flag = false;
		this->error_code = 255;
		this->label = ' ';
		this->number = 255;
		this->priority = 255;
		this->pin_enable = 255;
		this->pin_step = 255;
		this->pin_dir = 255;
		this->pin_MS1 = 255;
		this->pin_MS2 = 255;
		this->pin_MS3 = 255;
		this->counter = 0;
		this->period = 0;
		this->acceleration = 0;
		this->steps_for_acc = 1;
		this->steps_for_acc = 0;
		this->pulse_delay = 0;
	}
	motor_driver_A4988(char lbl, uint8_t nbr, uint8_t p_e, uint8_t p_s, uint8_t p_d, uint8_t MS1, uint8_t MS2, uint8_t MS3)
	{
		if (nbr > _MAX_MOTORS)
			motor_error(1);
		else
		{
			this->enable_flag = false;
			this->stop_flag = true;
			this->error_flag = false;
			this->mstep_correction_flag = false;
			this->error_code = 255;
			this->label = lbl;
			this->number = nbr;
			this->priority = 255;
			this->pin_enable = p_e;
			this->pin_step = p_s;
			this->pin_dir = p_d;
			this->pin_MS1 = MS1;
			this->pin_MS2 = MS2;
			this->pin_MS3 = MS3;
			this->counter = 0;
			this->period = 0;
			this->acceleration = 0;
			this->steps_for_acc = 1;
			this->steps_for_acc = 0;
			pulse_delay = 0;
		}
	}

	virtual void enable();
	void set_microstep_mode(uint8_t);
	const uint8_t get_pin_MS1();
	const uint8_t get_pin_MS2();
	const uint8_t get_pin_MS3();
	void set_pin_MS1(uint8_t);
	void set_pin_MS2(uint8_t);
	void set_pin_MS3(uint8_t);
	void set_microsteps_pins(uint8_t, uint8_t, uint8_t);
};
extern motor_driver Stepper_motor;
#endif