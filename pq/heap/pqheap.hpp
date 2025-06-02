
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>, public HeapVec<Data> {


private:

  // ...

protected:

  using HeapVec<Data>::size;
  using HeapVec<Data>::elements;

  // ...

public:

  // Default constructor
  PQHeap() = default; // Default constructor, no specifiers needed

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data>& con); // A priority queue obtained from a TraversableContainer
  PQHeap(MappableContainer<Data>&& con); // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap& other);

  // Move constructor
  PQHeap(PQHeap&& other) noexcept;


  /* ************************************************************************ */

  // Destructor
  virtual ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  PQHeap& operator=(const PQHeap& other);

  // Move assignment
  PQHeap& operator=(PQHeap&& other) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  const Data& Tip() const override;
  void RemoveTip() override;
  Data TipNRemove() override;


  void Insert(const Data& value) override; //(Copy of the value)
  void Insert(Data&& value) override; // (Move of the value)

  void Change(ulong index, const Data& value) override; //(Copy of the value)
  void Change(ulong index, Data&& value) override; //(Move of the value)

  void Clear() override;

  void HeapifyUp(ulong index);



protected:

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
