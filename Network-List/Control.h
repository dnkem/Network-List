#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <string>
#include "List.h"
#include <random>
#include <unordered_set>
#include <sstream>
#include "Tower.h"
#include "CellPhone.h"
#include "View.h"
#include "Network.h"

using namespace std;

class Control {
		
	public:
		void launch();
	
	private:
		void init();
		void addTower();
		void addCellPhone();
		
		void moveCellPhone();
		void printTowers();
		void printCellPhones();
		// maybe printall?

		void sendMessage();

		void printTowerMessages();
		void printCellPhoneMessages();
		void printConversation();


		void addC(string& id);
		void addT(string& id);
	
		

		View view;
		Network network;

	
};
#endif