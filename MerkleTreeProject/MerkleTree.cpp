#include "MerkleTree.h"
#include"SHA.h"
#include"Queue.h"
#include<fstream>
int lvl = 2;
// lvl for debuging will be deleted later
node::node(elementType x ) {
	data = x;
	left = nullptr;
	right = nullptr;

}
MerkleTree::MerkleTree(const char* filePath) {
	
	readFromFile(filePath);
	
	root = buildMerkleTree(changeListElementsToNodes(transactions)).getFront();

	

	
}
elementType MerkleTree::getMerkleRoot() {
//Queue<node*> mydata = changeListElementsToNodes(transactions);
//root = buildMerkleTree(mydata).getFront();
	 return root->data;
}
Queue<node*>& MerkleTree::changeListElementsToNodes(Queue<elementType> transactions) {
	Queue<node*> nodes;
	while (!transactions.isEmpty()) {
		// from  data queue -------> nodes queue

		// HASHING IS MISSING HERE to hash it bl maraa
		
		nodes.enqueue(new node((transactions.getFront())));
		transactions.dequeue();
	}


	nodes.display();
	return nodes;
}
Queue<node*> MerkleTree::buildMerkleTree(Queue<node*> transactions) {
	
	if (transactions.getSize() == 1) { return transactions; } //Base condition return list with only one element MERKLE ROOT.
	if (transactions.getSize() % 2 != 0) { transactions.enqueue(transactions.getBack()); } //if nodes are odd then add last element again.
	Queue<node*> updateList; // Creating a new list 

	
	
	int i = 1;
	while(!transactions.isEmpty())
	{
		
		// string a will be equal merged hash of two adjancent elements  -->[a = hash(a) + hash(b)]
		
		elementType a = transactions.getFront()->data; 
		//storing address of left node in pointer
		node* leftTemp = transactions.getFront();
		transactions.dequeue();
		a.append(transactions.getFront()->data);
		//storing address of right node in pointer
		node* rightTemp = transactions.getFront();

		transactions.dequeue();
		//create node with data value equal a and pointing to leftTemp and rightTemp
		//string mergedHash = hash_(a);
		node* tempNode = new node(a);
		tempNode->left = leftTemp;
		tempNode->right = rightTemp;

		
		//debug will be deleting later.........
		cout << "the node number " << i << " equal "<<endl
			<< tempNode->data <<endl<< " left node = "
			<< tempNode->left->data << endl;
		i++;
		/// update list recursivly.
		updateList.enqueue(tempNode);
	}
	// i was debuging this code will be deleted later.....
	cout << "^^^^^^^^^" << "level = " << lvl << "^^^^^^^^^" << endl;
	lvl++;
	return buildMerkleTree(updateList);
}
void MerkleTree::readFromFile(const char* filename) {

	std::ifstream infile(filename);
	if (!infile) {
		std::cerr << "Cannot open input file.\n";
		return;
	}
	std::string temp;
	while (std::getline(infile, temp)) {

		transactions.enqueue(temp);
	}

	return;
}
void MerkleTree::display() {


}


