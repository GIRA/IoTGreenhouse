#include <YunClient.h>
#include <ThingerYun.h>
#include <Stepper.h>
#define STEPS 48
//this is because i have some bug on the temperature calc.
#define temperatureDif 26

//layout:
//A0 = LDR
//A1 & A2 = therm.
//A3=switch
//D8 = R2
//D9 = R1
//D10 =Fan1
//D11 =Fan2
//D13 =onBoardLed
//Stepper: D3,D4,D5,D6 cables named 4 3 1 ??
Stepper stepper(STEPS, 3, 4,5,6);

ThingerYun thing("****", "****", "****");
bool pin13 = false;
bool pin8 = false;
bool pin9 = false;
bool pin10 = false;
bool pin11 = false;
bool stepping=false; 

const int numReadings = 20;
int current=0;
int A0readings[numReadings];
int A1readings[numReadings];
int A2readings[numReadings];

float A0avg=0.0;
float A1avg=0.0;
float A2avg=0.0;

float avg(int* values)
{
  float total=0.0;
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    total += values[thisReading];
  }
  return total/numReadings;
  
}

double toDegrees(float RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1)));  //for pull-down configuration
 //Temp =log(10000.0/(1024.0/RawADC-1)); // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 
 return Temp + temperatureDif;
}

void setup() {
  Bridge.begin();
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(7, INPUT);
  stepper.setSpeed(30);

thing["Stepping"] << [](pson & in) {
    if (in.is_empty()) {
      in = stepping;
    } else {
      stepping= in;
    }
  };  
  thing["D13"] << [](pson & in) {
    if (in.is_empty()) {
      in = pin13;
    } else {
      pin13 = in;
    }
    digitalWrite(13, pin13 ? HIGH : LOW);
  };
thing["D8"] << [](pson & in) {
    if (in.is_empty()) {
      in = pin8;
    } else {
      pin8 = in;
    }
    digitalWrite(8, pin8 ? HIGH : LOW);
  };
thing["D9"] << [](pson & in) {
    if (in.is_empty()) {
      in = pin9;
    } else {
      pin9 = in;
    }
    digitalWrite(9, pin9 ? HIGH : LOW);
  };
thing["D10"] << [](pson & in) {
    if (in.is_empty()) {
      in = pin10;
    } else {
      pin10 = in;
    }
    digitalWrite(10, pin10 ? HIGH : LOW);
  };

thing["D11"] << [](pson & in) {
    if (in.is_empty()) {
      in = pin11;
    } else {
      pin11 = in;
    }
    digitalWrite(11, pin11 ? HIGH : LOW);
  };

 
  
  thing["A0"] >> [](pson & out) {
    out = A0avg;
  };
  thing["A1"] >> [](pson & out) {
    out = toDegrees( A1avg);
  };
  thing["A2"] >> [](pson & out) {
    out = toDegrees(A2avg);
  };
  thing["A3"] >> [](pson & out) {
    out = (analogRead(A3)>512);
  };
  
}

// the loop function runs over and over again forever
void loop() {
  A0readings[current]=analogRead(A0);
  A1readings[current]=analogRead(A1);
  A2readings[current]=analogRead(A2);
  current++;
  current%=numReadings;
  
  A0avg=avg(A0readings);
  A1avg=avg(A1readings);
  A2avg=avg(A2readings);
  thing.handle();
  if(stepping ){
    stepper.step(30);
    }
}
