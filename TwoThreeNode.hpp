
#include "TwoThreeNode.h"

//Constructor
TwoThreeNode::TwoThreeNode( int value,
                               int tag, //Interior by default
                               TwoThreeNode* first,
                               TwoThreeNode* second,
                               TwoThreeNode* third,
                               TwoThreeNode* parent
                             )
{
    setTag(tag);        //Signals Leaf or Interior.
    setKey(value);      //Node Key
    setParent(parent);  //Pointer to Parent Node.
    setFirst(first);    //Pointer to First child Node.
    setSecond(second);  //Pointer to Second child Node.
    setThird(third);    //Pointer to Third child Node.
    setMinSecond(-1);   //Minimum Key of Second subtree.
    setMinThird(-1);    //Minimum Key of Third subtree.

    //NOTE minSecond and minThird are assigned from this Node's TwoThreeTree container,
    //     because they change according to the context of other Nodes in the tree
    //     upon insertion & deletion from the tree.
}

//Returns whether the Node is a Leaf
bool TwoThreeNode::isLeaf() { return m_tag == 1; }

//Parent
TwoThreeNode* TwoThreeNode::getParent() {return m_parent;}
void TwoThreeNode::setParent(TwoThreeNode* parent) {m_parent = parent;}

//First
TwoThreeNode* TwoThreeNode::getFirst() {return m_first;}
void TwoThreeNode::setFirst(TwoThreeNode* first) {m_first = first;}

//Second
TwoThreeNode* TwoThreeNode::getSecond() {return m_second;}
void TwoThreeNode::setSecond(TwoThreeNode* second) {m_second = second;}

//Third
TwoThreeNode* TwoThreeNode::getThird() {return m_third;}
void TwoThreeNode::setThird(TwoThreeNode* third) {m_third = third;}

//Key
int TwoThreeNode::getKey() {return m_key;}
void TwoThreeNode::setKey(int key) {m_key = key;}

//MinSecond
int TwoThreeNode::getMinSecond() {return m_minSecond;}
void TwoThreeNode::setMinSecond(int minSecond) {m_minSecond = minSecond;}

//MinThird
int TwoThreeNode::getMinThird() {return m_minThird;}
void TwoThreeNode::setMinThird(int minThird) {m_minThird = minThird;}

//Tag
int TwoThreeNode::getTag() {return m_tag;}
void TwoThreeNode::setTag(int tag) {m_tag = tag;}
