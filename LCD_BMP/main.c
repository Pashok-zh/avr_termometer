

#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "LCD.h"
#include "lcd_lib_2.h"
#include "bcd.h"
#include "bmp280.h"




//#define DHT22       //если незакоментировано то считается что подключен датчик DHT22 иначе DHT11

#define DHT_PORT        PORTD
#define DHT_DDR         DDRD
#define DHT_PIN         PIND
#define DHT_BIT         2



// ========================================================================================================================
// BMP180
// ========================================================================================================================


// промежуточные переменные
 char	 press;

// ========================================================================================================================
// ========================================================================================================================



//======================================================================
//DHT22
//======================================================================

char buff [16];  //буфер дисплея
float h=0;
float t=0;
int hum=0;
char d;
uint8_t data[5]={0,0,0,0,0};




int read_dht_hum()   //функция чтения данных датчика DHT22
{

	unsigned char i,j;

	//=============MCU send START
	DHT_DDR|=(1<<DHT_BIT); //pin as output
	DHT_PORT&=~(1<<DHT_BIT); //0
	_delay_ms(18);
	DHT_PORT|=(1<<DHT_BIT); //1
	DHT_DDR&=~(1<<DHT_BIT); //pin as input
	//=============check DHT11 response
	_delay_us(50);
	if (DHT_PIN&(1<<DHT_BIT))
	{
		return 0;
	}
	_delay_us(80);
	if (!(DHT_PIN&(1<<DHT_BIT)))
	{
		return 0;
	}
	//===============receive 40 data bits
	while (DHT_PIN&(1<<DHT_BIT));
	for (j=0; j<5; j++)
	{
		data[j]=0;
		for(i=0; i<8; i++)
		{
			while (!(DHT_PIN&(1<<DHT_BIT)));
			_delay_us (30);
			if (DHT_PIN&(1<<DHT_BIT))
			data[j]|=1<<(7-i);
			while (DHT_PIN&(1<<DHT_BIT));
		}
	}

	return 1;

}

void dht_read()
{
	hum=0;
	asm("cli");
	hum = read_dht_hum();
	asm("sei");
	if(hum==1)
	{
		
		h =  (data[0]<<8);
		h = h + data[1];
		h = h/10;
		t =  (data[2]<<8);
		t = t + data[3];
		if(t<0) //если температура ниже 0
		{
			t = t+32768; //убираем лишнее
			t = -t; //преобразуем в отрицательную
		}
		t = t/10;
		
	}
}



void pr()
{
	dht_read();

	LCDstring("t-",0,0);
	
	dtostrf(t, 3, 1, buff);
	
	LCDstring(buff,2,0);

	LCDstring("H-",0,1);

	dtostrf(h, 3, 1, buff);

	LCDstring(buff,2,1);
}

void bm()
{
	
	bmp280_get_status();
	bmp280_measure();
	LCDstring("Press-",7,0);
	dtostrf(_bmp280_pres/133.322, 3, 0, &press);
	LCDstring(&press,13,0);
	
}

//==========================================================================
//==========================================================================

int main (void)

{

	LCDinit();
	bmp280_init();

	while(1)
	{
		pr();
		_delay_ms(2000);
		bm();
		//_delay_ms(2000);
	}
	return 0;
}

