#include <avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>

#define Number_of_compare 1
unsigned char sec1=0;
unsigned char sec2=0;
unsigned char min1=0;
unsigned char min2=0;
unsigned char hour1=0;
unsigned char hour2=0;
unsigned char flag=0;
unsigned char sec=0;
unsigned char tick=0;
unsigned char mode=0;
unsigned char pause_flag=0;
unsigned char flag_toggel = 0;
unsigned char flag_sec_in = 0;
unsigned char flag_sec_d = 0;
unsigned char flag_min_in = 0;
unsigned char flag_min_d = 0;
unsigned char flag_hr_in = 0;
unsigned char flag_hr_d = 0;


void Timer1_comp(void){

	TCNT1=0;
	OCR1A=15625; //top value calculated
	TIMSK|=(1<<OCIE1A);

	TCCR1A = 0;
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10); //CTC, prescale 1024
}
ISR(TIMER1_COMPA_vect) //Functions for increment and decrement for display
{
	tick++;
	if(tick== Number_of_compare){
		tick=0;
		if(mode==0){
			 PORTD&=~(1<<PD0);
			PORTD&=~(1<<PD5);
			PORTD|=(1<<PD4);
		sec1++;
	if(sec1==10){
		sec1=0;
		sec2 ++;
	}

	if(sec2 == 6){
	        sec2 = 0;
	        min1++;
	    }
    if(min1 == 10){
        min1 = 0;
        min2++;
    }

    if(min2 == 6){
        min2 = 0;
        hour1++;
    }

    if(hour1 == 10){
        hour1 = 0;
        hour2++;
    }

    if(hour2 == 2 && hour1 == 4){
        hour2 = 0;
        hour1 = 0;
    }
		}
		else{
			PORTD&=~(1<<PD4);
			PORTD|=(1<<PD5);//active the yellow led
			if (sec1 > 0) {
			    sec1--;
			}
			else {
			    if (sec2 > 0) {
			        sec2--;
			        sec1 = 9;
			    }
			    else {
			        if (min1> 0) {
			            min1--;
			            sec2 = 5;
			            sec1 = 9;
			        }
			        else {
			            if (min2 > 0) {
			                min2--;
			                min1 = 9;
			                sec2 = 5;
			                sec1 = 9;
			            }
			            else {
			                if (hour1 > 0 || hour2 > 0) {
			                    if (hour1 > 0) hour1--;
			                    else { hour1 = 9; hour2--; }
			                    min2 = 5; min1 = 9;
			                    sec2 = 5; sec1 = 9;
			                }
			                else {

			                PORTD|=(1<<PD0);
			                }
			            }
			        }
			    }
			}






		}
	}


}
//////////////
void INT0_RESET(){
	GICR   |= (1<<INT0);
	MCUCR |= (1<<ISC01);   // falling edge for INT0
	MCUCR &= ~(1<<ISC00);

}
ISR(INT0_vect){
	tick=0;
	sec1=0;
	sec2=0;
	min1=0;
	min2=0;
	hour1=0;
	hour2=0;
	PORTD &= ~(1<<PD0); // clear buzzer
}
void INT1_PAUSE(){
	GICR|=(1<<INT1);

	MCUCR |= (1<<ISC10) | (1<<ISC11);
}
ISR(INT1_vect){
	pause_flag=1;

}
void INT2_RESUME(){
	GICR|=(1<<INT2);
	MCUCSR &= ~(1<<ISC2);
}
ISR(INT2_vect){
	pause_flag=0;
}
////////////////



