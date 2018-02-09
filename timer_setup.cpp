#include <Motor_driver\timer_setup.h>

#define OPT_SYSTEM_INTERNAL
#define OPT_BOARD_INTERNAL

void __attribute__((interrupt(), nomips16)) T3_IntHandler(void) {
	handle_pwm(TIMER3);
	IFS0CLR = 0x1000;
}


void __attribute__((interrupt(), nomips16)) T4_IntHandler(void) {
	handle_pwm(TIMER4);
	IFS0CLR = 0x10000;
}

void __attribute__((interrupt(), nomips16)) T5_IntHandler(void) {
	handle_pwm(TIMER5);
	IFS0CLR = 0x100000;
}

void initTimerISR(int timer, int prescalar, int period) {
	if (timer == TIMER3) {

		setIntVector(_TIMER_3_VECTOR, T3_IntHandler);


		T3CON = prescalar;
		TMR3 = 0;
		PR3 = period;

		IFS0CLR = 0x1000;
		IEC0SET = 0x1000;

		IPC3CLR = 0x0000001F;
		IPC3SET = (_T3_IPL_IPC << 2) | _T3_SPL_IPC;

		T3CONSET = 0x8000;
	}
	else if (timer == TIMER4) {

		setIntVector(_TIMER_4_VECTOR, T4_IntHandler);


		T4CON = prescalar;
		TMR4 = 0;
		PR4 = period;

		IFS0CLR = 0x10000;
		IEC0SET = 0x10000;

		IPC4CLR = 0x0000001F;
		IPC4SET = (_T4_IPL_IPC << 2) | _T4_SPL_IPC;

		T4CONSET = 0x8000;
	}
	else if (timer == TIMER5) {

		setIntVector(_TIMER_5_VECTOR, T5_IntHandler);


		T5CON = prescalar;
		TMR5 = 0;
		PR5 = period;

		IFS0CLR = 0x100000;
		IEC0SET = 0x100000;

		IPC5CLR = 0x0000001F;
		IPC5SET = (_T5_IPL_IPC << 2) | _T5_SPL_IPC;

		T5CONSET = 0x8000;
	}
}

void stopTimerISR(int timer) {

	if (timer == TIMER3) {
		IEC0CLR = 0x1000;
	}
	else if (timer == TIMER4) {
		IEC0CLR = 0x10000;
	}
	else if (timer == TIMER5) {
		IEC0CLR = 0x100000;
	}
}