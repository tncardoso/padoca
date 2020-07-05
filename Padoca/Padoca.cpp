#include "Padoca.h"

Padoca::Padoca(LiquidCrystal& lcd, Keypad& keypad, RotaryEncoder& encoder, byte encoder_button_pin):
    lcd_(lcd),
    keypad_(keypad),
    encoder_(encoder),
    encoder_button_pin_(encoder_button_pin),
    current_profile_(0),
    encoder_position_(0) {
}

void Padoca::AddProfile(Profile* profile) {
    profiles_.push_back(profile);
}

void Padoca::Setup() {
    Keyboard.begin();
    pinMode(encoder_button_pin_, INPUT);
    encoder_button_  = digitalRead(encoder_button_pin_);
    
    lcd_.begin(16, 2);
    lcd_.noBlink();
    UpdateDisplay();
}

void Padoca::Tick() {
    encoder_.tick();

    int new_encoder_button = digitalRead(encoder_button_);
    if (new_encoder_button != encoder_button_ && new_encoder_button == 0) {
        // pressed encoder button
    }
    
    int new_encoder_position = encoder_.getPosition();
    if (new_encoder_position != encoder_position_) {
        encoder_position_ = new_encoder_position;

        // changed profile
        current_profile_ = abs(encoder_position_) % profiles_.size();
        UpdateDisplay();
    }

    char key = keypad_.getKey();
    if (key != NO_KEY) {
        // keypad key pressed
        // Keyboard.print(key);
        profiles_[current_profile_]->Click(key);
    }
}

void Padoca::UpdateDisplay() {
    lcd_.clear();
    lcd_.setCursor(0, 0);
    lcd_.print("[");
    if (current_profile_ < 10) { lcd_.print("0"); }
    lcd_.print(current_profile_);
    lcd_.print("] ");
    lcd_.print(profiles_[current_profile_]->name());

}