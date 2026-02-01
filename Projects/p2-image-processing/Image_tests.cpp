#include "Image.hpp"
#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_height){
  Image img;
  Image_init(&img, 5, 4);
  ASSERT_EQUAL(Image_height(&img), 4);
}

TEST(test_width){ 
  Image img;
  Image_init(&img, 5, 4);
  ASSERT_EQUAL(Image_width(&img), 5);
}

TEST(test_init){ 
  Image img;
  Image_init(&img, 2, 2);

  ostringstream s;
  Image_print(&img, s);

  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_init2){ 
  Image img;
  Image_init(&img, 2, 2);

  string input = "P3 2 2 255 255 0 255 0 255 0 255 0 255 255 255 225 \n";
  istringstream ss_input(input);
  Image_init(&img, ss_input);

  string output_correct = "P3\n2 2\n255\n255 0 255 0 255 0 \n255 0 255 255 255 225 \n";
  std::ostringstream ss_output;
  Image_print(&img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);
}

TEST(test_get_set){
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  ASSERT_TRUE( Pixel_equal(Image_get_pixel(&img, 0, 0), red));
  ASSERT_TRUE( Pixel_equal(Image_get_pixel(&img, 0, 1), green));
  ASSERT_TRUE( Pixel_equal(Image_get_pixel(&img, 1, 0), blue));
  ASSERT_TRUE( Pixel_equal(Image_get_pixel(&img, 1, 1), white));
}

TEST(test_fill){
  Image img;
  const Pixel blue = {0, 0, 255};

  Image_init(&img, 2, 2);
  Image_fill(&img, blue);

  ASSERT_TRUE( Pixel_equal(Image_get_pixel(&img, 0, 0), blue));
  ASSERT_TRUE( Pixel_equal(Image_get_pixel(&img, 0, 1), blue));
  ASSERT_TRUE( Pixel_equal(Image_get_pixel(&img, 1, 0), blue));
  ASSERT_TRUE( Pixel_equal(Image_get_pixel(&img, 1, 1), blue));
}

// TEST(image_initialization_crabster){
//   Image img;
  

// }
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
