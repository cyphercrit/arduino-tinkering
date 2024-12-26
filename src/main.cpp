#include <Arduino.h>
#include "Arduino_LED_Matrix.h"

#define BUTTON_PIN 5
#define MOTOR_FI_PIN 9
#define MOTOR_BI_PIN 10

ArduinoLEDMatrix matrix;

uint8_t forwardFrame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }
};

uint8_t backwardFrame[8][12] = {
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }
};

uint8_t standbyFrame[8][12] = {
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }
};

int current_setting = 0;

void setup() {
    pinMode(MOTOR_FI_PIN, OUTPUT);
    pinMode(MOTOR_BI_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.begin(9600);
    matrix.begin();
    matrix.renderBitmap(standbyFrame, 8, 12);
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == LOW) {
        current_setting = (current_setting + 1) % 3;
        delay(200);
    }

    switch (current_setting) {
        case 0:
            digitalWrite(MOTOR_FI_PIN, LOW);
            digitalWrite(MOTOR_BI_PIN, LOW);
            matrix.renderBitmap(standbyFrame, 8, 12);
            break;
        case 1:
            digitalWrite(MOTOR_FI_PIN, HIGH);
            digitalWrite(MOTOR_BI_PIN, LOW);
            matrix.renderBitmap(backwardFrame, 8, 12);
            break;
        case 2:
            digitalWrite(MOTOR_FI_PIN, LOW);
            digitalWrite(MOTOR_BI_PIN, HIGH);
            matrix.renderBitmap(forwardFrame, 8, 12);
            break;
    }
}