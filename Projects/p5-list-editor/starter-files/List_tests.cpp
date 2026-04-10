#include <iterator>

#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_empty) {
  List<int> nothing;
  ASSERT_TRUE(nothing.empty());
}
TEST(test_size) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  ASSERT_EQUAL(sizes.size(), 5);
}
TEST(test_first) {
  List<int> fronts;
  for (int i = 0; i < 5; ++i) {
    fronts.push_back(i);
  }
  ASSERT_EQUAL(fronts.front(), 0);
}
TEST(test_last) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  ASSERT_EQUAL(sizes.back(), 4);
}
TEST(test_push_front) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.push_front(67);
  ASSERT_EQUAL(sizes.front(), 67);
}
TEST(test_pop_back) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.pop_back();
  ASSERT_EQUAL(sizes.back(), 3);
}
TEST(test_pop_front) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.push_front(67);
  sizes.pop_front();
  ASSERT_EQUAL(sizes.front(), 0);
}
TEST(test_clear) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.push_front(67);
  sizes.clear();
  ASSERT_EQUAL(sizes.size(), 0);
}
TEST(test_copy_construc) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.push_front(67);
  List<int> sizes_copy(sizes);
  ASSERT_EQUAL(sizes_copy.front(), 67);
}
TEST(test_equal_copy) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.push_front(67);
  List<int> sizes_copy = sizes;
  ASSERT_EQUAL(sizes_copy.front(), 67);
}
TEST(test_push_back_empty) {
  List<int> sizes;
  sizes.push_back(67);
  ASSERT_FALSE(sizes.empty());
  ASSERT_EQUAL(sizes.size(), 1);
  ASSERT_EQUAL(sizes.front(), 67);
  ASSERT_EQUAL(sizes.back(), 67);
}
TEST(test_push_front_empty) {
  List<int> sizes;
  sizes.push_front(67);
  ASSERT_FALSE(sizes.empty());
  ASSERT_EQUAL(sizes.size(), 1);
  ASSERT_EQUAL(sizes.front(), 67);
  ASSERT_EQUAL(sizes.back(), 67);
}
TEST(test_pop_front_one) {
  List<int> sizes;
  sizes.push_front(67);
  sizes.pop_front();
  ASSERT_TRUE(sizes.empty());
  ASSERT_EQUAL(sizes.size(), 0);
  ASSERT_EQUAL(sizes.begin(), sizes.end());
}
TEST(test_pop_back_one) {
  List<int> sizes;
  sizes.push_front(67);
  sizes.pop_back();
  ASSERT_TRUE(sizes.empty());
  ASSERT_EQUAL(sizes.size(), 0);
  ASSERT_EQUAL(sizes.begin(), sizes.end());
}
TEST(test_list_copy) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }

  List<int> sizes2(sizes);
  sizes.pop_front();

  ASSERT_EQUAL(sizes.size(), 4);
  ASSERT_EQUAL(sizes2.size(), 5);

  auto it = sizes2.begin();
  ASSERT_EQUAL(*it, 0);
  it++;
  ASSERT_EQUAL(*it, 1);
  it++;
  ASSERT_EQUAL(*it, 2);
}
TEST(test_equal_list_copy) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }

  List<int> sizes2;
  sizes2.push_back(69);

  sizes = sizes2;

  ASSERT_EQUAL(sizes.size(), 1);
  ASSERT_EQUAL(sizes2.size(), 1);

  ASSERT_EQUAL(sizes.front(), 69);
  ASSERT_EQUAL(sizes.back(), 69);
}
TEST(test_equal_list_copy_nonempty) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }

  List<int> sizes2 = sizes;

  ASSERT_EQUAL(sizes.size(), 5);
  ASSERT_EQUAL(sizes2.size(), 5);

  ASSERT_EQUAL(sizes2.front(), 0);
  ASSERT_EQUAL(sizes2.back(), 4);
}
TEST(test_equal_list_copy_empty) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }

  List<int> sizes2;

  sizes = sizes2;

  ASSERT_EQUAL(sizes.empty(), true);
  ASSERT_EQUAL(sizes2.empty(), true);

  ASSERT_TRUE(sizes2.begin() == sizes2.end());
  ASSERT_TRUE(sizes.begin() == sizes.end());
}

TEST(test_equal_list_copy_self) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }

  sizes = sizes;

  ASSERT_EQUAL(sizes.size(), 5);

  ASSERT_EQUAL(sizes.front(), 0);
  ASSERT_EQUAL(sizes.back(), 4);
}

