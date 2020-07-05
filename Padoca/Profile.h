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
        void Click(char key);
        
        inline Profile& AddCommand(char k, Command* command) { commands_[k].push_back(command); }
        inline const String name() { return name_; }

    private:
        String name_;
        std::map<char, std::vector<Command*>> commands_;
};

#endif