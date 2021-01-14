#include<iostream>;
#include<stdlib.h>;
#include<string>
#include<list>
#include "MerkleTree.h"
#include "SHA.h"

using namespace std;


int main() {

	/*Queue<string> *myTransactions = new Queue<string>();
	myTransactions->enqueue("as");
	myTransactions->enqueue("23");
	myTransactions->enqueue("54");
	myTransactions->enqueue("bl");*/
	const char* myfile = "sample.txt";
	MerkleTree* merkleTree = new MerkleTree(myfile);
	cout << merkleTree->getMerkleRoot() << endl;

	/*cout << "THE MERKLE ROOT IS : " << endl;
	cout<<merkleTree.getMerkleRoot()->data;
	cout << endl;*/


	//displayHash("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	return 0;
}