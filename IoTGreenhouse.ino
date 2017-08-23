#include <YunClient.h>
#include <ThingerYun.h>

ThingerYun thing("****", "****", "****");
bool pin13 = false;

void setup() {
  Bridge.begin();
  pinMode(13, OUTPUT);

  pinMode(7, INPUT);
  thing["led"] << [](pson & in) {
    if (in.is_empty()) {
      in = pin13;
    } else {
      pin13 = in;
    }
    digitalWrite(13, pin13 ? HIGH : LOW);
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
}
