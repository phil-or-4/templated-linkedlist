#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>
using namespace std;

template <typename T>
class List
{
  private:    

  public:
// struct for singly-linked list nodes
    struct Node
    {
      T      data;
      Node   *next;

      Node( const T & d = T{}, Node * n = nullptr)
        : data{ d },  next{ n } { }

    };

    // constructors
    List( ) { 
      init( );
    }

    ~List( ) {
      clear( );
    }
    /**
     * Disclaimer:  C++ conventions tell us that we should have a couple
     * of additional constructors here (a copy constructor, assignment operator
     * etc.)
     *
     * However, to keep things simple for now we will ignore that convention
     * (since the exposure to C++ is pretty variable it seems -- some students
     * having taken 141 before last semester; some students coming from 107,
     * etc.)
     */


    /**
     * function: clear
     * desc:  makes the calling list empty (but the list still
     *        exists).
     */
    void clear(){
      Node * p = front;
      Node *pnext;

      while(p != nullptr) {
        pnext = p->next;
        delete p;
        p = pnext;
      }
      front = back = nullptr;
	  listLength = 0;
    }





    /**
     * TODO
     *
     * function: length
     * desc:  returns the length of the calling list
     *        
     * REQUIREMENTS:  this is a working implementation, but
     *   it takes linear time.
     *
     *   Your job (todo):  make modifications so that this
     *     operation becomes constant time (O(1)).
     *
     *   This task is different from most others in that most of
     *       the "real" work you do to make this work
     *	in O(1) time will be in _other_ functions which affect
     *	the length of lists.
     *
     *	HINT:  you are free to add data members to the List class...
     *	       maybe for "bookkeeping"??
     */
    int length( ) const {
		return listLength;
    }


  public:

    // Return true if the list is empty, false otherwise.
    bool is_empty( ) const {
      return front == nullptr;
    }


    void print() const {
      Node *p = front;

      cout << "[ "; 
      while(p != nullptr) {
        cout << p->data << " ";
        p = p->next;
      }
      cout << "]\n";
    }

    void push_front(const T & data) {
      front = new Node(data, front);

      if(back == nullptr)
        back = front;
	  listLength++;			//increment the length by one
    }

    bool pop_front(T &val) {
      Node *tmp;

      if(front==nullptr)
        return false;
      val = front->data;

      tmp = front;
      front = front->next;
      delete tmp;
      if(front==nullptr)
        back = nullptr;
	  listLength--;
      return true;
    }

    void push_back(const T & val) {
      Node *tmp = new Node(val, nullptr);
	  listLength++;

      if(front == nullptr) {
        front = back = tmp;
      }
      else {
        back->next = tmp;
        back = tmp;
      }
    }

    bool remove_first(const T &x) {
      Node *p, *tmp;
      T dummy;

      if(front==nullptr) return false;
      if(front->data == x) {
        pop_front(dummy);
        return true;
      }
      p = front;
      while(p->next != nullptr) {
        if(x == p->next->data) {
          tmp = p->next;
          p->next = tmp->next;
          if(tmp == back)
            back = p;
          delete tmp;
		  listLength--;
          return true;
        }
        p = p->next;
      }
      return false;
    }

    int slow_remove_all(const T &x) {
      int n=0;

      while(remove_first(x))
        n++;
      return n;
    }

    bool is_sorted() const {
      Node *p = front;

      while(p!=nullptr && p->next != nullptr) {
        if(p->data > p->next->data)
          return false;
        p = p->next;
      }
      return true;
    }





    /** TODO
     *    function:  count
     *     description:  Counts number of occurrences 
     *     		of x in the list and returns that count.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the two lists.)
     */
    int count(const T &x) const {
		Node* p = front;
		int result = 0;

		//go through the list and count with result
		while (p != nullptr)
		{
			if (p->data == x)
			{
				result += 1;
			}
			p = p->next;
		}
		return result;
    }

    /* TODO 
     *    
     *  if list is empty, we do nothing and return arbitrary value
     *  otherwise, the last element in the list is removed and its
     *      value is returned.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the two lists.)
     *
     */
    bool pop_back(T &data) {
		Node* temp = front;
	
		//if there's only one element in the list
		if (temp == back && temp != nullptr)
		{
			data = temp->data;	//immediately return the data
			back = nullptr;		//ensure we don't point to anything
			front = back;		//set the front 
			delete temp;		//remove the element
			listLength--;
			return true;
		}

		while (temp != nullptr)
		{
			if (temp->next == back)
			{
				back = temp;		//set back to the thing before the real back
				temp = temp->next;	//move the pointer to the real back
				back->next = nullptr;	//make the new back point to nothing
				data = temp->data;	//return the data
				delete temp;		//unconnect node
				listLength--;			//update the length
				if (front == nullptr)
				{
					back = nullptr;
				}
				return true;
			}
			temp = temp->next;
		}
		return false;
    }

