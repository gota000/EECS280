#include <iostream>
using namespace std;




class Game {
 public:
  Game(/* game details */);
  void play();


   private:
  std::vector<Player*> players;
  Pack pack;
  // ...

  
  void shuffle();
  void deal(/* ... */);
  void make_trump(/* ... */);
  void play_hand(/* ... */);
  // ...


  for (size_t i = 0; i < players.size(); ++i) {
  delete players[i];
}

};





int main() {
  cout << "Hello World!\n";

//   // Read command line args and check for errors
//   Game game(/* game details */);
//   game.play();













}
