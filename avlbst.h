#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key,Value>* addNode(const std::pair<const Key, Value> &new_item);
    void insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
    void removeFix(AVLNode<Key,Value>* n, int8_t diff);
    void rotateRight(AVLNode<Key,Value>* node);
    void rotateLeft(AVLNode<Key,Value>* node);
};

// Performs a right rotation on n
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n) {
  if (n == NULL || n->getLeft() == NULL) return;
  AVLNode<Key,Value>* p = n->getParent();
  AVLNode<Key,Value>* l = n->getLeft();
  if (p == NULL) {
    BinarySearchTree<Key,Value>::root_ = l;
    l->setParent(NULL);
  }
  else {
    if (n == p->getLeft()) p->setLeft(l);
    else p->setRight(l);
    l->setParent(p);
  }
  n->setLeft(l->getRight());
  if (n->getLeft() != NULL) n->getLeft()->setParent(n);
  l->setRight(n);
  n->setParent(l);
}

// Performs a left rotation on n
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n) {
  if (n == NULL || n->getRight() == NULL) return;
  AVLNode<Key,Value>* p = n->getParent();
  AVLNode<Key,Value>* r = n->getRight();
  if (p == NULL) {
    BinarySearchTree<Key,Value>::root_ = r;
    r->setParent(NULL);
  }
  else {
    if (n == p->getLeft()) p->setLeft(r);
    else p->setRight(r);
    r->setParent(p);
  }
  n->setRight(r->getLeft());
  if (n->getRight() != NULL) n->getRight()->setParent(n);
  r->setLeft(n);
  n->setParent(r);
}

// Helper function that walks down the tree, inserts a node, and returns its address
// Assumes that the tree is not empty
// If the key is already in the tree, update the value and return NULL
template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::addNode(const std::pair<const Key, Value> &new_item) {
    AVLNode<Key,Value>* curr = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::root_);
    while (curr != NULL) {
        if (new_item.first < curr->getKey()) {
            if (curr->getLeft() == NULL) {
                AVLNode<Key,Value>* newnode = new AVLNode<Key,Value>(new_item.first,new_item.second,curr);
                curr->setLeft(newnode);
                return newnode;
            }
            else {
                curr = curr->getLeft();
            }
        }
        else if (curr->getKey() == new_item.first) {
            curr->setValue(new_item.second);
            return NULL;
        }
        else {
            if (curr->getRight() == NULL) {
                AVLNode<Key,Value>* newnode = new AVLNode<Key,Value>(new_item.first,new_item.second,curr);
                curr->setRight(newnode);
                return newnode;
            }
            else {
                curr = curr->getRight();
            }
        }
    }
    return NULL;
}

// Recursive helper function to fix balance
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n) {
  if (p == NULL || p->getParent() == NULL) return;
  AVLNode<Key,Value>* g = p->getParent();
  if (p == g->getLeft()) {
    g->updateBalance(-1);
    if (g->getBalance() == 0) {
      return;
    }
    else if (g->getBalance() == -1) {
      insertFix(g,p);
      return;
    }
    else {
      if (p->getKey() > n->getKey()) {
        rotateRight(g);
        g->setBalance(0);
        p->setBalance(0);
        return;
      }
      else {
        rotateLeft(p);
        rotateRight(g);
        if (n->getBalance() == -1) {
          p->setBalance(0);
          g->setBalance(1);
          n->setBalance(0);
        }
        else if (n->getBalance() == 0) {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        else {
          p->setBalance(-1);
          g->setBalance(0);
          n->setBalance(0);
        }
        return;
      }
    }
  }
  else {
    g->updateBalance(1);
    if (g->getBalance() == 0) {
      return;
    }
    else if (g->getBalance() == 1) {
      insertFix(g,p);
      return;
    }
    else {
      if (p->getKey() < n->getKey()) {
        rotateLeft(g);
        g->setBalance(0);
        p->setBalance(0);
        return;
      }
      else {
        rotateRight(p);
        rotateLeft(g);
        if (n->getBalance() == 1) {
          p->setBalance(0);
          g->setBalance(-1);
          n->setBalance(0);
        }
        else if (n->getBalance() == 0) {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        else {
          p->setBalance(1);
          g->setBalance(0);
          n->setBalance(0);
        }
        return;
      }
    }
  }
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
  if (BinarySearchTree<Key,Value>::root_ == NULL) {
    BinarySearchTree<Key,Value>::root_ = new AVLNode<Key,Value>(new_item.first, new_item.second, NULL);
  }
  else {
    AVLNode<Key,Value>* newnode = addNode(new_item);
    if (newnode != NULL) {
      if (newnode->getParent()->getBalance() != 0) {
        newnode->getParent()->setBalance(0);
      }
      else {
        if (newnode == newnode->getParent()->getRight()) newnode->getParent()->setBalance(1);
        else newnode->getParent()->setBalance(-1);
        insertFix(newnode->getParent(), newnode);
      }
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key,Value>* n, int8_t diff) {
  if (n == NULL) return;
  AVLNode<Key,Value>* p = n->getParent();
  int8_t ndiff = 0;
  if (p != NULL) {
    if (n == p->getLeft()) ndiff = 1;
    else ndiff = -1;
  }
  if (diff == -1) {
    if (n->getBalance() + diff == -2) {
      AVLNode<Key,Value>* c = n->getLeft();
      if (c->getBalance() == -1) {
        rotateRight(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      else if (c->getBalance() == 0) {
        rotateRight(n);
        n->setBalance(-1);
        c->setBalance(1);
      }
      else {
        AVLNode<Key,Value>* g = c->getRight();
        rotateLeft(c);
        rotateRight(n);
        if (g->getBalance() == 1) {
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        }
        else if (g->getBalance() == 0) {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else {
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    else if (n->getBalance() + diff == -1) {
      n->setBalance(-1);
    }
    else {
      n->setBalance(0);
      removeFix(p, ndiff);
    }

  }
  else {
    if (n->getBalance() + diff == 2) {
      AVLNode<Key,Value>* c = n->getRight();
      if (c->getBalance() == 1) {
        rotateLeft(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      else if (c->getBalance() == 0) {
        rotateLeft(n);
        n->setBalance(1);
        c->setBalance(-1);
      }
      else {
        AVLNode<Key,Value>* g = c->getLeft();
        rotateRight(c);
        rotateLeft(n);
        if (g->getBalance() == -1) {
          n->setBalance(0);
          c->setBalance(1);
          g->setBalance(0);
        }
        else if (g->getBalance() == 0) {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else {
          n->setBalance(-1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    else if (n->getBalance() + diff == 1) {
      n->setBalance(1);
    }
    else {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
  AVLNode<Key,Value>* n = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::internalFind(key));
  if (n == NULL) return;
  else {
    AVLNode<Key,Value>* l = n->getLeft();
    AVLNode<Key,Value>* r = n->getRight();
    int8_t diff = 0;
    if (l != NULL && r != NULL) {
      AVLNode<Key,Value>* pred = static_cast<AVLNode<Key,Value>*>(this->predecessor(n));
      nodeSwap(pred, n);
    }
    AVLNode<Key,Value>* p = n->getParent();
    if (p != NULL) {
      if (n == p->getLeft()) diff = 1;
      else diff = -1;
      this->singleChildRemove(n);
      removeFix(p,diff);
    }
    else {
      this->singleChildRemove(n);
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
