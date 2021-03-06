#include "Padoca.h"

Padoca::Padoca(LiquidCrystal& lcd, Keypad& keypad, RotaryEncoder& encoder, byte encoder_button_pin):
    lcd_(lcd),
    keypad_(keypad),
    encoder_(encoder),
    encoder_button_pin_(encoder_button_pin),
    current_profile_(0),
    encoder_position_(0),
    encoder_profile_selector_(true){
}

void Padoca::AddProfile(Profile* profile) {
    profiles_.push_back(profile);
}

void Padoca::Setup() {
    Keyboard.begin();
    pinMode(encoder_button_pin_, INPUT_PULLUP);
    encoder_button_  = digitalRead(encoder_button_pin_);
    
    lcd_.begin(16, 2);
    lcd_.noBlink();
    lcd_.createChar(0, CUSTOM_CHAR_LOCKER);
    lcd_.createChar(1, CUSTOM_CHAR_SCROLL);
    UpdateDisplay();
}

void Padoca::Tick() {
    encoder_.tick();

    int new_encoder_button = digitalRead(encoder_button_pin_);
    if (new_encoder_button == 1 && encoder_button_ == 0) {
        // pressed encoder button
        encoder_profile_selector_ = !encoder_profile_selector_;
        UpdateDisplay();
    }
    encoder_button_ = new_encoder_button;
    
    int new_encoder_position = encoder_.getPosition();
    int dir = new_encoder_position - encoder_position_;
    if (new_encoder_position != encoder_position_) {
        encoder_position_ = new_encoder_position;

        if (encoder_profile_selector_) {
          // changed profile
          current_profile_ = abs(encoder_position_) % profiles_.size();
          UpdateDisplay();
        } else {
          // used scroll
            char scroll_key = '-';
          if (dir > 0) {
            scroll_key = '+';
          }
          
          String name = profiles_[current_profile_]->Click(scroll_key);
          UpdateDisplayClick(scroll_key, name);
        }
    }

    char key = keypad_.getKey();
    if (key != NO_KEY) {
        // keypad key pressed
        String name = profiles_[current_profile_]->Click(key);
        UpdateDisplayClick(key, name);
    }
}

void Padoca::UpdateDisplay() {
    lcd_.clear();
    lcd_.setCursor(0, 0);
    lcd_.print("[");
    if (current_profile_ < 10) { lcd_.print("0"); }
    lcd_.print(current_profile_);
    lcd_.print("][");
    if (encoder_profile_selector_) {
      lcd_.write(static_cast<uint8_t>(0));
    } else {
      lcd_.write(static_cast<uint8_t>(1));
    }
    lcd_.print("] ");
    lcd_.print(profiles_[current_profile_]->name());
}

void Padoca::UpdateDisplayClick(char key, String name) {
    lcd_.setCursor(0, 1);
    for(int n = 0; n < 16; n++) { lcd_.print(" "); }
    lcd_.setCursor(0, 1);
    lcd_.print("[");
    lcd_.print(key);
    lcd_.print("] ");
    lcd_.print(name);
}
