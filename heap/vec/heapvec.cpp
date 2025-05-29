namespace lasd {

/* ************************************************************************** */

// Constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container)
  : Vector<Data>(container) {
  Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& container) noexcept
  : Vector<Data>(std::move(container)) {
  Heapify();
}

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& other)
  : Vector<Data>(other) { }

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& other) noexcept
  : Vector<Data>(std::move(other)) { }

/* ************************************************************************** */

// Assignment operators

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& other) {
  Vector<Data>::operator=(other);
  return *this;
}

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& other) noexcept {
  Vector<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
const Data& HeapVec<Data>::Top() const {
  if (Empty()) {
    throw std::length_error("Top: Empty heap");
  }
  return elements[0];
}

template <typename Data>
Data HeapVec<Data>::TopNRemove() {
  if (Empty()) {
    throw std::length_error("TopNRemove: Empty heap");
  }

  Data top = std::move(elements[0]);
  elements[0] = std::move(elements[size - 1]);
  Resize(size - 1);

  if (!Empty()) {
    HeapifyDown(0);
  }

  return top;
}

template <typename Data>
void HeapVec<Data>::Insert(const Data& value) {
  Resize(size + 1);
  elements[size - 1] = value;
  HeapifyUp(size - 1);
}

template <typename Data>
void HeapVec<Data>::Insert(Data&& value) {
  Resize(size + 1);
  elements[size - 1] = std::move(value);
  HeapifyUp(size - 1);
}

/* ************************************************************************** */

// Auxiliary functions

template <typename Data>
void HeapVec<Data>::Heapify() {
  if (size <= 1) return;
  
  // Start from the last parent node and heapify down
  for (long i = (size / 2) - 1; i >= 0; --i) {
    HeapifyDown(i);
  }
}

template <typename Data>
void HeapVec<Data>::HeapifyUp(ulong index) {
  while (index > 0) {
    ulong parent = (index - 1) / 2;
    if (elements[index] > elements[parent]) {
      std::swap(elements[index], elements[parent]);
      index = parent;
    } else {
      break;
    }
  }
}

template <typename Data>
void HeapVec<Data>::HeapifyDown(ulong index) {
  while (true) {
    ulong largest = index;
    ulong left = 2 * index + 1;
    ulong right = 2 * index + 2;

    // Find the largest among parent, left child, and right child
    if (left < size && elements[left] > elements[largest]) {
      largest = left;
    }
    if (right < size && elements[right] > elements[largest]) {
      largest = right;
    }

    // If the largest is not the parent, swap and continue
    if (largest != index) {
      std::swap(elements[index], elements[largest]);
      index = largest;
    } else {
      break;
    }
  }
}

/* ************************************************************************** */

}
