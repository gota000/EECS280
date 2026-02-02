#include <iostream>
#include "processing.hpp"
#include "Image.hpp"
#include <fstream>

using namespace std;

static void load_image(Image* img, const string &filename);
static void write_image(const Image* img, const string &filename);

int main(int argc, char* argv[]) {
    // cout << "1st argv is: " << argv[1] << endl;
    // cout << "2nd argv is: " << argv[2] << endl;
    // cout << "3rd argv is: " << stoi(argv[3]) << endl;
    // cout << "4th argv is: " << stoi(argv[4]) << endl;

    int width = stoi(argv[3]);
    int height = stoi(argv[4]);

    Image img;
    load_image(&img, argv[1]);

    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    Image_init(&img, fin);

    if(!(width > 0 && width <= Image_width(&img)
        && height > 0 && height <= Image_height(&img)
        && (argc == 4 || argc == 5))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }

    string new_file_name = argv[2];
    seam_carve(&img, width, height);
    write_image(&img, new_file_name);
}

static void write_image(const Image* img, const string &filename) {
  ofstream fout(filename);
  Image_print(img, fout);
}

static void load_image(Image* img, const string &filename) {
  
}
