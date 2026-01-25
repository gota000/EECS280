#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

TEST(test_init) {
  Matrix mat;
  Matrix_init(&mat, 2,3);

  ASSERT_EQUAL(Matrix_height(&mat), 3);
  ASSERT_EQUAL(Matrix_width(&mat), 2);

  for(int r = 0; r < Matrix_height(&mat); ++r){
    for(int c = 0; c < Matrix_width(&mat); ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), 0);
    }
  }
}

TEST(test_matrix_at) {
  Matrix mat;
  Matrix_init(&mat, 2,3);
}

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
