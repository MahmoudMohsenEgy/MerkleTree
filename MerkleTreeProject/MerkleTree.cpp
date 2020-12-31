#include "MerkleTree.h"
#include"SHA.h"
int lvl = 2;
// lvl for debuging will be deleted later
MerkleTree::MerkleTree(list<string> transactions) {
	this->transactions = transactions;
}
node* MerkleTree::getMerkleRoot() {
	list<node*> mydata = changeListElementsToNodes(this->transactions);
	root = buildMerkleTree(mydata).front();
	 return root;
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
		nodes.push_back(createNode(hash_(transactions.front())));
		transactions.pop_front();
	}



	return nodes;
}
list<node*> MerkleTree::buildMerkleTree(list<node*> transactions) {
	if (transactions.size() == 1) { return transactions; } //Base condition return list with only one element MERKLE ROOT.
	if (transactions.size() % 2 != 0) { transactions.push_back(transactions.back()); } //if nodes are odd then add last element again.
	list<node*> updateList; // Creating a new list 

	
	
	int i = 1;
	while(!transactions.empty())
	{
		
		// string a will be equal merged hash of two adjancent elements  -->[a = hash(a) + hash(b)]
		
		elementType a = transactions.front()->data; 
		//storing address of left node in pointer
		node* leftTemp = transactions.front();
		transactions.pop_front();
		a.append(transactions.front()->data);
		//storing address of right node in pointer
		node* rightTemp = transactions.front();

		transactions.pop_front();
		//create node with data value equal a and pointing to leftTemp and rightTemp
		//string mergedHash = hash_(a);
		node* tempNode = createNode(a);
		tempNode->left = leftTemp;
		tempNode->right = rightTemp;

		
		//debug will be deleting later.........
		cout << "the node number " << i << " equal "<<endl
			<< tempNode->data <<endl<< " left node = "
			<< tempNode->left->data << endl;
		i++;
		/// update list recursivly.
		updateList.push_back(tempNode);
	}
	// i was debuging this code will be deleted later.....
	cout << "^^^^^^^^^" << "level = " << lvl << "^^^^^^^^^" << endl;
	lvl++;
	return buildMerkleTree(updateList);
}
void MerkleTree::display() {


}


