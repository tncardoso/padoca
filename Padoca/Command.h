#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <Keyboard.h>
#include <ArduinoSTL.h>
#include <vector>

const unsigned int COM_CTRL = 1;
const unsigned int COM_ALT = 1 << 1;
const unsigned int COM_SHIFT = 1 << 2;

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

class CommandKey : public Command {
  public:
        CommandKey(String name, char key, unsigned int mod, int wait_time=200):
            Command(name),
            key_(key),
            mod_(mod),
            wait_time_(wait_time) {
          
        };
        void Click() {
          if (mod_ & COM_CTRL) {
            Keyboard.press(KEY_LEFT_CTRL);
          }

          if (mod_ & COM_ALT) {
             Keyboard.press(KEY_LEFT_ALT);
          }

          if (mod_ & COM_SHIFT) {
             Keyboard.press(KEY_LEFT_SHIFT);
          }

          Keyboard.press(key_);
          delay(wait_time_);
          Keyboard.releaseAll();
        }

    private:
        char key_;
        unsigned int mod_;
        int wait_time_;
};

#endif
