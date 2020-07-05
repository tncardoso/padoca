#include "Profile.h"

Profile::Profile(String name):
    name_(name) {
}

void Profile::Click(char key) {
    for(auto& cmd: commands_[key]) {
        cmd->Click();
    }
}