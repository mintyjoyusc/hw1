#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val) {
  if (tail_ == nullptr || tail_->last == ARRSIZE) {
    Item* newItem = new Item();

    // Correctly set first and last for a new Item
    newItem->first = 0;
    newItem->last = 0; //No elements at first

    if (tail_ != nullptr) {
      newItem->prev = tail_;
      tail_->next = newItem;
    } else {
      newItem->prev = nullptr; 
      head_ = newItem;  
      tail_ = newItem;
    }

    tail_ = newItem;
  }

  // Insert the value at the last index and increment it
  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;
}


void ULListStr::push_front(const std::string& val) {
  if (head_ == nullptr || head_->first == 0) {
    Item* newItem = new Item();

    newItem->first = ARRSIZE - 1; // Start from the end 
    newItem->last = ARRSIZE;

    if (head_ != nullptr) {
      newItem->next = head_;
      head_->prev = newItem;
    } else {
      newItem->next = nullptr; 
      head_ = newItem;
      tail_ = newItem;         // Update tail if the list was empty
    }
    
    head_ = newItem;
  } else {
    head_->first--; 
  }
  head_->val[head_->first] = val;
  size_++;
}

void ULListStr::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("List is empty");
  }
  tail_->last--;
  size_--;
  if (tail_->last == 0) {
    Item* temp = tail_;
    tail_ = tail_->prev;
    if (tail_ != nullptr) {
      tail_->next = nullptr;
    }
    delete temp;
    if (tail_ == nullptr) {
      head_ = nullptr;
    }
  }
}
void ULListStr::pop_front() {
  if (size_ == 0) {
    throw std::out_of_range("List is empty");
  }

  head_->first++;
  size_--;

  if (head_->first == head_->last) {
    Item* temp = head_;
    head_ = head_->next;

    if (head_ != nullptr) {
      head_->prev = nullptr;
    } 
    
    else {

      tail_ = nullptr; 
    }

    delete temp;
  }
}




std::string const & ULListStr::back() const {
  if (size_ == 0) {
    throw std::out_of_range("List is empty");
  }
  return tail_->val[tail_->last - 1];
}
std::string const & ULListStr::front() const {
  if (size_ == 0) {
    throw std::out_of_range("List is empty");
  }
  return head_->val[head_->first];
}
std::string* ULListStr::getValAtLoc(size_t loc) const {
  if (loc >= size_) {
    return nullptr; 
  }

  Item* curr = head_;
  size_t index = 0;

  while (curr != nullptr) {
    if (loc < index + (curr->last - curr->first)) {
      return &(curr->val[curr->first + (loc - index)]);
    }
    index += (curr->last - curr->first);
    curr = curr->next;
  }

  return nullptr; 
}



void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
