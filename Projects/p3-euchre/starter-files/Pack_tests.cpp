#include "Card.hpp"
#include "Pack.hpp"
#include "unit_test_framework.hpp"
#include <fstream>

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_init) {
    Pack pack;
    Card second = pack.deal_one();
    second = pack.deal_one();
    ASSERT_EQUAL(TEN, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
    pack.reset();
    second = pack.deal_one();
    ASSERT_EQUAL(NINE, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
}

TEST(test_pack_empty) {
  Pack pack;
  for (int i = 0; i < 24 - 1; ++i) {
    pack.deal_one();
    ASSERT_FALSE(pack.empty());
  }
  pack.deal_one();
  ASSERT_TRUE(pack.empty());
}

TEST(SHUFFLE){
  Pack pack;
  pack.shuffle();
  Card card = pack.deal_one();
  ASSERT_EQUAL(card, Card(KING, CLUBS));
  card = pack.deal_one();
  ASSERT_EQUAL(card, Card(JACK, HEARTS));
  card = pack.deal_one();
  ASSERT_EQUAL(card, Card(NINE, SPADES));
}

TEST_MAIN()
