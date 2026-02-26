#include <fstream>
#include <iostream>

#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;

class Game {
 public:
  Game(istream& fin, string& shuffles, int points,
       vector<pair<string, string>>& player_data)
      : pack(fin), points_win(points), suffle_toggle(shuffles) {
    for (pair<string, string> data : player_data) {
      players.push_back(Player_factory(data.first, data.second));
    }
  }
  void play() {
    while (team_1_points < points_win && team_2_points < points_win) {
      // shuffle at the start

      if (suffle_toggle == "shuffle") {
        shuffle();
      } else {
        pack.reset();
      }

      // reset things
      t1_roundwon = 0;
      t2_roundwon = 0;
      t1_maketrump = false;
      t2_maketrump = false;
      round = 1;

      // print stuff
      cout << "Hand " << hand << endl;
      cout << players[dealer_index]->get_name() << " deals" << endl;
      deal(dealer_index);
      int eldest_hand = (1 + dealer_index) % 4;
      upcard = pack.deal_one();
      cout << upcard << " turned up" << endl;
      cycle_make_trump();

      for (int trick = 0; trick < 5; ++trick) {
        current_led = lead_card(*players[eldest_hand]);
        eldest_hand = play_hand_cycle(eldest_hand);
      }
      march_euchered(t1_maketrump, t2_maketrump, t1_roundwon, t2_roundwon);
      t1_roundwon = 0;
      t2_roundwon = 0;
      dealer_index = (1 + dealer_index) % 4;
      hand++;
    }
    winner();
    end_game();
  }

 private:
  std::vector<Player*> players;
  Pack pack;
  int points_win;
  int team_1_points = 0;
  bool t1_maketrump = false;
  int t1_roundwon = 0;
  int t2_roundwon = 0;
  bool t2_maketrump = false;
  int team_2_points = 0;
  Suit trump_suit;
  int dealer_index = 0;
  int round = 1;
  int hand = 0;
  Card upcard;
  Suit order_up_suit;
  Card current_led;
  Card holder_card;

  string suffle_toggle;

  void shuffle() { pack.shuffle(); }
  /*Each player receives five cards, dealt in alternating batches of 3 and 2.
  That is, deal 3-2-3-2 cards then 2-3-2-3 cards, for a total of 5 cards each.
  The player to the left of the dealer receives the first batch, and dealing
  continues to the left until 8 batches have been dealt.
*/
  // need to account for dealer
  void deal_round(int& deal_first, int start_count) {
    for (int i = 0; i < 4; ++i) {
      int num_cards = (i % 2 == 0) ? start_count : (5 - start_count);
      for (int j = 0; j < num_cards; ++j) {
        players.at(deal_first)->add_card(pack.deal_one());
      }
      deal_first = (1 + deal_first) % 4;
    }
  }

  void deal(int dealer_index) {
    int deal_first = (1 + dealer_index) % 4;
    deal_round(deal_first, 3);
    deal_round(deal_first, 2);
  }

  void cycle_make_trump() {  // cycle of determining who makes the trump
    bool A = false;
    int person = (1 + dealer_index) % 4;  // person to the dealers left
    int counter = 0;
    while (!A) {
      A = make_trump(*players[person]);
      if (A == false) {
        cout << players[person]->get_name() << " passes" << endl;
      } else if (A == true) {
        if (person == 0 || person == 2) {
          t1_maketrump = true;
        } else {
          t2_maketrump = true;
        }
        cout << players[person]->get_name() << " orders up " << order_up_suit
             << endl;
        if (round == 2) {
          cout << endl;
        }
      }
      person = (1 + person) % 4;
      counter++;
      if (counter == 4 && !A) {
        round = 2;
      }
    }
    if (round == 1) {
      trump_suit = upcard.get_suit();
      add_and_discard(*players[dealer_index], upcard);
    } else if (round == 2) {
      trump_suit = order_up_suit;
    }
  }

  bool make_trump(Player& player) {
    return player.make_trump(
        upcard, player.get_name() == players.at(dealer_index)->get_name(),
        round, order_up_suit);
  }

  void add_and_discard(Player& player, const Card& upcard) {
    player.add_and_discard(upcard);
  }
  Card lead_card(Player& player) { return player.lead_card(trump_suit); }

