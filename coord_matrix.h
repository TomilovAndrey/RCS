#ifndef _COORD_MATRIX_h
#define _COORD_MATRIX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif

void init_rmatrix (float(*)[6], float(*)[6][3][3], uint8_t, uint8_t);
void init_lmatrix (float(*)[6], float(*)[6][3], uint8_t, uint8_t);
void init_all_matrix (float(*)[6], float(*)[6], float(*)[6][3][3], float(*)[6][3]);
void mult_matrix (float(*)[6][3][3], float(*)[3], uint8_t);
void add_matrix (float(*)[6][3], float(*)[3], uint8_t);
#endif