
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>,
                virtual public HeapVec<Data> {


private:

  // ...

protected:

  using Container::Size;

  // ...

public:

  // Default constructor
  PQHeap() = default; // Default constructor, no specifiers needed

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data>&); // A priority queue obtained from a TraversableContainer
  PQHeap(const MappableContainer<Data>&); // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap<Data>&);

  // Move constructor
  PQHeap(PQHeap<Data>&&) noexcept;


  /* ************************************************************************ */

  // Destructor
  virtual ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline PQHeap<Data>& operator=(const PQHeap<Data>&) = default;

  // Move assignment
  inline PQHeap<Data>& operator=(PQHeap<Data>&&) noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  Tip() const noexcept; // Override PQ member (must throw std::length_error when empty)
  RemoveTip() noexcept; // Override PQ member (must throw std::length_error when empty)
  TipNRemove() noexcept; // Override PQ member (must throw std::length_error when empty)


  Insert(const Data&); // Override PQ member (Copy of the value)
  Insert(Data&&); // Override PQ member (Move of the value)

  Change(const Data&); // Override PQ member (Copy of the value)
  Change(Data&&); // Override PQ member (Move of the value)

protected:

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
