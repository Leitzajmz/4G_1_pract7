#include <18F4620.h>
#device adc=10 
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#define lcd_rs_pin pin_d0
#define lcd_rw_pin pin_d1
#define lcd_enable_pin pin_d2
#define lcd_data4 pin_d4
#define lcd_data5 pin_d5
#define lcd_data6 pin_d6
#define lcd_data7 pin_d7 
#include <LCD.C>
#include "dht.h"

#define TX_232        PIN_C6
#define RX_232        PIN_C7
#use RS232(BAUD=9600, XMIT=TX_232, RCV=RX_232, BITS=8,PARITY=N, STOP=1)

#define __UP__ pin_b4
#define __DOWN__ pin_b5
#define __ENTER__ pin_b6
#define __BACK__   pin_b7

#define ledTemperatura pin_b0
#define ledHumedad pin_b1
#define ledLPG pin_b2
#define ledAlcohol pin_b3

int posicionMenu=1;
long actualizacionLCD=100;
long actualizacionSerial=100;
                                 
short flagMessage = 0x00;
short flagSettings = 0x00;
short flagConfSerial = 0x00;
short flagUpdate = 0x00;
short flagAlarm = 0x00;
short flagTemperature = 0x00;
short flagHumidity = 0x00;
short flagLpg = 0x00; 
short flagAlcohol = 0x00; 
short flagUP = 0x00;
short flagDown = 0x00;
short flagEnter = 0x00;
short flagBack = 0x00;

//Update Time 
long serialTime = 100; long auxiliarTS = 100;
long lcdTime = 100;    long auxiliarLCD = 100;

//Alarms
int temperatureAlarm = 30; int auxiliarAT = 30;
int humidityAlarm = 30;  int auxiliarAH = 30;
long lpgAlarm = 300; long auxiliarALPG = 300;
long alcoholAlarm = 300; long auxiliarAA=300;

int temperature=0;
int humidity=0;
long GasX=0; //LPG
long GasY=0; //Alcohol

void main (void){
   setup_oscillator(OSC_16MHZ);
   while(1){
      
   }
}   
