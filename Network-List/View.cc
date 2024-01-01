#include <iostream>
using namespace std;
#include <string>
#include <sstream>

#include "View.h"

void View::menu(vector<string>& menu, int& choice)
{
  cout << endl;
  cout << "Please make a selection:"<< endl<<endl;
  for (int i = 0; i < menu.size(); ++i){
    cout<<"  ("<<i+1<<") "<<menu[i]<<endl;
  }
  cout << "  (0) Exit" << endl<<endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;

  while (choice < 0 || choice > menu.size()) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::getLocation(int& x, int& y)
{
  cout << "Please enter an x coordinate: ";
  cin >> x;
  cout << "Please enter a y coordinate: ";
  cin >> y;
}

void View::getString(string& str)
{
  cin >> str;
}



void View::printList(const List& list)
{
  cout << endl;
  list.print();
  cout << endl;
}






