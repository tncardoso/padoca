#include "Profile.h"

Profile::Profile(String name):
    name_(name) {
}

String Profile::Click(char key) {
    if (commands_.find(key) == commands_.end()) {
        return "noop";
    }
    
    commands_[key]->Click();
    return commands_[key]->name();
}