  int play_hand_cycle(
      int eldest_hand) {  // print the person who ordered the led card and then
                          // cycle the play hand
    vector<Card> played;
    vector<int> player_index;
    played.push_back(current_led);
    player_index.push_back(eldest_hand);
    cout << current_led << " led by " << players[eldest_hand]->get_name()
         << endl;
    bool A = true;
    int counter = 0;
    int person = (1 + eldest_hand) % 4;  // left of eldest hand
    while (A) {
      holder_card = play_hand(*players[person]);
      played.push_back(holder_card);
      player_index.push_back(person);
      print_played(*players[person], holder_card);
      counter++;
      person = (1 + person) % 4;
      if (counter == 3) {
        A = false;
      }
    }
    int B = who_won(played, player_index);
    cout << players[B]->get_name() << " takes the trick" << endl;
    cout << endl;
    return B;
  }
  int who_won(vector<Card> played, vector<int> index) {
    Card win = played[0];
    int win_index = index[0];
    for (int i = 1; i < 4; ++i) {
      if (Card_less(win, played[i], current_led, trump_suit)) {
        win = played[i];
        win_index = index[i];
      }
    }
    if (win_index == 0 || win_index == 2) {
      t1_roundwon++;
    } else {
      t2_roundwon++;
    }
    return win_index;
  }

  void print_played(Player& player, Card holder_card) {
    cout << holder_card << " played by " << player.get_name() << endl;
  }

  Card play_hand(Player& player) {
    return player.play_card(current_led, trump_suit);
  }
  void march_euchered(bool t1trump, bool t2trump, int t1roundwon,
                      int t2roundwon) {
    bool euchered = false;
    bool march = false;
    if (t1trump && (t1roundwon == 3 || t1roundwon == 4)) {
      team_1_points++;
    } else if (t2trump && (t2roundwon == 3 || t2roundwon == 4)) {
      team_2_points++;
    }

    if (t1trump && t1roundwon == 5) {
      team_1_points = team_1_points + 2;
      march = true;
    }
    if (t2trump && t2roundwon == 5) {
      team_2_points = team_2_points + 2;
      march = true;
    }
    if (!t1trump && (t1roundwon == 3 || t1roundwon == 4 || t1roundwon == 5)) {
      team_1_points = team_1_points + 2;
      euchered = true;
    }
    if (!t2trump && (t2roundwon == 3 || t2roundwon == 4 || t2roundwon == 5)) {
      team_2_points = team_2_points + 2;
      euchered = true;
    }
    if (t1roundwon > t2roundwon) {
      cout << players[0]->get_name() << " and " << players[2]->get_name()
           << " win the hand" << endl;
    } else {
      cout << players[1]->get_name() << " and " << players[3]->get_name()
           << " win the hand" << endl;
    }
    if (euchered) {
      cout << "euchred!" << endl;
    } else if (march) {
      cout << "march!" << endl;
    }
    cout << players[0]->get_name() << " and " << players[2]->get_name()
         << " have " << team_1_points << " points" << endl;
    cout << players[1]->get_name() << " and " << players[3]->get_name()
         << " have " << team_2_points << " points" << endl;
    cout << endl;
  }

  void winner() {
    if (team_1_points >= points_win) {
      cout << players.at(0)->get_name() << " and " << players.at(2)->get_name()
           << " win!" << endl;
    } else {
      cout << players.at(1)->get_name() << " and " << players.at(3)->get_name()
           << " win!" << endl;
    }
  }

  void end_game() {
    for (size_t i = 0; i < players.size(); ++i) {
      delete players[i];
    }
  }
};

int main(int argc, char* argv[]) {
  if (!(argc == 12)) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
         << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
         << "NAME4 TYPE4" << endl;
    return 1;
  }
  string shuffle = argv[2];
  int points = stoi(argv[3]);
  string p1 = argv[4];
  string p1t = argv[5];
  string p2 = argv[6];
  string p2t = argv[7];
  string p3 = argv[8];
  string p3t = argv[9];
  string p4 = argv[10];
  string p4t = argv[11];

  if (!(points <= 100 && points >= 1 &&
        (shuffle == "shuffle" || shuffle == "noshuffle") &&
        (p1t == "Simple" || p1t == "Human") &&
        (p2t == "Simple" || p2t == "Human") &&
        (p3t == "Simple" || p3t == "Human") &&
        (p4t == "Simple" || p4t == "Human"))) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
         << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
         << "NAME4 TYPE4" << endl;
    return 1;
  }
  ifstream fin(argv[1]);
  if (!fin.is_open()) {
    cout << "Error opening " << argv[1] << endl;
    return 1;
  }

  for (int i = 0; i < argc; i++) {
    cout << argv[i] << " ";
  }
  cout << endl;

  //   // Read command line args and check for errors
  vector<pair<string, string>> player_data = {
      {p1, p1t}, {p2, p2t}, {p3, p3t}, {p4, p4t}};
  Game game(fin, shuffle, points, player_data);
  game.play();
}
