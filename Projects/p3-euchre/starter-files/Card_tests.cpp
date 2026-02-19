#include "Card.hpp"
#include "unit_test_framework.hpp"

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_default) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(card_suit_and_ranks) {
    Card a(NINE, HEARTS);
    ASSERT_EQUAL(a.get_rank(),NINE);
    ASSERT_EQUAL(a.get_suit(), HEARTS);
    Card a1(TEN, HEARTS);
    ASSERT_EQUAL(a1.get_rank(),TEN);
    ASSERT_EQUAL(a1.get_suit(), HEARTS);
    Card a2(FOUR, DIAMONDS);
    ASSERT_EQUAL(a2.get_rank(),FOUR);
    ASSERT_EQUAL(a2.get_suit(), DIAMONDS);
    ASSERT_EQUAL(a2.get_suit(HEARTS), DIAMONDS);
    ASSERT_EQUAL(a2.get_suit(SPADES), DIAMONDS);
    Card a3(JACK, DIAMONDS);
    ASSERT_EQUAL(a3.get_suit(HEARTS), HEARTS);

    // all four left bower 
    Card a4(JACK, SPADES);
    ASSERT_EQUAL(a4.get_suit(CLUBS), CLUBS);  
    Card a5(JACK, CLUBS);
    ASSERT_EQUAL(a5.get_suit(SPADES), SPADES);  
    Card a6(JACK, HEARTS);
    ASSERT_EQUAL(a6.get_suit(DIAMONDS), DIAMONDS); 

    // Non Jack
    Card a7(ACE, HEARTS);
    ASSERT_EQUAL(a7.get_suit(CLUBS), HEARTS);
    ASSERT_EQUAL(a7.get_suit(HEARTS), HEARTS);
}
TEST(face_card){
    Card j (JACK, DIAMONDS);
    ASSERT_TRUE(j.is_face_or_ace());
    Card A (ACE, DIAMONDS);
    ASSERT_TRUE(A.is_face_or_ace());

    Card B (QUEEN, HEARTS);
    ASSERT_TRUE(B.is_face_or_ace());
    Card C (KING, SPADES);
    ASSERT_TRUE(C.is_face_or_ace());
    Card D (TWO, HEARTS);
    ASSERT_FALSE(D.is_face_or_ace());
}
TEST(right_left_trump){
    Card C(JACK, CLUBS);
    ASSERT_TRUE(C.is_right_bower(CLUBS));
    ASSERT_TRUE(C.is_left_bower(SPADES));
    ASSERT_TRUE(C.is_trump(SPADES));
    ASSERT_TRUE(C.is_trump(CLUBS));
    Card a3(JACK, DIAMONDS);
    ASSERT_TRUE(a3.is_right_bower(DIAMONDS));
    ASSERT_TRUE(a3.is_left_bower(HEARTS));
    ASSERT_FALSE(a3.is_left_bower(SPADES));


}
TEST(next){
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
}
// Add more test cases here
TEST(card_less){
    Card A(ACE, CLUBS);
    Card B(JACK, DIAMONDS);
    Card C(JACK, CLUBS);
    Card D(TWO, HEARTS); 
    Card E(JACK, SPADES);

    ASSERT_TRUE(Card_less(C , B , DIAMONDS));
    ASSERT_TRUE(Card_less(B , C , CLUBS));
    ASSERT_TRUE(Card_less(D , C , CLUBS));
    ASSERT_TRUE(Card_less(C , D , HEARTS));
    ASSERT_TRUE(Card_less(A , D , HEARTS));
    ASSERT_TRUE(Card_less(D , B , HEARTS));

    ASSERT_TRUE(Card_less(D, A, B , DIAMONDS));
    ASSERT_TRUE(Card_less(B, E , A , CLUBS));
    ASSERT_TRUE(Card_less(A, C , D , CLUBS));
    ASSERT_TRUE(Card_less(B, E , D , CLUBS));
    ASSERT_FALSE(Card_less(C, C , D , CLUBS));

    Card F(JACK, CLUBS);  
    Card G(JACK, SPADES);   
    Card H(ACE, CLUBS);

    ASSERT_FALSE(Card_less(F, G, CLUBS));  
    ASSERT_FALSE(Card_less(F, H, CLUBS));  
    ASSERT_TRUE(Card_less(G, F, CLUBS)); 
    ASSERT_FALSE(Card_less(G, H, CLUBS));           

    Card I(SIX, HEARTS);      
    Card J(TWO, HEARTS);
    Card K(ACE, DIAMONDS);

    ASSERT_FALSE(Card_less(J, K, I, CLUBS));  
    ASSERT_TRUE(Card_less(K, J, I, CLUBS));  
}

TEST(comparisons){
    Card A(ACE, CLUBS);
    Card B(JACK, DIAMONDS);
    Card C(JACK, CLUBS);
    Card D(JACK, CLUBS);

    ASSERT_TRUE(B < A);
    ASSERT_FALSE(B <= C);
    ASSERT_FALSE(B == C);

    ASSERT_TRUE(D == C);

    ASSERT_TRUE(A > B);
    ASSERT_TRUE(B >= C); 
    ASSERT_TRUE(B != A);

    ASSERT_TRUE(C < B);

    Card E(JACK, SPADES);
    Card F(JACK, HEARTS);
    ASSERT_TRUE(E < F);
    ASSERT_TRUE(F < C);
    ASSERT_FALSE(F < E);
    ASSERT_TRUE(E <= E);
    ASSERT_TRUE(E >= E);
}


TEST(print){
    Card A(ACE, CLUBS);
    Card B(JACK, DIAMONDS);

    std::ostringstream ss_output;
    ss_output << A;
    ASSERT_TRUE(ss_output.str() == "Ace of Clubs")

    std::ostringstream ss_output2;
    ss_output2 << B;
    ASSERT_TRUE(ss_output2.str() == "Jack of Diamonds")
}

TEST(read){
    Card B(ACE, CLUBS);
    Card A;

    istringstream input("Ace of Clubs");
    input >> A;
    ASSERT_TRUE(A.get_rank() == B.get_rank());
    ASSERT_TRUE(A.get_suit() == B.get_suit());
}

TEST_MAIN()