void display_seven_segmant(void){
	PORTA|=(1<<0);
	PORTC=(PORTA&0xF0)|(sec1 & 0x0F);  //sec1 unit display
	_delay_ms(2);
	PORTA=0;
	PORTA|=(1<<1);
	PORTC=(PORTA&0xF0)|(sec2 & 0x0F); //sec2 tenth display
	_delay_ms(2);
	PORTA=0;
	PORTA|=(1<<2);
	PORTC=(PORTA&0xF0)|(min1 & 0x0F); //min1 unit display
	_delay_ms(2);
	PORTA=0;
	PORTA|=(1<<3);
	PORTC=(PORTA&0xF0)|(min2 & 0x0F); //min2 tenth display
	_delay_ms(2);
	PORTA=0;
	PORTA|=(1<<4);
	PORTC=(PORTA&0xF0)|(hour1 & 0x0F); //hour1 unit display
	_delay_ms(2);
	PORTA=0;
	PORTA|=(1<<5);
	PORTC=(PORTA&0xF0)|(hour2 & 0x0F); //hour2 tenth display
	_delay_ms(2);
	PORTA=0;
}
int main(){
	DDRC|=0x0F;//4 pins of the decoder
	PORTC&=0xF0;// 7-segment display zero at the beginning.
	DDRD&=(1<<PD2)&(1<<PD3);
	PORTD|=(1<<PD2);//activate the internal resistance
	DDRB&=~0xFF;//all buttoms
	PORTB|=0xFF;//activate the internal resistance
	DDRD|=(1<<PD0)|(1<<PD4)|(1<<PD5);//buzzer&2leds
	DDRA|=0x3F;//enable/disable pins for the six 7-segments
	PORTA=0x00;
	SREG  |= (1<<7);
	Timer1_comp();
	INT1_PAUSE();
	 INT2_RESUME();
	INT0_RESET();
	while(1){
		display_seven_segmant();
	if(!(PINB&(1<<PB7))){
		if(flag_toggel==0){
			mode^=1;
			flag_toggel=1;

		}

	}else{
			flag_toggel=0;
		}
//////
	if(mode){
		PORTD|=(1<<PD5);// active yellow led
		PORTD&=~(1<<PD4);
	}
	else{
		 PORTD&=~(1<<PD5);//active the red led
				 PORTD|=(1<<PD4);
	}

//////////
	if (pause_flag) // here i want to pause so i stopped the timer so no interrupts work
	{
		TIMSK&=~(1<<OCIE1A);
	}
	else{
		TIMSK|=(1<<OCIE1A);
	}

	if(pause_flag) //here this is the main event so i cant change in clock if not arealdy paused
	{
		if(!(PINB&(1<<PB1))) //hour increament
		{
			if(flag_hr_in==0){
				hour1++;
				if(hour1>9){
					hour1=0;
					hour2++;
				}
				if(hour2>2 ||(hour1>3 && hour2==2)){
					hour1=0;
					hour2=0;
				}
				flag_hr_in=1;
			}
		}

			else{
				flag_hr_in=0;

			}

		//////////
		  if(!(PINB & (1<<PB0))){
			            	 if(flag_hr_d==0){
			                 if(hour1==0 && hour2==0){
			                     hour2 = 2;
			                     hour1 = 3;
			                 } else
			                 {
			                     if(hour1==0){
			                         hour1=9;
			                         hour2--;
			                     } else {
			                        hour1--;
			                     }
			                 }
			                 flag_hr_d=1;
			            	 }
			             }
			             else{
			            	 flag_hr_d=0;
			             }

	//////////

		if(!(PINB&(1<<PB4))) //min increament
		{
			if(flag_min_in==0){
				min1++;
				if(min1>9){
					min1=0;
					min2++;
				}
				if(min2>5){
					min2=0;
				}
				flag_min_in=1;

			}
		}
		else{
			flag_min_in=0;
		}
		//////////
		if(!(PINB&(1<<PB3))) //min decrement
				{
					if(flag_min_d==0){
						if(min1==0 && min2==0){
							min1=9;
							min2=5;
						}
						else{
							if(min1==0){
								min1=9;
								if(min2>0) min2--;
							}
							else{
								min1--;
							}

						}
						flag_min_d=1;
					}
				}
				else{
					flag_min_d=0;
				}

	///////////////////

		if(!(PINB&(1<<PB6))) //seconds increament
		{
			if(flag_sec_in ==0){
				sec1++;
				if(sec1>9){
					sec1=0;
					sec2++;
				}
				if(sec2>5){
					sec2=0;
				}
				flag_sec_in =1;
			}

		}
		else{
			flag_sec_in =0;
		}

		//////////////
	if(!(PINB&(1<<PB5))) //seconds decreament
	{
		if(flag_sec_d==0){
			if(sec1==0 &&sec2==0){
				sec1=9;
				sec2=5;
			}
			else{
			if(sec1==0){
				sec1=9;
				sec2--;
			}
			else{
				sec1--;
			}
			}
			flag_sec_d=1;
		}

	}
	else{
		flag_sec_d=0;
	}


///////////////


}


}

	}


