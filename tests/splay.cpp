#include <catch.hpp>

#include "treap.h"

TEST_CASE("insert_root", "[root]") {
   Treap<int> TreapTree;
   TreapTree.insert(10);
   REQUIRE(TreapTree.search(10) != nullptr);
}



