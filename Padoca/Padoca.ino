#include "Padoca.h"

// Pins configurations.
// LCD pins.
const byte LCD_RS = 4;
const byte LCD_RW = 3;
const byte LCD_EN = 2;
const byte LCD_D4 = 18;
const byte LCD_D5 = 19;
const byte LCD_D6 = 20;
const byte LCD_D7 = 21;

// Rotary encoder (KY-040) pins.
const byte RENC_A = 0;
const byte RENC_B = 1;
const byte RENC_BUTTON = 5;

// Keypad configuration.
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
const byte KEYPAD_ROWS_PINS[KEYPAD_ROWS] = {15, 14, 16, 10};
const byte KEYPAD_COLS_PINS[KEYPAD_COLS] = {6, 7, 8, 9};
const byte KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'0', '1', '2', '3'},
  {'4','5','6', '7'},
  {'8', '9', 'a', 'b'},
  {'c','d','e', 'f'},
};


LiquidCrystal lcd(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Keypad keypad = Keypad(makeKeymap(KEYPAD_KEYS), KEYPAD_ROWS_PINS, KEYPAD_COLS_PINS, KEYPAD_ROWS, KEYPAD_COLS);
RotaryEncoder encoder(RENC_A, RENC_B);
Padoca padoca = Padoca(lcd, keypad, encoder, RENC_BUTTON);

Profile debug("Debug");
CommandText debug_0("button 0", "0");
CommandText debug_1("button 1", "1");
CommandText debug_2("button 2", "2");
CommandText debug_3("button 3", "3");
CommandText debug_4("button 4", "4");
CommandText debug_5("button 5", "5");
CommandText debug_6("button 6", "6");
CommandText debug_7("button 7", "7");
CommandText debug_8("button 8", "8");
CommandText debug_9("button 9", "9");
CommandText debug_a("button a", "a");
CommandText debug_b("button b", "b");
CommandText debug_c("button c", "c");
CommandText debug_d("button d", "d");
CommandText debug_e("button e", "e");
CommandText debug_f("button f", "f");

Profile work("Work");
CommandKey work_c("Meet Mic", 'd', COM_CTRL);
CommandKey work_d("Meet Camera", 'e', COM_CTRL);

void setup() {
  delay(3000);
    
  debug.AddCommand('0', &debug_0);
  debug.AddCommand('1', &debug_1);
  debug.AddCommand('2', &debug_2);
  debug.AddCommand('3', &debug_3);
  debug.AddCommand('4', &debug_4);
  debug.AddCommand('5', &debug_5);
  debug.AddCommand('6', &debug_6);
  debug.AddCommand('7', &debug_7);
  debug.AddCommand('8', &debug_8);
  debug.AddCommand('9', &debug_9);
  debug.AddCommand('a', &debug_a);
  debug.AddCommand('b', &debug_b);
  debug.AddCommand('c', &debug_c);
  debug.AddCommand('d', &debug_d);
  debug.AddCommand('e', &debug_e);
  debug.AddCommand('f', &debug_f);
  padoca.AddProfile(&debug);

  work.AddCommand('c', &work_c);
  work.AddCommand('d', &work_d);
  padoca.AddProfile(&work);
  
  padoca.Setup();
}

void loop() {
  padoca.Tick();
}