    /**
     * TODO:  
     *   function:  equal_to 
     *   description:  returns true(1) if lst1 and lst2
     *      contain exactly the same sequenc of values.
     *      Returns 0 otherwise.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the shorter of the two lists.
     **/
    bool equal_to(const List<T> &other) const {
		Node* otherPtr = other.front;
		Node* thisPtr = front;
		

		//if both lists are empty
		if (front == nullptr && other.front == nullptr)
		{
			return true;
		}
		if (other.front == nullptr || front == nullptr)		//first check if either list is empty, if they are return false
		{
			return false;
		}

		//if the both list have only one element
		if (otherPtr->next == nullptr && thisPtr->next == nullptr)
		{
			if (otherPtr->data != thisPtr->data)
			{
				return false;
			}
		}

		//simple length check
		if (listLength != other.listLength)
		{
			return false;
		}

		//loop til one of them are nullptr
		while (thisPtr->next != nullptr || otherPtr->next != nullptr)
		{
			if (thisPtr->data != otherPtr->data)
			{
				return false;
			}
			otherPtr = otherPtr->next;
			thisPtr = thisPtr->next;
			if (thisPtr->data != otherPtr->data)
			{
				return false;
			}
		}
		return true;
    }

    /**
     * TODO:  print in reverse order 
     *
     * Try to do without looking at notes!
     * Hints:  recursive helper function
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */
    void print_rev() const {
		Node* p = front;
		cout << "[ ";
		
		//recurse through the list
		if (p != nullptr)
		{
			print_recursive(p);
		}
		cout << "]" << endl;
    }

	void print_recursive(Node* p) const
	{
		if (p->next != nullptr)
		{
			print_recursive(p->next);
		}
		cout << p->data << " ";
	}

    /* TODO
     *  For full credit, you cannot allocate any new memory!
     *
     *  description:  self-evident 
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */
    void reverse() {
		//pop the next and push that to front ez
		Node* p = front;
		Node* toPushToFront;

		if (p == nullptr || p->next == nullptr)
		{
			//just leave if the list is empty
			return;
		}

		while (p->next->next != nullptr)
		{
			toPushToFront = p->next;			//save 2nd node
			p->next = toPushToFront->next;	//make 1 point to 2nd
			toPushToFront->next = front;		//make 2nd point to front
			front = toPushToFront;				//make 2nd the new front
		}
		toPushToFront = p->next;			//save the last node
		toPushToFront->next = front;		//make the last node point to whatevers in front
		front = toPushToFront;				//make the last node the new front
		p->next = nullptr;				//make the old first node point to nullptr
		back = p;						//finally make the p node the new back node
    }


    /** TODO
     *   function:  fast_remove_all
     *   description:  same behavior/semantics as
     *      slow_remove_all.  However, this function
     *      must guarantee linear time worst case 
     *      runtime (hence, "fast").
     *
     *   REQUIREMENT:  linear worst-case runtime.
     *
     *   Note:  your solution may be either recursive or 
     *   iteratieve.
     **/
    int fast_remove_all(const T &x) {
		Node* p = front;
		Node* next;
		Node* previous = nullptr;
		int counter = listLength;
		//if the list is empty
		if (p == nullptr)
		{
			return 0;
		}
		
		while (p != nullptr)
		{
			//if we reach a number to not delete set previous there so we can attach it to the next non-x number
			if (p->data != x)
			{
				previous = p;	//assign previous to the last non-x number
				p = p->next;	//moving right along
				continue;
			}
			else
			{
				next = p->next;			//set next
				//ensure that incase if front->data = x we move front to next and wait till p->data != x then stop moving front
				if (p == front)
				{
					front = next;
				}
				delete p;
				listLength--;			//dont forget to manage length
				p = next;				//make p point to next

				//if we reached the end then make previous non-x node the back of the list
				if (p == nullptr)
				{
					back = previous;
					if (previous != nullptr)
					{
						previous->next = nullptr;
					}
					break;
				}
				//if the next node is non-x then make previous->next point to it
				if (p->data != x && previous != nullptr)
				{
					previous->next = p;
				}
			}
		}
		//ensure front is nullptr when back is nullptr
		if (back == nullptr)
		{
			front = back;
		}
		return counter -= listLength;
    }

