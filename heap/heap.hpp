#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>,
             virtual public ClearableContainer {

private:

protected:

public:

  // Destructor
  virtual ~Heap() = default;

  /* ************************************************************************ */

  // Copy assignment
  Heap & operator=(const Heap &) = delete; // Copy assignment of abstract types is not possible.   

  // Move assignment
  Heap & operator=(Heap &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  // type IsHeap(argument) specifiers;
  virtual bool IsHeap() const = 0; // (must throw std::length_error when empty)

  // type Heapify(argument) specifiers;
  virtual void Heapify() = 0; // (must throw std::length_error when empty)

};

/* ************************************************************************** */

}

#endif
