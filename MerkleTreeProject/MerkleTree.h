#pragma once
#include<iostream>;
#include<stdlib.h>;
#include<string>

#include"Queue.h"


using namespace std;
typedef string elementType;

struct node {
	elementType data;
	node* left = nullptr;
	node* right = nullptr;
	node(elementType x);

};

class MerkleTree
{
	Queue<string> transactions;
	node* root;


public:MerkleTree( const char* filepath);
public: elementType getMerkleRoot();
private: Queue<node*> buildMerkleTree(Queue<node*> transactions);
private: Queue<node*>& changeListElementsToNodes(Queue<elementType>transactions);
private:void readFromFile(const char* fileName);


public: void display();





};


