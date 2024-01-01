#include "CellPhone.h"

int CellPhone::nextId = 1;
const char CellPhone::code = 'C';

CellPhone::CellPhone(string num, Location location):number(num), Entity(code, nextId++, location){
    // cout<<"Cellphone -- ctor"<<endl;
}

CellPhone::~CellPhone(){
   
}

List* CellPhone::getMessagesWith(const string& id, List& messages){
    List* listId = new List();
    messages.getMessagesWith(id, *listId);
    return listId;
}
void CellPhone::resetId(){
    nextId = 1;
}
void CellPhone::print(){
    cout<<"Cell Number: "<<number<<endl;
    Entity::print();
    // cout<<"Code:   "<<code<<endl;
    // cout<<"NextId: "<<nextId<<endl;
}