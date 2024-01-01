#include "Network.h"

Network::~Network(){
    for (int i=0; i<cells.size(); i++){
        delete cells[i];
    }
    for (int i=0; i<towers.size(); i++){
        delete towers[i];
    }
    // cells.clear();
    // towers.clear();
}

void Network::addCellPhone(string number, Location location){
    CellPhone* c = new CellPhone(number, location);
    cells.push_back(c);
    cout<<"cellphone added" <<endl;
    
}
void Network::addTower(Location l){
    Tower* t = new Tower(l);
    towers.push_back(t);
    cout<<"tower added" <<endl;
}
CellPhone* Network::getCellPhone(const string& id) const{
    for (int i=0; i<cells.size(); i++){ 
        if(cells[i]->equals(id)){   // note cells[i] is already a ptr
            return cells[i];
        }
    }
    return nullptr;
}
Tower* Network::getTower(const string& id) const{
    for (int i=0; i<towers.size(); i++){ 
        if(towers[i]->equals(id)){
            return towers[i];
        }
    }
    return nullptr;
}

bool Network::routeMessage(Message m){
    // use id to find cells
    CellPhone* sender = getCellPhone(m.getSender());
    CellPhone* receiver = getCellPhone(m.getReceiver());
    // check if nullptr
    if (sender == nullptr || receiver == nullptr){
        cout<<"One or both of theses cellphones do not exist"<<endl;
        return false;
    }
    // if it exists add the message

    sender->addMessage(m);
    receiver->addMessage(m);

    // get the closest tower for each
    Tower* senderT = findClosestTower(sender->getLocation());
    Tower* receiverT = findClosestTower(receiver->getLocation());
    
    // if they're the same, add the message to that tower
    if (senderT == receiverT){
        senderT->addMessage(m);
    } 
    else {
        senderT->addMessage(m);
        receiverT->addMessage(m);
    }
    return true;
}

Tower* Network::findClosestTower(Location l) const{
    int minDistance = 0;
    Tower* closestTower = nullptr;
    for (int i=0; i<towers.size(); i++){
        if (towers[i]->getLocation().getDistance(l) < minDistance || minDistance == 0){
            minDistance = towers[i]->getLocation().getDistance(l);
            closestTower = towers[i];
        }
    }
    return closestTower;
}

bool Network::moveCellPhone(string id, Location l){
    CellPhone* c = getCellPhone(id);
    if (c == nullptr) {
        cout<<"CellpPhone with this id doesn't exist"<<endl;
        return false;
    } 
    c->setLocation(l);
    return true;
}
bool Network::getMessageHistory(const string& id, const List** messages){
    CellPhone* c = getCellPhone(id);
    Tower* t = getTower(id);

    if (t == nullptr && c == nullptr){   // could cause an ERROR
        cout<< "ERROR - ID for the tower and/or cellphone doesn't exist"<<endl;
        return false;
    }
    else if(t == nullptr && c != nullptr){
        *messages = c->getMessageHistory();
    }
    else if (t != nullptr && c == nullptr){
        *messages = t->getMessageHistory();
    }
    else{
        *messages = c->getMessageHistory();
        *messages = t->getMessageHistory();
    }
    return true;

}
void Network::getMessagesWith(const string& id1, const string& id2, List& outputList){
    CellPhone* c1 = getCellPhone(id1);
    if (c1 == nullptr) { cout<<"This cellphone with this id doesn't exist"<<endl; return;}
    List* newL = c1->getMessagesWith(id2, *c1->getMessageHistory());
    outputList = *newL;
}
void Network::resetIds(){
    cells[cells.size()]->resetId();
    towers[towers.size()]->resetId();
}
void Network::printTowers(){
    for (int i=0; i<towers.size(); i++){
        towers[i]->print();
    }
}
void Network::printCellPhones(){
    for (int i=0; i<cells.size(); i++){
        cells[i]->print();
    }
}
