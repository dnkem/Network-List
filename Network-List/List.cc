#include <iostream>
#include <string>
using namespace std;

#include "List.h"

List::List():head(nullptr), tail(nullptr) {
    size = 0;
}


List::~List(){
   // deletes the nodes in the list
   cout<<"In List dtor"<<endl;
   Node* curr = head;
   Node* prev = nullptr;

   while(curr!=nullptr){
      prev = curr;
      curr = curr->next;
      delete prev;
      //cout<<"deleted";
   }
  
}

//add in sorted order by name
bool List::add(Message* msg){
   Node* newNode = new Node;  // create new node
   newNode->data = msg;       // assign its data

   // checks if the list is empty
   if (head == nullptr){
      newNode->next = nullptr;
      head = newNode;
      tail = newNode;
      size++;
      return true;
   }

   // select the next node and reassign the tail
   tail->next = newNode;
   tail = newNode;

   size++;
   return true;
}

const Message* List::remove(string name){
   // check bounds
   if (head == nullptr)return nullptr;
   // set up for checking
   Node* curr = head;   
   Node* prev = nullptr;

   while(curr != nullptr){
      if (curr->data->equalsReceiver(name) || curr->data->equalsSender(name)){   // condition at the top
         break;
      }
      prev = curr;      // traversal
      curr= curr->next;
   }

   // if the name doesn't exist in the list and curr traversed everything
   if (curr == nullptr){
      return nullptr;
   }
   // deletes the first element
   if (prev == nullptr){   // prev wouldn't have been assigned yet
      head = head->next;
   }else{ 
      // deletes the node in the middle/end
      prev->next = curr->next;
   }

   // copy of the node's data
   const Message* goner = curr->data;
   delete curr;
   size--;
   return goner;
}

const Message* List::remove(Message* msg){
   // check bounds
   if (head == nullptr)return nullptr;
   // set up for checking
   Node* curr = head;   
   Node* prev = nullptr;

   while(curr != nullptr){
      if (curr->data == msg){   // condition at the top
         break;
      }
      prev = curr;      // traversal
      curr= curr->next;
   }

   // if the name doesn't exist in the list and curr traversed everything
   if (curr == nullptr){
      return nullptr;
   }
   // deletes the first element
   if (prev == nullptr){   // prev wouldn't have been assigned yet
      head = head->next;
   }else{ 
      // deletes the node in the middle/end
      prev->next = curr->next;
   }

   // copy of the node's data
   const Message* goner = curr->data;
   delete curr;
   size--;
   return goner;
}

Message* List::removeFirst(){
   // check bounds
   if (isEmpty()) return nullptr;

   // copy & remove the first
   Node* prevHead = head;
   head = head->next;

   // if size = 1, deal with tail
   if (size == 1) {
      tail = nullptr;
   }
   
   // copy of the node's data
   Message* goner = prevHead->data;
   --size;
   delete prevHead;
   return goner;
}
void List::getMessagesWith(const string& id, List& outputList){
   Node* curr = head;
   while(curr!=nullptr){
      if (curr->data->getSender() == id || curr->data->getReceiver() == id){
         outputList.add(curr->data);
      }
      curr = curr->next;
   }
}

void List::getMessagesWith(const string& id1, const string& id2, List& outputList){
   Node* curr = head;
   while(curr!=nullptr){
        // find sender, then look at 
        if ((curr->data->getSender() == id1 && curr->data->getReceiver() == id2) || (curr->data->getSender() == id2 && curr->data->getReceiver() == id1) ){
            outputList.add(curr->data);
        }
      curr = curr->next;
   }
}

void List::removeMessagesWith(const string& id, List& outputList){
    // list of msgs w/ id

    List* msgs;
    getMessagesWith(id, *msgs);

    Node* currMsg = msgs->head; 
    Node* curr = head;
    while(currMsg!=nullptr){
        while(curr != nullptr){
            if (curr->data == currMsg->data){
               outputList.add(curr->data);
               //remove(curr->data);
            }
            curr = curr->next;
        }
        currMsg = currMsg->next;
    }
}

bool List::isEmpty() const{
    return head == nullptr;
}
int List::getSize() const{ return size; }

void List::print() const{
   cout<<"Printing List of Messages: "<<endl;
   
   if (head == nullptr){ cout<<"List is empty"<<endl; return;}

   Node* curr = head;
   while(curr!=nullptr){
      curr->data->print();
      curr = curr->next;   
   }
}