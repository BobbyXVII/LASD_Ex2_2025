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
                public SortableVector<Data> {

private:

  // ...

protected:

  using Container::size;
  using SortableVector<Data>::elements;

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  
  // A heap obtained from a TraversableContainer
  HeapVec(const TraversableContainer<Data>&);
  
  // A heap obtained from a MappableContainer
  HeapVec(MappableContainer<Data>&&) noexcept;

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
  HeapVec<Data>& operator=(const HeapVec<Data>&);

  // Move assignment
  HeapVec<Data>& operator=(HeapVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec<Data>&) const noexcept;
  bool operator!=(const HeapVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  // Override Heap member
  bool IsHeap() const noexcept override; // (must throw std::length_error when empty)

  // Override Heap member
  void Heapify() noexcept override; // (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)
  void Sort() noexcept override; // Override SortableLinearContainer member

  /* ************************************************************************ */

  // Specific member functions for Heap operations

  const Data& Top() const; // (must throw std::length_error when empty)
  Data TopNRemove(); // (must throw std::length_error when empty)
  void Insert(const Data&);
  void Insert(Data&&);

protected:

  // Auxiliary functions, if necessary!
  void HeapifyUp(ulong);
  void HeapifyDown(ulong);
  ulong Parent(ulong) const noexcept;
  ulong LeftChild(ulong) const noexcept;
  ulong RightChild(ulong) const noexcept;

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
