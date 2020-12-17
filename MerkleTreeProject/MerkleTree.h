#pragma once
#include<iostream>;
#include<stdlib.h>;
#include<string>
#include<list>
using namespace std;
typedef string elementType;

struct node {
	elementType data;
	node* left;
	node* right;

};

class MerkleTree
{
	list<string> transactions;
	
public:MerkleTree(list<string> transactions);
public: list<string> getMerkleRoot();

public: node* createNode(elementType x);

private: list<string> buildMerkleTree(list<string> transactions);
private: list<node*> changeListElementsToNodes(list<elementType> transactions);





};

