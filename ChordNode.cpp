#include "ChordNode.h"

#include <iostream>
#include <cassert>
#include "Config.h"

using namespace std;

ChordNode::ChordNode(int id): id(id)
{
  successor = this;
}

int ChordNode::lookup(int id) const
{
  #if TRACE == 1
  cout << "id in (" << this->id << ", " << successor->get_id() << "] ?";
  #endif

  if((id > this->id) && (id <= successor->get_id()))
  {
    #if TRACE == 1
    cout << " yes" << endl;
    #endif

    return successor->get_id();
  }
  #if TRACE == 1
  cout << " no" << endl;
  #endif

  return successor->lookup(id);
}

int ChordNode::get_id() const
{
  return id;
}

void ChordNode::set_successor(ChordNode* const successor)
{
  this->successor = successor;
}

void ChordNode::set_predecessor(ChordNode* const predecessor)
{
  this->predecessor = predecessor;
}

void ChordNode::set_finger(ChordNode* const finger_i, int i)
{
  if(i > 5) assert(0);
  this->finger[i] = finger_i;
}
