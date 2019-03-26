#ifndef TWOTHREENODE_H
#define TWOTHREENODE_H

class TwoThreeNode
{


public:

//Constructor
TwoThreeNode(int value=-1,
             int tag=0,  //Interior by default
             TwoThreeNode* first=nullptr,
             TwoThreeNode* second=nullptr,
             TwoThreeNode* third=nullptr,
             TwoThreeNode* parent=nullptr
            );

//Returns whether the Node is a leaf or interior
bool isLeaf();

/*Getters & Setters for each member*/

TwoThreeNode* getParent();
void setParent(TwoThreeNode* parent=nullptr);

TwoThreeNode* getFirst();
void setFirst(TwoThreeNode* first=nullptr);

TwoThreeNode* getSecond();
void setSecond(TwoThreeNode* second=nullptr);

TwoThreeNode* getThird();
void setThird(TwoThreeNode* third=nullptr);

int getKey();
void setKey(int key);

int getMinSecond();
void setMinSecond(int minSecond);

int getMinThird();
void setMinThird(int minThird);

int getTag();
void setTag(int tag);




private:

  //Private members of a 2-3 Node
  int m_key;
  int m_minSecond;           //Minimum key of second subtree
  int m_minThird;            //Minimum key of third subtree

  TwoThreeNode* m_parent; //Pointer to parent

  TwoThreeNode* m_first;  //Pointer to first child
  TwoThreeNode* m_second; //Pointer to second child
  TwoThreeNode* m_third;  //Pointer to third child

  int m_tag;                 //Tag: 0=Interior | 1=Leaf

};

#include "TwoThreeNode.hpp"

#endif
