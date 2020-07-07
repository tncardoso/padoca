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

void setup() {
  delay(3000);
  
  Profile* debug = new Profile("Debug");
  debug->AddCommand('0', new CommandText("button 0", "0"));
  debug->AddCommand('1', new CommandText("button 1", "1"));
  debug->AddCommand('2', new CommandText("button 2", "2"));
  debug->AddCommand('3', new CommandText("button 3", "3"));
  debug->AddCommand('4', new CommandText("button 4", "4"));
  debug->AddCommand('5', new CommandText("button 5", "5"));
  debug->AddCommand('6', new CommandText("button 6", "6"));
  debug->AddCommand('7', new CommandText("button 7", "7"));
  debug->AddCommand('8', new CommandText("button 8", "8"));
  debug->AddCommand('9', new CommandText("button 9", "9"));
  debug->AddCommand('a', new CommandText("button a", "a"));
  debug->AddCommand('b', new CommandText("button b", "b"));
  debug->AddCommand('c', new CommandText("button c", "c"));
  debug->AddCommand('d', new CommandText("button d", "d"));
  debug->AddCommand('e', new CommandText("button e", "e"));
  debug->AddCommand('f', new CommandText("button f", "f"));
  padoca.AddProfile(debug);


  Profile* work = new Profile("Work");
  //work->AddCommand('c', new CommandKey("(Un)mute Mic", 'd', COM_CTRL));
  //work->AddCommand('d', new CommandKey("Camera", 'e', COM_CTRL));
  //work->AddCommand('e', new CommandText("button e", "e"));
  padoca.AddProfile(work);
  
  padoca.Setup();
}

void loop() {
  padoca.Tick();
}
