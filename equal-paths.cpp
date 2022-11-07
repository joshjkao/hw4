#include "equal-paths.h"
using namespace std;

// #include <iostream>


// You may add any prototypes of helper functions here
bool help(Node* root, int height, int& target) {
  if (root == NULL) {
    return true;
  }
  else if (root->right == NULL && root->left == NULL) {
    if (target == 0) {
      target = height;
      return true;
    }
    else {
      return height == target;
    }
  }
  else {
    bool left = true;
    bool right = true;
    if (root->left != NULL) {
      left = help(root->left, height+1, target);
    }
    if (root->right != NULL) {
      right = help(root->right, height+1, target);
    }
    if (left && right) return true;
    else return false;
  }
}

bool equalPaths(Node * root)
{
    // Add your code below
  int target = 0;
  return help(root, 0, target);
}
