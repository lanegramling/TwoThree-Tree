

#include "TwoThreeTree.h"



//Constructor - initializes a root node to nullptr.
TwoThreeTree::TwoThreeTree() {
  m_root = nullptr;
}

//Destructor
TwoThreeTree::~TwoThreeTree() {


}

//Destroy a subtree
void TwoThreeTree::destroyTree(TwoThreeNode* subtree) {


}

//Insert a given value to the tree
void TwoThreeTree::insert(int value, TwoThreeNode* subtree) {
  if (!find(value, m_root)) {
    TwoThreeNode* newLeaf = new TwoThreeNode(value, LEAF);  //Create new leaf Node
    if (!m_root) m_root = newLeaf;                          //Empty tree case
    else if (m_root->isLeaf()) toInterior(value, m_root);   //Singleton tree case
    else performInsertion(newLeaf);                //General case
  }
}

void TwoThreeTree::performInsertion(TwoThreeNode* newLeaf) {
  //insertionPoint will be the parent INTERIOR Node that newLeaf will be inserted to.
  //inserting=true changes find() to return the insertion point of a value.
  TwoThreeNode* insertionPoint = find(newLeaf->getKey(), m_root, false, true);

  newLeaf->setParent(insertionPoint);

  //Properly order children of insertionPoint
  if (insertionPoint->getMinThird() == -1) {  //Inserting to 2-Node
    if (newLeaf->getKey() < insertionPoint->getFirst()->getKey()) {         //Inserting as first child
      insertionPoint->setThird(insertionPoint->getSecond());
      insertionPoint->setSecond(insertionPoint->getFirst());
      insertionPoint->setFirst(newLeaf);
    } else if (newLeaf->getKey() < insertionPoint->getSecond()->getKey()) { //Inserting as second child
      insertionPoint->setThird(insertionPoint->getSecond());
      insertionPoint->setSecond(newLeaf);
    } else insertionPoint->setThird(newLeaf);                               //Inserting as third child
    insertionPoint->setMinSecond(findMin(insertionPoint->getSecond())->getKey());
    insertionPoint->setMinThird(findMin(insertionPoint->getThird())->getKey());
    propagateChanges(insertionPoint);  //Update the minimums through the tree to be representative
  } else {                                    //Inserting to 3-Node
    //Need to split the insertion point node
    TwoThreeNode* splitInsertion = new TwoThreeNode(-1, INTERIOR, insertionPoint->getParent());

    //Perform split - original parent keeps the smaller two values
    if (newLeaf->getKey() < insertionPoint->getFirst()->getKey()) {         //Inserting as first child
      splitInsertion->setFirst(insertionPoint->getSecond());
      splitInsertion->setSecond(insertionPoint->getThird());
      insertionPoint->setSecond(insertionPoint->getFirst());
      insertionPoint->setFirst(newLeaf);
    } else if (newLeaf->getKey() < insertionPoint->getSecond()->getKey()) { //Inserting as second child
      splitInsertion->setFirst(insertionPoint->getSecond());
      splitInsertion->setSecond(insertionPoint->getThird());
      insertionPoint->setSecond(newLeaf);
    } else if (newLeaf->getKey() < insertionPoint->getThird()->getKey()) {  //Inserting as third child (first in split)
      splitInsertion->setFirst(newLeaf);
      splitInsertion->setSecond(insertionPoint->getThird());
      insertionPoint->setThird(nullptr);
    } else {                                                                //Inserting as fourth child (second in split)
      splitInsertion->setFirst(insertionPoint->getThird());
      splitInsertion->setSecond(newLeaf);
      insertionPoint->setThird(nullptr);
    }
    insertionPoint->setMinSecond(findMin(insertionPoint->getSecond())->getKey());
    splitInsertion->setMinSecond(findMin(splitInsertion->getSecond())->getKey());
    insertionPoint->setMinThird(-1);
    splitInsertion->setMinThird(-1);
    propagateChanges(insertionPoint, splitInsertion); //Propagates a tree split up the tree.
  }
}

