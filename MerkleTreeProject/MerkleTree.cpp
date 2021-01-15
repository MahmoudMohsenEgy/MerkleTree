#include "MerkleTree.h"
#include"SHA.h"
#include"Queue.h"
#include<fstream>
#include<iomanip>
int lvl = 2;
// lvl for debuging will be deleted later
node::node(elementType x) {
	data = x;
	left = nullptr;
	right = nullptr;
	parent = nullptr;

}
MerkleTree::MerkleTree(const char* filePath) {
	

	readFromFile(filePath);

	root = buildMerkleTree(changeListElementsToNodes(transactions)).getFront();




}
node* MerkleTree::getRootNode() {
	return root;
}
elementType MerkleTree::getMerkleRoot() {
	//Queue<node*> mydata = changeListElementsToNodes(transactions);
	//root = buildMerkleTree(mydata).getFront();
	return root->data;
}
Queue<node*> MerkleTree::changeListElementsToNodes(Queue<elementType> transactions) {
	Queue<node*> nodes;
	
	while (!transactions.isEmpty()) {
		sha256* sha = new sha256();
		// from  data queue -------> nodes queue

		// HASHING IS MISSING HERE to hash it bl maraa

		nodes.enqueue(new node(sha->hashing((transactions.getFront()))));
		transactions.dequeue();
	}


	return nodes;
}
Queue<node*> MerkleTree::buildMerkleTree(Queue<node*> transactions) {

	if (transactions.getSize() == 1) { return transactions; } //Base condition return list with only one element MERKLE ROOT.
	if (transactions.getSize() % 2 != 0) { transactions.enqueue(transactions.getBack()); } //if nodes are odd then add last element again.
	Queue<node*> updateList; // Creating a new list 



	int i = 1;
	while (!transactions.isEmpty())
	{
		sha256* sha = new sha256();

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
		node* tempNode = new node(sha->hashing(a));
		tempNode->left = leftTemp;
		tempNode->right = rightTemp;
		// pointing to parent
		leftTemp->parent = tempNode;
		rightTemp->parent = tempNode;
		if (i == 1) {
			leaves.enqueue(leftTemp);
			leaves.enqueue(rightTemp);
		}
		cout << "LeftTemp Parent is ---> " << leftTemp->parent->data << endl;
		cout << "RightTemp Parent is ---> " << rightTemp->parent->data << endl;


		//debug will be deleting later.........
		cout << "the node number " << i << " equal " << endl
			<< tempNode->data << endl << " left node = "
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

bool MerkleTree::merkleProof(int pos, elementType merkleRoot) {
	Queue<node*> x = leaves;
	cout << "X == " << endl;
	x.display();
	cout << endl;
	while (x.getSize() != pos) {
		x.dequeue();
	}
	Queue<node*> *siblingsNodes = new Queue<node*>();
	getSiblings(x.getFront(), siblingsNodes);
	string rootProof = buildProof(x.getFront(), siblingsNodes).getFront()->data;
	if (rootProof.compare(merkleRoot)==0) {
		return true;
	}
	else {
		return false;
	}
}
Queue<node*> MerkleTree:: buildProof(node* nodeFromPath,Queue<node*>* siblingNodes) {
	if (nodeFromPath->parent == nullptr) {
		Queue<node*> root = Queue<node*>();
		root.enqueue(nodeFromPath);
		return root;
	}
	else {
		sha256* sha = new sha256();
		string a = nodeFromPath->data;
		node* leftTemp = nodeFromPath;
		node* rightTemp = siblingNodes->getFront();
		a.append(siblingNodes->getFront()->data);
		siblingNodes->dequeue();

		node* temp = new node(sha->hashing(a));
		temp->left = leftTemp;
		temp->right = rightTemp;
		return buildProof(nodeFromPath->parent, siblingNodes);
	}

}
void MerkleTree::getSiblings(node* checkingNode, Queue<node*>* siblingsNodes ) {
	
	if (checkingNode->parent == nullptr) {
		siblingsNodes->display();
		
		return;
	}
	node* sibling = checkingNode->parent->left == checkingNode ? checkingNode->parent->right : checkingNode->parent->left;
	siblingsNodes->enqueue(sibling);
	getSiblings(checkingNode->parent, siblingsNodes);


}
void MerkleTree::append(elementType data) {
	transactions.enqueue(data);
	transactions.display();
	root = buildMerkleTree(changeListElementsToNodes(transactions)).getFront();

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
void MerkleTree::display(node* p, int indent)
{
	if (p != NULL) {
		if (p->right) {
			display(p->right, indent + 4);
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << p->data << "\n ";
		if (p->left) {
			std::cout << std::setw(indent) << ' ' << " \\\n";
			display(p->left, indent + 4);
		}
	}
} 



void MerkleTree::DestroyRecursive(node* node) {
	if (node)
	{
		DestroyRecursive(node->left);
		DestroyRecursive(node->right);
		delete node;
	}
}
MerkleTree::~MerkleTree() {
	
		DestroyRecursive(root);
	
}


