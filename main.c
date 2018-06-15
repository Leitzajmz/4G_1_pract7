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
short flagUp = 0x00;
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

//Functions prototypes
void portbChange();
#INT_RB
void interrupt_isr(void){     
   if(__UP__ == 0x01){
      flagUp = 0x01;
   }
   else if(__DOWN__ == 0x01){
      flagDown = 0x01;
   }
   else if(__ENTER__ == 0x01){
      flagEnter = 0x01;
   }
   else if(__BACK__ == 0x01){
      flagBack = 0x01;
   }
}
void main (void){
   setup_oscillator(OSC_16MHZ);
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
   set_tris_a(0x03);
   set_tris_d(0x00);
   set_tris_c(0xff);
   set_tris_b(0xF0);
   output_low(PIN_B0);
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   while(1){
      
   }
}   

void portbChange(){
   if(flagUp==1){
      if(flagSettings==0){
         if(posicionMenu==4)
            posicionMenu=1;
         else
            posicionMenu++;
      }
      else{
         if(flagConfSerial == 1){
            if(auxiliarTS==100)
               auxiliarTS=5000;
            else
               auxiliarTS-=100;
         }
         else if(flagUpdate == 1){
            if(auxiliarLCD == 100)
               auxiliarLCD = 2000;
            else
               auxiliarLCD-=100;
         }            
         else if(flagAlarm == 1){
            if(flagTemperature==1){
               if(auxiliarAT==1)
                  auxiliarAT=49;
               else
                  auxiliarAT-=1;                     
            }
            if(flagHumidity==1){
               if(auxiliarAH==21)
                  auxiliarAH=94;
               else
                  auxiliarAH-=1;
            }
            if(flagLpg==1){
               if(auxiliarALPG==300)
                  auxiliarALPG=10000;
               else
                  auxiliarALPG-=1;
            }
            if(flagAlcohol==1){
               if(auxiliarAA==300)
                  auxiliarAA=10000;
               else
                  auxiliarAA-=1;
            }
            if(posicionMenu==4)
               posicionMenu=1;
            else
               posicionMenu++;
         }
         else{
            if(posicionMenu==3)
               posicionMenu=1;
            else
               posicionMenu++;
         }      
      }
      printf(lcd_putc,"\f");
      flagUp = 0x00;
   }
      
      if(flagDown==1){
         if(flagSettings==0){
            if(posicionMenu==1)
               posicionMenu=4;
            else
               posicionMenu--;
         }
         else{
            if(flagConfSerial == 1){
               if(auxiliarTS==5000)
                  auxiliarTS=100;
               else
                  auxiliarTS+=100;
            }
            else if(flagUpdate == 1){
               if(auxiliarLCD == 2000)
                  auxiliarLCD = 100;
               else
                  auxiliarLCD+=100;
            }
            else if(flagAlarm == 1){
               if(flagTemperature==1){
                  if(auxiliarAT==49)
                     auxiliarAT=1;
                  else
                     auxiliarAT+=1;
               }
               if(flagHumidity==1){
                  if(auxiliarAH==94)
                     auxiliarAH=21;
                  else
                     auxiliarAH+=1;
               }
               if(flagLpg==1){
                  if(auxiliarALPG==10000)
                     auxiliarALPG=300;
                  else
                     auxiliarALPG+=1;
               }
               if(flagAlcohol==1){
                  if(auxiliarALPG==10000)
                     auxiliarALPG=300;
                  else
                     auxiliarALPG+=1;
               }
               if(posicionMenu==1)
                  posicionMenu=4;
               else
                  posicionMenu--;
            }
            else{
               if(posicionMenu==1)
                  posicionMenu=3;
               else
                  posicionMenu--;
            }  
         }
         printf(lcd_putc,"\f");
         flagDown = 0x00;
      }
      
      if(flagEnter == 1){
         if(flagSettings == 1){//Si el menu de configuraciones habilitado
            if(flagConfSerial==0 && flagUpdate==0 && flagAlarm==0){
               switch(posicionMenu){//Depende en la posicion donde se encuentre
                                    //Se habilitara el siguiente menu.
                  case 1:
                     flagConfSerial=1;
                  break;
                  case 2:
                     flagUpdate=1;
                  break;
                  case 3:
                     flagAlarm=1;
                     posicionMenu=1;//Reseteo el contador para el menu alarmas
                  break;
               }
            }
            else{
               if(flagConfSerial == 1){//Checo si esta dentro de la confSerial
                  serialTime = auxiliarTS;//Guardo el cambio
               }
               if(flagUpdate == 1){//Checo si esta entro de la confUpdateLCD
                  lcdTime = auxiliarLCD;//Guardo el cambio
               }
               if(flagAlarm == 1){//Checo si esta dentro de la confAlarma
                  if(flagTemperature==0 && flagHumidity==0 
                          && flagLpg==0 && flagAlcohol==0){
                     switch(posicionMenu){
                        case 1:
                           flagTemperature = 1;
                        break;
                        case 2:
                           flagHumidity = 1;
                        break;
                        case 3:
                           flagLpg = 1;
                        break;
                        case 4:
                           flagAlcohol = 1;
                        break;
                     }
                  }
                  else{
                     if(flagTemperature==1){
                        temperatureAlarm = auxiliarAT;
                     }
                     if(flagHumidity==1){
                        humidityAlarm = auxiliarAH;
                     }
                     if(flagLpg==1){
                        lpgAlarm = auxiliarALPG;
                     }
                     if(flagAlcohol==1){
                        alcoholAlarm = auxiliarAA;
                     }
                  }
               }
            }
          }        
         if(flagSettings == 0){//SI el menu de configuraciones no esta mostrandose
            flagSettings = 1;//Tons lo muestro.
            posicionMenu=1;//Reseteo el contador del menu
         }
         printf(lcd_putc,"\f");//Limpar la pantalla en cada cambio.
         flagEnter = 0x00;
      }
      if(flagBack == 1){
         if(flagSettings == 1){//Si el menu de configuraciones habilitado
            if(flagConfSerial == 1){//Checo si esta dentro de la confSerial
               flagConfSerial=0;;//Guardo el cambio
            }
            else if(flagUpdate == 1){//Checo si esta entro de la confUpdateLCD
               flagUpdate = 0;//Guardo el cambio
            }
            else if(flagAlarm == 1){//Checo si esta dentro de la confAlarma
               if(flagTemperature==1)
                  flagTemperature = 0;
               else if(flagHumidity==1)
                  flagHumidity = 0;
               else if(flagLpg==1)
                  flagLpg = 0;
               else if(flagAlcohol==1)
                  flagAlcohol = 0;
               else{
                  flagAlarm = 0;
                  posicionMenu=1;
               }
            }
            else {
               flagSettings = 0;//Tons lo muestro.
               posicionMenu=1;//Reseteo el contador del menu
            }
          }
         printf(lcd_putc,"\f");//Limpar la pantalla en cada cambio.
         flagBack = 0x00;
      }
}