//Propagates changes to the tree up to the root. This will update changes in minimums and
//split any interior 3-nodes it encounters. RightInterior contains any nodes that were
//split from interior 3-nodes.
void TwoThreeTree::propagateChanges(TwoThreeNode* leftInterior, TwoThreeNode* rightInterior) {
  //Root case
  if (leftInterior == m_root) {
    m_root = new TwoThreeNode(-1, INTERIOR, leftInterior, rightInterior);
    m_root->setMinSecond(findMin(m_root)->getKey());
  } else {  //Non-root case
    TwoThreeNode* parent = leftInterior->getParent();
    if (parent->getMinThird() == -1) {                //2-Node Parent
      if (leftInterior == parent->getFirst()) {         //rightInterior goes as middle child of parent
        parent->setThird(parent->getSecond());
        parent->setSecond(rightInterior);
      } else {                                          //rightInterior goes as third child of parent
        parent->setThird(rightInterior);
      }
    } else {                                          //3-Node parent - Need to split the parent
      TwoThreeNode* splitParent = new TwoThreeNode(-1, INTERIOR, parent->getParent());
      if (leftInterior == parent->getFirst()) {          //rightInterior goes as middle child of parent.
        splitParent->setFirst(parent->getSecond());
        splitParent->setSecond(parent->getThird());
        parent->setSecond(rightInterior);
        parent->setThird(nullptr);
      } else if (leftInterior == parent->getSecond()) {  //rightInterior goes as third child of parent (first in split)
        splitParent->setFirst(rightInterior);
        splitParent->setSecond(parent->getThird());
        parent->setThird(nullptr);
      } else {                                           //rightInterior goes as fourth child of parent (second in split)
        splitParent->setFirst(parent->getThird());
        splitParent->setSecond(rightInterior);
        parent->setThird(nullptr);
      }
      parent->setMinSecond(findMin(parent->getSecond())->getKey());
      splitParent->setMinSecond(findMin(splitParent->getSecond())->getKey());
      parent->setMinThird(-1);
      splitParent->setMinThird(-1);
      propagateChanges(parent, splitParent);
    }
  }
}

//node is turned into an interior Node, with originalLeaf and newLeaf are created as its children.
void TwoThreeTree::toInterior(int newValue, TwoThreeNode* node) {
  int originalLeafValue = node->getKey(); //Temporarily save value from provided Leaf Node
  node->setTag(INTERIOR);         //Make interior
  node->setKey(-1);

  //Create leaves to hold original Leaf and new Leaf's values
  TwoThreeNode* originalLeaf = new TwoThreeNode(originalLeafValue, LEAF, nullptr, nullptr, nullptr, node);
  TwoThreeNode* newLeaf = new TwoThreeNode(newValue, LEAF, nullptr, nullptr, nullptr, node);

  if (originalLeafValue < newValue) {   //Set children in order
    node->setFirst(originalLeaf);
    node->setSecond(newLeaf);
    node->setMinSecond(newValue);
  } else {
    node->setFirst(newLeaf);
    node->setSecond(originalLeaf);
    node->setMinSecond(originalLeafValue);
  }
}

//Delete a given value from the tree.
void TwoThreeTree::erase(int value, TwoThreeNode* subtree) {

}

//Delete the minimum value from the tree.
TwoThreeNode* TwoThreeTree::deleteMin(TwoThreeNode* subtree, bool verbose) {
    if (!m_root) return nullptr;
    TwoThreeNode* nodeToDelete = findMin(subtree);
    TwoThreeNode* parent = nodeToDelete->getParent();
    //Have parent and child determined, now need to delete the child properly.

}

//Delete the maximum value from the tree.
TwoThreeNode* TwoThreeTree::deleteMax(TwoThreeNode* subtree, bool verbose) {
  if (!m_root) return nullptr;
  TwoThreeNode* nodeToDelete = findMax(subtree);
  TwoThreeNode* parent = nodeToDelete->getParent();
  //Have parent and child determined, now need to delete the child properly.

}

//Find a given value in the tree. //Returns the insertion point for a value if inserting = True
TwoThreeNode* TwoThreeTree::find(int value, TwoThreeNode* subtree, bool verbose, bool inserting) {
  if (!m_root) {std::cout << "\nTree is empty."; return nullptr;}
  if (subtree->isLeaf()) {
    if (inserting) return subtree->getParent();
    else return (subtree->getKey() == value) ? subtree : nullptr;
  } else {
    if (value < subtree->getMinSecond()) return (find(value, subtree->getFirst(), false, inserting) == nullptr) ? subtree : find(value, subtree->getFirst(), false, inserting);
    else if ((subtree->getMinThird() != -1) && (value >= subtree->getMinThird())) return (find(value, subtree->getThird(), false, inserting) == nullptr) ? subtree : find(value, subtree->getThird(), false, inserting);
    else return (find(value, subtree->getSecond(), false, inserting) == nullptr) ? subtree : find(value, subtree->getSecond(), false, inserting);
  }
}

//Find the minimum value in the tree.
TwoThreeNode* TwoThreeTree::findMin(TwoThreeNode* subtree, bool verbose) {
  if (!m_root) return nullptr;
  TwoThreeNode* currentPos = (!subtree) ? m_root : subtree;
  while(currentPos->getFirst()) currentPos = currentPos->getFirst();
  return currentPos;
}

//Find the maximum value in the tree.
TwoThreeNode* TwoThreeTree::findMax(TwoThreeNode* subtree, bool verbose) {
  if (!m_root) return nullptr;
  TwoThreeNode* currentPos = (!subtree) ? m_root : subtree;
  while(currentPos->getThird()) currentPos = currentPos->getThird();
  while(currentPos->getSecond()) currentPos = currentPos->getSecond();
  return currentPos;
}

//Print out all elements using level order.
void TwoThreeTree::levelorder(TwoThreeNode* subtree) {


}
