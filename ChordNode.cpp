#include "ChordNode.h"

#include <iostream>
#include <cassert>
#include "Config.h"

using namespace std;

ChordNode::ChordNode(int id): id(id)
{
  successor = this;
}

/**
 * Naive search
 */
ChordNode* ChordNode::lookup(int id) const
{
  #if TRACE == 1
  cout << id << " in (" << this->id << ", " << successor->get_id() << "] ?";
  #endif

  if(n_in_inter(id, this->id, 1, successor->get_id(), 0))
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

/**
 * Finger using search
 */
ChordNode* ChordNode::find_sucessor(int id) const
{
  #if TRACE == 1
  cout << id << " in (" << this->id << ", " << successor->get_id() << "] ?";
  #endif

  if(n_in_inter(id, this->id, 1, successor->get_id(), 0))
  {
    #if TRACE == 1
    cout << " yes" << endl;
    #endif

    return successor;
  }
  #if TRACE == 1
  cout << " no" << endl;
  #endif

  for(int i = 5; i > 0; i--)
  {
    #if TRACE == 1
    cout << "\tfinger[" << i << "] in (" << this->id << ", " << id << ") ?";
    #endif

    if(n_in_inter(finger[i]->get_id(), this->id, 1, id, 1))
    {
      #if TRACE == 1
      cout << " yes" << endl;
      #endif

      return finger[i]->find_sucessor(id);
    }

    #if TRACE == 1
    cout << " no" << endl;
    #endif
  }
}

void ChordNode::fix_fingers()
{
  next++;
  next %= 6;
  int to_lookup = (id + (1 << next)) % 64;
  set_finger(lookup(to_lookup), next);
}

int ChordNode::n_in_inter(int n, int a, int strict_a, int b, int strict_b) const
{
  int cond_a, cond_b = 0;

  if(strict_a) cond_a = (n>a);
  else cond_a = (n>=a);

  if(strict_b) cond_b = (n<b);
  else cond_b = (n<=b);

  // Normal case
  if(b > a) return (cond_a && cond_b);

  // The interval crosses the loop point
  else return (cond_a || cond_b);
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
