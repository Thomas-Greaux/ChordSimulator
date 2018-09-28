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
  ChordNode* lookup(int id) const;
  void fix_fingers();

  // Getters
  int get_id() const;

  // Setters
  void set_successor(ChordNode* const successor);
  void set_predecessor(ChordNode* const predecessor);
  void set_finger(ChordNode* const finger_i, int i);

  // Displays
  void print_fingers() const;
};

#endif
