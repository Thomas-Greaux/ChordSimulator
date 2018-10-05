#ifndef _CHORDNODE_H_
#define _CHORDNODE_H_

class ChordNode
{
private:
  int id;
  ChordNode* successor = nullptr;
  ChordNode* predecessor = nullptr;
  ChordNode* finger[6] = {nullptr};

public:
  ChordNode(int id);

  // Chord methods
  void join(ChordNode* known_node);
  void stabilize();
  void notify(ChordNode* x);
  void check_predecessor();
  ChordNode* lookup(int id) const;
  ChordNode* find_successor(int id);
  int next = 0;
  void fix_fingers();

  // Helpers methods
  int n_in_inter(int n, int a, int strict_a, int b, int strict_b) const;

  // Getters
  int get_id() const;
  ChordNode* get_predecessor() const;
  ChordNode* get_successor() const;

  // Setters
  void set_successor(ChordNode* const successor);
  void set_predecessor(ChordNode* const predecessor);
  void set_finger(ChordNode* const finger_i, int i);

  // Displays
  void print_fingers() const;
};

#endif
