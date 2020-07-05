#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <Keyboard.h>

class Command {
    public:
        virtual Command(String name): name_(name) {};
        virtual ~Command() {};
        inline const String name() { return name_; }

        virtual void Click() = 0;

    private:
        String name_;
};

class CommandText : public Command {
    public:
        CommandText(String name, String text): Command(name), text_(text) {};
        void Click() {
            Keyboard.print(text_);
        }

    private:
        String text_;
};

#endif