#ifndef _PADOCA_H_
#define _PADOCA_H_

#include <ArduinoSTL.h>
#include <vector>

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Keyboard.h>
#include <RotaryEncoder.h>

#include "Profile.h"

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

};

#endif
