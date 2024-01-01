
#include "TestControl.h"
#include "Network.h"
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;
#define NUM_TOWERS 5
#define NUM_PHONES 5

const string phoneNumbers[NUM_PHONES] = {"(123) 456-7890", "(234) 567-8901", "(345) 678-9012", "(456) 789-0123", "(567) 890-1234"};


void TestControl::launch(){

    vector<string> menu ={
        "Test add and print Towers",
        "Test add and print CellPhones",
        "Test send message",
        "Test print messages in Tower",
        "Test print messages in CellPhone",
        "Test print conversation",
        "Test move CellPhone",
        "Test all and get mark"
    };

    int choice = -1;

    while (choice!= 0){
        view.menu(menu, choice);
        tester.clearInputBuffer();
        switch(choice){
            case 1: testAddTowers(); break;
            case 2: testAddCellPhones(); break;
            case 3: testSendMessage(); break;
            case 4: testPrintTowerMessages(); break;
            case 5: testPrintCellPhoneMessages(); break;
            case 6: testPrintConversation(); break;
            case 7: testMoveCellPhone(); break;
            case 8: int mark = testAddTowers();
                    mark+= testAddCellPhones();
                    mark+= testPrintTowerMessages();
                    mark+= testPrintCellPhoneMessages();
                    mark+= testPrintConversation();
                    std::cout<<endl<<"Automated marks total: "<<mark<<"/10"<<endl;
                    std::cout<<endl<<"The next 2 tests require manual inspection of the output."<<endl;
                    std::cout<<"Each section is worth 2 marks, for a total of 4 marks."<<endl;
                    tester.pressEnterToContinue();

                    mark+= testSendMessage();
                    mark+= testMoveCellPhone();

                    cout<<"Total marks: "<<mark<<" + <manual marks> /14"<<endl;
                    
                    break;
        }
    }
    std::cout<<"exiting program!!!"<<endl;
}

void TestControl::initTowers(Network& network, Location* locations){
    cout<<"Initializing towers..."<<endl;
    for (int i = 0; i < NUM_TOWERS; ++i){
        network.addTower(locations[i]);
    }
    cout<<"Towers initialized!"<<endl;
}

void TestControl::initCellPhones(Network& network, Location* locations){
    cout<<"Initializing cellphones..."<<endl;
    
    for (int i = 0; i < NUM_PHONES; ++i){
        network.addCellPhone(phoneNumbers[i], locations[i]);
    }
    cout<<"Cellphones initialized!"<<endl;
}

int TestControl::testAddTowers(){
    int marks = 2;
    Network network;
    network.resetIds();
    cout<<"1. Test add and print towers"<<endl;

    // generate and store random locations
    Location locations[NUM_TOWERS];
    string loc[NUM_TOWERS];
    for (int i = 0; i < NUM_TOWERS; ++i){
        locations[i] = Location(rand()%100, rand()%100);
        tester.initCapture();
        locations[i].print();
        tester.endCapture();
        loc[i] = tester.getOutput();
    }
    initTowers(network, locations);

    cout<<"Printing towers..."<<endl;
    tester.initCapture();
    network.printTowers();
    tester.endCapture();

    int error = 0;
    tester.find({0,1,2,3,4}, loc, error);

    if (error>0){
        cout<<error<<" locations not found, test failed, -1"<<endl;
        cout<<"Tower print should print location data"<<endl;
        marks -= 1;
    }else{

        cout<<"All locations found"<<endl<<endl;
    }

    string labels[NUM_TOWERS] = {"T1", "T2", "T3", "T4", "T5"};
    tester.find({0,1,2,3,4}, labels, error);
    if (error>0){
        cout<<error<<" labels not found, test failed"<<endl;
        marks -= 1;
    }else{
        cout<<"All labels found"<<endl<<endl;
    }
    cout<<"Test complete, marks: "<<marks<<endl;
    return marks;

}


