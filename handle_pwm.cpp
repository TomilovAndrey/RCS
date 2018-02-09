#include <Motor_driver\handle_pwm.h>

uint8_t step_pins[_MAX_MOTORS] = {};
uint counters[_MAX_MOTORS] = {};
uint timers[_MAX_MOTORS] = {};
uint periods[_MAX_MOTORS] = {};
int accelerations[_MAX_MOTORS] = {};
int spurts[_MAX_MOTORS] = {};
uint8_t pulse_delays[_MAX_MOTORS] = {};

bool enable_flags[_MAX_MOTORS] = {};
bool stop_flags[_MAX_MOTORS] = {};
bool error_flags[_MAX_MOTORS] = {};
uint8_t error_codes[_MAX_MOTORS] = {};

uint8_t steps_for_acc = 0;
uint8_t steps_acc_counter = 0;

void start_cycle()
{
	initTimerISR(TIMER3, TIMER_PRESCALAR_1_8, 0x64);
}
void stop_cycle()
{
	stopTimerISR(TIMER3);
}
void set_pwm_obj(motor_driver* motor)
{
	uint8_t number = motor->get_number();

	if (number == 255)
		motor_error(1);
	else
	{
		if (motor->get_pin_step() == 255)
			motor_error(2);
		else
		{
			step_pins[number] = motor->get_pin_step();
			counters[number] = motor->counter;
			timers[number] = 0;
			if (motor->period == 0)
				motor_error(3);
			else
			{
				periods[number] = motor->period;
				accelerations[number] = motor->acceleration;
				pulse_delays[number] = motor->pulse_delay;

				enable_flags[number] = motor->get_enable_flag();
				stop_flags[number] = motor->get_stop_flag();
				error_flags[number] = motor->get_error_flag();
				error_codes[number] = motor->get_error_code();
			}
		}
	}
}
void set_pwm_data(uint counter, uint period, int acceleration, uint8_t pulse_delay, uint8_t number)
{
	if (number == 255)
		motor_error(1);
	else
	{
		counters[number] = counter;
		timers[number] = 0;
		if (period == 0)
			motor_error(3);
		else
		{
			periods[number] = period;
			accelerations[number] = acceleration;
			pulse_delays[number] = pulse_delay;
		}
	}
}
void set_pwm_flags(bool enable_flag, bool stop_flag, bool error_flag, uint8_t number)
{
	enable_flags[number] = enable_flag;
	stop_flags[number] = stop_flag;
	error_flags[number] = error_flag;
}
void handle_pwm(int timer)
{
	for (uint8_t i = 0; i < _MAX_MOTORS; i++)
	{
		if (enable_flags[i] == true && stop_flags[i] == false && counters[i] > 0)
		{
			if (timers[i] <= timer_freq)
			{
				digitalWrite(step_pins[i], HIGH);
				delayMicroseconds(pulse_delays[i]);
				digitalWrite(step_pins[i], LOW);

				steps_acc_counter++;
				if (steps_acc_counter == steps_for_acc)
				{
					if (periods[i] >= min_pwm_period)
					{
						if (periods[i] >= max_pwm_period)
						{
							error_flags[i] = true;
							error_codes[i] = 3;
							periods[i] = max_pwm_period;
						}
						else
						{
							periods[i] -= accelerations[i];
							accelerations[i] += spurts[i];
						}
					}
					else
						periods[i] = min_pwm_period;

					steps_acc_counter = 0;
				}
				
				timers[i] = periods[i] + timer_freq - pulse_delays[i];

				counters[i]--;
			}
			else
				timers[i] -= timer_freq;
		}
	}
}
 