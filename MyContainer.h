#ifndef MYCONTAINER_H_INCLUDED
#define MYCONTAINER_H_INCLUDED

// C++ program to implement a custom container class template with basic operations.
#include <iostream>
#include <iterator>
#include <stdexcept>
using namespace std;


// Custom container class template
template <class T, class Allocator = allocator<T>> class MyContainer{
  public:
    // Type definitions for easier access to types used in the container
    // Type of elements stored in the container
    using value_type = T;

    // Allocator type used for memory management
    using allocator_type = Allocator;

    // Reference type to the container's elements
    using reference = value_type &;

    // Constant reference type to the container's elements
    using const_reference = const value_type &;

    // Type for size and capacity of the container
    using size_type = size_t;

    // Type for difference between iterator positions
    using difference_type = ptrdiff_t;

    // Iterator class for the custom container
    class iterator{
      public:
        // Type definitions for the iterator

        // Category tag for random access iterators
        using iterator_category = random_access_iterator_tag;

        // Type of elements the iterator points to
        using value_type = T;

        // Type for difference between iterators
        using difference_type = ptrdiff_t;

        // Pointer type to the element
        using pointer = T *;
        // Reference type to the element
        using reference = T &;

        // Constructor to initialize the iterator with a pointer to an element
        iterator(pointer ptr) : ptr_(ptr) {
        }

        // Dereference operator to access the element pointed to by the iterator
        reference operator*() const{
            return *ptr_;
        }

        // Arrow operator to access the element's members
        pointer operator->() const{
            return ptr_;
        }

        // Prefix increment operator to move the iterator to the next element
        iterator &operator++(){
            ++ptr_;
            return *this;
        }

        // Postfix increment operator to move the iterator to the next element and return the previous
        // position
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }

        // Equality operator to compare if two iterators are equal (point to the same element)
        bool operator==(const iterator &other) const{
            return ptr_ == other.ptr_;
        }

        // Inequality operator to compare if two iterators are not equal (point to different elements)
        bool operator!=(const iterator &other) const{
            return ptr_ != other.ptr_;
        }

      private:
        pointer ptr_; // Pointer to the element the iterator currently points to
    };

    // Default constructor to create an empty container
    MyContainer() : data_(nullptr), size_(0), capacity_(0){
    }

    // Copy constructor to create a container as a copy of another container
    MyContainer(const MyContainer &other) : size_(other.size_), capacity_(other.capacity_){

        // Allocate memory for the elements
        data_ = allocator_type().allocate(capacity_);
        // Copy elements from the other container
        copy(other.data_, other.data_ + size_, data_);
    }

    // Destructor to clean up the allocated memory when the container is destroyed
    ~MyContainer(){
        // Deallocate the allocated memory
        allocator_type().deallocate(data_, capacity_);
    }

    // Member function to add a new element at the end of the container
    void push_back(const T &value){
        if (size_ == capacity_){

            // If the container is full, allocate more memory
            size_type new_capacity = capacity_ ? 2 * capacity_ : 1;
            T *new_data = allocator_type().allocate(new_capacity);
            copy(data_, data_ + size_, new_data);
            allocator_type().deallocate(data_, capacity_);
            data_ = new_data;
            capacity_ = new_capacity;
        }
        data_[size_++] = value;
    }

    // Member function to remove the last element from the container
    void pop_back(){
        // Only remove if the container is not empty
        if (size_ > 0){
            --size_;
        }
    }

    // Member function to access an element at a given index with bounds checking
    reference at(size_type index){
        if (index >= size_){

            // Throw an exception if the index is invalid
            throw out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Const version of the 'at' function to access elements in a read-only context
    const_reference at(size_type index) const{
        if (index >= size_){

            // Throw an exception if the index is invalid
            throw out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Member function to get the number of elements currently in the container
    size_type size() const{
        return size_;
    }

    // Member function to check if the container is empty
    bool empty() const{
        return size_ == 0;
    }

    // Member function to get an iterator pointing to the first element of the container
    iterator begin(){
        return iterator(data_);
    }

    // Member function to get an iterator pointing to the end (one past the last element) of the container
    iterator end(){
        return iterator(data_ + size_);
    }

  private:
    // Pointer to the container's elements
    T *data_;

    // Number of elements in the container
    size_type size_;

    // Allocated capacity of the container
    size_type capacity_;
};

#endif // MYCONTAINER_H_INCLUDED
