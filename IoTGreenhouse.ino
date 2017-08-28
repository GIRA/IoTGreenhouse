#include <YunClient.h>
#include <ThingerYun.h>
#include <Stepper.h>
#define STEPS 48

//cables named 4 3 1 ??
Stepper stepper(STEPS, 3, 4,5,6);

ThingerYun thing("**", "**", "**");
bool pin13 = false;
bool pin8 = false;
bool pin9 = false;
bool pin10 = false;
bool pin11 = false;
bool stepping=false; 






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

  thing["D7"] >> [](pson & out) {
    out = digitalRead(7);
  };
  
  thing["A0"] >> [](pson & out) {
    out = analogRead(A0);
  };
  thing["A1"] >> [](pson & out) {
    out = analogRead(A1);
  };
  thing["A2"] >> [](pson & out) {
    out = analogRead(A2);
  };
  thing["A3"] >> [](pson & out) {
    out = analogRead(A3);
  };
    thing["A4"] >> [](pson & out) {
    out = analogRead(A4);
  };
  thing["A5"] >> [](pson & out) {
    out = analogRead(A5);
  };
}

// the loop function runs over and over again forever
void loop() {
  thing.handle();
  if(stepping ){
    stepper.step(30);

    }
}
