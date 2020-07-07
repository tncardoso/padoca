#ifndef _PROFILE_H_
#define _PROFILE_H_

#include <WString.h>
#include <ArduinoSTL.h>
#include <vector>
#include <map>

#include "Command.h"

class Profile {
    public:
        Profile(String name);
        String Click(char key);
        
        inline void AddCommand(char k, Command* command) { commands_[k] = command; }
        inline const String name() { return name_; }

    private:
        String name_;
        std::map<char, Command*> commands_;
};

#endif
