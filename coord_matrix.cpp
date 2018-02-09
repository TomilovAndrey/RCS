#include <6axis_robot\coord_matrix.h>

uint8_t x0 = 1;
uint8_t x1 = 2;
uint8_t x2 = 4;

uint8_t z0 = 0;
uint8_t z1 = 3;
uint8_t z2 = 5;

void init_rmatrix (float(*angles)[6], float(*rmatrix)[6][3][3], uint8_t axis, uint8_t number)
{
	uint8_t m = axis + 1;
	uint8_t n = axis + 2;

	if (m >= 3)
		m -= 3;
	if (n >= 3)
		n -= 3;

	for (uint8_t i = 0; i < 3; i++)
	{
		for (uint8_t j = 0; j < 3; j++)
		{
			if (i == j)
			{
				if (i == axis)
					(*rmatrix)[number][i][j] = 1;
				else
					(*rmatrix)[number][i][j] = cos((*angles)[number]);
			}
			else
				if (i == m && j == n)
					(*rmatrix)[number][i][j] = -sin((*angles)[number]);
				else
					if (i == n && j == m)
						(*rmatrix)[number][i][j] = sin((*angles)[number]);
					else
						(*rmatrix)[number][i][j] = 0;
		}
	}
}
void init_lmatrix (float(*arms)[6], float(*lmatrix)[6][3], uint8_t axis, uint8_t number)
{
	(*lmatrix)[number][axis] += (*arms)[number];
}
void init_all_matrix (float(*angles)[6], float(*arms)[6], float(*rmatrix)[6][3][3], float(*lmatrix)[6][3])
{
	for (uint8_t i = 0; i < 6; i++)
	{
		init_lmatrix(arms, lmatrix, 2, i);

		if (i == x0 || i == x1 || i == x2)
			init_rmatrix(angles, rmatrix, 0, i);
		else
			init_rmatrix(angles, rmatrix, 2, i);

	}
}
void mult_matrix (float(*matrix_1)[6][3][3], float(*matrix_2)[3], uint8_t number)
{
	float temp;
	float result[3] = {};

	for (uint8_t i = 0; i < 3; i++)
	{
		temp = 0;

		for (uint8_t j = 0; j < 3; j++)
		{
			temp += (*matrix_1)[number][i][j] * (*matrix_2)[j];
		}

		result[i] = temp;
	}

	for (uint8_t i = 0; i < 3; i++)
	{
		(*matrix_2)[i] = result[i];
	}
}
void add_matrix (float(*matrix_1)[6][3], float(*matrix_2)[3], uint8_t number)
{
	for (uint8_t i = 0; i < 3; i++)
	{
		(*matrix_2)[i] += (*matrix_1)[number][i];
	}
}