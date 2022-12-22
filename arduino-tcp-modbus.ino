#include <SPI.h>
#include <Ethernet.h>

#include "Mudbus.h"


Mudbus Mb;

void setup()
{
  uint8_t mac[]     = { 0x90, 0xA2, 0xDA, 0x00, 0x51, 0x06 };
  uint8_t ip[]      = { 123, 45, 0, 101 };
  uint8_t gateway[] = { 123, 45, 0, 1 };
  uint8_t subnet[]  = { 255, 255, 255, 0 };
  Ethernet.begin(mac, ip, gateway, subnet);
  //Avoid pins 4,10,11,12,13 when using ethernet shield

  delay(5000);  //Time to open the terminal
  Serial.begin(9600);
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  Mb.R[2] = 1500;  
}

void loop()
{
  Mb.Run();
  
  Mb.R[0] = analogRead(A0);

  double Volts = double(Mb.R[0]) / 1023 * 5;
  Mb.R[1] = Volts * 1000;                     
  double Threshold = double(Mb.R[2]) / 1000; 
    
  //Analog outputs 0-255
  int Rescaled = map(Mb.R[0], 0, 1023, 0, 255);
  analogWrite(6, Rescaled);            

  //Digital outputs
  Mb.C[0] = Volts > Threshold;
  digitalWrite(7, Mb.C[0]);    
  
  Mb.C[1] = Volts < Threshold;
  digitalWrite(8, Mb.C[1]);                 


  delay(1000);
  Serial.print("A0=");
  Serial.print(Mb.R[0]);
  Serial.print("  Volts=");
  Serial.print(Volts);
  Serial.print("  Threshold=");
  Serial.print(Threshold);

  Serial.print(" additional val 1 =");
  Serial.print(Mb.R[3]);

  Serial.print(" additional val 2 =");
  Serial.print(Mb.R[4]);
  
  Serial.println("  ");

}