    /** TODO
     * function:  insert_sorted
     *
     * description:  assumes given list is already in sorted order
     *	   and inserts x into the appropriate position
     * 	   retaining sorted-ness.
     * Note 1:  duplicates are allowed.
     *
     * Note 2:  if given list not sorted, behavior is undefined/implementation
     * 		dependent.  We blame the caller.
     * 		So... you don't need to check ahead of time if it is sorted.
     *
     *
     * REQUIREMENTS:
     *
     *   O(n) runtime
     */
    void insert_sorted(const T &x) {
		Node* p = front;
		Node* previous;
		//if the list is empty just push the x in
		if (p == nullptr)
		{
			push_front(x);
			return;
		}
		//if x is >= the back then push it back
		else if (x >= back->data)
		{
			push_back(x);
			return;
		}
		//if x <= front then push it front
		else if (x <= front->data)
		{
			push_front(x);
			return;
		}

		//go through the list until p.data is becomes greater then x
		while (p->data <= x)
		{
			previous = p;		//save the previous thing before p
			p = p->next;
		}

		//make the new xNode and put x in it, then insert it between previous and p
		Node* xNode = new Node();
		xNode->data = x;
		previous->next = xNode;
		xNode->next = p;
		listLength++;
    }

    /** TODO
     * function:  merge_with
     *
     * description:  assumes both list a and b are in
     * 	sorted (non-descending) order and merges them
     * 	into a single sorted list with the same
     * 	elements.  
     *
     * 	This single sorted list is stored in a while
     * 	b becomes empty.
     *
     * 	if either of given lists are not sorted, 
     * 	we blame the caller and the behavior is
     * 	implementation dependent -- i.e., don't worry
     * 	about it!
     *
     *      Condition in which both parameters are the same
     *      list (not merely "equal"), the function simply 
     *      does nothing and returns.  This can be tested
     *      with simple pointer comparison.
     *
     * 	Example:
     *
     * 		a:  [2 3 4 9 10 30]
     * 		b:  [5 8 8 11 20 40]
     *
     * 		after call a.merge_with(b):
     *
     * 		  a:  [2 3 4 5 8 8 9 10 11 20 30 40]
     * 		  b:  []
     * 
     *
     * REQUIREMENTS:
     *
     * 	Runtime Must be linear in the length of the 
     * 	resulting merged list (or using variables above, 
     * 	O(a.length()+b.length()).
     *
     *  should not allocate ANY new list
     * 	nodes -- it should just re-link existing
     * 	nodes.
     */
    void merge_with(List<T> &other){
		Node* p = front;
		Node* previous = nullptr;
		Node* otherP = other.front;

		//if both lists are the same just return
		if (p == other.front || other.front == nullptr)
		{
			return;
		}

		//if the first list is empty just make front and back point to the other list
		if (p == nullptr)
		{
			front = other.front;
			back = other.back;
			listLength = other.listLength;
			other.front = nullptr;
			other.back = nullptr;
			other.listLength = 0;
			return;
		}

		//if the other lists front is >= front then just attach the nodes to this list
		if (back->data <= other.front->data)
		{
			back->next = other.front;
			back = other.back;
			listLength += other.listLength;
			other.front = nullptr;
			other.back = nullptr;
			other.listLength = 0;
			return;
		}

		//if the first list if populated 
		while (otherP != nullptr && p != nullptr)
		{
			//find a p where it's data is > otherP.data
			while (p != nullptr && p->data < otherP->data)
			{
				previous = p;		//remember the previous
				p = p->next;
			}

			//if we reach the end of list a
			if (p == nullptr)
			{
				//loop and just insert the rest of b into a
				while (otherP != nullptr)
				{
					other.front = other.front->next;
					insert(previous, otherP, p);
					previous = otherP;
					otherP = other.front;
				}
			}
			//if a isn't exhausted
			else
			{
				//loop an insert into a while making sure otherP.data <= p.data
				while (otherP != nullptr && otherP->data <= p->data)
				{
					other.front = other.front->next;
					insert(previous, otherP, p);
					previous = otherP;
					otherP = other.front;
				}
			}
		}
		other.listLength = 0;
		other.back = nullptr;
    }
	private:
	void insert(Node* first, Node* toInsert, Node* second)
	{
		//if we are still at the start of list a
		if (first == nullptr)
		{
			front = toInsert;	//make toInsert our new front
		}
		//if we are at the end of the list
		else if (second == nullptr)
		{
			back = toInsert;		//make toInsert our back
			first->next = toInsert;
		}
		//if we are in the middle of the list simply insert toInsert
		else
		{
			first->next = toInsert;
		}
		toInsert->next = second;
		listLength++;
	}
	public:

