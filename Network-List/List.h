#ifndef LIST_H
#define LIST_H

#include <string>
#include "Message.h"

using namespace std;

class List{

    class Node{
        public:
            Message* data;
            Node* next;
    };

    public:
        List();
        ~List();
        bool add(Message*);

        Message* get(const string& name);
        Message* get(int index);
        int getSize() const;
        void getMessagesWith(const string& id, List& outputList);
        void getMessagesWith(const string& id1, const string& id2, List& outputList);
//      bool messageInList(Message& m, List& list);

        const Message* remove(string name);
        const Message* remove(Message* msg);
        Message* removeFirst();
        void removeMessagesWith(const string& id, List& outputList);

        bool isEmpty() const;
        void print() const;
    
    private:
        Node* head;
        Node* tail;
        int size;

};


#endif
