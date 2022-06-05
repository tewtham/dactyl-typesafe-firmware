#include <Arduino.h>

#include "./reader.h"
#include "./constants.h"
#include "./layout.h"

Reader_::Reader_() {}

uint8_t reader_columns [] = { NICE_COL_0, NICE_COL_1, NICE_COL_2, NICE_COL_3, NICE_COL_4, NICE_COL_5 };
uint8_t reader_rows [] = { NICE_ROW_0, NICE_ROW_1, NICE_ROW_2, NICE_ROW_3, NICE_ROW_4, NICE_ROW_5 };

void Reader_::init(void) {
  for (int i = 0; i < 5; i++) {
    pinMode(reader_columns[i], INPUT);
    pinMode(reader_rows[i], INPUT_PULLDOWN);
  }
  
  for (int col = 0; col < 5; col++) {
    pinMode(reader_columns[col], OUTPUT);
    for (int row = 0; row < 5; row++) {
      state[row][col] = digitalRead(reader_rows[row]) != LOW;
    }
    pinMode(reader_columns[col], INPUT);
    delayMicroseconds(10);
  }
}

uint32_t lastChange = 0;
void Reader_::updateState(void) {
  if(millis() - lastChange < DEBOUNCE_MS) return;
  
  for (int col = 0; col <= 5; col++) {
    pinMode(reader_columns[col], OUTPUT);
    for (int row = 0; row <= 5; row++) {
      bool value = digitalRead(reader_rows[row]) != LOW;
      if (value == state[row][col]) continue;

      Serial.print("changed (col row) ");
      Serial.print(col + 6, DEC);
      Serial.print(" ");
      Serial.println(row, DEC);

      // Layout manages both halves, so we need to offset by 6 for the right one
      if (value) {
        Layout.btnPress(row, col + 6);
      } else {
        Layout.btnRelease(row, col + 6);
      }

      state[row][col] = value;
      lastChange = millis();
    }
    pinMode(reader_columns[col], INPUT);
    delayMicroseconds(10);
  }
}

Reader_ Reader;
