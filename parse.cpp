// Module for parse G and M command from serial port on arduino controllers
// Created by Tomilov Andrey 12.01.2018

#include <Parse\parse.h>

String cmd; //String object with command's frame

bool parse_err; //error flag
uint8_t parse_error_code; //error code

char command_types[_MAX_COMMANDS_IN_FRAME]; //array with types of every commands in frame (G or M command)
uint8_t command_codes[_MAX_COMMANDS_IN_FRAME]; //array with codes of every commands in frame (example: in G03 command code = 3)
int8_t command_number; //uses for index of command_types and command_codes array element 

uint8_t g_command_counter; //counter for G-commands
uint8_t m_command_counter; //counter for M-commands
uint8_t parameter_counter; // counter for parameters (X, Y, Z e.t.c)

uint8_t G; //uses for calculation G-command code
uint8_t M; //uses for calculation M-command code

float X; //0-element in float_parameters array
bool x_flag; //X-parameter's flag
float Y; //1-element in float_parameters array
bool y_flag; //Y-parameter's flag
float Z; //2-element in float_parameters array
bool z_flag; //Z-parameter's flag
int P; //0-element in int_parameters array
bool p_flag; //P-parameter's flag
float F; //3-element in float_parameters array
bool f_flag; //F-parameter's flag
float S; //4-element in float_parameters array
bool s_flag; //S-parameter's flag
float R; //5-element in float_parameters array
bool r_flag; //R-parameter's flag
int D; //1-element in int_parameters array
bool d_flag; //D-parameter's flag
int L; //2-element in int_parameters array
bool l_flag; //L-parameter's flag
float I; //6-element in float_parameters array
bool i_flag; //I-parameter's flag
float J; //7-element in float_parameters array
bool j_flag; //J-parameter's flag
float K; //8-element in float_parameters array
bool k_flag; //K-parameter's flag

int int_parameters[_MAX_INT_PARAMETERS]; //array with int-parameters
float float_parameters[_MAX_FLOAT_PARAMETERS]; //array with float-parameters

