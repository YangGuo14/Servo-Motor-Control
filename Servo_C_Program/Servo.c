#include <avr/io.h>
#include <util/delay.h>

#define __DELAY_BACKWARD_COMPATIBLE__

/* This is the Design By Contract macros.*/
#define DBC // Can turn off these macros by commenting out this line
#ifdef DBC
/* needs to be at main since we are going to use Pin13 as our LED to warn us on assert fails */
#define DBC_SETUP() \
	/* turn on Pin 13 as we will use to indicate assertion/error failed */ \
	DDRB |= _BV(DDB5); 

#define PRE_CONDITION_DBC(eval_expression, time_blink_delay) \
	while (!(eval_expression))  \
	{ \
		PORTB |= _BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
		PORTB &= ~_BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
	}

#define POST_CONDITION_DBC(eval_expression, time_blink_delay) \
	while (!(eval_expression))  \
	{ \
		PORTB |= _BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
		PORTB &= ~_BV(PORTB5); \
		/* half the delay off on post condition */ \
		my_delay_ms(time_blink_delay/2); \
	}
#elif
/* These are empty for when turned off */
#define DBC_SETUP() {}
#define PRE_CONDITION(eval_expression, time_blink_delay) {}
#define POST_CONDITION(eval_expression, time_blink_delay) {}
#endif

#define SECOND_IN_ms 1000
#define MY_BUTTON1 PD7 
#define MY_BUTTON2 PD6 

void pwm_setup();
void pwm_0();
void pwm_180();

short check_button_press_and_release(int button);
void my_delay_ms( unsigned int delay);


void main()
{
	DBC_SETUP();
	pwm_setup();
	while(1)
	{
		while(1)
		{
			if(check_button_press_and_release(MY_BUTTON1))
				break;
			pwm_0();  //0 degree
	}
      			
		while(1)
		{
			if(check_button_press_and_release(MY_BUTTON2))
				break;
			pwm_180();   //180 degree
		}
	}
}

void pwm_setup()
{
	//Configure TIMER1
	ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).
	OCR1A = 0;
	OCR1B = 0;

	// set none-inverting mode
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
	// set Fast PWM mode using ICR1 as TOP - MODE 14
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
    
	// START the timer with no prescaler
	TCCR1B |= (1 << CS10);

	DDRD|=(1<<PD4);//PWM Pins as Out
}

void pwm_0()
{
	if (check_button_press_and_release(MY_BUTTON1))
	{
		OCR1B = 97;
	}
}

void pwm_180()
{
	if (check_button_press_and_release(MY_BUTTON2))
	{
		OCR1A = 425;
	}
}

/* 
 * checks when a button on the D port is pressed assuming a pull-down in non-pressed state 
 * 
 * WIRING: input and resitor on same connection, Vcc on other connection
 */
short check_button_press_and_release(int button)
{
	int ret_val = 0;

	PRE_CONDITION_DBC(button >= 0, 6000);
	PRE_CONDITION_DBC(button < 8, 7000);

	if ((PIND & (1 << button)) != 0)
	{
		/* software debounce */
		_delay_ms(15);
		if ((PIND & (1 << button)) != 0)
		{
			/* wait for button to be released */
			while((PIND & (1 << button)) != 0)
				ret_val = 1;
		}
	}

	POST_CONDITION_DBC(ret_val == 1 || ret_val == 0, 5000);

	return ret_val;
}


/* 
 * Handles larger delays the _delay_ms can't do by itself (not sure how accurate)  
 * Note no DBC as this function is used in the DBC !!! 
 *
 * borrowed from : https://www.avrfreaks.net/forum/delayms-problem 
 * */
void my_delay_ms(unsigned int delay) 
{
	unsigned int i;

	for (i=0; i<(delay/10); i++) 
	{
		_delay_ms(10);
	}
	for (i=0; i < delay % 10; i++) 
	{
		_delay_ms(1);
	}
}
