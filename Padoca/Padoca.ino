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
  debug->AddCommand('0', new CommandText("0", "0"));
  /*
    .AddCommand('1', new CommandText("1", "1"))
    .AddCommand('2', new CommandText("2", "2"))
    .AddCommand('3', new CommandText("3", "3"))
    .AddCommand('4', new CommandText("4", "4"))
    .AddCommand('5', new CommandText("5", "5"))
    .AddCommand('6', new CommandText("6", "6"))
    .AddCommand('7', new CommandText("7", "7"))
    .AddCommand('8', new CommandText("8", "8"))
    .AddCommand('9', new CommandText("9", "9"))
    .AddCommand('a', new CommandText("a", "a"))
    .AddCommand('b', new CommandText("b", "b"))
    .AddCommand('c', new CommandText("c", "c"))
    .AddCommand('d', new CommandText("d", "d"))
    .AddCommand('e', new CommandText("e", "e"))
    .AddCommand('f', new CommandText("f", "f"));*/
  padoca.AddProfile(debug);
  // 

  padoca.Setup();
}

void loop() {
  padoca.Tick();
}