    /**
     * TODO
     * function:  clone
     *
     * description:  makes a "deep copy" of the given list a
     *   and returns it (as a List pointer).
     *
     * NOTE:  this functionality would normally be folded into
     *  a "copy constructor"
     *
     */
    List<T> * clone() const {
		List<T> *result = new List<T>();
		Node* p = front;
		if (p != nullptr)
		{
			//simply loop and push the values into a new List
			while (p != nullptr)
			{
				result->push_back(p->data);
				p = p->next;
			}
			return result;
		}
		delete result;		//to avoid memory leaks
		return nullptr;
    }

    /**
     * TODO
     * function:  prefix
     *
     * description:  removes the first k elements from the
     *               calling list which are used to form a new list
     *		            which is then returned.
     *
     *		if n is the length of the given list, we have the
     *		following boundary conditions:
     *
     *		  if k==0:
     *			    calling list unchanged and an empty list returned
     *		  if k>=n:
     *			    calling becomes empty and a list containing
     *			    all elements previously in lst is returned.
     *
     *		examples:
     *
     *		  EX1:  lst:  [2, 3, 9, 7, 8]
     *			k:    3
     *
     *			call:
     *
     *			  List<int> * pre = lst.prefix(3);
     *
     *			after call:
     *			   lst:  [7, 8]
     *			   returned list (prefix):  [2, 3, 9]
     *
     *		  EX2  lst:  [2, 3, 9, 7, 8]
     *			k:    0
     *
     *		  call:
     *
     *			  List<int> * pre = lst.prefix(0);
     *
     *			after call:
     *			   lst:  [2, 3, 9, 7, 8]  (unchanged)
     *			   returned list:  []
     *
     *		  EX3  lst:  [2, 3, 9, 7, 8]
     *			k:    5
     *
     *		  call:
     *
     *			  List<int> * pre = lst.prefix(5);
     *
     *			after call:
     *			   lst:  []
     *			   returned list:  [2, 3, 9, 7, 8]
     *
     * REQUIREMENTS:
     *
     *	RUNTIME:  THETA(n) worst case where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned prefix should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be 
     *                  allocated or deallocated; you should just 
     *                  "re-use" the existing nodes.  HOWEVER, you will
     *		               need to allocate a List object for the returned
     *		               prefix (but, again, the underlying Nodes should be
     *		               re-used from the calling list).
     */
    List<T> * prefix(unsigned int k) {
		List<T> *result = new List<T>();
		Node* p = front;
		Node* lastOfPrefix;

		//boundary cases
		if (k <= 0)
		{
			return result;
		}
		else if (k > listLength - 1)
		{
			result->front = front;
			result->back = back;
			result->listLength = listLength;
			listLength = 0;
			front = back = nullptr;
			return result;
		}

		int counter = 0;
		while (p != nullptr && counter < k)
		{
			lastOfPrefix = p;
			p = p->next;
			counter++;
		}

		//now that we loop to the kth position in the list simply redirect the nodes to their 
		result->front = front;
		result->back = lastOfPrefix;
		lastOfPrefix->next = nullptr;
		front = p;
		listLength -= counter;
		result->listLength += counter;
		return result;

    }

