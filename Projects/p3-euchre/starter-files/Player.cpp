#include <cassert>
#include <cmath>
#include <iostream>
#include <array>
#include "Player.hpp"
#include "Card.hpp"

using namespace std;

/*To answer your question:

We do need to create the constructors for the derived classes. 
It is absolutely right to create the name as a private member variable and use the constructor to set it.

So, whatever you're seeing in the hpp file is just the base class.
 You'll need to create two classes One for Human and Other for simple, and derive the stuff from the Base class.*/

std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

class SimplePlayer : public Player{
private:
    string player_name = "";
    array<Card, 6> cards;
    int next;

public:
    SimplePlayer(const std::string &name) : player_name(name){
        next = 0;
    }
        
    const std::string & get_name() const override{
        return player_name; 
    }
    void add_card(const Card &c) override{
        if(next < MAX_HAND_SIZE){
            cards[next] = c;
            next++;
        }
    }
    //REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override{
        assert(round == 1 || round == 2);
        if(round == 1){  // round one
            for(int j = SPADES; j < 4 ; ++j){ // goes through all of the suits
                if(upcard.get_suit() == j){ // if the upcard is equal the suit
                int count = 0;
                for(int i = 0 ; i< 5; ++i){ //create a counter at 0 and then loop through all the cards
                    if((cards[i].get_suit() == j && cards[i].is_face_or_ace()) || cards[i].is_left_bower(static_cast<Suit>(j))){// if the card is the upcard suit 
                        count++;                        //and is a face or ace or left bower it adds to counter
                    }
                }
                if(count >= 2){ // if the suit had more than 2 
                    order_up_suit = static_cast<Suit>(j); // order the upcard and then return true
                    return true;
                }
            }
            }
            return false; // else then just return false for pass
    }
    if(round == 2){
        if(is_dealer){
            order_up_suit = Suit_next(upcard.get_suit());
            return true;
        }
        int card_suit = Suit_next(upcard.get_suit());                
        int count1 = 0;
        for(int i = 0 ; i< 5; ++i){ //create a counter at 0 and then loop through all the cards
                    if((cards[i].get_suit() == card_suit && cards[i].is_face_or_ace()) || cards[i].is_left_bower(static_cast<Suit>(card_suit))){// if the card is the upcard suit 
                        count1++;                        //and is a face or ace or left bower it adds to counter
                    }
                }
                if(count1 >= 2){ // if the suit had more than 2 
                    order_up_suit = static_cast<Suit>(card_suit); // order the upcard and then return true
                    return true;
                }
                return false;
        
     }
     return false;
    }
    // //REQUIRES Player has at least one card
    // //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override{
        Suit trump_suit = upcard.get_suit();

        Card least_card = cards[0];
        int least_index = 0;
        // find lowest in 5 cards in the player hand
        for (int i = 0; i < next; i++){
            // find lowest card
            if (Card_less(cards.at(i), least_card, trump_suit)){
                least_card = cards.at(i);
                least_index = i;
            }
        }

        if (Card_less(upcard, least_card, trump_suit)) {
            // Do nothing if the upcard is the worst card 
        } else {
            // Replace the card with 
            cards[least_index] = upcard;
        }
    }
    Card lead_card(Suit trump) override{
        // If you dont have any trump cards then play highest non trump card

        // check if all is trump
        bool all_trump = true;
        for (int i = 0; i < next; i++){
            if (cards.at(i).get_suit() != trump){
                all_trump = false;
            }
        }

        Card highest_card = cards[0];
        // if it is trump
        if (all_trump){
            for (int i = 0; i < next; i++){
                // find highest card
                if (Card_less(highest_card, cards.at(i), trump)){
                    highest_card = cards.at(i);
                }
            }
        } else {
            for (int i = 0; i < next; i++){
                // find highest card non trump
                if (Card_less(highest_card, cards.at(i), trump) && (cards.at(i).get_suit() != trump)){
                    highest_card = cards.at(i);
                }
            }
        }
        return highest_card;
    }
    Card play_card(const Card &led_card, Suit trump) override{
        return cards[0];
    }
};


Player * Player_factory(const std::string &name, const std::string &strategy) {
    // We need to check the value of strategy and return 
    // the corresponding player type.
    if (strategy == "Simple") {
        // The "new" keyword dynamically allocates an object.
        
        return new SimplePlayer(name);
    }
    // Repeat for each other type of Player
    // Invalid strategy if we get here
    
    assert(false);
    return nullptr;
}

// //EFFECTS returns player's name 
// const std::string & get_name(){
//     //  return Player_factory(const std::string &name, const std::string &strategy);
// }

// //REQUIRES player has less than MAX_HAND_SIZE cards
// //EFFECTS  adds Card c to Player's hand
// void add_card(const Card &c) {

// }

// //REQUIRES round is 1 or 2
// //MODIFIES order_up_suit
// //EFFECTS If Player wishes to order up a trump suit then return true and
// //  change order_up_suit to desired suit.  If Player wishes to pass, then do
// //  not modify order_up_suit and return false.
// bool make_trump(const Card &upcard, bool is_dealer,
//                           int round, Suit &order_up_suit){
                            
// }

// //REQUIRES Player has at least one card
// //EFFECTS  Player adds one card to hand and removes one card from hand.
// void add_and_discard(const Card &upcard){

// }

// //REQUIRES Player has at least one card
// //EFFECTS  Leads one Card from Player's hand according to their strategy
// //  "Lead" means to play the first Card in a trick.  The card
// //  is removed the player's hand.
// Card lead_card(Suit trump){
    
// }

// //REQUIRES Player has at least one card
// //EFFECTS  Plays one Card from Player's hand according to their strategy.
// //  The card is removed from the player's hand.
// Card play_card(const Card &led_card, Suit trump){

// }