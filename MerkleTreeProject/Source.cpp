#include<iostream>;
#include<stdlib.h>;
#include<string>
#include<list>
#include "MerkleTree.h"

using namespace std;


int main() {

	list<string> myTransactions = { ("12"),("34"),("X6"),("78"),("YG") };
	MerkleTree merkleTree(myTransactions);
	cout << "THE MERKLE ROOT IS : " << endl;
	cout<<merkleTree.getMerkleRoot()->data;






	return 0;
}