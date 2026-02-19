#include "Card.hpp"
#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_add) {
  Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(NINE, SPADES));
  aarush->add_card(Card(TEN, SPADES));
  aarush->add_card(Card(QUEEN, SPADES)); 
  aarush->add_card(Card(KING, SPADES));
  aarush->add_card(Card(ACE, SPADES));

  aarush->add_and_discard(
    Card(NINE, HEARTS) 
  );

  Card card_led = aarush->lead_card(HEARTS);

  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); 

  delete aarush;
}

TEST(test_add2) {
    // if the upcard is the worst, then you dont do anything
    Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(TEN, HEARTS));
  aarush->add_card(Card(KING, HEARTS));
  aarush->add_card(Card(QUEEN, HEARTS)); 
  aarush->add_card(Card(JACK, DIAMONDS));
  aarush->add_card(Card(ACE, HEARTS));

  aarush->add_and_discard(
    Card(NINE, HEARTS) 
  );

  Card c1 = aarush->lead_card(HEARTS);
  Card c2 = aarush->lead_card(HEARTS);
  Card c3 = aarush->lead_card(HEARTS);
  Card c4 = aarush->lead_card(HEARTS);
  Card c5 = aarush->lead_card(HEARTS);

  ASSERT_TRUE(!(c1 == Card(NINE, HEARTS)));
  ASSERT_TRUE(!(c2 == Card(NINE, HEARTS)));
  ASSERT_TRUE(!(c3 == Card(NINE, HEARTS)));
  ASSERT_TRUE(!(c4 == Card(NINE, HEARTS)));
  ASSERT_TRUE(!(c5 == Card(NINE, HEARTS)));

  delete aarush;
}

TEST(test_add3) {
    // if the upcard is the not worst, then replace
    Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(NINE, HEARTS));
  aarush->add_card(Card(TEN, HEARTS));
  aarush->add_card(Card(QUEEN, HEARTS)); 
  aarush->add_card(Card(JACK, DIAMONDS));
  aarush->add_card(Card(KING, HEARTS));

  aarush->add_and_discard(
    Card(JACK, HEARTS) 
  );

  Card c1 = aarush->lead_card(HEARTS);

  ASSERT_TRUE(c1 == Card(JACK, HEARTS));

  delete aarush;
}

TEST(test_add4) {
    // All cards are trump
    Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(NINE, HEARTS));
  aarush->add_card(Card(TEN, HEARTS));
  aarush->add_card(Card(QUEEN, HEARTS)); 
  aarush->add_card(Card(ACE, HEARTS));
  aarush->add_card(Card(KING, HEARTS));

  Card c1 = aarush->lead_card(HEARTS);

  ASSERT_TRUE(c1 == Card(ACE, HEARTS));

  delete aarush;
}

TEST(test_add5) {
    // trump and non trump hand
    Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(NINE, HEARTS));
  aarush->add_card(Card(TEN, HEARTS));
  aarush->add_card(Card(QUEEN, HEARTS)); 
  aarush->add_card(Card(ACE, SPADES));
  aarush->add_card(Card(KING, HEARTS));

  Card c1 = aarush->lead_card(SPADES);

  ASSERT_TRUE(c1 == Card(KING, HEARTS));

  delete aarush;
}

TEST(test_add6) {
    // first index is trump
    Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(ACE, SPADES));
  aarush->add_card(Card(TEN, HEARTS));
  aarush->add_card(Card(QUEEN, HEARTS)); 
  aarush->add_card(Card(ACE, HEARTS));
  aarush->add_card(Card(KING, HEARTS));

  Card c1 = aarush->lead_card(SPADES);

  ASSERT_TRUE(c1 == Card(ACE, HEARTS));

  delete aarush;
}

TEST(test_add7) {
    // left bower is trump
    Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(TEN, HEARTS));
  aarush->add_card(Card(JACK, CLUBS));
  aarush->add_card(Card(QUEEN, HEARTS)); 
  aarush->add_card(Card(ACE, HEARTS));
  aarush->add_card(Card(KING, HEARTS));

  Card c1 = aarush->lead_card(SPADES);

  ASSERT_TRUE(c1 == Card(ACE, HEARTS));

  delete aarush;
}

