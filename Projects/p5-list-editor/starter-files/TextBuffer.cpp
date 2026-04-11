#include "TextBuffer.hpp"

#include <cassert>

// EFFECTS: Creates an empty text buffer. Its cursor is at the past-the-end
//          position, with row 1, column 0, and index 0.
TextBuffer::TextBuffer() {
  row = 1;
  column = 0;
  index = 0;
  cursor = data.end();
}

// MODIFIES: *this
// EFFECTS:  Moves the cursor one position forward and returns true,
//           unless the cursor is already at the past-the-end position,
//           in which case this does nothing and returns false.
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
bool TextBuffer::forward() {
  if (index == data.size()) {
    return false;
  }
  char current = *cursor;
  cursor++;
  index++;
  if (current == '\n') {
    row++;
    column = 0;
  } else {
    column++;
  }
  return true;
}

// MODIFIES: *this
// EFFECTS:  Moves the cursor one position backward and returns true,
//           unless the cursor is already at the first character in
//           the buffer, in which case this does nothing and returns false.
// HINT:     Implement and use the private compute_column() member
//           function to compute the column when moving left from the
//           beginning of a line to the end of the previous one.
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
bool TextBuffer::backward() {
  if (0 == index) {
    return false;
  }
  cursor--;
  index--;
  if (*cursor == '\n') {
    row--;
    column = compute_column();
  } else {
    column--;
  }
  return true;
}

// MODIFIES: *this
// EFFECTS:  Inserts a character in the buffer before the cursor position.
//           If the cursor is at the past-the-end position, this means the
//           inserted character is the last character in the buffer.
//           The cursor remains in the same place as before the insertion.
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
void TextBuffer::insert(char c) {
  if (index == data.size()) {
    data.push_back(c);
  } else {
    data.insert(cursor, c);
  }
  index++;
  if (c == '\n') {
    row++;
    column = 0;
  } else {
    column++;
  }
}

// MODIFIES: *this
// EFFECTS:  Removes the character from the buffer that is at the cursor and
//           returns true, unless the cursor is at the past-the-end position,
//           in which case this does nothing and returns false.
//           The cursor will now point to the character that was after the
//           deleted character, or the past-the-end position if the deleted
//           character was the last one in the buffer.
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
bool TextBuffer::remove() {
  if (index == data.size()) {
    return false;
  }
  cursor = data.erase(cursor);
  return true;
}

// MODIFIES: *this
// EFFECTS:  Moves the cursor to the start of the current row (column 0).
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
void TextBuffer::move_to_row_start() {
  if (column == 0) {  // if its alr at the start
    return;
  }

  while (cursor != data.begin()) {
    cursor--;

    if (*cursor == '\n') {
      cursor++;  // this is because \n is considered the one above
      break;
    }

    index--;
  }
  column = 0;
}

// MODIFIES: *this
// EFFECTS:  Moves the cursor to the end of the current row (the
//           newline character that ends the row, or the past-the-end
//           position if the row is the last one in the buffer).
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
void TextBuffer::move_to_row_end() {
  while (cursor != data.end()) {
    if (*cursor == '\n') {
      break;
    }
    cursor++;
    index++;
    column++;
  }
}

// REQUIRES: new_column >= 0
// MODIFIES: *this
// EFFECTS:  Moves the cursor to the given column in the current row,
//           if it exists. If the row does not have that many columns,
//           moves to the end of the row (the newline character that
//           ends the row, or the past-the-end position if the row is
//           the last one in the buffer).
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
void TextBuffer::move_to_column(int new_column) {
  assert(new_column >= 0);

  move_to_row_start();

  // go to the row
  while (!is_at_end() && data_at_cursor() != '\n' && column < new_column) {
    forward();
  }
}

// MODIFIES: *this
// EFFECTS:  Moves the cursor to the previous row, retaining the
//           current column if possible. If the previous row is
//           shorter than the current column, moves to the end of the
//           previous row (the newline character that ends the row).
//           Does nothing if the cursor is already in the first row.
//           Returns true if the position changed, or false if it did
//           not (i.e. if the cursor was already in the first row).
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
bool TextBuffer::up() {
  int old_col = column;
  if (row == 1) {
    return false;
  }
  // go to the previous row
  while (true) {
    backward();
    if (data_at_cursor() == '\n') {
      break;
    }
  }
  // compute the new column length();
  int new_col = compute_column();
  if (old_col > new_col) {
    return true;
  } else {
    move_to_column(old_col);
    return true;
  }
}

// MODIFIES: *this
// EFFECTS:  Moves the cursor to the next row, retaining the current
//           column if possible. If the next row is shorter than the
//           current column, moves to the end of the next row (the
//           newline character that ends the row, or the past-the-end
//           position if the row is the last one in the buffer). Does
//           nothing if the cursor is already in the last row.
//           Returns true if the position changed, or false if it did
//           not (i.e. if the cursor was already in the last row).
// NOTE:     Your implementation must update the row, column, and index
//           if appropriate to maintain all invariants.
bool TextBuffer::down() {
  int current_col = column;
  Iterator old_cur = cursor;
  int old_row = row;
  int old_column = column;
  int old_index = index;

  if (index == data.size()) {
    return false;
  }
  while (index < data.size() && data_at_cursor() != '\n') {
    cursor++;
    index++;
    column++;
  }
  if (index == data.size()) {
    cursor = old_cur;
    row = old_row;
    column = old_column;
    index = old_index;
    return false;
  }
  cursor++;
  column = 0;
  row++;
  index++;
  for (int i = 0; i < current_col; i++) {
    if (index == data.size() || data_at_cursor() == '\n') {
      return true;
    }
    column++;
    cursor++;
    index++;
  }
  return true;
}

// EFFECTS:  Returns whether the cursor is at the past-the-end position.
bool TextBuffer::is_at_end() const {
  if (index == data.size()) {
    return true;
  } else {
    return false;
  }         
}

// REQUIRES: the cursor is not at the past-the-end position
// EFFECTS:  Returns the character at the current cursor
char TextBuffer::data_at_cursor() const {
  assert(!is_at_end());
  return *cursor;
}

// EFFECTS:  Returns the row of the character at the current cursor.
int TextBuffer::get_row() const { return row; }

// EFFECTS:  Returns the column of the character at the current cursor.
int TextBuffer::get_column() const { return column; }

// EFFECTS:  Returns the index of the character at the current cursor
//           with respect to the entire contents. If the cursor is at
//           the past-the-end position, returns size() as the index.
int TextBuffer::get_index() const { return index; }

// EFFECTS:  Returns the number of characters in the buffer.
int TextBuffer::size() const { return data.size(); }

// EFFECTS:  Returns the contents of the text buffer as a string.
// HINT: Implement this using the string constructor that takes a
//       begin and end iterator. You may use this implementation:
//         return std::string(data.begin(), data.end());
std::string TextBuffer::stringify() const {
  return std::string(data.begin(), data.end());
}

// EFFECTS: Computes the column of the cursor within the current row.
// NOTE: This does not assume that the "column" member variable has
//       a correct value (i.e. the row/column INVARIANT can be broken).
int TextBuffer::compute_column() const {
  int count = 0;
  Iterator copy = cursor;
  int i = index;

  while (i > 0) {
    copy--;

    if (*copy == '\n') {
      return count;
    }

    count++;
    i--;
  }
  return count;
}
