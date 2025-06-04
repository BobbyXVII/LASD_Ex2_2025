#include "pqheap.hpp"
#include <stdexcept>
#include <utility>
namespace lasd {

/* ************************************************************************** */

// Constructors

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& container)
  : HeapVec<Data>(container) {
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& container)
  : HeapVec<Data>(std::move(container)) {
}

// Copy constructor
template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other)
  : HeapVec<Data>(other) {
}

// Move constructor
template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept
  : HeapVec<Data>(std::move(other)) {
}

/* ************************************************************************** */

// Assignment operators

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
  HeapVec<Data>::operator=(other);
  return *this;
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
  HeapVec<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Specific member functions (inherited from PQ)

template <typename Data>
const Data& PQHeap<Data>::Tip() const {
  return HeapVec<Data>::Top();
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
  HeapVec<Data>::TopNRemove();
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
  return HeapVec<Data>::TopNRemove();
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
  HeapVec<Data>::Insert(value);
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) {
  HeapVec<Data>::Insert(std::move(value));
}

template <typename Data>
void PQHeap<Data>::Clear() {
  HeapVec<Data>::Clear();
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& value) {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  
  Data oldValue = this->elements[index];
  this->elements[index] = value;
  
  // Se il nuovo valore è maggiore del precedente, heapify up
  if (value > oldValue) {
    this->HeapifyUp(index);
  }
  // Se il nuovo valore è minore del precedente, heapify down
  else if (value < oldValue) {
    this->HeapifyDown(index);
  }
  // Se sono uguali, non serve fare nulla
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data&& value) {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  
  Data oldValue = this->elements[index];
  this->elements[index] = std::move(value);
  
  // Se il nuovo valore è maggiore del precedente, heapify up
  if (this->elements[index] > oldValue) {
    this->HeapifyUp(index);
  }
  // Se il nuovo valore è minore del precedente, heapify down
  else if (this->elements[index] < oldValue) {
    this->HeapifyDown(index);
  }
  // Se sono uguali, non serve fare nulla
}

/* ************************************************************************** */

}
