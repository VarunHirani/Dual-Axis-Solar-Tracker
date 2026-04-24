#include <Servo.h>

Servo servoH;
Servo servoV;

// Servo pins
int pinH = 9;
int pinV = 10;

// LDR pins
int TL = A0;
int TR = A3;
int BL = A1;
int BR = A2;

int posH = 90;
int posV = 90;

// Tuning
int tolerance = 5;      
float smoothing = 0.15; 

float errH_f = 0;
float errV_f = 0;

int readLDR(int pin) {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / 5;
}

void setup() {
  servoH.attach(pinH);
  servoV.attach(pinV);

  servoH.write(posH);
  servoV.write(posV);

  Serial.begin(9600);
}

void loop() {
  int tl = readLDR(TL);
  int tr = readLDR(TR);
  int bl = readLDR(BL);
  int br = readLDR(BR);

  if (tl < 50) tl = tr;
  if (tr < 50) tr = tl;
  if (bl < 50) bl = br;
  if (br < 50) br = bl;

  int left   = (tl + bl) / 2;
  int right  = (tr + br) / 2;
  int top    = (tl + tr) / 2;
  int bottom = (bl + br) / 2;

  float errH = (right - left) * 100.0 / (left + right + 1);
  float errV = (bottom - top) * 100.0 / (top + bottom + 1);

  errH_f = (1 - smoothing) * errH_f + smoothing * errH;
  errV_f = (1 - smoothing) * errV_f + smoothing * errV;

  if (abs(errH_f) > tolerance) {
    int stepH = constrain(errH_f / 5, -4, 4);
    posH += stepH;
  }

  if (abs(errV_f) > tolerance) {
    int stepV = constrain(errV_f / 5, -4, 4);
    posV += stepV;
  }

  posH = constrain(posH, 20, 160);
  posV = constrain(posV, 50, 130);

  servoH.write(posH);
  servoV.write(posV);

  Serial.print("TL: "); Serial.print(tl);
  Serial.print(" TR: "); Serial.print(tr);
  Serial.print(" BL: "); Serial.print(bl);
  Serial.print(" BR: "); Serial.print(br);

  Serial.print(" | H: "); Serial.print(posH);
  Serial.print(" V: "); Serial.println(posV);

  delay(30);
}