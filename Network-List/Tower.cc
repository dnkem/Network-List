#include "Tower.h"

int Tower::nextId = 1; // This will produce the next id number to be passed into the Entity constructor***
const char Tower::code = 'T';
Tower::Tower(Location location):Entity(code, nextId++, location){
    // cout<<"Tower ctor"<<endl;
}
Tower::~Tower(){

}
void Tower::resetId(){
    nextId = 1;
}

void Tower::print(){
    cout<<"Tower"<<endl;
    Entity::print();
    // cout<<"nextId: "<<nextId<<endl;
    // cout<<"Code:   "<<code<<endl;
}