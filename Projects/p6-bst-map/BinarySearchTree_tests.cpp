#include <sstream>

#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"

TEST(test_empty) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.empty());
}

TEST(test_size) {
  BinarySearchTree<int> tree;
  ASSERT_EQUAL(tree.size(), 0);
  tree.insert(1);
  ASSERT_EQUAL(tree.size(), 1);
  ASSERT_EQUAL(tree.height(), 1);
  tree.insert(2);
  ASSERT_EQUAL(tree.size(), 2);
  ASSERT_EQUAL(tree.height(), 2);
}

TEST(test_size_tree) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);
  ASSERT_EQUAL(tree.size(), 4);
  ASSERT_EQUAL(tree.height(), 3);
  ASSERT_EQUAL(*tree.min_greater_than(2),3);
  ASSERT_EQUAL(*tree.min_greater_than(0),1);
}
TEST(test_copy_node) {
  BinarySearchTree<int> tree;
  //   auto it = tree.begin();
  //   it++;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  BinarySearchTree<int> tree2(tree);
  ASSERT_EQUAL(*tree2.min_element(), 1);
  ASSERT_EQUAL(*tree2.max_element(), 5);
}

TEST(test_inorder) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);
  std::ostringstream os;
  tree.traverse_inorder(os);
  ASSERT_EQUAL(os.str(), "1 3 4 5 ");
}

TEST(test_preorder) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);
  std::ostringstream os;
  tree.traverse_preorder(os);
  ASSERT_EQUAL(os.str(), "5 3 1 4 ");
}

TEST(test_arrow_arrow) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);
  std::ostringstream os;
  os << tree;
  ASSERT_EQUAL(os.str(), "[ 1 3 4 5 ]");
}

TEST(test_find) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);

  auto it = tree.find(1);
  ASSERT_EQUAL(*it, 1);
  auto it3 = tree.find(3);
  ASSERT_EQUAL(*it3, 3);

  auto it2 = tree.find(10);
  ASSERT_EQUAL(it2, tree.end());

  BinarySearchTree<int> tree_empty;
  auto it4 = tree_empty.find(1);
  ASSERT_TRUE(it4 == tree_empty.end());
}

TEST(test_min_and_max) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_EQUAL(1, *tree.min_element());

  ASSERT_EQUAL(5, *tree.max_element());
}

TEST(test_min_greater_than) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);
  tree.insert(6);
  ASSERT_TRUE(tree.check_sorting_invariant());

  ASSERT_EQUAL(*tree.min_greater_than(1), 3);
  ASSERT_EQUAL(*tree.min_greater_than(3), 4);
  ASSERT_EQUAL(*tree.min_greater_than(4), 5);
  ASSERT_EQUAL(*tree.min_greater_than(5), 6);
}

TEST(test_begin_end) {
  BinarySearchTree<int> tree;
  ASSERT_TRUE(tree.begin() == tree.end());
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);

  ASSERT_EQUAL(*tree.begin(), 1);
}

TEST(test_begin_plus) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);

  auto it = tree.begin();
  ASSERT_EQUAL(*it, 1);
  it++;
  ASSERT_EQUAL(*it, 3);
  it++;
  ASSERT_EQUAL(*it, 4);
  it++;
  ASSERT_EQUAL(*it, 5);
}

TEST(test_begin_postfix) {
  BinarySearchTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(1);
  tree.insert(4);

  auto it = tree.begin();
  auto it2 = it++;

  ASSERT_EQUAL(*it, 3);
  ASSERT_EQUAL(*it2, 1);
}

TEST(test_sorting_empy) {
  BinarySearchTree<int> tree;

  ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_sort_inv) {
  BinarySearchTree<int> b;
  b.insert(1);
  b.insert(0);
  // change first datum to 2, resulting in the first broken tree above
  *b.begin() = 2;
  ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_pair) {
  BinarySearchTree<std::pair<int, std::string>> tree;
  tree.insert(std::make_pair(1, "HELLO"));

  auto it = tree.find(std::make_pair(1, "HELLO"));
  ASSERT_TRUE(it != tree.end());
  ASSERT_EQUAL(it->first, 1);
  ASSERT_EQUAL(it->second, "HELLO");
}

TEST_MAIN()