int TestControl::testAddCellPhones(){
    int marks = 2;
    Network network;
    network.resetIds();
    cout<<"2. Test add and print cellphones"<<endl;

    // generate and store random locations
    Location locations[NUM_PHONES];
    string loc[NUM_PHONES];
    for (int i = 0; i < NUM_PHONES; ++i){
        locations[i] = Location(rand()%100, rand()%100);
        tester.initCapture();
        locations[i].print();
        tester.endCapture();
        loc[i] = tester.getOutput();
    }
    initCellPhones(network, locations);

    cout<<"Printing cellphones..."<<endl;
    tester.initCapture();
    network.printCellPhones();
    tester.endCapture();

    int error = 0;
    tester.find({0,1,2,3,4}, loc, error);

    if (error>0){
        cout<<error<<" locations not found, test failed, -1"<<endl;
        cout<<"Cellphone print should print location data"<<endl;
        marks -= 1;
    }else{

        cout<<"All locations found"<<endl<<endl;
    }

    string labels[NUM_PHONES] = {"C1", "C2", "C3", "C4", "C5"};
    tester.find({0,1,2,3,4}, labels, error);
    if (error>0){
        cout<<error<<" labels not found, test failed"<<endl;
        marks -= 1;
    }else{
        cout<<"All labels found"<<endl<<endl;
    }
    cout<<"Test complete, marks: "<<marks<<endl;
    return marks;
}

int TestControl::testSendMessage(){
    Location tLocs[NUM_TOWERS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_PHONES] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Network network;
    network.resetIds();
    cout<<"3. Test send message"<<endl<<endl;
    cout<<"We are adding phones and towers to a network. When a message is sent, it should be routed through the closest tower to both sender and receiver."<<endl;
    cout<<"We will test when both phones are near the same tower, and different towers. At which point we will print the Towers and the Cellphones, and a visual inspection will confirm if the proper NUMBER of messages exists in each case."<<endl;

    initTowers(network, tLocs);
    initCellPhones(network, cLocs);

    cout<<"Sending message from C1 to C2 (different towers, T1 and T2)"<<endl;
    string textMessages[4]= {"C1 says hello to C2", "C2 says hello to C1", "C4 says hello to C5", "C5 says hello to C4"};
    
    network.routeMessage(Message("C1", "C2", textMessages[0]));
    network.routeMessage(Message("C2", "C1", textMessages[1]));
    network.routeMessage(Message("C1", "C2", textMessages[0]));
    network.routeMessage(Message("C2", "C1", textMessages[1]));
    network.routeMessage(Message("C4", "C5", textMessages[2]));
    network.routeMessage(Message("C5", "C4", textMessages[3]));
    network.routeMessage(Message("C4", "C5", textMessages[2]));
    network.routeMessage(Message("C5", "C4", textMessages[3]));
    network.routeMessage(Message("C1", "C4", textMessages[3]));


    cout<<"Printing cellphones:"<<endl<<endl;
    network.printCellPhones();

    cout<<endl<<"There should be 5 messages in C1 and C4, and 4 messages in C2 and C5"<<endl<<endl;

    tester.pressEnterToContinue();

    cout<<"Printing towers:"<<endl<<endl;
    network.printTowers();

    cout<<endl<<"There should be 5 messages in T1 and T5, and 4 messages in T2"<<endl<<endl;
    cout<<"Give 2 marks for perfect, 1 mark if one of the Towers or Cellphones is wrong, 0 otherwise"<<endl;

    tester.pressEnterToContinue();
    return 0;


}

