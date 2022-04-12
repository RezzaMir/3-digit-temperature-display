
int transistor1 = 5;    
int transistor2 = 4;  
int transistor3 = 3;  
int outputenable=10;    
int clockPin=13;   
int dataPin=12;  
int latch=7;
int sensorValue;  
int celc;
int Remainder;
int CENTS1;    
int CENTS2;
int CENTS3;   

// Done Initializing


// The array
int outbuff[10] = {0xC0,0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x98};
void setup() {


//Outputs
pinMode(clockPin,OUTPUT);
pinMode(dataPin, OUTPUT);  
pinMode(transistor1, OUTPUT); 
pinMode(transistor2, OUTPUT);  
pinMode (outputenable, OUTPUT);  
pinMode(transistor3, OUTPUT);  
analogReference(EXTERNAL);  
}


void loop() {
  
// Set up sensor
sensorValue = analogRead(A3);  
  
  Serial.begin(9600);
  Serial.print("sensor= ");
  Serial.println(sensorValue);

delay(10);  

float CENTS = (sensorValue/1023.0*2-.5)*100; 
    Serial.print("CENTS= ");
    Serial.println(CENTS);

      {
      int CENTS1 = CENTS/100;  
      Remainder=int (CENTS)%100;
      CENTS2=Remainder/10;    
      CENTS3=Remainder%10;  
      if( CENTS < 0) 
      {   
      CENTS2 = -(CENTS2);
      }

      digitalWrite(latch,LOW);
      if ( CENTS<0)
      {
      shiftOut(dataPin,clockPin,MSBFIRST, B10111111);
      }

      else 
      {
      shiftOut(dataPin, clockPin,MSBFIRST,outbuff[CENTS1]);

      }

// For digits

digitalWrite(latch,HIGH);  
digitalWrite(outputenable,LOW);  
digitalWrite(transistor1,LOW);  
delay(5);   

digitalWrite(transistor1,HIGH);  
digitalWrite(outputenable,HIGH);  
digitalWrite(latch,LOW);  

shiftOut(dataPin, clockPin,MSBFIRST,outbuff[CENTS2]); 
digitalWrite(latch,HIGH);  
digitalWrite(outputenable,LOW);
digitalWrite(transistor2,LOW);
delay(5);  

digitalWrite(transistor2,HIGH);
digitalWrite(outputenable,HIGH);
digitalWrite(latch,LOW);  
shiftOut(dataPin, clockPin,MSBFIRST,outbuff[CENTS3]); 

digitalWrite(latch,HIGH);   
digitalWrite(outputenable,LOW);  
digitalWrite(transistor3,LOW);    
delay(5);  

digitalWrite(transistor3,HIGH);   
digitalWrite(outputenable,HIGH);
delay(5);
}
}
