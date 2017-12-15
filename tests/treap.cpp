#include <catch.hpp>

#include "treap.h"

/*
    nullptr     ->      10
*/

TEST_CASE("insert_root", "[root]") {
   Treap<int> testTreap;
   testTreap.Insert(10);
   REQUIRE(*testTreap.getKeyRoot() == 10);
   REQUIRE(testTreap.getLeftKey(10) == nullptr);
   REQUIRE(testTreap.getRightKey(10) == nullptr);
   REQUIRE(testTreap.getCount() == 1);
   REQUIRE(testTreap.getRoot() != 0);
}

/*
if "10" priority > "7" priority
    10     ->      10		
                  /  	
                 7
else 
    10     ->       7
    		     \
		      10
*/
TEST_CASE("Inserting left child", "[ilch]") {
   Treap<int> testTreap;
   testTreap.Insert(10);
   testTreap.Insert(7);
   int root = 7;
   if(*testTreap.getPriority(7) < *testTreap.getPriority(10))
       root = 10;
   REQUIRE(*testTreap.getKeyRoot() == root);
   REQUIRE(testTreap.getCount() == 2);
   REQUIRE(testTreap.getRoot() != 0);
   REQUIRE(testTreap.Search(7) != nullptr);
   REQUIRE(testTreap.Search(10) != nullptr);
}

/*
if "10" priority > "75" priority
    10     ->      10		
                     \ 	
                      75
else 
    10     ->       75
    		   /
		  10
*/
TEST_CASE("Inserting right child", "[irch]") {
   Treap<int> testTreap;
   testTreap.Insert(10);
   testTreap.Insert(75);
   REQUIRE(*testTreap.getKeyRoot() == 75);
   REQUIRE(*testTreap.getLeftKey(75) == 10);
   REQUIRE(testTreap.getRightKey(75) == nullptr);
   REQUIRE(testTreap.getCount() == 2);
   REQUIRE(testTreap.getRoot() != 0);
   REQUIRE(*testTreap.getPriority(75) > *testTreap.getPriority(10)); 
   REQUIRE(testTreap.getLeftKey(10) == nullptr);
   REQUIRE(testTreap.getRightKey(10) == nullptr);
}
/*
if "10" priority > "25" priority > "75" priority
    10     ->      10	   ->     10	
                     \ 	            \
                      75             25
                                       \
		                        75  
if "25" priority < "75" priority < "10" priority 
    10     ->      10	   ->     10	
                     \ 	            \
                      75             75
                                    /  
		                   25
if "10" priority < "25" priority < "75" priority
    10     ->      75	   ->     75	
                   /   	          /
                  10             25   
                                /     
		               10     
if "10" priority < "75" priority < "25" priority
    10     ->      75	   ->     25	
                   / 	           \	
                  10                75
                                   /     
		                 10 
if "75" priority < "10" priority < "25" priority
    10     ->      10	   ->     25	
                     \ 	           \	
                      75            75
                                   /     
		                 10 
if "75" priority < "10" priority < "25" priority
    10     ->      10	   ->     25	
                     \ 	          /	
                      75         10
                                  \     
		                   75
if "25" priority < "10" priority < "75" priority
    10     ->      75	   ->      75	
                   / 	          /	
                  10             10
                                  \   
		                   25 
if "10" priority < "25" priority < "75" priority
    10     ->      75	   ->      75	
                   / 	            \	
                  10                 25
                                     /
		                   10
*/
TEST_CASE("Inserting", "[irch]") {
	Treap<int> testTreap;
	testTreap.Insert(10);
	testTreap.Insert(75);
	testTreap.Insert(25);
	int maxPriority = *testTreap.getPriority(75);
	if(maxPriority < *testTreap.getPriority(10))
   		maxPriority = *testTreap.getPriority(10);
	if(maxPriority < *testTreap.getPriority(25))
		maxPriority = *testTreap.getPriority(25);
    if(maxPriority == *testTreap.getPriority(25))
   	{
  		REQUIRE(*testTreap.getKeyRoot() == 25);
   	}
   	if(maxPriority == *testTreap.getPriority(75))
   	{
   		REQUIRE(*testTreap.getKeyRoot() == 75);
   	}
   	if(maxPriority == *testTreap.getPriority(10))
   	{
   		REQUIRE(*testTreap.getKeyRoot() == 10);
   	}
   	REQUIRE(testTreap.getCount() == 3);
   	REQUIRE(testTreap.Search(75) != nullptr);
   	REQUIRE(testTreap.Search(25) != nullptr);
   	REQUIRE(testTreap.Search(10) != nullptr);
   }

/*
      nullptr  ->    10    ->    nullptr
*/

  TEST_CASE("remove root", "[irch]") {
	Treap<int> testTreap;
	testTreap.Insert(10);
	testTreap.Remove(10);
	REQUIRE(testTreap.getKeyRoot() == nullptr);
	REQUIRE(testTreap.getRoot() == nullptr);
	REQUIRE(testTreap.getCount() == 0);
}
/*
if "10" priority > "11" priority
    10     ->      10	   ->   10	
                     \ 	
                      11
else 
    10     ->       11     ->    11
    		   /
		  10
*/
  TEST_CASE("remove list", "[irch]") {
	Treap<int> testTreap;
	testTreap.Insert(10);
	testTreap.Insert(11);
	testTreap.Remove(10);
	int root = 10;
	if(*testTreap.getPriority(10) < *testTreap.getPriority(11))
       		root = 11;
	REQUIRE(*testTreap.getKeyRoot() == root);
	REQUIRE(testTreap.getRightKey(root) == nullptr);
	REQUIRE(testTreap.getLeftKey(root) == nullptr);
	REQUIRE(testTreap.getRoot() != nullptr);
	REQUIRE(testTreap.getCount() == 1);
}
