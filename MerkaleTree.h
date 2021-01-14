#pragma once
#include<iostream>
#include<stdlib.h>
#include<string>
#include"Queue.h"

typedef std::string dataType;
class MerkleTree {

private:
	class MerkleNode {

	public:
		MerkleNode* left;
		MerkleNode* right;
		dataType data;
		MerkleNode() :left(NULL), right(NULL) {}
		MerkleNode(MerkleNode* left, MerkleNode* right, dataType data) :left(left), right(right), data(data) {}

	};

	MerkleNode* root;
	Queue<dataType> base;
	void readFromFile(const char* fileName);
	Queue<dataType>changeListElementsToNodes(Queue<dataType> transactions);
	Queue<dataType>build(Queue<dataType> transactions);


public:
	dataType getRoot();
	MerkleTree(Queue<dataType> data);
	~MerkleTree();
	void printTree();

};
