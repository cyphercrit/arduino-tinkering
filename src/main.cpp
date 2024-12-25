#include <Arduino.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

void setup() {
    matrix.begin();
}


uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void loop() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 12; j++) {
            frame[i][j] = 1;
            frame[j][i] = 1;
            matrix.renderBitmap(frame, 8, 12);
            delay(50);
            frame[i][j] = 0;
            frame[j][i] = 0;
            matrix.renderBitmap(frame, 8, 12);
        }
    }
}