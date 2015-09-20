#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <vector>
#include <string>
#include <unordered_map>
#include "link.h"



using namespace std;


class node{
	int ID;
	unordered_map<int, link*> ForwardTo;
	unordered_map<int, link*> BackTo;
	
public:
	void ConnectForward(node &, link &);
	void ConnectBack(node&, link&);
	void SetID(int);
	int GetID();

};

#endif