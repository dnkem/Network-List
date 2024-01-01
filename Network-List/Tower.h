#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"

class Tower: public Entity{
    public:
        Tower(Location);
        ~Tower();
        static void resetId();
        void print();

    private:
        static const char code;
        static int nextId;


};

#endif