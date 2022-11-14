#include <iostream>
#include <map>
#include <set>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests

  srand(0);
  // AVLTree<int,int> it;
  // bool running = true;
  // for (int n = 0; n < 50 && running; n++) {
  //   for (int i = 0; i < 8 && running; i++) {
  //     int randi = rand() % 100;
  //     it.insert(std::make_pair(randi,i));
  //     cout << "inserting " << randi << std::endl;
  //     if (!it.isBalanced()) {
  //       cout << "balanced failed" << std::endl;
  //       running = false;
  //     }
  //     it.print();
  //   }
  //   it.clear();
  // }

  AVLTree<int, double> bst;
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(4, 1.0));
  bst.print();
	bst.remove(1);

  bst.print();

  // BinarySearchTree<int, int> at;

    // AVL Tree Tests
    
    
    // at.print();

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    // return 0;
}
