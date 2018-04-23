#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
byte addresses[][6] = {"0"};

struct package
{
  int i=0;
  char c;
  boolean b;
  double d;
};

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(115200);
  delay(100);
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate( RF24_250KBPS ) ;
  radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
  delay(500);
}

void loop() {
  if(radio.available())
  {
    while(radio.available())
    {
      radio.read( &data, sizeof(data) );
    }
  }
  
  Serial.println(data.i);
  Serial.println(data.c);
  Serial.println(data.b);
  Serial.println(data.d);
  delay(1000);
}
