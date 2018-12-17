//
//***************************************************************************
#include "bcd.h"

//������ "����" ��� ������� 
#ifdef MIRROR_NULL_
  #define SYMB_NULL 48
#else
  #define SYMB_NULL 32
#endif

void BCD_1Lcd(unsigned char value)
{
    value += 48;
    LcdSendData(value);                  // ones
}

void BCD_2Lcd(unsigned char value)
{
    unsigned char high = 0;
    
    while (value >= 10)                 // Count tens
    {
        high++;
        value -= 10;
    }
    if (high) high += 48;
    else high = SYMB_NULL;
    LcdSendData(high);

    value += 48;
    LcdSendData(value);                  // Add ones
}


void BCD_3Lcd(unsigned char value)
{
    unsigned char high = 0;
    unsigned char flag = 0;
   
    if (value >= 100) flag = 48;   
    else flag = SYMB_NULL;
    while (value >= 100)                // Count hundreds
    {
        high++;
        value -= 100;
    }
    if (high) high += 48;
    else high = SYMB_NULL;
    LcdSendData(high );
    
    high = 0;
    while (value >= 10)                 // Count tens
    {
        high++;
        value -= 10;
    }
    if (high) high += 48;
    else high = flag;
    LcdSendData(high );
    
    value += 48;
    LcdSendData(value);                  // Add ones
}

void BCD_3IntLcd(unsigned int value)
{
    unsigned char high = 0;
    unsigned char flag = 0;
   
    if (value >= 100) flag = 48;   
    else flag = SYMB_NULL;
    while (value >= 100)                // Count hundreds
    {
        high++;
        value -= 100;
    }
    if (high) high += 48;
    else high = SYMB_NULL;
    LcdSendData(high );
    
    high = 0;
    while (value >= 10)                 // Count tens
    {
        high++;
        value -= 10;
    }
    if (high) high += 48;
    else high = flag;
    LcdSendData(high );
    
    value += 48;
    LcdSendData(value);                  // Add ones
}

void BCD_4IntLcd(unsigned int value)
{
    unsigned char high = 0;
    unsigned char flag = 0;
    unsigned char flag2 = 0;  
    
    
    if (value >= 1000) {flag = 48; flag2 = 48;}  
    else
    {
      if (value >= 100) {flag = SYMB_NULL; flag2 = 48;}
      else {flag = SYMB_NULL; flag2 = SYMB_NULL;}
    }
    
    while (value >= 1000)                // Count thousand
    {
        high++;
        value -= 1000;
    }
    if (high) high += 48;
    else high = SYMB_NULL;
    LcdSendData(high);
    
    high = 0;
    while (value >= 100)                // Count hundreds
    {
        high++;
        value -= 100;
    }
    if (high) high += 48;
    else high = flag;
    LcdSendData(high );
    
    
    high = 0;
    while (value >= 10)                 // Count tens
    {
        high++;
        value -= 10;
    }
    if (high) high += 48;
    else high = flag2;
    LcdSendData(high );
    
    value += 48;
    LcdSendData(value);  
}




