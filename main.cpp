#include <iostream>

#include "Config.h"
#include "ChordNode.h"

using namespace std;

int main()
{
  cout << "Hello world!" << endl << TRACE << endl;

  // Node creation
  ChordNode N1(1);
  ChordNode N8(8);
  ChordNode N14(14);
  ChordNode N21(21);
  ChordNode N32(32);
  ChordNode N38(38);
  ChordNode N42(42);
  ChordNode N48(48);
  ChordNode N51(51);
  ChordNode N56(56);

  // Chord Ring
  N1.set_predecessor(&N56);
  N1.set_successor(&N8);

  N8.set_predecessor(&N1);
  N8.set_successor(&N14);

  N14.set_predecessor(&N8);
  N14.set_successor(&N21);

  N21.set_predecessor(&N14);
  N21.set_successor(&N32);

  N32.set_predecessor(&N21);
  N32.set_successor(&N38);

  N38.set_predecessor(&N32);
  N38.set_successor(&N42);

  N42.set_predecessor(&N38);
  N42.set_successor(&N48);

  N48.set_predecessor(&N42);
  N48.set_successor(&N51);

  N51.set_predecessor(&N48);
  N51.set_successor(&N56);

  N56.set_predecessor(&N51);
  N56.set_successor(&N1);

  /*
  cout << "N1 lookup 51 : " << endl;
  //N1.lookup(51);
  cout << "N32 lookup 51 : " << N32.lookup(51) << endl << endl;

  cout << "N1 lookup 49 : " << N32.lookup(49) << endl;
  cout << "N1 lookup 50 : " << N1.lookup(50) << endl;
  */

  for(int i = 0; i<6; i++)
  {
    N1.fix_fingers();
    N8.fix_fingers();
    N14.fix_fingers();
    N21.fix_fingers();
    N32.fix_fingers();
    N38.fix_fingers();
    N42.fix_fingers();
    N48.fix_fingers();
    N51.fix_fingers();
    N56.fix_fingers();
  }

  N1.print_fingers();
  N8.print_fingers();
  N14.print_fingers();
  N21.print_fingers();
  N32.print_fingers();
  N38.print_fingers();
  N42.print_fingers();
  N48.print_fingers();
  N51.print_fingers();
  N56.print_fingers();

  N8.lookup(54);
  cout << "----------" << endl;
  N8.find_sucessor(54);
  cout << "----------" << endl;
  N14.find_sucessor(4);

  return 0;
}
