#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <vector>
#include "List.h"

using namespace std;


class View
{
  public:
    void menu(vector<string>&, int& choice);
    void printList(const List& list);
    void getLocation(int& x, int& y);
    void getString(string& str);
  
};

#endif
