#include <catch.hpp>

#include "treap.h"

TEST_CASE("insert_root", "[root]") {
   Treap<int> testTreap;
   testTreap.Insert(10);
   REQUIRE(testTreap.getKeyRoot() == 10);
   REQUIRE(testTreap.getLeftKey(10) == nullptr);
   REQUIRE(testTreap.getRightKey(10) == nullptr);
   REQUIRE(testTreap.getCount() == 1);
   REQUIRE(testTreap.getRoot() != 0);
}


TEST_CASE("Inserting left child", "[ilch]") {
   Treap<int> testTreap;
   testTreap.Insert(10);
   testTreap.Insert(7);
   REQUIRE(*testTreap.getKeyRoot() == 7);
   REQUIRE(testTreap.getLeftKey(7) == nullptr);
   REQUIRE(*testTreap.getRightKey(7) == 10);
   REQUIRE(testTreap.getCount() == 2);
   REQUIRE(testTreap.getRoot() != 0);
   REQUIRE(testTreap.getLeftKey(10) == nullptr);
   REQUIRE(testTreap.getRightKey(10) == nullptr);
   REQUIRE(*testTreap.getPriority(10) > *testTreap.getPriority(7)); 
}


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

TEST_CASE("Inserting right child", "[irch]") {
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



  TEST_CASE("remove root", "[irch]") {
	Treap<int> testTreap;
	testTreap.Insert(10);
	testTreap.Remove(10);
	REQUIRE(testTreap.getKeyRoot() == nullptr);
	REQUIRE(testTreap.getRoot() == nullptr);
	REQUIRE(testTreap.getCount() == 0);
}

  TEST_CASE("remove list", "[irch]") {
	Treap<int> testTreap;
	testTreap.Insert(10);
	testTreap.Insert(11);
	testTreap.Remove(10);
	int root = 11;
	if(*testTreap.getPriority(11) < *testTreap.getPriority(10))
		root = 10;
	REQUIRE(*testTreap.getKeyRoot() == root);
	REQUIRE(testTreap.getRightKey(root) == nullptr);
	REQUIRE(testTreap.getLeftKey(root) == nullptr);
	REQUIRE(testTreap.getRoot() != nullptr);
	REQUIRE(testTreap.getCount() == 1);
}
