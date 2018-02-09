#include <Motor_driver\handle_pwm.h>

void motor_error(uint8_t error_code)
{
	switch (error_code)
	{
	case 1:
		Serial.print("Error 0x00001. Not correct motor's number.\n");
		break;
	case 2:
		Serial.print("Error 0x00002. Motor's pin in init status.\n");
		break;
	case 3:
		Serial.print("Error 0x00003. Motor's period = 0.\n");
		break;
	default:
		break;
	}
}

const bool motor_driver::get_enable_flag()
{
	return this->enable_flag;
}
const bool motor_driver::get_stop_flag()
{
	return this->stop_flag;
}
const bool motor_driver::get_error_flag()
{
	return this->error_flag;
}
const bool motor_driver::get_msteps_correction_flag()
{
	return this->mstep_correction_flag;
}
const uint8_t motor_driver::get_error_code()
{
	return this->error_code;
}
const char motor_driver::get_label()
{
	return this->label;
}
const uint8_t motor_driver::get_number()
{
	return this->number;
}
const uint8_t motor_driver::get_priority()
{
	return this->priority;
}
const uint8_t motor_driver::get_pin_enable()
{
	return this->pin_enable;
}
const uint8_t motor_driver::get_pin_step()
{
	return this->pin_step;
}
const uint8_t motor_driver::get_pin_dir()
{
	return this->pin_dir;
}

void motor_driver::set_enable_flag(bool flag)
{
	this->enable_flag = flag;
}
void motor_driver::set_stop_flag(bool flag)
{
	this->stop_flag = flag;
}
void motor_driver::set_error_flag(bool flag)
{
	this->error_flag = flag;
}
void motor_driver::set_msteps_correction_flag(bool flag)
{
	this->mstep_correction_flag = flag;
}
void motor_driver::set_flags(uint8_t flags_code)
{
	switch (flags_code)
	{
	case 1: //init/off mode 
		this->enable_flag = false;
		this->stop_flag = true;
		this->error_flag = false;
		break;
	case 2: //run mode
		this->enable_flag = true;
		this->stop_flag = false;
		this->error_flag = false;
		break;
	case 3: //on/stop/idle mode
		this->enable_flag = true;
		this->stop_flag = true;
		this->error_flag = false;
		break;
	case 4: //error with stop mode
		this->enable_flag = true;
		this->stop_flag = true;
		this->error_flag = true;
		break;
	case 5: //error without stop mode
		this->enable_flag = true;
		this->stop_flag = false;
		this->error_flag = true;
		break;
	case 6: //error with deenergysing mode
		this->enable_flag = false;
		this->stop_flag = true;
		this->error_flag = true;
		break;
	default:
		//error
		break;
	}
}
void motor_driver::set_label(char lbl)
{
	this->label = lbl;
}
void motor_driver::set_number(uint8_t nbr)
{
	this->number = nbr;
}
void motor_driver::set_priority(uint8_t prt)
{
	this->priority = prt;
}
void motor_driver::set_pin_enable(uint8_t enable)
{
	this->pin_enable = enable;
}
void motor_driver::set_pin_step(uint8_t stp)
{
	this->pin_step = stp;
}
void motor_driver::set_pin_dir(uint8_t drn)
{
	this->pin_dir = drn;
}
void motor_driver::set_pins(uint8_t enable, uint8_t stp, uint8_t drn)
{
	this->pin_enable = enable;
	this->pin_step = stp;
	this->pin_dir = drn;
}

