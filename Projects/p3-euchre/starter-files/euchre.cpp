#include <iostream>
#include <fstream>
#include "Pack.hpp"
#include "Player.hpp"

using namespace std;




// class Game {
//  public:
//   Game(/* game details */);
//   void play();


//    private:
//   std::vector<Player*> players;
//   Pack pack;
//   // ...

  
//   void shuffle();
//   void deal(/* ... */);
//   void make_trump(/* ... */);
//   void play_hand(/* ... */);
//   // ...


//   for (size_t i = 0; i < players.size(); ++i) {
//   delete players[i];
// }

// };





int main(int argc, char* argv[]) {


if(!(argc == 12)){
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

    if( !( points <= 100 && points >= 1
     && (shuffle == "shuffle"  ||   shuffle == "noshuffle") 
     && (p1t =="Simple" ||p1t =="Human" ) 
     && (p2t =="Simple" ||p2t =="Human" )  
    && (p3t =="Simple" ||p3t =="Human")
    && (p4t =="Simple" ||p4t =="Human") )   ){

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

 
  

  
//   // Read command line args and check for errors
//   Game game(/* game details */);
//   game.play();









}