TEST(test_add8) {
    // check if lead is removing cards well
    Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(TEN, HEARTS));
  aarush->add_card(Card(JACK, HEARTS));
  aarush->add_card(Card(QUEEN, HEARTS)); 
  aarush->add_card(Card(ACE, SPADES));
  aarush->add_card(Card(KING, HEARTS));

  Card c1 = aarush->lead_card(SPADES);
  Card c2 = aarush->lead_card(SPADES);

  ASSERT_TRUE(c1 == Card(KING, HEARTS));
  ASSERT_TRUE(c2 == Card(QUEEN, HEARTS));

  delete aarush;
}

TEST(test_player) {
  Player * human = Player_factory("Mark", "Human");
  ostringstream oss1; 
  oss1 << * human;
  ASSERT_EQUAL(oss1.str(), "Mark");
  Player * robot = Player_factory("Aarush", "Simple");
  ostringstream oss2;
  oss2 << *robot;
  ASSERT_EQUAL(oss2.str(), "Aarush");
  delete human;
  delete robot;
}

TEST(player_make_trump1) {
  Player * Mark = Player_factory("Mark", "Simple");
  Mark->add_card(Card(NINE, HEARTS));
  Mark->add_card(Card(TEN, HEARTS));
  Mark->add_card(Card(QUEEN, HEARTS));
  Mark->add_card(Card(KING, HEARTS));
  Mark->add_card(Card(ACE, HEARTS));
  Card nine_HEARTS(NINE, HEARTS);
  Suit trump;
  bool orderup = Mark->make_trump(nine_HEARTS, true, 1, trump);
  //(upcard, dealer, round, order up)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);
  delete Mark;
}
TEST(player_make_trump2) {
  Player * Mark = Player_factory("Mark", "Simple");
  Mark->add_card(Card(NINE, CLUBS));
  Mark->add_card(Card(TEN, CLUBS));
  Mark->add_card(Card(QUEEN, CLUBS));
  Mark->add_card(Card(KING, CLUBS));
  Mark->add_card(Card(ACE, CLUBS));
  Card nine_HEARTS(NINE, HEARTS);
  Suit trump;
  bool orderup = Mark->make_trump(nine_HEARTS, true, 1, trump);
  //(upcard, dealer, round, order up)
  ASSERT_FALSE(orderup);

  delete Mark;
}
TEST(player_make_trump3) {
  Player * Mark = Player_factory("Mark", "Simple");
  Mark->add_card(Card(NINE, HEARTS));
  Mark->add_card(Card(TEN, HEARTS));
  Mark->add_card(Card(QUEEN, HEARTS));
  Mark->add_card(Card(KING, HEARTS));
  Mark->add_card(Card(ACE, HEARTS));
  Card nine_HEARTS(NINE, HEARTS);
  Suit trump;
  bool orderup = Mark->make_trump(nine_HEARTS, true, 2, trump);
  //(upcard, dealer, round, order up)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, DIAMONDS);
  delete Mark;
}
TEST(player_make_trump4) {
  Player * David = Player_factory("David", "Simple");
  David->add_card(Card(NINE, HEARTS));
  David->add_card(Card(TEN, HEARTS));
  David->add_card(Card(QUEEN, HEARTS));
  David->add_card(Card(KING, HEARTS));
  David->add_card(Card(ACE, HEARTS));
  Card nine_DIAMONDS(NINE, DIAMONDS);
  Suit trump;
  bool orderup = David->make_trump(nine_DIAMONDS, false, 2, trump);
  //(upcard, dealer, round, order up)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);
  delete David;
}
TEST(player_make_trump5) {
  Player * David = Player_factory("David", "Simple");
  David->add_card(Card(NINE, CLUBS));
  David->add_card(Card(TEN, CLUBS));
  David->add_card(Card(QUEEN, CLUBS));
  David->add_card(Card(KING, CLUBS));
  David->add_card(Card(JACK, HEARTS));
  Card nine_DIAMONDS(NINE, DIAMONDS);
  Suit trump;
  bool orderup = David->make_trump(nine_DIAMONDS, false, 2, trump);
  //(upcard, dealer, round, order up)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);
  delete David;
}
TEST(player_make_trump6) {
  Player * David = Player_factory("David", "Simple");
  David->add_card(Card(NINE, CLUBS));
  David->add_card(Card(TEN, CLUBS));
  David->add_card(Card(QUEEN, CLUBS));
  David->add_card(Card(KING, CLUBS));
  David->add_card(Card(TEN, HEARTS));
  Card nine_DIAMONDS(NINE, DIAMONDS);
  Suit trump;
  bool orderup = David->make_trump(nine_DIAMONDS, false, 2, trump);
  //(upcard, dealer, round, order up)
  ASSERT_FALSE(orderup);
  delete David;
}
TEST(player_make_trump7) {
  Player * David = Player_factory("David", "Simple");
  David->add_card(Card(NINE, CLUBS));
  David->add_card(Card(TEN, CLUBS));
  David->add_card(Card(QUEEN, HEARTS));
  David->add_card(Card(KING, CLUBS));
  David->add_card(Card(TEN, HEARTS));
  Card nine_DIAMONDS(NINE, DIAMONDS);
  Suit trump;
  bool orderup = David->make_trump(nine_DIAMONDS, false, 1, trump);
  //(upcard, dealer, round, order up)
  ASSERT_FALSE(orderup);
  delete David;
}
TEST(player_make_trump8) {
  Player * David = Player_factory("David", "Simple");
  David->add_card(Card(NINE, CLUBS));
  David->add_card(Card(TEN, CLUBS));
  David->add_card(Card(QUEEN, DIAMONDS));
  David->add_card(Card(KING, CLUBS));
  David->add_card(Card(JACK, HEARTS));
  Card nine_DIAMONDS(NINE, DIAMONDS);
  Suit trump;
  bool orderup = David->make_trump(nine_DIAMONDS, false, 1, trump);
  //(upcard, dealer, round, order up)
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, DIAMONDS);
  delete David;
}
TEST(player_make_trump9) {
  Player * David = Player_factory("David", "Simple");
  David->add_card(Card(NINE, CLUBS));
  David->add_card(Card(TEN, CLUBS));
  David->add_card(Card(QUEEN, DIAMONDS));
  David->add_card(Card(KING, CLUBS));
  David->add_card(Card(JACK, CLUBS));
  Card nine_DIAMONDS(NINE, DIAMONDS);
  Suit trump;
  bool orderup = David->make_trump(nine_DIAMONDS, false, 2, trump);
  //(upcard, dealer, round, order up)
  ASSERT_FALSE(orderup);
  delete David;
}
TEST(player_make_trump10) {
  Player * David = Player_factory("David", "Simple");
  David->add_card(Card(NINE, CLUBS));
  David->add_card(Card(TEN, CLUBS));
  David->add_card(Card(QUEEN, DIAMONDS));
  David->add_card(Card(KING, CLUBS));
  David->add_card(Card(JACK, DIAMONDS));
  Card nine_DIAMONDS(NINE, DIAMONDS);
  Suit trump;
  bool orderup = David->make_trump(nine_DIAMONDS, false, 2, trump);
  //(upcard, dealer, round, order up)
  ASSERT_TRUE(orderup);
   ASSERT_EQUAL(trump, HEARTS);
  delete David;
}

