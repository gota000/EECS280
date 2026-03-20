#include <fstream>
#include <iostream>
using namespace std;





int main(int argc, char* argv[]){
    if (! ((argc == 2) || (argc == 3)) ) {
    cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
    return 1;
  }
  for(int i = 1; i <= argc; ++i){
     ifstream fin(argv[i]);
  if (!fin.is_open()) {
    cout << "Error opening file: " << argv[i] << endl;
    return 1;
  }
}

    cout.precision(3);
}