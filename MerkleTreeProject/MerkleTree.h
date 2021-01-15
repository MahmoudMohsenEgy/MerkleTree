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
	node* parent = nullptr;
	node(elementType x);

};

class MerkleTree
{
	Queue<string> transactions;
	node* root;
	Queue<node*> leaves;
	


public:MerkleTree( const char* filepath);
public:~MerkleTree();






private:void DestroyRecursive(node* node);




public: elementType getMerkleRoot();
public: void append(elementType data);
private: Queue<node*> buildMerkleTree(Queue<node*> transactions);
private: Queue<node*> changeListElementsToNodes(Queue<elementType>transactions);
private:void readFromFile(const char* fileName);


public: void display();
public:bool merkleProof(int pos, elementType merkleRoot);
private:void getSiblings(node* checkingNode, Queue<node*>* siblingsNodes);
private:Queue<node*> buildProof(node* nodeFromPath,Queue<node*>* siblingNodes);
	   





};


