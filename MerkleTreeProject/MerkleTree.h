#pragma once
#include<iostream>;
#include<stdlib.h>;
#include<string>
#include<list>


using namespace std;
typedef string elementType;

struct node {
	elementType data;
	node* left = nullptr;
	node* right= nullptr;
	node(elementType x);

};

class MerkleTree
{
	list<string> transactions;
	node* root;
	
public:MerkleTree(list<string> transactions);
public: node* getMerkleRoot();
public: node* createNode(elementType x);
private: list<node*> buildMerkleTree(list<node*> transactions);
private: list<node*> changeListElementsToNodes(list<elementType> transactions);

public: void display();





};
