#include <SPI.h>
#include "RF24.h"
#include <string.h>

RF24 radio(7, 8); // CE, CSN
byte addresses[][6] = {"0"};
//const char text[] = "Hello World";

struct package
{
  int i=0;
  char c;
  boolean b;
  double d;
};

typedef struct package Package;
Package data;

char cadena[30]; 
byte posicion=0;
char *token;
const char delimiter[1] = " ";
int aux;

void setup() {
  Serial.begin(115200);
  delay(100);
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate( RF24_250KBPS ) ;
  radio.openWritingPipe(addresses[0]);
  //radio.printDetails();
  delay(500);
}

void loop() {
  if(Serial.available())
  {
    memset(cadena, 0,sizeof(cadena));
 
    while(Serial.available()>0)
    {
      delay(5);
      cadena[posicion]=Serial.read();      
      posicion++;      
    }

    token = strtok(cadena, delimiter);
    data.i = atoi(token);
    Serial.println(data.i);

    token = strtok(NULL, delimiter);
    data.c = token[0];
    Serial.println(data.c);

    token = strtok(NULL, delimiter);
    aux = atoi(token);
    if ( aux == 1)
    {
      data.b = true;
    }
    else
    {
      data.b = false;
    }
    Serial.println(data.b);

    token = strtok(NULL, delimiter);
    data.d = atof(token);
    Serial.println(data.d);
    
    posicion=0;
  }

  radio.write(&data, sizeof(data));
  delay(1000);
}
