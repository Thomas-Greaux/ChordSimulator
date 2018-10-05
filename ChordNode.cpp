#include "ChordNode.h"

#include <iostream>
#include <cassert>
#include "Config.h"

using namespace std;

ChordNode::ChordNode(int id): id(id)
{
  successor = this;
}

void ChordNode::join(ChordNode* known_node)
{
  predecessor = nullptr;
  successor = known_node->find_successor(id);
  #ifdef TRACE_JOIN
  cout << "N" << id << ".join(" << known_node->id << ") " << endl;
  cout << "\tpredecessor = nullptr" << endl << "\tsuccessor = " << successor->get_id() << endl;
  #endif
}

void ChordNode::stabilize()
{
  #ifdef TRACE_STABILIZE
  cout << "N" << id << ".stabilize()" << endl;
  #endif
  ChordNode* x = successor->get_predecessor();
  if(x != nullptr)
  {
    #ifdef TRACE_STABILIZE
    cout << "\tx = N" << x->get_id() << endl;
    cout << "\tN" << x->get_id() << " in (" << id << ", " << successor->get_id() << ") ? ";
    #endif
    if(n_in_inter(x->get_id(), id, 1, successor->get_id(), 1))
    {
      successor = x;
      #ifdef TRACE_STABILIZE
      cout << "yes" << endl;
      cout << "\tsuccessot = N" << x->get_id() << endl;
      #endif
    }
    else
    {
      #ifdef TRACE_STABILIZE
      cout << "no" << endl;
      #endif
    }
  }
  successor->notify(this);
}

void ChordNode::notify(ChordNode* x)
{
  #ifdef TRACE_STABILIZE
  cout << "\tN" << id << ".stabilize(" << x->get_id() << ")" << endl;
  cout << "\t\tpredecessor == nullptr || N" << x->get_id() << " in (" << predecessor->get_id() << ", " << id << ") ? ";
  #endif
  if(predecessor == nullptr || n_in_inter(x->get_id(), predecessor->get_id(), 1, id, 1))
  {
    predecessor = x;
    #ifdef TRACE_STABILIZE
    cout << "yes" <<  endl;
    cout << "\t\tpredecessor = N" << x->get_id() << endl;
    #endif
  }
  else
  {
    #ifdef TRACE_STABILIZE
    cout << "no" <<  endl;
    #endif
  }
}

void ChordNode::check_predecessor()
{
  /* TODO : simulate network */
}

/**
 * Naive search
 */
ChordNode* ChordNode::lookup(int id) const
{
  #ifdef TRACE_LOOKUP
  cout << id << " in (" << this->id << ", " << successor->get_id() << "] ?";
  #endif

  if(n_in_inter(id, this->id, 1, successor->get_id(), 0))
  {
    #ifdef TRACE_LOOKUP
    cout << " yes" << endl;
    #endif

    return successor;
  }
  #ifdef TRACE_LOOKUP
  cout << " no" << endl;
  #endif

  return successor->lookup(id);
}

/**
 * Finger-using search
 */
ChordNode* ChordNode::find_successor(int id)
{
  #ifdef TRACE_FIND_SUCCESSOR
  cout << "N" << this->id << ".find_successor(" << id << ")" << endl;
  cout << "\t" << id << " in (" << this->id << ", " << successor->get_id() << "] ?";
  #endif

  if(n_in_inter(id, this->id, 1, successor->get_id(), 0))
  {
    #ifdef TRACE_FIND_SUCCESSOR
    cout << " yes" << endl;
    cout << "\treturn " << successor->get_id() << endl;
    #endif

    return successor;
  }
  #ifdef TRACE_FIND_SUCCESSOR
  cout << " no" << endl;
  #endif

  for(int i = 5; i > 0; i--)
  {
    #ifdef TRACE_FIND_SUCCESSOR
    cout << "\tfinger[" << i << "] = N" << finger[i]->get_id() << " in (" << this->id << ", " << id << ") ?";
    #endif

    if(finger[i] != nullptr)
    {
      if(n_in_inter(finger[i]->get_id(), this->id, 1, id, 1))
      {
        #ifdef TRACE_FIND_SUCCESSOR
        cout << " yes" << endl;
        #endif

        return finger[i]->find_successor(id);
      }
    }

    #ifdef TRACE_FIND_SUCCESSOR
    cout << " no" << endl;
    #endif
  }
  cout << "BP" << endl;
  return this;
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
  if(b >= a) return (cond_a && cond_b);

  // The interval crosses the loop point
  else return (cond_a || cond_b);
}

int ChordNode::get_id() const
{
  return id;
}

ChordNode* ChordNode::get_predecessor() const
{
  return predecessor;
}

ChordNode* ChordNode::get_successor() const
{
  return successor;
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
  cout << "N" << id << "'s finger table:" << endl;
  for(int i = 0; i<6; i++)
  {
    if(finger[i] != nullptr) cout << "\tfinger[" << i << "]: " << finger[i]->get_id() << endl;
  }
  cout << endl;
}
