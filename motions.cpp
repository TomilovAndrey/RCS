#include <Motions\motions.h>

motor_driver_A4988 motors[_MAX_MOTORS];

int steps_old = 0; //steps 
int period_start_old = 0; //period ms
int acceleration_dec_old = 0; //decrement ms

char command_types[_MAX_COMMANDS_IN_FRAME] = {};
uint8_t command_codes[_MAX_COMMANDS_IN_FRAME] = {};
int int_parameters[_MAX_INT_PARAMETERS] = {};
float float_parameters[_MAX_FLOAT_PARAMETERS] = {};

char command_types_old[_MAX_COMMANDS_IN_FRAME] = {};
uint8_t command_codes_old[_MAX_COMMANDS_IN_FRAME] = {};
int int_parameters_old[_MAX_INT_PARAMETERS] = {};
float float_parameters_old[_MAX_FLOAT_PARAMETERS] = {};

void motion_error(uint8_t error_code)
{
	switch (error_code)
	{
	case 1:
		Serial.print("Error 0x00000. Not correct motion's number.\n");
		break;
	case 2:
		Serial.print("Error 0x00000. Negative end speed.\n");
		break;
	}
}

void init_frame()
{
	for (uint8_t i = 0; i < _MAX_COMMANDS_IN_FRAME; i++)
		command_types_old[i] = command_types[i];
	for (uint8_t i = 0; i < _MAX_COMMANDS_IN_FRAME; i++)
		command_codes_old[i] = command_codes_old[i];
	for (uint8_t i = 0; i < _MAX_INT_PARAMETERS; i++)
		int_parameters_old[i] = int_parameters[i];
	for (uint8_t i = 0; i < _MAX_FLOAT_PARAMETERS; i++)
		float_parameters_old[i] = float_parameters[i];
	load_frame(&command_types, &command_codes, &float_parameters, &int_parameters);
}
void init_motors()
{
	for (uint8_t i = 0; i < _MAX_AXIS_MOTORS; i++)
	{
		motors[i].set_number(i);
		motors[i].set_label(axis_labels[i]);
		motors[i].set_pins(axis_pins[i][0], axis_pins[i][1], axis_pins[i][2]);
		motors[i].set_microsteps_pins(axis_microsteps_pins[i][0], axis_microsteps_pins[i][1], axis_microsteps_pins[i][2]);
		motors[i].enable();
		motors[i].on();
	}

	for (uint8_t i = _MAX_AXIS_MOTORS; i < _MAX_MOTORS; i++)
	{
		motors[i].set_number(i);
		motors[i].enable();
		motors[i].on();
	}
}
/*
init_motion() - function for motion's data initialization for motor.
____________________________________________________________________

uint8_t number - motor number in array;

uint8_t data_type - type of all input data:
__________________________________________________________________

1 - steps (number) | start period (ms) | period decrement (ms)
2 - steps (number) | start speed (steps/sec) | acceleration (steps/sec^2)
3 - mm | start speed (mm/sec) | acceleration (mm/sec^2)
4 - mm | start speed (mm/min) | acceleration (mm/min^2)
5 - angle | start speed (angles/sec) | acceleration (angles/sec^2)
6 - angle | start speed (angles/min) | acceleration (angles/min^2)
__________________________________________________________________
*/
void init_motion(uint8_t number, uint8_t data_type, uint8_t priority, bool direction, float distance, float speed_start, float acceleration, uint8_t pulse_delay)
{
	if (number > _MAX_MOTORS)
		motion_error(1);
	else
	{
		uint steps = 0; //steps 
		uint period_start = min_pwm_period; //period ms
		uint acceleration_dec = 0; //ms increment
		uint8_t steps_for_acc = 1;
		uint8_t steps_for_acc_counter = 0;

		float speed_end = 0;
		uint period_end = 0;
		float acc_dec = 0;

		switch (data_type)
		{
		case 1:
			steps = static_cast<uint>(distance);
			period_start = static_cast<uint>(speed_start);
			acceleration_dec = static_cast<int>(acceleration);
			break;
		case 2:
			steps = static_cast<uint>(roundf(distance));
			period_start = static_cast<uint>(roundf(msec / speed_start));
			speed_end = sqrt(speed_start * speed_start + 2 * acceleration * distance);
			period_end = static_cast<uint>(roundf(msec / speed_end));
			acc_dec = (period_start - period_end) / steps;
			if (acc_dec < 1 && acc_dec != 0)
			{
				do
				{
					acc_dec *= 10;
					steps_for_acc_counter++;
				} while (acc_dec < 1);

				for (uint8_t i = 0; i < steps_for_acc_counter; i++)
					steps_for_acc *= 10;
			}
			acceleration_dec = static_cast<int>(roundf(acc_dec));
			break;
		case 3:
			steps = static_cast<uint>(roundf(distance * steps_in_mm));
			period_start = static_cast<uint>(roundf(msec / (speed_start * steps_in_mm)));
			speed_end = sqrt(speed_start * speed_start + 2 * acceleration * distance);
			period_end = static_cast<uint>(roundf(msec / (speed_end * steps_in_mm)));
			acc_dec = (period_start - period_end) / steps;
			if (acc_dec < 1 && acc_dec != 0)
			{
				do
				{
					acc_dec *= 10;
					steps_for_acc_counter++;
				} while (acc_dec < 1);

				for (uint8_t i = 0; i < steps_for_acc_counter; i++)
					steps_for_acc *= 10;
			}
			acceleration_dec = static_cast<int>(roundf(acc_dec));
			break;
		case 4:
			steps = static_cast<uint>(roundf(distance * steps_in_mm));
			period_start = static_cast<uint>(roundf(60 * msec / (speed_start * steps_in_mm)));
			speed_end = sqrt(speed_start * speed_start + 2 * acceleration * distance);
			period_end = static_cast<uint>(roundf(60 * msec / (speed_end * steps_in_mm)));
			acc_dec = (period_start - period_end) / steps;
			if (acc_dec < 1 && acc_dec != 0)
			{
				do
				{
					acc_dec *= 10;
					steps_for_acc_counter++;
				} while (acc_dec < 1);

				for (uint8_t i = 0; i < steps_for_acc_counter; i++)
					steps_for_acc *= 10;
			}
			acceleration_dec = static_cast<int>(roundf(acc_dec));
			break;
		case 5:
			steps = static_cast<uint>(roundf(distance * steps_in_angle));
			period_start = static_cast<uint>(roundf(msec / (speed_start * steps_in_angle)));
			speed_end = sqrt(speed_start * speed_start + 2 * acceleration * distance);
			period_end = static_cast<uint>(roundf(msec / (speed_end * steps_in_angle)));
			acc_dec = (period_start - period_end) / steps;
			if (acc_dec < 1 && acc_dec != 0)
			{
				do
				{
					acc_dec *= 10;
					steps_for_acc_counter++;
				} while (acc_dec < 1);

				for (uint8_t i = 0; i < steps_for_acc_counter; i++)
					steps_for_acc *= 10;
			}
			acceleration_dec = static_cast<int>(roundf(acc_dec));
			break;
		case 6:
			steps = static_cast<uint>(roundf(distance * steps_in_angle));
			period_start = static_cast<uint>(roundf(60 * msec / (speed_start * steps_in_angle)));
			speed_end = sqrt(speed_start * speed_start + 2 * acceleration * distance);
			period_end = static_cast<uint>(roundf(60 * msec / (speed_end * steps_in_angle)));
			acc_dec = (period_start - period_end) / steps;
			if (acc_dec < 1 && acc_dec != 0)
			{
				do
				{
					acc_dec *= 10;
					steps_for_acc_counter++;
				} while (acc_dec < 1);

				for (uint8_t i = 0; i < steps_for_acc_counter; i++)
					steps_for_acc *= 10;
			}
			acceleration_dec = static_cast<int>(roundf(acc_dec));
			break;
		default:
			break;
		}
		motors[number].init(direction, steps, period_start, acceleration_dec, pulse_delay);
		motors[number].steps_for_acc = steps_for_acc;

		Serial.print("Motion data: ");
		Serial.print(motors[number].get_label());
		Serial.print("\n");
		Serial.print("_____________________________________________________________________\n");
		Serial.print("Steps: ");
		Serial.print(motors[number].counter);
		Serial.print("\n");
		Serial.print("Period: ");
		Serial.print(motors[number].period);
		Serial.print("\n");
		Serial.print("Acceleration (decrement ms): ");
		Serial.print(motors[number].acceleration);
		Serial.print(" on every ");
		Serial.print(motors[number].steps_for_acc);
		Serial.print(" steps");
		Serial.print("\n");
		Serial.print("____________________________________________________________________\n");
	}
}
void motion_run(uint8_t number)
{
	motors[number].run();
}
void motion_stop(uint8_t number)
{
	motors[number].stop();
}