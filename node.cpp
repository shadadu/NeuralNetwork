#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "node.h"
#include "link.h"


using namespace std;



void node::ConnectForward(node &n, link & h)
{
	int id = n.GetID();
	ForwardTo.insert( pair < int,link * > (id, &h));
}
void node::ConnectBack(node & n, link & h)
{
	int id = n.GetID();
	BackTo.insert( pair < int, link * > (id, &h));
}
void node::SetID(int id)
{
	ID = id;
}
int node::GetID()
{
	return ID;
}