TEST(test_play_card) { 
  
  Player * Franny = Player_factory("Franny", "Simple");
  Franny->add_card(Card(NINE, HEARTS));
  Franny->add_card(Card(TEN, SPADES));
  Franny->add_card(Card(QUEEN, SPADES));
  Franny->add_card(Card(KING, SPADES));
  Franny->add_card(Card(ACE, SPADES));
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = Franny->play_card(nine_diamonds, HEARTS  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(TEN, SPADES));
  delete Franny;
}
TEST(test_play_card2) { 
  
  Player * Franny = Player_factory("Franny", "Simple");
  Franny->add_card(Card(JACK, HEARTS));
  Franny->add_card(Card(JACK, DIAMONDS));
  Franny->add_card(Card(QUEEN, SPADES));
  Franny->add_card(Card(KING, SPADES));
  Franny->add_card(Card(ACE, SPADES));
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = Franny->play_card(nine_diamonds, HEARTS  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(QUEEN, SPADES));
  delete Franny;
}
TEST(test_play_card3) { 
  
  Player * Franny = Player_factory("Franny", "Simple");
  Franny->add_card(Card(NINE, HEARTS));
  Franny->add_card(Card(TEN, SPADES));
  Franny->add_card(Card(JACK, HEARTS));
  Franny->add_card(Card(KING, DIAMONDS));
  Franny->add_card(Card(ACE, SPADES));
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = Franny->play_card(nine_diamonds, DIAMONDS  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, HEARTS));
  delete Franny;
}
TEST(test_play_card4) { 
  
  Player * Franny = Player_factory("Franny", "Simple");
  Franny->add_card(Card(JACK, CLUBS));
  Franny->add_card(Card(TEN, SPADES));
  Franny->add_card(Card(QUEEN, SPADES));
  Franny->add_card(Card(KING, SPADES));
  Franny->add_card(Card(ACE, SPADES));
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = Franny->play_card(nine_diamonds, SPADES  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(TEN, SPADES));
  delete Franny;
}
// Add more tests here
TEST(test_add_and_discard) {
  Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(NINE, DIAMONDS));
  aarush->add_card(Card(TEN, DIAMONDS));
  aarush->add_card(Card(QUEEN, DIAMONDS)); 
  aarush->add_card(Card(KING, DIAMONDS));
  aarush->add_card(Card(ACE, DIAMONDS));

  aarush->add_and_discard(Card(NINE, HEARTS) ); //upcard gets rid of 9 diamonds

  Card card_led = aarush->lead_card(HEARTS);

  Card ace_diamonds(ACE, DIAMONDS);
  ASSERT_EQUAL(card_led, ace_diamonds); 

  delete aarush;
}
TEST(test_add_and_discard2) {
  Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(JACK, DIAMONDS));
  aarush->add_card(Card(TEN, DIAMONDS));
  aarush->add_card(Card(QUEEN, DIAMONDS)); 
  aarush->add_card(Card(KING, DIAMONDS));
  aarush->add_card(Card(ACE, DIAMONDS));

  aarush->add_and_discard(Card(NINE, DIAMONDS) ); 

  Card card_led = aarush->lead_card(DIAMONDS);

  Card card_placed(JACK, DIAMONDS);
  ASSERT_EQUAL(card_led, card_placed); 

  delete aarush;
}
TEST(test_add_and_discard3) {
  Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(JACK, HEARTS));
  aarush->add_card(Card(TEN, DIAMONDS));
  aarush->add_card(Card(QUEEN, DIAMONDS)); 
  aarush->add_card(Card(KING, DIAMONDS));
  aarush->add_card(Card(ACE, DIAMONDS));

  aarush->add_and_discard(Card(NINE, DIAMONDS) ); 

  Card card_led = aarush->lead_card(DIAMONDS);

  Card card_placed(JACK, HEARTS);
  ASSERT_EQUAL(card_led, card_placed); 

  delete aarush;
}
TEST(test_add_and_discard4) {
  Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(JACK, CLUBS));
  aarush->add_card(Card(TEN, DIAMONDS));
  aarush->add_card(Card(QUEEN, DIAMONDS)); 
  aarush->add_card(Card(KING, DIAMONDS));
  aarush->add_card(Card(ACE, DIAMONDS));

  aarush->add_and_discard(Card(NINE, DIAMONDS) ); 

  Card card_led = aarush->lead_card(DIAMONDS);

  Card card_placed(ACE, DIAMONDS);
  ASSERT_EQUAL(card_led, card_placed); 

  delete aarush;
}
TEST(test_add_and_discard5) {
  Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(JACK, SPADES));
  aarush->add_card(Card(JACK, SPADES));
  aarush->add_card(Card(TEN, SPADES)); 
  aarush->add_card(Card(NINE, HEARTS));
  aarush->add_card(Card(NINE, DIAMONDS));

  aarush->add_and_discard(Card(NINE, SPADES) ); 

  Card card_led = aarush->lead_card(SPADES);

  Card card_placed(NINE, DIAMONDS);
  ASSERT_EQUAL(card_led, card_placed); 

  delete aarush;
}
TEST(test_add_and_discard6) {
  Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(JACK, SPADES));
  aarush->add_card(Card(JACK, SPADES));
  aarush->add_card(Card(TEN, CLUBS)); 
  aarush->add_card(Card(NINE, HEARTS));
  aarush->add_card(Card(NINE, SPADES));

  aarush->add_and_discard(Card(ACE, CLUBS) ); 

  Card card_led = aarush->lead_card(CLUBS);

  Card card_placed(NINE, HEARTS);
  ASSERT_EQUAL(card_led, card_placed); 

  delete aarush;
}
TEST(test_add_and_discard7) {
  Player * aarush = Player_factory("Aarush", "Simple");
  aarush->add_card(Card(JACK, SPADES));
  aarush->add_card(Card(JACK, HEARTS));
  aarush->add_card(Card(TEN, CLUBS)); 
  aarush->add_card(Card(NINE, HEARTS));
  aarush->add_card(Card(NINE, SPADES));

  aarush->add_and_discard(Card(TEN, DIAMONDS) ); 

  Card card_led = aarush->lead_card(DIAMONDS);

  Card card_placed(JACK, SPADES);
  ASSERT_EQUAL(card_led, card_placed); 

  delete aarush;
}

TEST_MAIN()
