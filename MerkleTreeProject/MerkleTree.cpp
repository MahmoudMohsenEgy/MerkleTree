#include "MerkleTree.h"

MerkleTree::MerkleTree(list<string> transactions) {
	this->transactions = transactions;
}
list<string> MerkleTree::getMerkleRoot() {
	return this->buildMerkleTree(this->transactions);
}
node* MerkleTree::createNode(elementType x) {
	node* p = new node;
	if (p == 0) { return 0; }// Memory is FULL error (NO SPACE in HEAP)
	p->data = x;
	p->left = nullptr;
	p->right = nullptr;
	
	return p;
}
list<node*> MerkleTree::changeListElementsToNodes(list<elementType> transactions) {
	list<node*> nodes;
	while (!transactions.empty()) {
		// from  data queue -------> nodes queue
		// HASHING IS MISSING HERE to hash it bl maraa
		nodes.push_back(createNode(transactions.front()));
		transactions.pop_front();
	}



	return nodes;
}
list<string> MerkleTree::buildMerkleTree(list<string> transactions) {
	if (transactions.size() == 1) { return transactions; } //Base condition 
	list<string> updateList; // Creating a new list 
	
	
	while(!transactions.empty())
	{
		// string a will be equal merged hash of two adjancent elements  -->[a = hash(a) + hash(b)]
		elementType a = transactions.front(); 
		//storing address of left node in pointer
		node* leftTemp;
		transactions.pop_front();
		a.append(transactions.front());
		//storing address of right node in pointer
		node* rightTemp;
		transactions.pop_front();
		//create node with data value equal a and pointing to leftTemp and rightTemp

		
		updateList.push_back(a);
	}
	return buildMerkleTree(updateList);
}


