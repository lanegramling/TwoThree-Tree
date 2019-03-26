#ifndef TWOTHREETREE_H
#define TWOTHREETREE_H

#include <iostream>
#include "TwoThreeNode.h"

class TwoThreeTree {

public:



//Constructor - initializes a root node to nullptr.
TwoThreeTree();

//Destructor
~TwoThreeTree();

//Destroy a subtree
void destroyTree(TwoThreeNode* subtree);

//Insert a given value to the tree
void insert(int value, TwoThreeNode* subtree=nullptr);

//Perform a general case insertion on a 2 or 3 Node, provided a Node
void performInsertion(TwoThreeNode* newLeaf);

//Propagate changes up a tree to keep it balanced with accurate minKeys.
void propagateChanges(TwoThreeNode* leftInterior, TwoThreeNode* rightInterior=nullptr);

//Turn a leaf node into an interior node - helper method
void toInterior(int newValue, TwoThreeNode* node);

//Delete the minimum value from the tree.
TwoThreeNode* deleteMin(TwoThreeNode* subtree=nullptr, bool verbose=true);

//Delete the maximum value from the tree.
TwoThreeNode* deleteMax(TwoThreeNode* subtree=nullptr, bool verbose=true);

//Delete a given value from the tree.
void erase(int value, TwoThreeNode* subtree=nullptr);

//Find a given value in the tree.
TwoThreeNode* find(int value, TwoThreeNode* subtree=nullptr, bool verbose=true, bool inserting=false);

//Find the minimum value in the tree.
TwoThreeNode* findMin(TwoThreeNode* subtree=nullptr, bool verbose=true);

//Find the maximum value in the tree.
TwoThreeNode* findMax(TwoThreeNode* subtree=nullptr, bool verbose=true);

//Find Parent Node of a value to insert - helper method
TwoThreeNode* findParent(int value, TwoThreeNode* subtree);

//Print out all elements using level order.
void levelorder(TwoThreeNode* subtree=nullptr);


private:

TwoThreeNode* m_root; //Root node


//Semantically friendly Tag constants
const int LEAF = 1;
const int INTERIOR = 0;

};

#include "TwoThreeTree.hpp"


#endif
