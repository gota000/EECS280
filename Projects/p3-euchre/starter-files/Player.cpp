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
            if (!cards[i].is_trump(trump)){
                all_trump = false;
            }
        }

        int chosen_index = 0;
        if (all_trump){
            // Find highest card
            for (int i = 0; i < next; i++){
                if (Card_less(cards.at(chosen_index), cards.at(i), trump)){
                    chosen_index = i;
                }
            }
        } else {
            // edit chosen_index cause index 0 might be a trump
            for (int i = 0; i < next; i++){
                if (!cards[i].is_trump(trump)){
                    chosen_index = i;
                    break;
                }
            }

            // find highest non trump
            for (int i = 0; i < next; i++){
                if (!cards.at(i).is_trump(trump) &&
                    Card_less(cards.at(chosen_index), cards.at(i), trump)){
                    chosen_index = i;
                }
            }
        }

        Card lead_card = cards[chosen_index];
        // Remove the card from hand
        cards[chosen_index] = cards[next - 1];
        next--;
        return lead_card;
    }
    Card play_card(const Card &led_card, Suit trump) override{
        //When playing a card, Simple Players use a simple strategy that considers only the suit that was led. A more complex strategy would also consider the cards on the table.
//If a Simple Player can follow suit, they play the highest card that follows suit. Otherwise, they play the lowest card in their hand.


        // first case, is play a card if you have a card that follows the lead suit
        for (int i = 0; i < next; i++) {
            // check if cards match the trump suit
            if (cards.at(i).is_trump(trump)){

            }
        }
                // is next the amount of cards in the hand
        // second case, is if you dont have any trump cards or lead cards
        int lowest = cards[0].get_rank();
        int low = 0;
        for(int j = 0; j < next; j++){
         if(cards[j].get_rank() < lowest){
            lowest = cards[j].get_rank();
            low = j;
         }
            
        }
        return cards[low];
        // Mark you do this case!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ok chigga
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