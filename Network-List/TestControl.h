#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <sstream>
#include "Network.h"
#include "View.h"
#include "Tester.h"

using namespace std;

class TestControl {
		
	public:
		void launch();
	
	private:
		void initTowers(Network& network, Location* locations);
		void initCellPhones(Network& network, Location* locations);
		int testAddTowers();
		int testAddCellPhones();
		int testSendMessage();
		int testPrintTowerMessages();
		int testPrintCellPhoneMessages();
		int testPrintConversation();
		int testMoveCellPhone();
		

		View view;
		Tester tester;
	

		
	
};
#endif