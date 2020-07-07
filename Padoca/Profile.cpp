#include "Profile.h"

Profile::Profile(String name):
    name_(name) {
}

String Profile::Click(char key) {
    if (commands_.find(key) == commands_.end()) {
        return "noop";
    } else if (commands_[key].empty()) {
        return "noop";
    }
    
    for(auto cmd: commands_[key]) {
        cmd->Click();
    }
    
    return commands_[key][0]->name();
}