    /**
     * TODO
     * function:  filter_leq
     *
     * description:  removes all elements of the given list (lst) which
     *		are less than or equal to a given value (cutoff)
     *		
     *		A list containing the removed elements is returned.
     *
     * examples:
     *
     *	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
     *		cutoff:  4
     *
     *		after call:
     *			lst:  [9, 8, 12, 7]
     *			returned list:  [4, 2, 4, 3]
     *
     *       -----------------------------------------
     *	EX2: 	lst:  [6, 5, 2, 1]
     *		cutoff:  6
     *
     *		after call:
     *			lst:  []
     *	 		returned list:  [6, 5, 2, 1]
     *
     * REQUIREMENTS:
     *
     *	RUNTIME:  THETA(n) where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned list should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
     *		   you should just "re-use" the existing nodes.  HOWEVER, you will
     *		   need to allocate a LIST structure itself (i.e., for the returned
     *		   list).
     *			
     */
    List<T> * filter_leq(const T & cutoff) {
		List<T> *result = new List<T>();
		Node* p = front;
		Node* past = nullptr;
		Node* next;
		Node* resultPast;
		
		//if the list is empty forget it
		if (p == nullptr)
		{
			return nullptr;
		}

		//loop throught til we find a p->data <= cutoff
		while (p != nullptr)
		{
			next = p->next;				//store the next node, we'll need it after we've mangeled p
			if (p->data <= cutoff)
			{
				//setup past to point to next
				if (past != nullptr)
				{
					//back = past;
					past->next = next;
				}
				//if the result list is empty then make front = p
				if (result->front == nullptr)
				{
					result->front = result->back = p;
					p->next = nullptr;			//prepare p to be the back of the list incase there's only one item in result returned
					resultPast = result->front;			//set up resultPast
					result->back = p;			//prepare p to be the back
												//bookkeeping
					result->listLength += 1;
					listLength -= 1;
				}
				else
				{
					resultPast->next = p;	//make resultPast point to p
					result->back = p;		//make p the back
					resultPast = p;			//move the resultPast up for the next loop
					p->next = nullptr;
											//bookkeeping
					result->listLength += 1;
					listLength -= 1;
				}
				//move front to next after we've destroyed p, and front.data isn't <= cutoff
				if(front->data <= cutoff) front = next;
			}
			//if we found a p->data with > cutoff, make it the past node
			else
			{
				past = p;
			}
			//told you the next would be useful
			p = next;
		}

		//sanity check
		if (front == nullptr)
		{
			back = nullptr;
		}
		return result;
    }

    /**
     * TODO
     * function:  concat
     *
     * description:  concatenates the calling list with parameter list (other)
     *    The resulting concatenation is reflected the calling list; the 
     *    parameter list (other) becomes empty.
     *
     *    example:
     *
     *	EX1:  a: [2, 9, 1]
     *	      b: [5, 1, 2]
     *
     *	      call:  
     *	            a.concat(b);
     *
     *	after call:
     *
     *		a: [2, 9, 1, 5, 1, 2]
     *		b: []
     *
     * REQUIREMENTS:  
     *
     *     runtime:  O(1)
     *
     *     sanity:  this operation makes sense when a and b
     *		are distinct lists.  For example, we don't
     *		want/allow the caller to do something like
     *		this:
     *
     *			List<int> *my_list = new List<int>();;
     *
     *			my_list->push_front(my_lst, 4);
     *			my_list->push_front(my_lst, 2);
     *
     *			my_lst->concat(my_lst);
     *
     *		your implementation must detect if it is being
     *		called this way.  If so the function does nothing
     *		and (optionally) prints an error message to
     *		stderr.
     *	
     */
    void concat(List<T> &other) {

      if(this == &other) {
        cerr << "warning:  List::concat():  calling object same as parameter";
        cerr << "\n          list unchanged\n";
        return;
      }

	  //if our list is empty then make our front point to their front
	  if (front == nullptr) front = other.front;
	  //if our back is null also then make our back point to their back
	  if (back == nullptr)
	  {
		  back = other.back;
	  }
	  //if our list is populated, simply make our back point to other back
	  else
	  {
		  back->next = other.front;
	  }
	  //then delete the other.back and other.front
	  other.front = other.back = nullptr;
	  //bookkeeping
	  listLength += other.listLength;
	  other.listLength = 0;

      cout << "List::concat(): no error...\n";
    }


