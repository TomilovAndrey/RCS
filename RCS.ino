#include <rcslib.h>

String command;
char income_byte;

void setup()
{
	Serial.begin(9600);
	start_cycle();
	init_motors();
	init_motion(0, 3, 1, true, 100.0, 15.0, -2.25, std_pulse_delay);
	motion_run(0);
	//delay(5000);
	//motion_stop(0);

	/*motor_driver_A4988 motor_test = { 't',0,2,3,4,5,6,7 };
	motor_test.init(true, 1000, 1000, 0, 3);
	motor_test.run();*/
}

void loop()
{
	while (Serial.available() > 0)
	{
		income_byte = Serial.read();
		if (income_byte == '\n')
		{
			parse(&command);
			print_frame();

			command = "";
		}
		else
			command += income_byte;
	}
}
