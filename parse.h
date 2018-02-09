#ifndef _PARSE_h
#define _PARSE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

#include <math.h>

const uint8_t _MAX_COMMANDS_IN_FRAME = 4; //maximum commands in frame
const uint8_t _MAX_FLOAT_PARAMETERS = 9; //maximum float-parameters
const uint8_t _MAX_INT_PARAMETERS = 3; //maximum int-parameters

void parse_error(uint8_t);
uint8_t scan_string(uint8_t, char, char);
int calc_int_parameter(uint8_t, uint8_t);
float calc_float_parameter(uint8_t, uint8_t, uint8_t);
void parse(String*);
void load_frame(char(*)[_MAX_COMMANDS_IN_FRAME], uint8_t(*)[_MAX_COMMANDS_IN_FRAME], float(*)[_MAX_FLOAT_PARAMETERS], int(*)[_MAX_INT_PARAMETERS]);
void print_frame();
#endif