    /**
     * TODO
     *
     * function:  compare_with
     * description: compares the calling list with parameter list (other)
     *    "LEXICALLY" (essentially a generalization of dictionary
     *    ordering).
     *
     *    link:  https://en.wikipedia.org/wiki/Lexicographical_order
     *
     *    Return Value:
     *
     *       o if the two lists are identical, 0 is returned.
     *       o if the calling list is lexically BEFORE the other list,
     *             -1 is returned
     *       o otherwise, the other list is lexically before the calling
     *             list and 1 (positive one) is returned.
     *
     *    Properties and examples:
     *
     *        The empty list is lexically before all non-empty lists
     *          (you can say it is "less than" all non-empty lists).
     *
     *        Examples (using mathematical notation):
     *
     *          [2 5 1] < [3 1 1 1 1]    (think dictionary ordering!)
     *
     *          [4 1 3] < [4 1 3 0 0 0]  (prefix: just like "car" is before
     *                                            "cartoon" in the dictionary).
     * 
     *          [4 5 6 1 2 3 9 9 9] < [4 5 6 1 4 0 0] 
     *                   ^                     ^
     *                      (they have a common prefix of length 4; but at
     *                      the fifth position they differ and the left list
     *                      is the winner (smaller) -- no need to look further)
     *
     *                      
     *        Templates?
     *
     *          Since List is a template class, the elements of a particular
     *          list need not be integers.  For example, we could have
     *          lists of strings.
     *
     *          Good news:  the exact same principle applies because 
     *          strings can be compared just like integers can be compared!
     *
     *          Great news:  you don't need to think about this at all!
     *          The exact same code you would write if you assumed the element
     *          type is integer will work for other types like strings.
     *
     *          Why?  Because, for example, all of these operators:
     *
     *                   <, <=, ==, > and >= 
     *
     *          all work on strings.  They are not 'built-in' to C++, but
     *          the class string has "overloaded" these operators (they 
     *          result in an appropriate function call).
     *
     *          (In a subsequent exercise, we will do this kind of 
     *          overloading ourselves!)
     *                                     
     *        Examples with lists of strings:
     *
     *          ["egg", "goat"] < ["egg", "globe", "apple"]
     *
     *          ["zebra", "fun"] < ["zebra", "funny"]
     *
     *        [Yes, the components of these lists are THEMSELVES compared
     *        lexically, but the string class is doing those comparisons)
     *
     */
    int compare_with(const List<T> &other) const {
		Node* myP = front;
		Node* otherP = other.front;
		
		//loop through while myP and otherP arent' null
		while (myP != nullptr && otherP != nullptr)
		{
			//we are looking for the nodes that have different values
			if (myP->data > otherP->data)
			{
				return 1;
			}
			if (myP->data < otherP->data)
			{
				return -1;
			}
			myP = myP->next;
			otherP = otherP->next;
		}
		//if we reached the end of one of the list simply compare the lengths and that will tell you the lexicallity

		if (listLength > other.listLength)
		{
			return 1;
		}
		else if (listLength < other.listLength)
		{
			return -1;
		}
		else if (listLength == other.listLength)
		{
			return 0;
		}
    }



    /*
     * TODO
     *
     * function:  suffix_maxes
     *
     * desc:  constructs a new list of the same length as the calling object
     *        with the value stored at position i of the new list is the MAXIMUM
     *        value in the suffix (or tail) of the calling list starting from
     *        position i.
     *
     *        This new list is returned and the calling list is unchanged.
     *
     *        Example:
     *
     *          Given List:  [6, -18, 12, 4, 1, 7, 2, 5  4]
     *                                    ^^^^^^^^^^^^^^^^
     *
     *          New list:    [12, 12, 12, 7, 7, 7, 5, 5, 4]
     *                                    ^
     *
     *              (as a sub-example, the marked entry in the new list
     *              (marked with '^') is the max of the marked suffix in the
     *              given list (marked with a bunch of '^'s).
     *
     * REQUIREMENTS:
     *
     *        Total Runtime:   O(n)
     *        Calling list is unchanged.
     *
     */
    List<T> * suffix_maxes() const{
		Node* p = front;

		//check for an empty list
		if (front == nullptr)
		{
			return nullptr;
		}
		List<T> *result = new List<T>();
		return suffixHelper(p, result);

    }

	private:
	List<T> * suffixHelper(Node* temp, List<T> * suffix) const
	{
		static T max;		//store the current max data in max
		//recurse through the list
		if (temp->next != nullptr)
		{
			max = temp->next->data;				//set max as you go
			suffixHelper(temp->next, suffix);	//recursive call
		}

		//if data is <= max then push it into suffix
		if (temp->data <= max)
		{
			suffix->push_front(max);
			return suffix;
		}
		//if data > max then update max and push that data instead
		else
		{
			max = temp->data;
			suffix->push_front(max);
			return suffix;
		}
	}
	public:
	
	//TODO REMOVE WHEN TURNING IN
	T get(int i)
	{
		Node* temp = front;
		int counter = 0;
		while (temp != nullptr && counter < i)
		{
			temp = temp->next;
			counter++;
		}
		return temp->data;
	}


  private:
    Node *front;
    Node *back;
	int listLength;		//length variable for bookkeeping

    void init( ) {
      front = nullptr;
      back = nullptr;
	  listLength = 0;
    }
};

#endif