TEST(default_construc) {
  List<int>::Iterator first;
  List<int>::Iterator second;
  ASSERT_TRUE(first == second);
  ASSERT_FALSE(first != second);
}
TEST(default_equalityu_iterators2) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  List<int>::Iterator first = sizes.begin();
  List<int>::Iterator second = sizes.begin();
  ASSERT_TRUE(first == second);
  first++;
  ASSERT_TRUE(first != second);
}
TEST(default_equalityu_iterators) {
  List<int> sizes;
  sizes.push_back(67);
  ASSERT_TRUE(sizes.begin() != sizes.end());
}
TEST(test_iterator_begin) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  auto it = sizes.begin();
  ASSERT_EQUAL(*it, 0);
}
TEST(test_iterator_end) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  auto it = sizes.end();
  it--;
  ASSERT_EQUAL(*it, 4);
}
TEST(test_iterator_plus) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  auto it = sizes.begin();
  it++;
  ASSERT_EQUAL(*it, 1);
}
TEST(test_iterator_minus) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  auto it = sizes.begin();
  it++;
  it++;
  it--;
  ASSERT_EQUAL(*it, 1);
}

TEST(test_insert_empy) {
  List<int> sizes;
  auto it = sizes.insert(sizes.begin(), 10);
  ASSERT_EQUAL(*it, 10);
}
TEST(test_insert_first) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.insert(sizes.begin(), 10);
  ASSERT_EQUAL(sizes.size(), 6);
  ASSERT_EQUAL(sizes.front(), 10);

  auto it = sizes.begin();
  ASSERT_EQUAL(*it, 10);
  it++;
  ASSERT_EQUAL(*it, 0);
  it--;
  ASSERT_EQUAL(*it, 10);
}
TEST(test_insert_back) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.insert(sizes.end(), 10);
  ASSERT_EQUAL(sizes.size(), 6);
  ASSERT_EQUAL(sizes.back(), 10);

  auto it = sizes.end();
  it--;
  ASSERT_EQUAL(*it, 10);
  it--;
  ASSERT_EQUAL(*it, 4);
  it++;
  ASSERT_EQUAL(*it, 10);
}
TEST(test_insert_middle) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  auto middle = sizes.begin();
  middle++;
  sizes.insert(middle, 10);
  ASSERT_EQUAL(sizes.size(), 6);

  auto it = sizes.begin();
  ASSERT_EQUAL(*it, 0);
  it++;
  ASSERT_EQUAL(*it, 10);
  it--;
  ASSERT_EQUAL(*it, 0);
  it++;
  it++;
  ASSERT_EQUAL(*it, 1);
  it--;
  ASSERT_EQUAL(*it, 10);
}

TEST(test_erase_first) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  sizes.erase(sizes.begin());
  ASSERT_EQUAL(sizes.size(), 4);
  ASSERT_EQUAL(sizes.front(), 1);

  auto it = sizes.begin();
  ASSERT_EQUAL(*it, 1);
  it++;
  ASSERT_EQUAL(*it, 2);
  it--;
  ASSERT_EQUAL(*it, 1);
}
TEST(test_erase_end) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  auto end_it = sizes.end();
  end_it--;
  sizes.erase(end_it);
  ASSERT_EQUAL(sizes.size(), 4);
  ASSERT_EQUAL(sizes.back(), 3);

  auto it = sizes.end();
  it--;
  ASSERT_EQUAL(*it, 3);
  it--;
  ASSERT_EQUAL(*it, 2);
  it++;
  ASSERT_EQUAL(*it, 3);
}
TEST(test_erase_middle) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }
  auto middle = sizes.begin();
  middle++;
  sizes.erase(middle);
  ASSERT_EQUAL(sizes.size(), 4);

  auto it = sizes.begin();
  ASSERT_EQUAL(*it, 0);
  it++;
  ASSERT_EQUAL(*it, 2);
  it--;
  ASSERT_EQUAL(*it, 0);
}
TEST(test_decrememnt2) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }

  auto it = sizes.end();
  auto other = it--;
  ASSERT_TRUE(other == sizes.end());
  ASSERT_EQUAL(*it, 4);
}
TEST(test_increment2) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }

  auto it = sizes.begin();
  auto other = it++;
  ASSERT_TRUE(other == sizes.begin());
  ASSERT_EQUAL(*it, 1);
}
TEST(test_insert_begining) {
  List<int> sizes;
  for (int i = 0; i < 5; ++i) {
    sizes.push_back(i);
  }

  auto it = sizes.insert(sizes.begin(), 67);
  ASSERT_TRUE(it == sizes.begin());
  ASSERT_EQUAL(*it, 67);
  ASSERT_EQUAL(sizes.front(), 67);
}

TEST_MAIN()
