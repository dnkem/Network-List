
#include "Control.h"
#include <limits>
#include <vector>

using namespace std;
#define NUM_TOWERS 5
#define NUM_PHONES 5

extern const string phoneNumbers[NUM_PHONES];



void Control::launch(){

    vector<string> menu ={
        "Print towers",
        "Print cellphones",
        "Add tower",
        "Add cellphone", 
        "Send message",
        "Print messages stored in tower",
        "Print messages stored in cellphone",
        "Print conversation",
        "Move cellphone"
    };

    init();
    int choice = -1;

    while (choice!= 0){
        view.menu(menu, choice);
        switch(choice){
            case 1: printTowers(); break;
            case 2: printCellPhones(); break;
            case 3: addTower(); break;
            case 4: addCellPhone(); break;
            case 5: sendMessage(); break;
            case 6: printTowerMessages(); break;
            case 7: printCellPhoneMessages(); break;
            case 8: printConversation(); break;
            case 9: moveCellPhone(); break;
        }
    }
    cout<<"exiting program!!!"<<endl;
}

void Control::init(){
    cout<<"Initializing cells and towers..."<<endl;
    for (int i = 0; i < NUM_TOWERS; ++i){
        network.addTower(Location(rand()%100, rand()%100));
    }
    for (int i = 0; i < NUM_PHONES; ++i){
        network.addCellPhone(phoneNumbers[i], Location(rand()%100, rand()%100));
    }
    cout<<"All entities initialized!"<<endl;
}

void Control::addTower(){       // 1
    cout<<"Adding tower..."<<endl;
    int x, y;
    view.getLocation(x, y);
    network.addTower(Location(x, y));
    cout<<"Tower added!"<<endl;
}

void Control::printTowers(){       //1
    cout<<"Printing towers..."<<endl;
    network.printTowers();
}

void Control::printCellPhones(){
    cout<<"Printing cellphones..."<<endl;
    network.printCellPhones();
}


void Control::addC(string& id){
    if (id.find('C') == string::npos){
        id = "C" + id;
    }
}

void Control::addT(string& id){
    if (id.find('T') == string::npos){
        id = "T" + id;
    }
}



void Control::addCellPhone(){
    cout<<"Adding cellphone...\nPlease enter phone number:"<<endl;
    string number;
    view.getString(number);
    int x, y;
    view.getLocation(x, y);
    network.addCellPhone(number, Location(x, y));
}


void Control::sendMessage(){
    cout<<"Sending message..."<<endl;
    string sender, receiver, message;
    printCellPhones();
    cout<<"Please enter sender id:"<<endl;
    view.getString(sender);
    addC(sender);
    cout<<"Please enter receiver id:"<<endl;
    view.getString(receiver);
    addC(receiver);
    cout<<"Please enter message:"<<endl;
    view.getString(message);
    network.routeMessage(Message(sender, receiver, message));
    // ERROR A3 - "initial value of reference to non-const must be an lvalue"
    // I checked both message and Network for route and I'm not sure how to fix the issue
}

void Control::printTowerMessages(){
    cout<<"Printing tower messages..."<<endl;
    string id;
    network.printTowers();
    cout<<"Please enter tower id:"<<endl;
    view.getString(id);
    addT(id);
    cout<<"Printing message history for: "<<id<<endl;
    const List* l;
    if (network.getMessageHistory(id, &l)){
        view.printList(*l);
    }else{
        cout<<"Tower not found!"<<endl;
    }
}

void Control::printCellPhoneMessages(){
    string id;
    network.printCellPhones();
    cout<<"Please enter cellphone id: "<<endl;
    view.getString(id);
    addC(id);
    cout<<"Printing message history for: "<<id<<endl;
    const List* l;
    if (network.getMessageHistory(id, &l)){
        view.printList(*l);
    }else{
        cout<<"Cellphone not found!"<<endl;
    }
}

void Control::printConversation(){
    string id1, id2;
    network.printCellPhones();
    cout<<"Please enter cellphone id 1: "<<endl;
    view.getString(id1);
    addC(id1);
    cout<<"Please enter cellphone id 2: "<<endl;
    view.getString(id2);
    addC(id2);
    cout<<"Printing conversation between: "<<id1<<" and "<<id2<<endl;
    List l;
    network.getMessagesWith(id1, id2, l);
    view.printList(l);
}

void Control::moveCellPhone(){
    string id;
    printCellPhones();
    cout<<"Please enter the cellphone id: "<<endl;
    view.getString(id);
    addC(id);
    cout<<"Moving cellphone: "<<id<<endl;
    int x, y;
    view.getLocation(x, y);
    network.moveCellPhone(id, Location(x, y));
}


const string phoneNumbers[NUM_PHONES] = {"(123) 456-7890", "(234) 567-8901", "(345) 678-9012", "(456) 789-0123", "(567) 890-1234"};

