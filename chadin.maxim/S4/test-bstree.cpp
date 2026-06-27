#include <boost/test/unit_test.hpp>
#include "bstree.hpp"
#include <string>

BOOST_AUTO_TEST_SUITE(ChadinBSTreeCoreTests)

BOOST_AUTO_TEST_CASE(fakes_empty_tree_boundary)
{
  chadin::BSTree<int, std::string> tree;

  BOOST_CHECK(tree.empty());
  BOOST_CHECK_EQUAL(tree.size(), 0);
  BOOST_CHECK(tree.begin() == tree.end());
  BOOST_CHECK(tree.cbegin() == tree.cend());
  BOOST_CHECK_THROW(tree.get(10), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(insertion_and_overwriting)
{
  chadin::BSTree<int, std::string> tree;

  tree.push(5, "apple");
  tree.push(3, "banana");
  tree.push(5, "orange");

  BOOST_CHECK_EQUAL(tree.size(), 2);
  BOOST_CHECK_EQUAL(tree.get(5), "orange");
  BOOST_CHECK_EQUAL(tree.get(3), "banana");
  BOOST_CHECK(tree.has(5));
}

BOOST_AUTO_TEST_CASE(referential_stability_after_drop)
{
  chadin::BSTree<int, std::string> tree;
  tree.push(20, "root");
  tree.push(10, "left");
  tree.push(30, "right");
  tree.push(25, "right_left");

  auto itRightLeft = tree.cbegin();
  ++itRightLeft; ++itRightLeft;
  BOOST_CHECK_EQUAL(itRightLeft->first, 25);

  tree.drop(30);

  BOOST_CHECK_EQUAL(itRightLeft->first, 25);
  BOOST_CHECK_EQUAL(itRightLeft->second, "right_left");
}

BOOST_AUTO_TEST_CASE(topology_rotation_test)
{
  chadin::BSTree<int, std::string> tree;
  tree.push(50, "root");
  tree.push(20, "l");
  tree.push(70, "r");
  tree.push(60, "rl");
  tree.push(80, "rr");

  auto itR = tree.cbegin();
  ++itR; ++itR; ++itR;
  BOOST_CHECK_EQUAL(itR->first, 70);

  auto initialRootHeight = tree.height();

  auto newTop = tree.rotateLeft(itR);

  BOOST_CHECK_EQUAL(newTop->first, 70);
  BOOST_CHECK(tree.height() <= initialRootHeight + 1);

  auto itAfterRot = tree.cbegin();
  BOOST_CHECK_EQUAL(itAfterRot->first, 20);
  ++itAfterRot;
  BOOST_CHECK_EQUAL(itAfterRot->first, 50);
}

BOOST_AUTO_TEST_CASE(copy_constructor_and_assignment)
{
  chadin::BSTree<int, std::string> tree1;
  tree1.push(1, "one");
  tree1.push(2, "two");

  chadin::BSTree<int, std::string> tree2(tree1);
  BOOST_CHECK_EQUAL(tree2.size(), 2);
  BOOST_CHECK(tree2.has(1));

  chadin::BSTree<int, std::string> tree3;
  tree3 = tree1;
  BOOST_CHECK_EQUAL(tree3.get(2), "two");

  tree1.push(3, "three");
  BOOST_CHECK_EQUAL(tree1.size(), 3);
  BOOST_CHECK_EQUAL(tree2.size(), 2);
}

BOOST_AUTO_TEST_SUITE_END()
