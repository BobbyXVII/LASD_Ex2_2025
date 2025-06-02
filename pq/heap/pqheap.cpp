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
  return HeapVec<Data>::Top(); // Delega al metodo Top() di HeapVec
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
  if (this->Empty()) {
    throw std::length_error("RemoveTip: Priority queue is empty");
  }
  
  // Sposta l'ultimo elemento alla radice e rimuovi l'ultimo
  this->elements[0] = std::move(this->elements[this->size - 1]);
  this->Resize(this->size - 1);
  
  // Ripristina la proprietà dell'heap se non è vuoto
  if (!this->Empty()) {
    this->HeapifyDown(0);
  }
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
  return HeapVec<Data>::TopNRemove(); // Delega al metodo TopNRemove() di HeapVec
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
  HeapVec<Data>::Insert(value); // Delega al metodo Insert() di HeapVec
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) {
  HeapVec<Data>::Insert(std::move(value)); // Delega al metodo Insert() di HeapVec
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, const Data& value) {
  if (index >= this->size) {
    throw std::out_of_range("Change: Index out of range");
  }
  
  this->elements[index] = value;
  
  // Ripristina la proprietà dell'heap
  this->Heapify();
}

template <typename Data>
void PQHeap<Data>::Change(ulong index, Data&& value) {
  if (index >= this->size) {
    throw std::out_of_range("Change: Index out of range");
  }
  
  this->elements[index] = std::move(value);
  
  // Ripristina la proprietà dell'heap
  this->Heapify();
}

/* ************************************************************************** */

}
