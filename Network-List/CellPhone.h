#ifndef CELLPHONE_H
#define CELLPHONE_H

#include "Entity.h"

class CellPhone: public Entity{
    public:
        // entity stuff is included in ctor 
        CellPhone(string num, Location);
        ~CellPhone();
        void setLocation(const Location& l){ Entity::loc = l;}

        List* getMessagesWith(const string& id, List& messages);
        static void resetId();
        void print();

    private:
        string number;
        static const char code;
        static int nextId;

};

#endif