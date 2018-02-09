#include <6Axis_robot\print_matrix.h>

void print_matrix(float(*matrix)[6][3][3])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				//printf("%0.2f ", (*matrix)[i][j][k]);
				Serial.print((*matrix)[i][j][k]);
				Serial.print("\t");
			}
			Serial.print("\n");
		}
		Serial.print("\n");
	}
}
void print_matrix(float(*matrix)[6][3])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//printf("%0.2f ", (*matrix)[i][j]);
			Serial.print((*matrix)[i][j]);
			Serial.print("\t");
		}
		Serial.print("\n");
	}
}
void print_matrix(float(*matrix)[6])
{
	for (int i = 0; i < 6; i++)
	{
		//printf("%0.2f ", (*matrix)[i]);
		Serial.print((*matrix)[i]);
		Serial.print("\t");
	}
}
void print_matrix(float(*matrix)[3])
{
	for (int i = 0; i < 3; i++)
	{
		//printf("%0.2f ", (*matrix)[i]);
		Serial.print((*matrix)[i]);
		Serial.print("\t");
	}
}
