#include "Entity.h"

Entity::Entity(char c, int i, Location& l):loc(l){
    string iString = to_string(i);
    id = c + iString;
}

Entity::~Entity(){
    // delete messageHistory;
}

List* Entity::getMessageHistory(){
    List* mPtr = &messageHistory;
    return mPtr;
}

Location Entity::getLocation() const{
    return loc;
}

int Entity::getNumMessages() const{
    return messageHistory.getSize();
}

bool Entity::equals(const string& id)const{
    return id == this->id;
}

void Entity::addMessage(const Message& m){
    Message* newPtr = new Message(m);
    messageHistory.add(newPtr);
    // help --- w/ const
}

void Entity::print()const{
    cout<<"ID:              "<<id<<endl;
    cout<<"Location:        "; loc.print(); cout<<endl;
    cout<<"Num of Messages: "<<getNumMessages()<<endl;
    cout<<endl;
}