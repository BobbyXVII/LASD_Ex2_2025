
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>
            , virtual public ClearableContainer {


private:

protected:

public:

  // Destructor
  virtual ~Heap() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline Heap & operator=(const Heap &) = delete; // Copy assignment of abstract types is not possible.   

  // Move assignment
  inline Heap & operator=(Heap &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  // type IsHeap(argument) specifiers;
  IsHeap() const noexcept; // (must throw std::length_error when empty)

  // type Heapify(argument) specifiers;
  Heapify() noexcept; // (must throw std::length_error when empty)

};

/* ************************************************************************** */

}

#endif
