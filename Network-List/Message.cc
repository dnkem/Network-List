#include "Message.h"

Message::Message(const string& s, const string& r, const string& m){
    sender = s;
    receiver = r;
    message = m;
}
Message::~Message(){ }

string Message::getSender() const{
    return sender;
}
string Message::getReceiver() const{
    return receiver;
}
bool Message::equalsSender(const string& s) const{
    return sender == s;
}
bool Message::equalsReceiver(const string& r) const{
    return receiver == r;
}
void Message::print() const{
    cout<<"Sender:   "<<sender<<endl;
    cout<<"Receiver: "<<receiver<<endl;
    cout<<"Message:  "<<message<<endl;
}