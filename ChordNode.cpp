#include "ChordNode.h"

#include <iostream>
#include <cassert>
#include "Config.h"

using namespace std;

ChordNode::ChordNode(int id): id(id)
{
  successor = this;
}

ChordNode* ChordNode::lookup(int id) const
{
  #if TRACE == 1
  cout << "id in (" << this->id << ", " << successor->get_id() << "] ?";
  #endif

  if((id > this->id) && (id <= successor->get_id()))
  {
    #if TRACE == 1
    cout << " yes" << endl;
    #endif

    return successor;
  }
  #if TRACE == 1
  cout << " no" << endl;
  #endif

  return successor->lookup(id);
}

void ChordNode::fix_fingers()
{
  static int next = 0;
  next++;
  next %= 6;
  set_finger(lookup(id + (1 << (next))), next);
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

void ChordNode::print_fingers() const
{
  for(int i = 0; i<6; i++)
  {
    if(finger[i] != nullptr) cout << "finger[" << i << "]: " << finger[i]->get_id() << endl;
  }
  cout << endl;
}