void motor_driver::enable()
{
	pinMode(this->pin_enable, OUTPUT);
	pinMode(this->pin_step, OUTPUT);
	pinMode(this->pin_dir, OUTPUT);
}
void motor_driver::on()
{
	this->set_flags(3);
	digitalWrite(this->pin_enable, LOW);
	set_pwm_flags(this->enable_flag, this->stop_flag, this->error_flag, this->number);
}
void motor_driver::off()
{
	this->set_flags(1);
	digitalWrite(this->pin_enable, HIGH);
	set_pwm_flags(this->enable_flag, this->stop_flag, this->error_flag, this->number);
}
void motor_driver::init(bool drn, uint ctr, uint prd, int acn, uint8_t p_d)
{
	this->enable();
	this->on();
	this->direction = drn;
	if (this->direction == true)
		digitalWrite(this->pin_dir, HIGH);
	else
		digitalWrite(this->pin_dir, LOW);

	this->counter = ctr;
	this->period = prd;
	this->acceleration = acn;
	this->pulse_delay = p_d;
	set_pwm_obj(this);
}
void motor_driver::init_data(bool drn, uint ctr, uint prd, int acn, uint8_t p_d)
{
	this->direction = drn;
	if (this->direction == true)
		digitalWrite(this->pin_dir, HIGH);
	else
		digitalWrite(this->pin_dir, LOW);

	this->counter = ctr;
	this->period = prd;
	this->acceleration = acn;
	this->pulse_delay = p_d;
	set_pwm_data(this->counter, this->period, this->acceleration, this->pulse_delay, this->number);
}
void motor_driver::run()
{
	this->set_flags(2);
	set_pwm_flags(this->enable_flag, this->stop_flag, this->error_flag, this->number);
}
void motor_driver::stop()
{
	this->set_flags(3);
	set_pwm_flags(this->enable_flag, this->stop_flag, this->error_flag, this->number);
}
void motor_driver::error(uint8_t error_code)
{
	this->error_flag = true;
	set_pwm_flags(this->enable_flag, this->stop_flag, this->error_flag, this->number);
}

void motor_driver_A4988::enable()
{
	pinMode(this->pin_enable, OUTPUT);
	pinMode(this->pin_step, OUTPUT);
	pinMode(this->pin_dir, OUTPUT);

	pinMode(this->pin_MS1, OUTPUT);
	pinMode(this->pin_MS2, OUTPUT);
	pinMode(this->pin_MS3, OUTPUT);
}
void motor_driver_A4988::set_microstep_mode(uint8_t mode)
{
	switch (mode)
	{
	case 1:
		digitalWrite(pin_MS1, LOW);
		digitalWrite(pin_MS2, LOW);
		digitalWrite(pin_MS3, LOW);
		break;
	case 2:
		digitalWrite(pin_MS1, HIGH);
		digitalWrite(pin_MS2, LOW);
		digitalWrite(pin_MS3, LOW);
		break;
	case 4:
		digitalWrite(pin_MS1, LOW);
		digitalWrite(pin_MS2, HIGH);
		digitalWrite(pin_MS3, LOW);
		break;
	case 8:
		digitalWrite(pin_MS1, HIGH);
		digitalWrite(pin_MS2, HIGH);
		digitalWrite(pin_MS3, LOW);
		break;
	case 16:
		digitalWrite(pin_MS1, HIGH);
		digitalWrite(pin_MS2, HIGH);
		digitalWrite(pin_MS3, HIGH);
		break;
	}
}
const uint8_t motor_driver_A4988::get_pin_MS1()
{
	return this->pin_MS1;
}
const uint8_t motor_driver_A4988::get_pin_MS2()
{
	return this->pin_MS2;
}
const uint8_t motor_driver_A4988::get_pin_MS3()
{
	return this->pin_MS3;
}
void motor_driver_A4988::set_pin_MS1(uint8_t MS1)
{
	this->pin_MS1 = MS1;
}
void motor_driver_A4988::set_pin_MS2(uint8_t MS2)
{
	this->pin_MS2 = MS2;
}
void motor_driver_A4988::set_pin_MS3(uint8_t MS3)
{
	this->pin_MS3 = MS3;
}
void motor_driver_A4988::set_microsteps_pins(uint8_t MS1, uint8_t MS2, uint8_t MS3)
{
	this->pin_MS1 = MS1;
	this->pin_MS2 = MS2;
	this->pin_MS3 = MS3;
}