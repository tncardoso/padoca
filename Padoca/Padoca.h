#ifndef _PADOCA_H_
#define _PADOCA_H_

#include <ArduinoSTL.h>
#include <vector>

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Keyboard.h>
#include <RotaryEncoder.h>

#include "Profile.h"

const byte CUSTOM_CHAR_LOCKER[] = {
    B00000,
    B01110,
    B10001,
    B10001,
    B11111,
    B11011,
    B11011,
    B11111
};

const byte CUSTOM_CHAR_SCROLL[] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B11111,
    B01110,
    B00100
};

class Padoca {
    public:
        Padoca(LiquidCrystal& lcd, Keypad& keypad, RotaryEncoder& encoder, byte encoder_button_pin);
        void AddProfile(Profile* profile);
        void Setup();
        void Tick();

    private:
        void UpdateDisplay();
        void UpdateDisplayClick(char key, String name);

        LiquidCrystal& lcd_;
        Keypad& keypad_;
        RotaryEncoder& encoder_;
        byte encoder_button_pin_;
        std::vector<Profile*> profiles_;
        size_t current_profile_;
        int encoder_position_;
        int encoder_button_;
        bool encoder_profile_selector_;

};

#endif
