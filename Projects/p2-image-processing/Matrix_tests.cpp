#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <cassert>

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
TEST(test_print){
  Matrix mat;
  Matrix_init(&mat, 5,2);      // 20 50 70 0 0
  *Matrix_at(&mat, 0, 0) = 20; // 0  5  0 20 7 
  *Matrix_at(&mat, 0, 1) = 50;
  *Matrix_at(&mat, 0, 2) = 70;
  *Matrix_at(&mat, 1, 1) = 5;
  *Matrix_at(&mat, 1, 3) = 20;
  *Matrix_at(&mat, 1, 4) = 7;
  ostringstream test;
  test << "5 2\n"
           << "20 50 70 0 0 \n"
           << "0 5 0 20 7 \n";
  ostringstream printed;
  Matrix_print(&mat, printed);
  ASSERT_EQUAL(test.str(), printed.str()); // :0
  
}

TEST(test_matrix_at) {
  Matrix mat;
  Matrix_init(&mat, 2,3);

  // fill with numbers
  for(int r = 0; r < Matrix_height(&mat); ++r){
    for(int c = 0; c < Matrix_width(&mat); ++c){
      *Matrix_at(&mat, r, c) = r+c;
    }
  }
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 0);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 2);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 1), 3);

  const int *ptr = Matrix_at(&mat, 1, 1);
  ASSERT_EQUAL(*ptr, 2);

  Matrix_init(&mat, 1,1);
  *Matrix_at(&mat, 0, 0) = 21;
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 21);
}

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill) {
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

TEST (test_fill_border) {
  Matrix mat;
  Matrix_init(&mat, 3,4);
  Matrix_fill_border(&mat, 2);

  for(int c = 0; c < Matrix_width(&mat); ++c){
    ASSERT_EQUAL(*Matrix_at(&mat, 0, c), 2);
  }

  for(int c = 0; c < Matrix_width(&mat); ++c){
    ASSERT_EQUAL(*Matrix_at(&mat, Matrix_height(&mat) - 1, c), 2);
  }

  for (int r = 1; r < Matrix_height(&mat) - 1; r++){
    ASSERT_EQUAL(*Matrix_at(&mat, r, 0), 2);
    ASSERT_EQUAL(*Matrix_at(&mat, r, Matrix_width(&mat) - 1), 2);
  }
}

TEST (test_max) {
Matrix mat;
  Matrix_init(&mat, 5,2);      // 20 50 70 0 0
  *Matrix_at(&mat, 0, 0) = 20; // 0  5  0 20 7 
  *Matrix_at(&mat, 0, 1) = 50;
  *Matrix_at(&mat, 0, 2) = 70;
  *Matrix_at(&mat, 1, 1) = 5;
  *Matrix_at(&mat, 1, 3) = 20;
  *Matrix_at(&mat, 1, 4) = 7;
  ASSERT_EQUAL(Matrix_max(&mat), 70);
}

TEST (test_column_of_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 4,3); 
  *Matrix_at(&mat, 0, 0) = 1; 
  *Matrix_at(&mat, 0, 1) = 0;
  *Matrix_at(&mat, 0, 2) = 1;
  *Matrix_at(&mat, 0, 3) = 0;
  
  *Matrix_at(&mat, 1, 0) = 4; 
  *Matrix_at(&mat, 1, 1) = 8;
  *Matrix_at(&mat, 1, 2) = 4;
  *Matrix_at(&mat, 1, 3) = 1;

  *Matrix_at(&mat, 2, 0) = 0; 
  *Matrix_at(&mat, 2, 1) = 1;
  *Matrix_at(&mat, 2, 2) = 9;
  *Matrix_at(&mat, 2, 3) = 3;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,0, 0, 4), 1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,1, 1, 3), 2);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,2, 1, 4), 1);

  Matrix_init(&mat, 1,1);
  *Matrix_at(&mat, 0, 0) = 21;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,0, 0, 1), 0);
}
TEST(test_min_val_in_row){
  Matrix mat;
  Matrix_init(&mat, 5, 3);      
  //  1  |2 |3 |4 | 5 
  //  6  |7 |8 |9 | 10
  //  11 |12|13|14| 15 
  *Matrix_at(&mat, 0, 0) = 1; 
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 0, 3) = 4;
  *Matrix_at(&mat, 0, 4) = 5;

  *Matrix_at(&mat, 1, 0) = 6; 
  *Matrix_at(&mat, 1, 1) = 7;
  *Matrix_at(&mat, 1, 2) = 8;
  *Matrix_at(&mat, 1, 3) = 9;
  *Matrix_at(&mat, 1, 4) = 10;

  *Matrix_at(&mat, 2, 0) = 11; 
  *Matrix_at(&mat, 2, 1) = 12;
  *Matrix_at(&mat, 2, 2) = 13;
  *Matrix_at(&mat, 2, 3) = 14;
  *Matrix_at(&mat, 2, 4) = 15;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0,4), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0,5), 6);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 3,5), 9);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 4,5), 10);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 2, 4,5), 15);

  Matrix_init(&mat, 1,1);
  *Matrix_at(&mat, 0, 0) = 21;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat,0, 0, 1), 21);

}
TEST_MAIN() // Do NOT put a semicolon here
