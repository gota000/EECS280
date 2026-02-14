#include <cassert>
#include <cmath>
#include <iostream>
#include <array>
#include "Pack.hpp"
#include "Card.hpp"

using namespace std;
  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(){
    next = 0;
    int index = 0;
    for (int i = SPADES; i <= DIAMONDS; i++){
        for (int j = NINE; j <= ACE; j++) {
            Card card(static_cast<Rank>(j), static_cast<Suit>(i));
            cards[index] = card;
            index++;
        }
    }
  }

  

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(std::istream& pack_input){
    next = 0;
    for (int i = 0; i < PACK_SIZE; i++){
        Card new_card;
        pack_input >> new_card;
        cards[i] = new_card;
    }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    Card next_card = cards.at(next);
    next++;
    return next_card;
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
//1 2 3 4 5 6 7 8 9 10 11 12
//13 14 15 16 17 18 19 20 21 22 23 24

//then
// 13 1 14 2 15 3 16 4 17 5 18 6
// 19 7 20 8 21 9 22 10 23 11 24 12

    next = 0;

    for(int i = 0; i < 7 ; ++i){
        array<Card, PACK_SIZE/2> holder;
        array<Card, PACK_SIZE/2> holder2;

        for(int j=0; j < PACK_SIZE/2; ++j){
            holder[j] = cards[j];
            holder2[j] = cards[j + PACK_SIZE/2];
        }
        for(int k=0; k < PACK_SIZE/2; ++k){
            cards[2*k] = holder2[k];
            cards[2*k + 1] = holder[k];
        }
    }
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    return (next > PACK_SIZE - 1);
  }