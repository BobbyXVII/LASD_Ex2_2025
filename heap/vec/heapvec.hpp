
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>,
                /* virtual */ public Vector<Data> {

private:

  // ...

protected:

  // using Container::???;
  using Container::Size;

  // ...

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  
  // A heap obtained from a TraversableContainer
  HeapVec(const TraversableContainer<Data>&);
  
  // A heap obtained from a MappableContainer
  HeapVec(const MappableContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec<Data>&);

  // Move constructor
  HeapVec(HeapVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline HeapVec<Data>& operator=(const HeapVec<Data>&) = default;

  // Move assignment
  inline HeapVec<Data>& operator=(HeapVec<Data>&&) noexcept = default;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const HeapVec<Data>&) const noexcept; // Comparison of abstract types is not possible.
  inline bool operator!=(const HeapVec<Data>&) const noexcept; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  // Override Heap member
  IsHeap() override noexcept; // (must throw std::length_error when empty)

  // Override Heap member
  Heapify() override noexcept; // (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)
  inline void Sort() noexcept override; // Override SortableLinearContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
