#include <cassert>
#include "Matrix.hpp"
using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
    assert(width > 0);
    assert(height > 0);
    mat->height = height;
    mat->width = width;
    mat->data.assign(mat->height * mat->width, 0);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
    os << mat->width << " " << mat->height << '\n';
    int length = mat->width * mat->height;

    int counter = 0;
    for(int i = 0; i < length; i++){
        os << mat->data[i] << " ";
        counter++;
        if(counter == mat->width){
            os << '\n';
            counter = 0;
        }
    }

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
    return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
    assert(row >= 0);
    assert(row < mat->height);
    assert (column >= 0);
    assert(column < mat->width);

    int row_section = row * mat->width;
    int* number = &mat->data.at(row_section + column);    

    return number;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    assert(row >= 0);
    assert(row < mat->height);
    assert(column >= 0);
    assert(column < mat->width);

    int row_section = (row - 1) * column;
    const int* number = &mat->data.at(row_section + (column - 1));  
    return number;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    for (int i = 0; i < mat->data.size(); i++){
        mat->data[i] = value;
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
    // Fill top row
    for (int i = 0; i < mat->width; i++){
        *Matrix_at(mat, 0, i) = value;
    }

    // Fill middle rows (left and right)
    for (int i = 1; i < mat->height - 1; i++) {
        *Matrix_at(mat, i, 0) = value;
        *Matrix_at(mat, i, mat->width - 1) = value;
    }

    // Fill bottom row
    for (int i = 0; i < mat->width; i++){
        *Matrix_at(mat, mat->height - 1, i) = value;
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
    int length = mat->height * mat->width;
    int max = mat->data[0];
    for(int i=0; i < length; i++){
        if(max < mat->data[i]){
            max = mat->data[i];
        }
    }
    return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
    assert(row >= 0);
    assert(row < mat->height);
    assert(column_start >= 0);
    assert(column_end < mat->width);
    assert(column_start < column_end);

    int min_column = column_end;
    int main_min_value = *Matrix_at(mat, 0, column_end);
    for (int i = column_end; i >= column_start; i--){
        int colomn_min_value = *Matrix_at(mat, 0, i);
        for (int j = 1; j < mat->height; j++) {
            if (*Matrix_at(mat, 0, i) < colomn_min_value){
                colomn_min_value = *Matrix_at(mat, 0, i);
            }
        }
        if (colomn_min_value < main_min_value) {
            main_min_value = colomn_min_value;
            min_column = i;
        }
    }
    return min_column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {

    int min = mat->data[column_start];
    for(int i = column_start; i < column_end; i++){
        for(int j = 1; j <= row; j++){
            if(min > mat->data[i*j]){
                min = mat->data[i*j];
            }
        }
    }
    return min;
}
