/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Statistics Project
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_count();
void test_sum();
void test_mean();
void test_median();
void test_min();
void test_max();
void test_stdev();
void test_percentile();
void test_filter();

// Precision for floating point comparison
const double epsilon = 0.00001;

int main() {
  test_count();
  test_sum();
  test_mean();
  test_median();
  test_min();
  test_max();
  test_stdev();
  test_percentile();
  test_filter();

  return 0;
}

static bool almost_equal(double x, double y) {
  return abs(x - y) < epsilon;
}

void test_count() {
  cout << "Test Count" << endl;

  vector<double> data = {-2, 4, 3, 5};
  assert(count(data) == 4);

  cout << "Count PASS" << endl;
}

void test_sum() {
  cout << "Test Sum" << endl;

  vector<double> data = {-2, 4, 3, 5};
  assert(sum(data) == 10);

  data = {-2};
  assert(sum(data) == -2);

  cout << "Sum PASS!" << endl;
}

void test_mean() {
  cout << "Test Mean" << endl;

  vector<double> data = {-3, 3, 5, 2};
  assert(almost_equal(mean(data), 1.75f));

  data = {12};
  assert(almost_equal(mean(data), 12.0f));
    
  cout << "Mean PASS!" << endl;
}

void test_median() {
  cout << "Test Median" << endl;

  vector<double> data = {-3, 3, 5, 2};
  assert(almost_equal(median(data), 2.5f));

  data = {12};
  assert(almost_equal(median(data), 12.0f));

  data = {-4, 20, -2};
  assert(almost_equal(median(data), -2.0f));
    
  cout << "Median PASS!" << endl;
}

void test_min() {
  cout << "Test Min" << endl;

  vector<double> data = {-3, 3, 5, 2};
  assert(min(data) == -3.0f);

  data = {12};
  assert(min(data) == 12.0f);
    
  cout << "Min PASS!" << endl;
}

void test_max() {
  cout << "Test Max" << endl;

  vector<double> data = {-3, 3, 5, 2};
  assert(max(data) == 5.0f);

  data = {12};
  assert(max(data) == 12.0f);
    
  cout << "Max PASS!" << endl;
}

void test_stdev() {
  cout << "Test Standard Deviation" << endl;

  vector<double> data = {-3, 3, 5, 2};
  assert(almost_equal(stdev(data), 3.40343f));

  data = {12, -4};
  assert(almost_equal(stdev(data), 11.313708f));
    
  cout << "Standard Deviation PASS!" << endl;
}

void test_percentile() {
  cout << "Test Percentile" << endl;

  vector<double> data = {-3, 3, 5, 2};
  assert(almost_equal(percentile(data, 0.3f), 1.5f));

  data = {12};
  assert(almost_equal(percentile(data, 0.6f), 12.0f));

  data = {12, 15};
  assert(almost_equal(percentile(data, 1.0f), 15.0f));
    
  cout << "Percentile PASS!" << endl;
}

void test_filter() {
  cout << "Test Filter" << endl;

  vector<double> data = {-3, 3, 5, 2};
  vector<double> criteria = {1, 0, 1, 0};
  assert(filter(data, criteria, 1) == vector<double>({-3, 5}));

  data = {-3, 3};
  criteria = {0, 5};
  assert(filter(data, criteria, 5) == vector<double>({3}));

  data = {-3, 3};
  criteria = {0, 2};
  assert(filter(data, criteria, 5) == vector<double>({}));
    
  cout << "Filter PASS!" << endl;
}