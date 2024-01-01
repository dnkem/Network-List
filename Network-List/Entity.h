#ifndef ENTITY_H
#define ENTITY_H

#include "Location.h"
#include "List.h"

class Entity{
    public:
        Entity(char, int, Location&);
        ~Entity();

        List* getMessageHistory();  // help ---- ptr or no ptr
        Location getLocation() const;
        int getNumMessages() const;

        bool equals(const string& id) const;
        void print() const;

        void addMessage(const Message& m);


    protected: 
        string id;
        Location loc;

    private: 
        List messageHistory;

};

#endif