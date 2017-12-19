// James Mathew
// p3.cpp
// Implements the tree class and its functions

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tree.h"
using namespace std;

int main()
{
  srand(time(0));	
  int maxDigits = 19;
  int maxNum = 100;
  int val = rand() % maxNum;
  Tree newTree(val);
  Tree copyTree(val);
  Tree assTree(val);
  
  int* inputNums = new int[maxDigits + 1];
  inputNums[0] = val;
  for (int i = 0; i < maxDigits;) { // adds values to trees
    val = rand() % maxNum;
    if (i % 2 == 0) {
      copyTree.insertVal(val);
    }
    if (i % 3 == 0) {
      assTree.insertVal(val);
    }
    if (newTree.insertVal(val)) {
      inputNums[i+1] = val;
      i++;
      
    }
  } 
  // testing print
  cout << "inorder copyTree " << endl;
  copyTree.printInOrder();
  cout << "inorder assTree " << endl;
  assTree.printInOrder();
  cout << "preOrder " << endl;
  newTree.printPreOrder(); 
  cout << ""<< endl;
  cout << "inorder " << endl;
  newTree.printInOrder();
  
  // testing findVal
  cout << ""<< endl;
  for (int i = 0; i < maxDigits + 1; i++) {
    if(newTree.findVal(inputNums[i])) {
      cout << inputNums[i] << " is in the tree." << endl;
    }
  }
  
  // testing max, min and height
  cout << ""<< endl;
  cout << "min is " << newTree.min() <<endl; // testing min
  
  cout << ""<< endl;
  cout << "max is " << newTree.max() <<endl; // tesing max
  
  cout << ""<< endl;
  cout << "height is " << newTree.height() <<endl; // tesing max
  
  // testing remove
  int x;
  for (int i = 0; i < 5; i++) {
    x = rand() % (maxDigits + 1);
    cout << ""<< endl;
    cout << "removing "<< inputNums[x] << endl;
    newTree.remove(inputNums[x]);
  }
  
  // testing copy constructor and assignment operator
  cout << ""<< endl;
  cout << "inorder " << endl;
  newTree.printInOrder();
  cout << ""<< endl;
  copyTree = Tree(newTree);
  cout << "copy tree after copy" << endl;
  copyTree.printInOrder();
  cout << ""<< endl;
  assTree = newTree;
  cout << "ass tree after copy" << endl;
  assTree.printInOrder();
  delete[] inputNums;
  return 0;
}
