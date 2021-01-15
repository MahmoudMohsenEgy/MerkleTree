#include<iostream>;
#include<stdlib.h>;
#include<string>
#include<list>
#include "MerkleTree.h"
#include "SHA.h"

using namespace std;


int main() {

	const char* myfile = "sample.txt";
	MerkleTree* merkleTree = new MerkleTree(myfile);
	cout << merkleTree->getMerkleRoot() << endl;
	cout << endl << endl << endl;
	cout << "PROOOOOF =======" << merkleTree->merkleProof(3,"d8c131f9a5fdb77781dc1538cbb12ebd5ff67f5ebad2f4ef1b8a9cdcf3cfc91") << endl;
	system("pause");
	merkleTree->append("e");
	cout << merkleTree->getMerkleRoot() << endl;
	cout << endl << endl << endl;
	cout << "PROOOOOF =======" << merkleTree->merkleProof(3, "d8c131f9a5fdb77781dc1538cbb12ebd5ff67f5ebad2f4ef1b8a9cdcf3cfc91") << endl;

	

	
	return 0;
}