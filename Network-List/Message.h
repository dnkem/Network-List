#ifndef MESSAGE_H
#define MESSAGE_H

using namespace std;

#include "defs.h"
#include <iostream>
#include <string>
// #include "Location.h"



class Message{
    public:
        Message(const string& s = "Paul", const string& r = "Bob", const string& m = "Heyyy");
        ~Message();
        // getters
        string getSender() const;
        string getReceiver() const;
        // others
        void print() const;
        bool equalsSender(const string&) const;
        bool equalsReceiver(const string&) const;

    private:
        string sender;
        string receiver;
        string message;

};


#endif