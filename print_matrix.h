#ifndef _PRINT_MATRIX_h
#define _PRINT_MATRIX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

void print_matrix(float(*)[6][3][3]);
void print_matrix(float(*)[6][3]);
void print_matrix(float(*)[6]);
void print_matrix(float(*)[3]);
#endif