void reset_parameters()
{
	G = 0;
	M = 0;
	X = 0;
	x_flag = false;
	Y = 0;
	y_flag = false;
	Z = 0;
	z_flag = false;
	P = 0;
	p_flag = false;
	F = 0;
	f_flag = false;
	S = 0;
	s_flag = false;
	R = 0;
	r_flag = false;
	D = 0;
	d_flag = false;
	L = 0;
	l_flag = false;
	I = 0;
	i_flag = false;
	J = 0;
	j_flag = false;
	K = 0;
	k_flag = false;

	g_command_counter = 0;
	m_command_counter = 0;
	parameter_counter = 0;

	for (uint8_t j = 0; j < _MAX_COMMANDS_IN_FRAME; j++)
	{
		command_types[j] = ' ';
		command_codes[j] = 0;
	}
	for (uint8_t j = 0; j < _MAX_INT_PARAMETERS; j++)
	{
		int_parameters[j] = 0;
	}
	for (uint8_t j = 0; j < _MAX_FLOAT_PARAMETERS; j++)
	{
		float_parameters[j] = 0.0;
	}

	command_number = -1;
	parse_err = false;
	parse_error_code = 255;
}
void parse_error(uint8_t error_code)
{
	parse_err = true;
	parse_error_code = error_code;

	switch (error_code)
	{
	case 0:
		Serial.print("Error 0x00000. Null command. \n");
		break;
	case 1:
		Serial.print("Error 0x00001. Excess number of commands in frame. \n");
		break;
	case 2:
		Serial.print("Error 0x00002. Not correct g-command code. \n");
		break;
	case 3:
		Serial.print("Error 0x00003. Not correct m-command code. \n");
		break;
	case 4:
		Serial.print("Error 0x00004. Scan_string function error. Error in command_type parametr. \n");
		break;
	case 5:
		Serial.print("Error 0x00005. Not correct type of command or parameter. \n");
		break;
	case 6:
		Serial.print("Error 0x00006. Not correct command syntax. Deficiency number of space-symbols. \n");
		break;
	case 7:
		Serial.print("Error 0x00007. Not correct command syntax. Excess number of space-symbols. \n");
		break;
	case 8:
		Serial.print("Error 0x00008. Not correct X-parameter. \n");
		break;
	case 9:
		Serial.print("Error 0x00009. Not correct Y-parameter. \n");
		break;
	case 10:
		Serial.print("Error 0x00010. Not correct Z-parameter. \n");
		break;
	case 11:
		Serial.print("Error 0x00011. Not correct P-parameter. \n");
		break;
	case 12:
		Serial.print("Error 0x00012. Not correct F-parameter. \n");
		break;
	case 13:
		Serial.print("Error 0x00013. Not correct S-parameter. \n");
		break;
	case 14:
		Serial.print("Error 0x00014. Not correct R-parameter. \n");
		break;
	case 15:
		Serial.print("Error 0x00015. Not correct D-parameter. \n");
		break;
	case 16:
		Serial.print("Error 0x00016. Not correct L-parameter. \n");
		break;
	case 17:
		Serial.print("Error 0x00017. Not correct I-parameter. \n");
		break;
	case 18:
		Serial.print("Error 0x00018. Not correct J-parameter. \n");
		break;
	case 19:
		Serial.print("Error 0x00019. Not correct K-parameter. \n");
		break;
	case 20:
		Serial.print("Error 0x00020. Repeat X-parameter. \n");
		break;
	case 21:
		Serial.print("Error 0x00021. Repeat Y-parameter. \n");
		break;
	case 22:
		Serial.print("Error 0x00022. Repeat Z-parameter. \n");
		break;
	case 23:
		Serial.print("Error 0x00023. Repeat P-parameter. \n");
		break;
	case 24:
		Serial.print("Error 0x00024. Repeat F-parameter. \n");
		break;
	case 25:
		Serial.print("Error 0x00025. Repeat S-parameter. \n");
		break;
	case 26:
		Serial.print("Error 0x00026. Repeat R-parameter. \n");
		break;
	case 27:
		Serial.print("Error 0x00027. Repeat D-parameter. \n");
		break;
	case 28:
		Serial.print("Error 0x00028. Repeat L-parameter. \n");
		break;
	case 29:
		Serial.print("Error 0x00029. Repeat I-parameter. \n");
		break;
	case 30:
		Serial.print("Error 0x00030. Repeat J-parameter. \n");
		break;
	case 31:
		Serial.print("Error 0x00032. Repeat K-parameter. \n");
		break;
	}
}
uint8_t scan_string(uint8_t i, char end_byte, char type)
{
	char byte;
	uint8_t code_counter = 0;
	uint8_t j = i + 1;
	while (1)
	{
		byte = cmd[j];
		if (byte == end_byte || byte == '\0')
			break;
		if ((byte < '0' || byte > '9') && (byte != '.' || (byte == '.' && end_byte == ' ')))
		{
			if (type == 'G')
				parse_error(2);
			else
				if (type == 'M')
					parse_error(3);
				else
					if (type == 'X')
						parse_error(8);
					else
						if (type == 'Y')
							parse_error(9);
						else
							if (type == 'Z')
								parse_error(10);
							else
								if (type == 'P')
									parse_error(11);
								else
									if (type == 'F')
										parse_error(12);
									else
										if (type == 'S')
											parse_error(13);
										else
											if (type == 'R')
												parse_error(14);
											else
												if (type == 'D')
													parse_error(15);
												else
													if (type == 'L')
														parse_error(16);
													else
														if (type == 'I')
															parse_error(17);
														else
															if (type == 'J')
																parse_error(18);
															else
																if (type == 'K')
																	parse_error(19);
																else
																	parse_error(4);
		}
		code_counter++;
		j++;
	}
	return code_counter;
}
int calc_int_parameter(uint8_t start_byte_number, uint8_t code_counter)
{
	int parameter = 0;
	int int_part = 0;
	for (uint8_t j = 1; j <= code_counter; j++)
	{
		int_part = (cmd[start_byte_number + j] - '0');
		uint8_t value = code_counter - j;
		while (value > 0)
		{
			int_part *= 10;
			value--;
		}
		parameter += int_part;
	}
	return parameter;
}
float calc_float_parameter(uint8_t start_byte_number, uint8_t code_counter_int, uint8_t code_counter_fract)
{
	float parameter = 0.0;
	int int_part = 0;
	float fraction_part = 0.0;
	for (uint8_t j = 1; j <= code_counter_int; j++)
	{
		int_part = (cmd[start_byte_number + j] - '0');
		uint8_t value = code_counter_int - j;
		while (value > 0)
		{
			int_part *= 10;
			value--;
		}
		parameter += int_part;
	}
	uint8_t shift = start_byte_number + code_counter_int + 1;
	for (uint8_t j = 1; j <= code_counter_fract; j++)
	{
		fraction_part = (cmd[shift + j] - '0');
		for (uint8_t k = 0; k < j; k++)
			fraction_part *= 0.1;
		parameter += fraction_part;
	}
	return parameter;
}
void parse(String* command)
{
	cmd = (*command);
	int cmd_length = cmd.length();
	if (cmd_length == 0)
	{
		parse_error(0);
	}
	char byte;
	uint8_t code_counter;
	uint8_t command_type_number;
	uint8_t space_counter = 0;
	reset_parameters();
	for (uint8_t i = 0; i < cmd_length; i++)
	{
		byte = cmd[i];
		if (byte == 'G')
			g_command_counter++;
		else
			if (byte == 'M')
				m_command_counter++;
			else
				if (byte == 'X' || byte == 'Y' || byte == 'Z' || byte == 'P' || byte == 'F' || byte == 'S' || byte == 'R' || byte == 'D' || byte == 'L' || byte == 'I' || byte == 'J' || byte == 'K')
					parameter_counter++;
				else
					if (byte == ' ')
						space_counter++;
					else
						if (byte != '.' && (byte < '0' || byte > '9'))
						{
							parse_error(5);
							return;
						}
						else
							if (g_command_counter + m_command_counter > _MAX_COMMANDS_IN_FRAME)
							{
								parse_error(1);
								return;
							}
	}
	if (space_counter < g_command_counter + m_command_counter + parameter_counter - 1)
	{
		parse_error(6);
		return;
	}
	else
		if (space_counter > g_command_counter + m_command_counter + parameter_counter - 1)
		{
			parse_error(7);
			return;
		}
		else
			for (uint8_t i = 0; i < cmd_length; i++)
			{
				byte = cmd[i];
				//##############################################################################
				if (byte == 'G')
				{
					command_number++;
					code_counter = scan_string(i, ' ', byte);
					G = calc_int_parameter(i, code_counter);
					i += code_counter + 1;
					command_codes[command_number] = G;
					command_types[command_number] = 'G';
					continue;
				}
				else//##############################################################################
					if (byte == 'M')
					{
						command_number++;
						code_counter = scan_string(i, ' ', byte);
						M = calc_int_parameter(i, code_counter);
						i += code_counter + 1;
						command_codes[command_number] = M;
						command_types[command_number] = 'M';
						continue;
					}
					else//##############################################################################
						if (byte == 'X')
						{
							if (x_flag == true)
							{
								parse_error(20);
								return;
							}
							x_flag = true;
							uint8_t code_counter_int = scan_string(i, '.', byte);
							if (parse_err == true)
								return;
							uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
							if (parse_err == true)
								return;
							X = calc_float_parameter(i, code_counter_int, code_counter_fract);
							float_parameters[0] = X;
							i += code_counter_int + code_counter_fract + 2;
							continue;
						}
						else//##############################################################################
							if (byte == 'Y')
							{
								if (y_flag == true)
								{
									parse_error(21);
									return;
								}
								y_flag = true;
								uint8_t code_counter_int = scan_string(i, '.', byte);
								if (parse_err == true)
									return;
								uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
								if (parse_err == true)
									return;
								Y = calc_float_parameter(i, code_counter_int, code_counter_fract);
								float_parameters[1] = Y;
								i += code_counter_int + code_counter_fract + 2;
								continue;
							}
							else//##############################################################################
								if (byte == 'Z')
								{
									if (z_flag == true)
									{
										parse_error(22);
										return;
									}
									z_flag = true;
									uint8_t code_counter_int = scan_string(i, '.', byte);
									if (parse_err == true)
										return;
									uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
									if (parse_err == true)
										return;
									Z = calc_float_parameter(i, code_counter_int, code_counter_fract);
									float_parameters[2] = Z;
									i += code_counter_int + code_counter_fract + 2;
									continue;
								}
								else//##############################################################################
									if (byte == 'P')
									{
										if (p_flag == true)
										{
											parse_error(23);
											return;
										}
										p_flag = true;
										uint8_t code_counter_int = scan_string(i, ' ', byte);
										if (parse_err == true)
											return;
										P = calc_int_parameter(i, code_counter_int);
										int_parameters[0] = P;
										i += code_counter_int + 1;
										continue;
									}
									else//##############################################################################
										if (byte == 'F')
										{
											if (f_flag == true)
											{
												parse_error(24);
												return;
											}
											p_flag = true;
											uint8_t code_counter_int = scan_string(i, '.', byte);
											if (parse_err == true)
												return;
											uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
											if (parse_err == true)
												return;
											F = calc_float_parameter(i, code_counter_int, code_counter_fract);
											float_parameters[3] = F;
											i += code_counter_int + code_counter_fract + 2;
											continue;
										}
										else//##############################################################################
											if (byte == 'S')
											{
												if (s_flag == true)
												{
													parse_error(25);
													return;
												}
												s_flag = true;
												uint8_t code_counter_int = scan_string(i, '.', byte);
												if (parse_err == true)
													return;
												uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
												if (parse_err == true)
													return;
												S = calc_float_parameter(i, code_counter_int, code_counter_fract);
												float_parameters[4] = S;
												i += code_counter_int + code_counter_fract + 2;
												continue;
											}
											else//##############################################################################
												if (byte == 'R')
												{
													if (r_flag == true)
													{
														parse_error(26);
														return;
													}
													r_flag = true;
													uint8_t code_counter_int = scan_string(i, '.', byte);
													if (parse_err == true)
														return;
													uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
													if (parse_err == true)
														return;
													R = calc_float_parameter(i, code_counter_int, code_counter_fract);
													float_parameters[5] = R;
													i += code_counter_int + code_counter_fract + 2;
													continue;
												}
												else//##############################################################################
													if (byte == 'D')
													{
														if (d_flag == true)
														{
															parse_error(27);
															return;
														}
														d_flag = true;
														uint8_t code_counter_int = scan_string(i, ' ', byte);
														if (parse_err == true)
															return;
														D = calc_int_parameter(i, code_counter_int);
														int_parameters[1] = D;
														i += code_counter_int + 1;
														continue;
													}
													else//##############################################################################
														if (byte == 'L')
														{
															if (l_flag == true)
															{
																parse_error(28);
																return;
															}
															l_flag = true;
															uint8_t code_counter_int = scan_string(i, ' ', byte);
															if (parse_err == true)
																return;
															L = calc_int_parameter(i, code_counter_int);
															int_parameters[2] = L;
															i += code_counter_int + 1;
															continue;
														}
														else//##############################################################################
															if (byte == 'I')
															{
																if (i_flag == true)
																{
																	parse_error(29);
																	return;
																}
																i_flag = true;
																uint8_t code_counter_int = scan_string(i, '.', byte);
																if (parse_err == true)
																	return;
																uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
																if (parse_err == true)
																	return;
																I = calc_float_parameter(i, code_counter_int, code_counter_fract);
																float_parameters[6] = I;
																i += code_counter_int + code_counter_fract + 2;
																continue;
															}
															else//##############################################################################
																if (byte == 'J')
																{
																	if (j_flag == true)
																	{
																		parse_error(30);
																		return;
																	}
																	j_flag = true;
																	uint8_t code_counter_int = scan_string(i, '.', byte);
																	if (parse_err == true)
																		return;
																	uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
																	if (parse_err == true)
																		return;
																	J = calc_float_parameter(i, code_counter_int, code_counter_fract);
																	float_parameters[7] = J;
																	i += code_counter_int + code_counter_fract + 2;
																	continue;
																}
																else//##############################################################################
																	if (byte == 'K')
																	{
																		if (k_flag == true)
																		{
																			parse_error(31);
																			return;
																		}
																		k_flag = true;
																		uint8_t code_counter_int = scan_string(i, '.', byte);
																		if (parse_err == true)
																			return;
																		uint8_t code_counter_fract = scan_string(i + code_counter_int + 1, ' ', byte);
																		if (parse_err == true)
																			return;
																		K = calc_float_parameter(i, code_counter_int, code_counter_fract);
																		float_parameters[8] = K;
																		i += code_counter_int + code_counter_fract + 2;
																		continue;
																	}
			}
}
void load_frame(char (*cmd_types)[_MAX_COMMANDS_IN_FRAME], uint8_t (*cmd_codes)[_MAX_COMMANDS_IN_FRAME], float (*float_prms)[_MAX_FLOAT_PARAMETERS], int (*int_prms)[_MAX_INT_PARAMETERS])
{
	for (uint j = 0; j < _MAX_COMMANDS_IN_FRAME; j++)
		(*cmd_types)[j] = command_types[j];
	for (uint j = 0; j < _MAX_COMMANDS_IN_FRAME; j++)
		(*cmd_codes)[j] = command_codes[j];
	for (uint j = 0; j < _MAX_INT_PARAMETERS; j++)
		(*int_prms)[j] = int_parameters[j];
	for (uint j = 0; j < _MAX_FLOAT_PARAMETERS; j++)
		(*float_prms)[j] = float_parameters[j]; 
}
void print_frame()
{
	if (parse_err == false)
	{
		Serial.print("Parse from serial port:\n");
		Serial.print("____________________________________________________________________\n");
		Serial.print("Commands: ");
		for (uint8_t j = 0; j < _MAX_COMMANDS_IN_FRAME; j++)
		{
			Serial.print(command_types[j]);
			Serial.print(command_codes[j]);
			Serial.print("\t");
		}
		Serial.print("\n\n");
		Serial.print("Float parameters: \n");
		Serial.print("X\t");
		Serial.print("Y\t");
		Serial.print("Z\t");
		Serial.print("F\t");
		Serial.print("S\t");
		Serial.print("R\t");
		Serial.print("I\t");
		Serial.print("J\t");
		Serial.print("K\t");
		Serial.print("\n");
		for (uint8_t j = 0; j < _MAX_FLOAT_PARAMETERS; j++)
		{
			Serial.print(float_parameters[j]);
			Serial.print("\t");
		}
		Serial.print("\n\n");
		Serial.print("Integer parameters: \n");
		for (uint8_t j = 0; j < _MAX_INT_PARAMETERS; j++)
		{
			Serial.print(int_parameters[j]);
			Serial.print("\t");
		}
		Serial.print("\n");
	}
}