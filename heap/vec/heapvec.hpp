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
                public Vector<Data> {

private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::elements;

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  
  // A heap obtained from a TraversableContainer
  HeapVec(const TraversableContainer<Data>& con);
  
  // A heap obtained from a MappableContainer
  HeapVec(MappableContainer<Data>&& con);

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec& other);

  // Move constructor
  HeapVec(HeapVec&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec& operator=(const HeapVec& other);

  // Move assignment
  HeapVec& operator=(HeapVec&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HeapVec& other) const noexcept;
  bool operator!=(const HeapVec& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  // Override Heap member
  bool IsHeap() const noexcept override; // (must throw std::length_error when empty)

  // Override Heap member
  void Heapify() override;

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)
  void Sort() noexcept override;

  /* ************************************************************************ */

  void Clear() override; // Override ClearableContainer member
  
  // Heap-specific operations
  const Data& Top() const; // Get the top element (max element)
  Data TopNRemove(); // Remove and return the top element
  void Insert(const Data& value); // Insert an element
  void Insert(Data&& value); // Insert an element (move version)

protected:
  void Swap(ulong, ulong); // Swap elements at two indices
  // Auxiliary functions, if necessary!
  void HeapifyUp(ulong);
  void HeapifyDown(ulong);
  void BuildHeap();

  ulong Parent(ulong) const;
  ulong LeftChild(ulong) const;
  ulong RightChild(ulong) const;

  bool HasParent(ulong) const noexcept;
  bool HasLeftChild(ulong) const noexcept;
  bool HasRightChild(ulong) const noexcept;

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
