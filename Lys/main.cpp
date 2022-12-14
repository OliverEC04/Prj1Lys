#define F_CPU 16000000
#include <util/delay.h>
#include "Headers/uart.h"
#include "Headers/mma8652.h"

#include "Headers/LedDriver.h"

#include "Headers/DriveLight.h"
extern DriveLight driveLight;

#include "Headers/CrownLight.h"
extern CrownLight crownLight;

#include "Headers/Motor.h"
extern Motor M;

#include "Headers/Timer.h"
extern Timer T;

#include "Headers/Position.h"
extern Position P;

#include "Headers/Speaker_driver.h"
extern Speaker_driver S;

int main(void)
{		
	InitUART(9600,8);
	initAcc();
	DDRA &= ~(1<<5);
	sei();
	int time = 0;
	
	S.initSpeakerdriver();
	
	while (1)
	{
		while (PINA & (1<<5))
		{
		}
		M.setSpeed(100,2);
		S.StartSound();
		driveLight.drive();
		
		PORTB |= (1<<0);
		while (P.getPosition() < 1)
		{
		}
		PORTB |= (1<<1);
		while (P.getPosition() < 2)
		{
		}
		M.setSpeed(50,1);
		driveLight.brake(10);
		time = T.getTime();
		PORTB |= (1<<2);
		while (AccY() > -40) //-320    320
		{
		}
		M.setSpeed(100,0);
		TCNT3 = 0;
		time = T.getTime();
		PORTB |= (1<<3);
		while (T.getTime() > (time+2))
		{
		}
		M.setSpeed(-100,0);
		driveLight.brake(0);
		TCNT3 = 0;
		time = T.getTime();
		while (T.getTime() > (time+3))
		{
		}
		M.setSpeed(30,2);
		while (AccY() > -320) //-320    320
		{
		}
		M.setSpeed(90,3);
		PORTB |= (1<<4);
		while (P.getPosition() < 3)
		{
		}
		M.setSpeed(30,3);
		PORTB |= (1<<5);
		while (P.getPosition() < 4)
		{
		}
		M.setSpeed(100,2);
		PORTB |= (1<<6);
		while (P.getPosition() < 5)
		{
		}
		time = T.getTime();
		PORTB |= (1<<7);
		while (T.getTime() > (time+10))
		{
		}
		M.setSpeed(50,1);
		while (P.getPosition() < 6)
		{
		}
		M.setSpeed(-100,3);
		while (P.getPosition() < 7)
		{
		}
		time = T.getTime();
		while (T.getTime() > (time+10))
		{
		}
		M.setSpeed(-50,1);
		while (P.getPosition() < 8)
		{
		}
		M.setSpeed(100,3);
		while (P.getPosition() < 11)
		{
		}
		time = T.getTime();
		while (T.getTime() > (time+15))
		{
		}
		M.setSpeed(0,2);
		S.EndSound();
		/*time = T.getTime();
		
		time = T.getTime();
		while (T.getTime() > (time+50))
		{
		}
		M.setSpeed(0,1);
		driveLight.brake(10);*/
		
	}
	return 0;
}