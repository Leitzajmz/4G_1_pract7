#BIT dataDht = 0xF82.4             //pin de dato de entrada del DHT11 portc
#BIT dht_io = 0xF94.4  //bit 0 del tris b para ponerlo como entrada o salida
short timeOut;
void inicioDht11();
short respuesta();
unsigned int readData();
void inicioDht11(){
   dht_io = 0;  //configuracion del pin C4 como salida
   dataDht = 0;       //se encia un 0 al sensor
   delay_ms(18);
   dataDht = 1;
   delay_us(30);
   dht_io = 1;  //configuracion de pin C4 como entrada
}
short respuesta(){
   delay_us(40);
   if(!dataDht){                     // Read and test if connection pin is low
      delay_us(80);
      if(dataDht){                    // Read and test if connection pin is high
         delay_us(50);
         return 1;}
   }
}
unsigned int readData(){
   unsigned int i, k, data = 0;     // k is used to count 1 bit reading duration
   if(timeOut)
      break;
   for(i = 0; i < 8; i++){
      k = 0;
      while(!dataDht){                          // Wait until pin goes high
         k++;
         if (k > 100) {
            timeOut = 1; 
            break;
         }
         delay_us(1);
      }
      disable_interrupts(GLOBAL);
      delay_us(30);
      if(!dataDht)
         bit_clear(data, (7 - i));               // Clear bit (7 - i)
      else{
         bit_set(data, (7 - i));                 // Set bit (7 - i)
         while(dataDht){                         // Wait until pin goes low
            k++;
            if (k > 100) {timeOut = 1; break;}
               delay_us(1);}
      }
      enable_interrupts(GLOBAL);
   }
   return data;
}
