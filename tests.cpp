/*
Author: Phillip Sopt
Description:
This is the set of test cases I made for the List.h. It should cover all the cases for every function.
Note that these set of test cases were written using Visual Studios testing framework. So if you want to use them,
either convert them to regular old assert commands in C++ or import it into Visual Studio.



*/
#include "stdafx.h"
#include "CppUnitTest.h"
#include "List.h" 
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		const int max = 999999;

		TEST_METHOD(Length)
		{
			List<int> temp = List<int>();
			int i;
			int val = 0;
			//add 99999999 items to the list
			for (i = 0; i < max; i++)
			{
				temp.push_front(9);
			}
			Assert::AreEqual(i, temp.length(), L"length() failed", LINE_INFO());

			//removing everything in the list			
			for (i = 0; i < max; i++)
			{
				temp.pop_front(val);
			}
			Assert::AreEqual(0, temp.length());

			for (i = 0; i < max; i++)
			{
				temp.push_front(9);
			}
			temp.clear();
			Assert::AreEqual(0, temp.length(), L"length after clear");

			//testing push_back selectively
			temp.push_back(3);
			temp.push_back(7);
			temp.push_back(8);
			temp.push_back(3);
			temp.push_back(8);
			temp.push_back(3);
			Assert::AreEqual(6, temp.length());
			temp.slow_remove_all(8);
			Assert::AreEqual(4, temp.length());
			temp.slow_remove_all(3);
			temp.slow_remove_all(7);
			Assert::AreEqual(0, temp.length());

			temp.push_back(3);
			temp.push_back(3);
			temp.pop_back(val);
			Assert::AreEqual(1, temp.length(), L"length popback failed");
			temp.pop_back(val);
			Assert::AreEqual(0, temp.length(), L"length single element popback");
			temp.pop_back(val);
			Assert::AreEqual(0, temp.length(), L"length empty popback");
		}

		TEST_METHOD(Count)
		{
			List<int> temp = List<int>();
			int i;
			int val = 0;
			Assert::AreEqual(0, temp.count(9), L"empty Count failed");
			for (i = 0; i < max; i++)
			{
				temp.push_front(9);
			}
			Assert::AreEqual(max, temp.count(9), L"int max count failed");
			temp.pop_front(val);
			Assert::AreEqual(max - 1, temp.count(9), L"count popback failed");
			temp.clear();

			temp.push_back(0);
			temp.push_back(0);
			temp.push_back(0);
			temp.push_back(0);
			temp.push_back(0);

			Assert::AreEqual(5, temp.count(0));
		}

		TEST_METHOD(popback)
		{
			List<int> temp = List<int>();
			int i;
			int val = 0;
			Assert::AreEqual(false, temp.pop_back(val), L"empty popback failed");

			temp.push_front(9);
			Assert::AreEqual(true, temp.pop_back(val), L"one element popback failed");

			temp.push_front(9);
			for (i = 0; i < 3; i++)
			{
				temp.push_front(8);
			}
			temp.pop_back(val);
			Assert::AreEqual(9, val, L"popback on 9");

			for (i = 0; i < temp.length(); i++)
			{
				Assert::AreEqual(true, temp.pop_back(val), L"all popback failed");
			}

			for (i = 0; i < 99; i++)		//push to the list and immediate pop the value
			{
				temp.push_front(9);
				Assert::AreEqual(true, temp.pop_back(val));
			}

			for (i = 0; i < 999; i++)
			{
				temp.push_front(8);
			}
			for (i = 0; i < 999; i++)		//now for the painstaking process
			{
				Assert::AreEqual(true, temp.pop_back(val));
			}
		}

		TEST_METHOD(equal_to)
		{
			List<int> temp = List<int>();
			List<int> other = List<int>();
			int i;
			int val = 0;

			Assert::AreEqual(true, temp.equal_to(other), L"equal_to empty lists");

			temp.push_back(9);
			Assert::AreEqual(false, temp.equal_to(other), L"equal_to temp with one element and other empty");

			other.push_back(8);
			Assert::AreEqual(false, temp.equal_to(other), L"equal_to simple check");
			other.pop_back(val);
			other.push_back(9);
			Assert::AreEqual(true, temp.equal_to(other), L"equal_to cloned list");

			other.clear();
			temp.clear();

			temp.push_back(1);
			temp.push_back(2);
			temp.push_back(3);
			other.push_back(1);
			other.push_back(2);
			other.push_back(3);
			other.push_back(-99);
			Assert::AreEqual(false, temp.equal_to(other),L"t");

			for (i = 0; i < max; i++)
			{
				temp.push_back(rand());
				other.push_back(rand());
			}
			Assert::AreEqual(false, other.equal_to(temp), L"equal_to random same length");
			temp.clear();
			temp.push_back(1);
			Assert::AreEqual(false, temp.equal_to(other), L"equal_to max and single elem");
			for (i = 0; i < max; i++) temp.push_back(rand());

			for (i = 0; i < max / 2; i++)
			{
				temp.pop_front(val);
			}
			Assert::AreEqual(false, other.equal_to(temp), L"equal_to different lengths");

			temp.clear();
			other.clear();

			Assert::AreEqual(true, other.equal_to(temp));

			int arr[] = { 3,2,4,5,1,8,4,6,2,78,3,62,35,45346,7,4568,2,436357345,89,65,43,457,4,1,35,6 };

			for (i = 0; i < 26; i++)
			{
				temp.push_back(arr[i]);
				other.push_back(arr[i]);
			}
			Assert::AreEqual(true, temp.equal_to(other), L"equal_to same elems in lists");
			Assert::AreEqual(true, temp.equal_to(temp), L"equal_to same list");

			//now for strings
			List<char*> a = List<char*>();
			List<char*> b = List<char*>();

			a.push_back("pizza");
			b.push_back("pizza");

			Assert::AreEqual(true, a.equal_to(b), L"Line 177");

			a.push_back("chicken");
			a.push_back("tomato");
			a.push_back("spage");	//this is with an 'a'
			b.push_back("chicken");
			b.push_back("tombto");
			b.push_back("spbge");	//this is different

			Assert::AreEqual(false, a.equal_to(b), L"Line 177");

		}

		TEST_METHOD(print_reverse)
		{
			List<int> temp = List<int>();
			int i;
			int val = 0;
			int arr[] = { 3,2,4,5,1,8,4,6,2,78,3,62,35,45346,7,4568,2,436357345,89,65,43,457,4,1,35,6 };

			temp.print_rev();

			for (i = 0; i < 26; i++)
			{
				temp.push_back(arr[i]);
			}

			temp.print_rev();
			cout << "test" << endl;
			cout << "testtest" << endl;
		}

		TEST_METHOD(testReverse)
		{
			List<int> temp = List<int>();
			int i;
			int val = 0;

			int arr[] = { 1,2,3,4,5,6,7,8 };
			int arr2[] = { 8,7,6,5,4,3,2,1 };

			//empty reverse
			temp.reverse();

			//single item list
			temp.push_front(0);
			temp.reverse();
			temp.pop_front(val);
			Assert::AreEqual(0, val);

			//two item list
			temp.push_front(2);
			temp.push_front(1);
			temp.reverse();
			temp.pop_front(val);
			Assert::AreEqual(2, val);
			temp.pop_back(val);
			Assert::AreEqual(1, val);

			//3 item list
			temp.push_front(3);
			temp.push_front(2);
			temp.push_front(1);
			temp.reverse();
			temp.pop_front(val);
			Assert::AreEqual(3, val, L"3 element failed");
			temp.pop_front(val);
			Assert::AreEqual(2, val, L"3 element failed");
			temp.pop_front(val);
			Assert::AreEqual(1, val, L"3 element failed");

			//8 item list
			for (i = 0; i < 8; i++)
			{
				temp.push_back(arr[i]);
			}
			temp.reverse();
			for (i = 0; i < 8; i++)
			{
				temp.pop_front(val);
				Assert::AreEqual(arr2[i], val, L"8 element failed");
			}

			for (i = 0; i < /*max*/ 100; i++)
			{
				temp.push_back(i);
			}
			temp.reverse();
			for (i = 0; i < /*max*/ 100; i++)
			{
				temp.pop_front(val);
				Assert::AreEqual(/*max*/ 100 - i - 1, val, L"max element failed");
			}
		}

		TEST_METHOD(fastRemoveAll)
		{
			List<int> temp = List<int>();
			int i;
			int val = 0;

			Assert::AreEqual(0, temp.fast_remove_all(2), L"empty List");

			//list of {2}
			temp.push_front(2);

			Assert::AreEqual(1, temp.fast_remove_all(2), L"length of one with one val to delete");

			//list of {1, 2}
			temp.push_front(1);
			temp.push_back(2);

			Assert::AreEqual(1, temp.fast_remove_all(2), L"{1,2}");
			temp.clear();

			//list of {2, 1}
			temp.push_front(2);
			temp.push_back(1);

			Assert::AreEqual(1, temp.fast_remove_all(2), L"{2,1}");
			temp.clear();

			//list of {2, 2}
			temp.push_front(2);
			temp.push_back(2);

			Assert::AreEqual(2, temp.fast_remove_all(2), L"{2,2}");
			temp.clear();

			//list of {1, 2, 3}
			temp.push_front(1);
			temp.push_back(2);
			temp.push_back(3);

			Assert::AreEqual(1, temp.fast_remove_all(2), L"{1,2,3}");
			temp.clear();

			//list of {2, 1, 3}
			temp.push_front(2);
			temp.push_back(1);
			temp.push_back(3);

			Assert::AreEqual(1, temp.fast_remove_all(2), L"{2,1,3}");
			temp.clear();

			//list of {2, 2, 3}
			temp.push_front(2);
			temp.push_back(2);
			temp.push_back(3);

			Assert::AreEqual(2, temp.fast_remove_all(2), L"{2,2,3}");
			temp.clear();

			//list of {3, 2, 2}
			temp.push_front(3);
			temp.push_back(2);
			temp.push_back(2);

			Assert::AreEqual(2, temp.fast_remove_all(2), L"{3,2,2}");
			temp.clear();

			//list of {2, 2, 2}
			temp.push_front(2);
			temp.push_back(2);
			temp.push_back(2);

			Assert::AreEqual(3, temp.fast_remove_all(2), L"{2,2,2}");
			temp.clear();

			for (i = 0; i < 100; i++)
			{
				temp.push_front(rand() % 3);
			}
			temp.fast_remove_all(2);
			Assert::AreNotEqual(100, temp.length());
		}

		TEST_METHOD(testInsertSorted)
		{
			List<int> temp = List<int>();
			int i;
			int val = 0;
			int arr[] = { 0, 1, 1, 3, 4, 5, 5, 7 };

			temp.insert_sorted(0);
			Assert::AreEqual(1, temp.length());
			temp.pop_front(val);

			temp.push_front(3);
			temp.push_front(1);
			temp.insert_sorted(2);
			temp.pop_front(val);
			temp.pop_front(val);
			Assert::AreEqual(2, val);
			temp.clear();

			for (i = 0; i < 8; i++)
			{
				temp.insert_sorted(arr[i]);
			}

			for (i = 0; i < 8; i++)
			{
				temp.pop_front(val);
				Assert::AreEqual(arr[i], val);
			}

			for (i = 0; i < 8; i++)
			{
				temp.insert_sorted(arr[i]);
			}

			temp.insert_sorted(2);
			temp.insert_sorted(6);
			Assert::AreEqual(2, temp.get(3));
			Assert::AreEqual(6, temp.get(8));

		}

		TEST_METHOD(testMergeWith)
		{
			List<int> temp = List<int>();
			List<int> temp2 = List<int>();
			int i;
			int val = 0;

			//empty merge
			temp.merge_with(temp2);
			Assert::AreEqual(0, temp.length(), L"empty");

			//one elem in b
			temp2.push_back(1);
			temp.merge_with(temp2);
			Assert::AreEqual(1, temp.length(), L"one elem in b");
			Assert::AreEqual(true, temp2.is_empty(), L"is b empty");

			temp.clear();
			temp2.clear();

			//[2] in a  and [1] in b
			temp.push_back(2);
			temp2.push_back(1);
			temp.merge_with(temp2);
			Assert::AreEqual(1, temp.get(0), L"Line 401");
			Assert::AreEqual(2, temp.get(1), L"Line 402");

			temp.clear();
			temp2.clear();

			//[1,2,3] <- [4]
			temp.push_back(1);
			temp.push_back(2);
			temp.push_back(3);
			temp2.push_back(4);
			temp.merge_with(temp2);
			Assert::AreEqual(4, temp.get(3), L"Line 411");

			temp.clear();
			temp2.clear();

			//[5,5,5] <- [1]
			temp.push_back(5);
			temp.push_back(5);
			temp.push_back(5);
			temp2.push_back(1);
			temp.merge_with(temp2);
			Assert::AreEqual(1, temp.get(0), L"Line 420");
			Assert::AreEqual(5, temp.get(3), L"Line 421");

			temp.clear();
			temp2.clear();

			/* this test
			a:  [2 3 4 9 10 30]
			b : [5 8 8 11 20 40]
			a : [2 3 4 5 8 8 9 10 11 20 30 40]
			b : []
			*/
			temp.push_back(2);
			temp.push_back(3);
			temp.push_back(4);
			temp.push_back(9);
			temp.push_back(10);
			temp.push_back(30);
			temp2.push_back(5);
			temp2.push_back(8);
			temp2.push_back(8);
			temp2.push_back(11);
			temp2.push_back(20);
			temp2.push_back(40);
			temp.merge_with(temp2);
			Assert::AreEqual(2, temp.get(0), L"Line 445");
			Assert::AreEqual(5, temp.get(3), L"Line 446");
			Assert::AreEqual(8, temp.get(5), L"Line 447");
		}

		TEST_METHOD(testDeepCopy)
		{
			List<int> temp = List<int>();
			List<int> *temp2;
			int i;
			int val = 0;

			temp.push_back(1);

			temp2 = temp.clone();
			if (!temp.equal_to(*temp2))	Assert::Fail();

			delete temp2;

			temp.push_back(3);
			temp.push_back(4);

			temp2 = temp.clone();
			Assert::AreEqual(1, temp2->get(0));
			Assert::AreEqual(3, temp2->get(1));
			Assert::AreEqual(4, temp2->get(2));

			delete temp2;
		}

		TEST_METHOD(testPrefix)
		{	
			List<int> temp = List<int>();
			List<int> *temp2;
			int i;
			int val = 0;

			temp2 = temp.prefix(0);
			Assert::AreEqual(0, temp2->length(), L"Line 507");

			//[1] -> prefix(0)
			temp.push_back(1);
			temp2 = temp.prefix(0);
			Assert::AreEqual(0, temp2->length(), L"Line 507");

			//[1] -> prefix(1)
			temp2 = temp.prefix(1);
			Assert::AreEqual(1, temp2->get(0), L"Line 513");
			Assert::AreEqual(0, temp.length());
			/*
			EX1:  lst:  [2, 3, 9, 7, 8]
			k : 3
			*/

			temp.push_back(2);
			temp.push_back(3);
			temp.push_back(9);
			temp.push_back(7);
			temp.push_back(8);
			temp2 = temp.prefix(3);
			Assert::AreEqual(2, temp2->get(0), L"Line 529");
			Assert::AreEqual(9, temp2->get(2), L"Line 530");
			Assert::AreEqual(7, temp.get(0), L"Line 531");
			Assert::AreEqual(8, temp.get(1), L"Line 532");
			Assert::AreEqual(3, temp2->length(), L"Line 533");
			Assert::AreEqual(2, temp.length(), L"Line 534");
					
			temp.clear();
			temp.push_back(2);
			temp.push_back(3);
			temp.push_back(9);
			temp.push_back(7);
			temp.push_back(8);
			temp2 = temp.prefix(5);
			Assert::AreEqual(0, temp.length(), L"Line 543");
			Assert::AreEqual(2, temp2->get(0), L"Line 544");
			Assert::AreEqual(8, temp2->get(4), L"Line 545");
			
			for ( i = 0; i < max; i++)
			{
				temp.push_front(rand());
			}

			temp2 = temp.prefix(max-1);
			Assert::AreEqual(1, temp.length());
		}

		TEST_METHOD(testFilterLEQ)
		{
			List<int> temp = List<int>();
			List<int> *temp2;
			int i;
			int val = 0;

			//[1] cutoff 1
			temp.push_front(1);
			temp2 = temp.filter_leq(1);
			Assert::AreEqual(1, temp2->length(), L"Line 566");
			Assert::AreEqual(1, temp2->get(0), L"Line 567");
			Assert::AreEqual(0, temp.length(), L"Line 568");
			temp.clear();

			//[1,2] cutoff of 2
			temp.push_front(2);
			temp.push_front(1);
			temp2 = temp.filter_leq(2);
			Assert::AreEqual(2, temp2->length(), L"Line 574");
			Assert::AreEqual(1, temp2->get(0), L"Line 575");
			Assert::AreEqual(2, temp2->get(1), L"Line 576");
			Assert::AreEqual(0, temp.length(), L"Line 577");
			Assert::AreEqual(true, temp.is_empty(), L"Line 578");
			temp.clear();

			//[2,1] cutoff of 1
			temp.push_front(1);
			temp.push_front(2);
			temp2 = temp.filter_leq(1);
			Assert::AreEqual(1, temp2->get(0));
			Assert::AreEqual(2, temp.get(0));
			Assert::AreEqual(1, temp2->length());
			Assert::AreEqual(1, temp.length());
			
			temp.clear();

			//[1,1,1] cutoff of 1
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(1);
			temp2 = temp.filter_leq(1);
			Assert::AreEqual(3, temp2->length(), L"Line 588");
			Assert::AreEqual(1, temp2->get(0), L"Line a");
			Assert::AreEqual(1, temp2->get(1), L"Line b");
			Assert::AreEqual(0, temp.length(), L"Line c");
			temp.clear();

			//[3,1,1,2] cutoff of 1
			temp.push_back(3);
			temp.push_back(1);
			temp.push_back(1);
			temp.push_back(2);
			temp2 = temp.filter_leq(1);
			Assert::AreEqual(1, temp2->get(0));
			Assert::AreEqual(1, temp2->get(1));
			Assert::AreEqual(3, temp.get(0));
			Assert::AreEqual(2, temp.get(1));

			temp.clear();

			int arr[] = { 2, 7, 3, 9 , 8 , 4 };
			for ( i = 0; i < 6; i++)
			{
				temp.push_back(arr[i]);
			}
			temp2 = temp.filter_leq(4);
			Assert::AreEqual(2, temp2->get(0));
			Assert::AreEqual(3, temp2->get(1));
			Assert::AreEqual(4, temp2->get(2));
			Assert::AreEqual(7, temp.get(0));
			Assert::AreEqual(9, temp.get(1));
			Assert::AreEqual(8, temp.get(2));
			temp.clear();


			for (i = 0; i < 6; i++)
			{
				temp.push_back(arr[i]);
			}
			temp2 = temp.filter_leq(7);
			Assert::AreEqual(2, temp.length());
		}

		TEST_METHOD(testConcat)
		{
			List<int> temp = List<int>();
			List<int> temp2 = List<int>();
			int i;
			int val = 0;

			temp.push_front(1);
			temp.concat(temp);
			Assert::AreEqual(1, temp.get(0));
			temp.clear();

			temp2.push_back(1);
			temp.concat(temp2);
			Assert::AreEqual(1, temp.get(0), L"",LINE_INFO());

			temp2.clear();
			temp.clear();

			temp.push_back(1);
			temp.concat(temp2);
			Assert::AreEqual(1, temp.get(0));

			temp2.clear();
			temp.clear();

			temp.push_back(1);
			temp.push_back(2);
			temp.push_back(6);
			temp2.push_back(8);
			temp2.push_back(3);
			temp2.push_back(7);
			temp2.push_back(0);
			temp.concat(temp2);
			Assert::AreEqual(0, temp2.length());
			Assert::AreEqual(7, temp.length());
			int arr[] = { 1,2,6,8,3,7,0 };
			for ( i = 0; i < 7; i++)
			{
				Assert::AreEqual(arr[i], temp.get(i));

			}
		}

		TEST_METHOD(testCompare)
		{
			List<int> temp = List<int>();
			List<int> temp2 = List<int>();
			int i;
			int val = 0;

			//[].compare[]
			Assert::AreEqual(0, temp.compare_with(temp2), L"a");
			Assert::AreEqual(0, temp2.compare_with(temp), L"b");

			//[1].compare[]
			temp.push_back(1);
			Assert::AreEqual(1, temp.compare_with(temp2), L"c");
			Assert::AreEqual(-1, temp2.compare_with(temp), L"d");
			
			//[1].compare[2,3,5]
			temp2.push_back(2);
			temp2.push_back(3);
			temp2.push_back(5);
			Assert::AreEqual(-1, temp.compare_with(temp2), L"e");
			Assert::AreEqual(1, temp2.compare_with(temp), L"f");

			//[1,3,5,2].compare[2,3,5]
			temp.push_back(3);
			temp.push_back(5);
			temp.push_back(2);
			Assert::AreEqual(-1, temp.compare_with(temp2), L"g");
			Assert::AreEqual(1, temp2.compare_with(temp), L"h");

			//[1,3,5,2].compare[2,3,5,1]
			temp2.push_back(1);
			Assert::AreEqual(-1, temp.compare_with(temp2), L"i");
			Assert::AreEqual(1, temp2.compare_with(temp), L"j");

			List<char*> a = List<char*>();
			List<char*> b = List<char*>();

			a.push_back("egg");
			a.push_back("goat");
			b.push_back("egg");
			b.push_back("globe");
			b.push_back("apple");
			Assert::AreEqual(-1, a.compare_with(b));

		}


		TEST_METHOD(testSuffixMaxes)
		{
			List<int> temp = List<int>();
			List<int> *temp2;
			int i;
			int val = 0;



			/*
			[6, -18, 12, 4, 1, 7, 2, 5  4]
			to
			[12, 12, 12, 7, 7, 7, 5, 5, 4]
			*/
			temp.push_back(6);
			temp.push_back(-18);
			temp.push_back(12);
			temp.push_back(4);
			temp.push_back(1);
			temp.push_back(7);
			temp.push_back(2);
			temp.push_back(5);
			temp.push_back(4);
			temp2 = temp.suffix_maxes();

		}





	};
}