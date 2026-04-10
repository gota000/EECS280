#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <cassert>  //assert
#include <iostream>
#include <iterator>  //std::bidirectional_iterator_tag

template <typename T>
class List {
  // OVERVIEW: a doubly-linked, double-ended list with Iterator interface
 public:
  // EFFECTS:  returns true if the list is empty
  bool empty() const { return !first; }

  // EFFECTS: returns the number of elements in this List
  // HINT:    Traversing a list is really slow. Instead, keep track of the size
  //          with a private member variable. That's how std::list does it.
  int size() const { return list_size; }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the first element in the list by reference
  T& front() {
    assert(!empty());
    return first->datum;
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the last element in the list by reference
  T& back() {
    assert(!empty());
    return last->datum;
  }

  // EFFECTS:  inserts datum into the front of the list
  void push_front(const T& datum) {
    // Allocate new Node to heap
    Node* n = new Node;

    // Set data to the data of current first node
    n->datum = datum;
    n->next = first;
    n->prev = nullptr;

    // The previous old first should point to new n
    // Different for if the list was empy
    if (empty()) {
      first = n;
      last = n;
    } else {
      first->prev = n;
      first = n;
    }
    list_size++;
  }

  // EFFECTS:  inserts datum into the back of the list
  void push_back(const T& datum) {
    // Allocate new Node to heap
    Node* n = new Node;

    // Set data to the data of current last node
    n->datum = datum;
    n->next = nullptr;
    n->prev = last;

    // The previous old last should point to new n

    if (empty()) {
      first = n;
      last = n;
    } else {
      last->next = n;
      last = n;
    }

    list_size++;
  }

  // REQUIRES: list is not empty
  // MODIFIES: invalidates all iterators to the removed element
  // EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node* sacrifice = first;

    // check if there is one element
    if (first == last) {
      first = nullptr;
      last = nullptr;
    } else {
      first = first->next;
      first->prev = nullptr;
    }

    delete sacrifice;
    list_size--;
  }

  // REQUIRES: list is not empty
  // MODIFIES: invalidates all iterators to the removed element
  // EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node* sacrifice = last;

    // check if there is one element
    if (first == last) {
      first = nullptr;
      last = nullptr;
    } else {
      last = last->prev;
      last->next = nullptr;
    }
    delete sacrifice;
    list_size--;
  }

  // MODIFIES: invalidates all iterators to the removed elements
  // EFFECTS:  removes all items from the list
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

  // Default Constructor
  List() : first(nullptr), last(nullptr), list_size(0) {}

  // Destructor
  ~List() { clear(); }

  // Copy Costructor
  List(const List& other) : first(nullptr), last(nullptr), list_size(0) { copy_all(other); }

  // Overloading Assignment OPerator
  List<T>& operator=(const List<T>& other) {
    if (&other == this) {
      return *this;
    }
    clear();
    copy_all(other);
    return *this;
  }

 private:
  // a private type
  struct Node {
    Node* next;
    Node* prev;
    T datum;
  };

  // REQUIRES: list is empty
  // EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T>& other) {
    assert(empty());
    for (Node* np = other.first; np; np = np->next) {
      push_back(np->datum);
    }
  }

  Node* first;  // points to first Node in list, or nullptr if list is empty
  Node* last;   // points to last Node in list, or nullptr if list is empty

  int list_size;

 public:
  ////////////////////////////////////////
  class Iterator {
   public:
    // OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.

    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {};

    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.

    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() {  // prefix -- (e.g. --it)
      assert(list_ptr);
      // assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else {  // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) {  // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    T& operator*() const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() {
      assert(list_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator copy = *this;
      operator++();
      return copy;
    }

    bool operator==(const Iterator& other) const {
      return list_ptr == other.list_ptr && node_ptr == other.node_ptr;
    }

    bool operator!=(const Iterator& other) const { return !(*this == other); }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const { return &operator*(); }

   private:
    const List* list_ptr;  // pointer to the List associated with this Iterator
    Node* node_ptr;        // current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position in the given List
    Iterator(const List* lp, Node* np) : list_ptr(lp), node_ptr(np) {}

  };  // List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const { return Iterator(this, first); }

  // return an Iterator pointing to "past the end"
  Iterator end() const { return Iterator(this, nullptr); }

  // REQUIRES: i is a valid, dereferenceable iterator associated with this list
  // MODIFIES: invalidates all iterators to the removed element
  // EFFECTS: Removes a single element from the list container.
  //          Returns An iterator pointing to the element that followed the
  //          element erased by the function call
  Iterator erase(Iterator i) {
    assert(i.list_ptr == this);
    assert(i.node_ptr != nullptr);

    Node* current = i.node_ptr;
    Node* next = current->next;

    // different if it is one element
    if (current == first && current == last){
      first = nullptr;
      last = nullptr;
    }
    // if the current is the first, then "delete" first element
    else if (current == first) {
      first = current->next;
      first->prev = nullptr;
    }
    // if the current is the last, then also delete that 
    else if (current == last) {
      last = current->prev;
      last->next = nullptr;
    }
    // goofy if in the middle
    else {
      current->prev->next = current->next;
      current->next->prev = current->prev;
    }
    delete current;
    list_size--;
    return Iterator(this, next);
  }

  // REQUIRES: i is a valid iterator associated with this list
  // EFFECTS: Inserts datum before the element at the specified position.
  //          Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T& datum) {
    assert(i.list_ptr == this);

    Node *n = new Node();
    n->datum = datum;

    // if it is inserting into the first node 
    if (i.node_ptr == first){
      n->next = first;
      n->prev = nullptr;

      // check if it is empty 
      if (empty()) {
        first = n;
        last = n;
      } else {
        first->prev = n;
        first = n;
      }
    }
    // if it is the last element
    else if (i.node_ptr == nullptr) {
      n->next = nullptr;
      n->prev = last; 

      // if it is empty
      if (empty()) {
        first = n;
        last = n;
      } else {
        last->next = n;
        last = n;
      }
    }
    // another goofy middle case 
    else {
      Node *current = i.node_ptr;
      n->next = current;
      n->prev = current->prev;
      current->prev->next = n;
      current->prev = n;
    }

    list_size++;
    return Iterator(this, n);
  }
};  // List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif  // Do not remove this. Write all your code above this line.
