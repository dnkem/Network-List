#ifndef NETWORK_H
#define NETWORK_H

#include "CellPhone.h"
#include "Tower.h"
#include <vector>

class Network{
    public:
        ~Network();

        void addCellPhone(string, Location);
        void addTower(Location);
        CellPhone* getCellPhone(const string& id) const;
        Tower* getTower(const string& id) const;
        Tower* findClosestTower(Location) const;
        bool routeMessage(Message);
        bool moveCellPhone(string, Location);
        bool getMessageHistory(const string& id, const List** messages);
        void getMessagesWith(const string& id1, const string& id2, List& outputList);
        void resetIds();
        void printTowers();
        void printCellPhones();


    private:
        vector<CellPhone*> cells;
        vector<Tower*> towers;
};

#endif