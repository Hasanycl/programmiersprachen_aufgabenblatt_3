#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>
#include <utility>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.12)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  //Dereferencing to access values
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    else {
        return node->value;
    }
  }

  //Dereferencing
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    else {
        return &node->value;
    }
  } 


  /* PREINCREMENT advances one element forward and returns it*/
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    
     node = node->next;
     return *this;
  }

  /* POSTINCREMENT returns the iterator first then advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    else if (node->next == nullptr) {//if we reach to the end
        ListNode<T>* firstversion = node;//to store first version
        node = nullptr;
        return ListIterator<T>{ firstversion };
    }
    else {
        node = node->next;
        return ListIterator<T>{ node->prev };
    }
  }


  /*Equality-Operation for Iterator
   checks if iterators are refering same node */
  bool operator==(ListIterator<T> const& x) const {

      return (node == x.node);
  }

  /*checks if the nodes of the iterators are not equal */
  bool operator!=(ListIterator<T> const& x) const {

      return !(node == x.node);
  } 

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } else {
      return ListIterator{nullptr};
    }
  }


  ListNode <T>* node = nullptr;
};



template <typename T>
class List {
public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type = T;
    using pointer = T*;
    using const_pointer = T const*;
    using reference = T&;
    using const_reference = T const&;
    using iterator = ListIterator<T>;


    /* default constructor */
    List() :
        size_{ 0 },
        first_{ nullptr },
        last_{ nullptr }{}


    //Copy-Konstruktor using Deep-Copy semantics
    List(List const& otherList) :List() {//if i dont do :List() i get an error which is probably because of initializing membervariables
        ListNode<T>* n = otherList.first_;//to track otherList
        for (int i = 1; i <= otherList.size(); i++) {//copies the value with push_back until the given list ends
            push_back(n->value);
            n = n->next;

        }

    }


    //Move-Konstruktor
    List(List&& rhs) :
        size_{rhs.size_},
        first_{ rhs.first_ },
        last_{ rhs.last_ }{
        rhs.size_ = 0;
        rhs.first_ = nullptr;
        rhs.last_ = nullptr;
    }


    //TODO: Initializer-List Konstruktor , takes the content from ini_list and puts them into the list
   List(std::initializer_list<T> ini_list):
        size_{ 0 },
        first_{ nullptr },
        last_{ nullptr }{
           for(auto element : ini_list) {
                this->push_back(element);
        }
  }

    //swap function
    void swap(List& otherList) {
        std::swap(size_, otherList.size_);
        std::swap(first_, otherList.first_);
        std::swap(last_, otherList.last_);

    }
    //(unifying) Assignment operator
    List& operator=(List otherList) {
        swap(otherList);
        return *this;
    }

    //checks if two lists equal
    bool operator==(List const& rhs) const {

        if (this->size_ == rhs.size_) {
            ListNode<T>* temp = first_;
            ListNode<T>* temp1 = rhs.first_;
            while (temp != nullptr && temp1 != nullptr) {

                if (temp->value != temp->value) { return false; }//if values are not same

                temp = temp->next; //move to next node
                temp1 = temp1->next;
            }
            return true;
        }
        else {
            return false;//if sizes are not equal
        }
    }

    bool operator!=(List const& rhs) const {
        if (*this == rhs) {
            return false;
        }
        else { return true; }
    }

    /* Destructor */
    ~List() {
        clear();
    }

    /* returns an iterator to the first element of the list */
    ListIterator<T> begin() {

        return ListIterator<T>{first_};
    }

    /* returns an iterator to element after last element */
    ListIterator<T> end() {

        return ListIterator<T>{nullptr};
    }

    /* deletes all of the elements */
    void clear() {
        while (!empty()) {
            pop_back();
        }
    }


    /* ... */
    //TODO: member function insert (Aufgabe 3.13)
   

    //makes the elements of the list reverse
    void reverse() {
        ListNode<T>* curr = first_;//pointer curr to track current node
        ListNode<T>* temp;
        while (curr != nullptr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        std::swap(first_, last_);
    }


    /*adds an element to front of the list */
    void push_front(T const& element) {
        ListNode<T>* n = new ListNode<T>{ element , nullptr , nullptr };
        if (empty()) {
            first_ = n;
            last_ = n;
        }
        else {
            n->next = first_;
            first_->prev = n;
            first_ = n;
        }
        ++size_;
    }

    /*adds an element to back of the list */
    void push_back(T const& element) {
        ListNode<T>* n = new ListNode<T>{ element , nullptr , nullptr };
        if (empty()) {
            first_ = n;
            last_ = n;
        }
        else {
            n->prev = last_;
            last_->next = n;
            last_ = n;
        }
        ++size_;
      

    }

    /*removes an element from the front */
    void pop_front() {
        if (empty()) {
            throw "List is empty";
        }

        else if (size() == 1) {

            delete first_;
            first_ = nullptr;
            last_ = nullptr;
            --size_;
        }
        else {
            first_ = first_->next;
            delete first_->prev;
            first_->prev = nullptr;
            --size_;
        }
    }

    /* removes an element from the back*/
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      else if (size() == 1) {

          delete first_;
          first_ = nullptr;
          last_ = nullptr;
          --size_;
      }
      else if (size() > 1){
      
          last_ = last_->prev;
          delete last_->next;
          last_->next = nullptr;
          --size_;
        }

    }

    /* returns a reference to the first element */
    T& front() {
      if(empty()) {
        throw "List is empty";
      }
      else {
          return first_->value;
      }
    }

    /* returns a reference to the last element */
    T& back() {
      if(empty()) {
        throw "List is empty";
      }
      else {
          return last_->value;
      }
    }

    /* checks if the list is empty or not */
    bool empty() const {
      if (size() == 0) {
        return true;
      }
      return false;
   };


    /* returns the size of our list */
    std::size_t size() const{

      return size_;
  };


  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* makes the elements of the list reverse(free function)*/
template<typename T>
List<T>* reverse( List<T> const& otherList){
    List<T>* temp = new List<T>{ otherList};
    temp->reverse();
    return temp;
}

// Free function to concatenate two lists together
template<typename T>
List<T> operator+(List<T> list, List<T> list1) {
    List<T> result{list};//to store the result
    for (auto element : list1) {
        result.push_back(element);
    }
    return result;
}


#endif // # define BUW_LIST_HPP