int TestControl::testPrintTowerMessages(){
    Location tLocs[NUM_TOWERS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_PHONES] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Network network;
    network.resetIds();
    cout<<"4. Test print messages in Tower"<<endl<<endl;

    cout<<"We are adding phones and towers to a network. When a message is sent, it should be routed to the closest tower to both cellphones."<<endl;
    cout<<"We will test when both phones are near the same tower, and different towers"<<endl;

    initTowers(network, tLocs);
    initCellPhones(network, cLocs);

    cout<<"Sending message from C1 to C2 (different towers, T1 and T2)"<<endl;
    string textMessages[4]= {"C1 says hello to C2", "C2 says hello to C1", "C4 says hello to C5", "C5 says hello to C4"};
    
    network.routeMessage(Message("C1", "C2", textMessages[0]));
    network.routeMessage(Message("C2", "C1", textMessages[1]));


    cout<<"Printing messages in T1"<<endl;
    const List* messages;
    network.getMessageHistory("T1", &messages);
    tester.initCapture();
    messages->print();
    tester.endCapture();

    int error = 0;
    tester.find({0,1}, textMessages, error);

    if (error>0){
        cout<<error<<" messages not found, test failed"<<endl;
        cout<<"Tower print should print messages"<<endl;
        return 0;
    }else{

        cout<<"All messages found"<<endl<<endl;
    }

    cout<<"Printing messages in T2"<<endl;
    network.getMessageHistory("T2", &messages);
    tester.initCapture();
    messages->print();
    tester.endCapture();

    tester.find({0,1}, textMessages, error);

    if (error>0){
        cout<<error<<" messages not found, test failed"<<endl;
        return 0;
    }else{    
            cout<<"All messages found"<<endl<<endl;
        }

    cout<<"Testing 2 phones, same tower"<<endl<<endl;

    cout<<"Sending message between C4 and C5 (same tower, T5)"<<endl;

    network.routeMessage(Message("C4", "C5", textMessages[2]));
    network.routeMessage(Message("C5", "C4", textMessages[3]));

    cout<<"Printing messages in T5"<<endl;
    network.getMessageHistory("T5", &messages);
    tester.initCapture();
    messages->print();
    tester.endCapture();

    tester.find({2,3}, textMessages, error);

    if (error>0){
        cout<<error<<" messages not found, test failed"<<endl;
        return 0;
    }else{    
            cout<<"All messages found"<<endl<<endl;
        }

    cout<<"Test complete, marks: 2"<<endl;
    return 2;


}
int TestControl::testPrintCellPhoneMessages(){
    Location tLocs[NUM_TOWERS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_PHONES] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Network network;
    network.resetIds();
    cout<<"5. Test print messages in CellPhone"<<endl<<endl;
    cout<<"We are adding phones and towers to a network. When a message is sent, it should be routed to the closest tower to both cellphones."<<endl;
    cout<<"We will test when both phones are near the same tower, and different towers"<<endl;

    initTowers(network, tLocs);
    initCellPhones(network, cLocs);

    cout<<"Sending message from C1 to C2 (different towers, T1 and T2)"<<endl;
    string textMessages[4]= {"C1 says hello to C2", "C2 says hello to C1", "C4 says hello to C5", "C5 says hello to C4"};
    
    network.routeMessage(Message("C1", "C2", textMessages[0]));
    network.routeMessage(Message("C2", "C1", textMessages[1]));


    cout<<"Printing messages in C1"<<endl;
    const List* messages;
    network.getMessageHistory("C1", &messages);
    tester.initCapture();
    messages->print();
    tester.endCapture();

    int error = 0;
    tester.find({0,1}, textMessages, error);

    if (error>0){
        cout<<error<<" messages not found, test failed"<<endl;
        return 0;
    }else{

        cout<<"All messages found"<<endl<<endl;
    }

    cout<<"Printing messages in C2"<<endl;
    network.getMessageHistory("C2", &messages);
    tester.initCapture();
    messages->print();
    tester.endCapture();

    tester.find({0,1}, textMessages, error);

    if (error>0){
        cout<<error<<" messages not found, test failed"<<endl;
        return 0;
    }else{    
            cout<<"All messages found"<<endl<<endl;
        }

    cout<<"Testing 2 phones, same tower"<<endl<<endl;

    cout<<"Sending message between C4 and C5 (same tower, T5)"<<endl;

    network.routeMessage(Message("C4", "C5", textMessages[2]));
    network.routeMessage(Message("C5", "C4", textMessages[3]));

    cout<<"Printing messages in C5"<<endl;
    network.getMessageHistory("C5", &messages);
    tester.initCapture();
    messages->print();
    tester.endCapture();

    tester.find({2,3}, textMessages, error);

    if (error>0){
        cout<<error<<" messages not found, test failed"<<endl;
        return 0;
    }else{    
            cout<<"All messages found"<<endl<<endl;
        }

    cout<<"Printing messages in C4"<<endl;
    network.getMessageHistory("C4", &messages);
    tester.initCapture();
    messages->print();
    tester.endCapture();

    tester.find({2,3}, textMessages, error);

    if (error>0){
        cout<<error<<" messages not found, test failed"<<endl;
        return 0;
    }else{    
            cout<<"All messages found"<<endl<<endl;
        }

    cout<<"Test complete, marks: 2"<<endl;
    return 2;

}

