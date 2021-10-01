#define F_CPU 8000000UL

#include <avr/io.h>

void PORT_INIT(void);
void TIMER_INIT(void);

int main(void){
	PORT_INIT();
	TIMER_INIT();
	
	uint8_t duty_cycle = 25;				///< Variable to hold the duty cycle of the PWM signal.
	
	OCR1A = 100*duty_cycle;					///< Set OCR1A to generate ON time of PWM signal according to required duty cycle.
}

/*!
 *	@brief Initialize Ports.
 */

void PORT_INIT(void){
	DDRD |= (1<<PD5);					///< Set OC1A as output to generate PWM signal.
}

/*!
 *	@brief Initialize timer/counter1 to generate a 50 Hz Phase Correct PWM signal at OC1A.
 */

void TIMER_INIT(void){
	TCCR1A = (1<<COM1A1)|(1<<WGM11);			///< Select Phase Correct PWM mode with ICR1 as TOP. Clear OC1A on compare match and Set OC1A at BOTTOM (non-inverting mode).
	TCCR1B = (1<<WGM13)|(1<<CS11);				///< Select Phase Correct PWM mode with ICR1 as TOP and set prescalar value of 8.
	ICR1 = 9999;						///< Set TOP value to determine frequency of the PWM signal.
}
