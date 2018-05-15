#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

List<int> * slow_list(int n) {

  // placeholder
  return nullptr;
}

int main(int argc, char *argv[]){
  List<int> *list = new List<int>();
  List<string> *list2 = new List<string>();
  List<string> *list3 = new List<string>();
  int x;
  int n, ndel;

  n = 1000;

  if(argc == 2) {
    n = atoi(argv[1]);
  }


  for(x=1; x<=4; x++) {
    list->push_front(x);
  }
  list->print();

  for(x=1; x<=4; x++) {
    list->push_back(x);
  }

  list->print();

  list->pop_front(x);
  cout << "popped " << x <<endl;
  list->print();

  list->slow_remove_all(2);
  cout << "after remove-all(2):\n";
  list->print();
  list->print_rev();

  // string words[] = {"hello", "goodbye", "sunrise", "sunset"};
  string words[] = {"alice", "bob", "cathy", "donald"};


  for(int i=0; i<4; i++) {
      list2->push_front(words[i]);
      list3->push_back(words[i]);
  }

  list2->print();
  list3->print();

  cout << "list  sorted?  " << list->is_sorted() << endl;
  cout << "list2 sorted?  " << list2->is_sorted() << endl;
  cout << "list3 sorted?  " << list3->is_sorted() << endl;


  // list2->front = NULL;
  

  delete list;
  delete list2;
  delete list3;

  /***  UNCOMMENT THIS CODE ONCE YOU HAVE WRITTEN YOUR
   *     slow_list FUNCTION

  list = slow_list(n);

  cout << "starting slow_remove_all (n=" << n << ")" << endl;
  ndel = list->slow_remove_all(0);
  cout << "slow_remove_all done!" << endl;
  cout << "    num-deleted:    " << ndel << endl;
  cout << "    list-len after: " << list->length()   << endl;

  delete list;

  ***/
  getchar();
  return 0;
}