int TestControl::testPrintConversation(){
    Location tLocs[NUM_TOWERS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_PHONES] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Network network;
    network.resetIds();
    cout<<"6. Test print conversation"<<endl<<endl;
    cout<<"This should find all messages between two cellphones, for example, C1 and C5. All messages";
    cout<<" between them would be stored in either phone. All sent messages will be printed. "<<endl;

    initTowers(network, tLocs);
    initCellPhones(network, cLocs);

    string fromMessages[10]= {"C3", "C2", "C3", "C2", "C4", "C5", "C2", "C5", "C2", "C4"};
    string toMessages[10] = {"C2", "C1", "C2", "C3", "C5", "C3", "C5", "C4", "C3", "C1"};
    string printedMessages[10]; 
    
    for (int i = 0; i < 10; ++i){
        Message temp(fromMessages[i], toMessages[i], "hello for the "+to_string(i)+"th time");
        network.routeMessage(temp);
        tester.initCapture();  
        temp.print();
        tester.endCapture();
        cout<<endl;
        printedMessages[i] = tester.getOutput();
    }


    cout<<"Printing conversation between C2 and C3"<<endl;
    List conversation;
    network.getMessagesWith("C2", "C3", conversation);
    tester.initCapture();
    conversation.print();
    tester.endCapture();

    int error = 0;
    tester.find({0,2,3,8}, printedMessages, error);
    
    if (error>0){
        cout<<error<<" messages not found, test failed"<<endl;
        return 0;
    }

    cout<<"All messages found between C2 and C3"<<endl;

    tester.confirmAbsent({1,4,5,6,7,9}, printedMessages, error);

    if (error>0){
        cout<<error<<" messages found between other people, test failed"<<endl;
        return 0;
    }

    cout<<"No other messages found."<<endl<<"Test passed, 2 marks"<<endl;

    return 2;

}

int TestControl::testMoveCellPhone(){
    Location tLocs[NUM_TOWERS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_PHONES] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Network network;
    network.resetIds();
    cout<<"7. Test move cellphone"<<endl<<endl;
    cout<<"This test will verify that after a cellphone moves that its messages are routed through a different tower. "<<endl;

    initTowers(network, tLocs);
    initCellPhones(network, cLocs);

    string c2 = "C2";
    string c4 = "C4";
    for (int i = 0; i < 2; ++i){
        Message temp1(c2, c4, "hello for the "+to_string(i)+"th time");
        Message temp2(c4, c2, "hello for the "+to_string(i)+"th time");

        network.routeMessage(temp1);
        network.routeMessage(temp2);
    }

    cout<<"Print towers"<<endl;
    network.printTowers();

    cout<<"Verify that there are 4 messages in T2 and T5, and 0 messages in T1, T3, T4"<<endl;

    tester.pressEnterToContinue();

    cout<<"Move C2 to (1,1)"<<endl;
    network.moveCellPhone(c2, Location(1,1));

    cout<<"Printing cellphones:"<<endl;
    network.printCellPhones();

    cout<<"Verify that C2 is at (1,1)"<<endl;
    tester.pressEnterToContinue();

    for (int i = 0; i < 2; ++i){
        Message temp1(c2, c4, "hello for the "+to_string(i+2)+"th time");
        Message temp2(c4, c2, "hello for the "+to_string(i+2)+"th time");

        network.routeMessage(temp1);
        network.routeMessage(temp2);
    }

    cout<<"Print towers"<<endl;
    network.printTowers();

    cout<<"Verify that there are 4 messages in T1, T2, 8 messages in T5, and 0 messages in T3, T4"<<endl;
    cout<<"2 marks for everything correct, 1 mark for up to two things wrong, 0 otherwise"<<endl;

    tester.pressEnterToContinue();


    return 0;

}