namespace lasd {

/* ************************************************************************** */

// Constructors

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container)
  : SortableVector<Data>(container) {
  Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& container) noexcept
  : SortableVector<Data>(std::move(container)) {
  Heapify();
}

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& other)
  : SortableVector<Data>(other) { }

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& other) noexcept
  : SortableVector<Data>(std::move(other)) { }

/* ************************************************************************** */

// Assignment operators

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& other) {
  SortableVector<Data>::operator=(other);
  return *this;
}

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& other) noexcept {
  SortableVector<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& other) const noexcept {
  return SortableVector<Data>::operator==(other);
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (inherited from Heap)


// IsHeap checks if the current vector satisfies the heap property.
template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
  if (this->Empty()) {
    return true;
  }
  
  for (ulong i = 0; i < size / 2; ++i) {
    ulong left = LeftChild(i);
    ulong right = RightChild(i);
    
    if (left < size && elements[i] < elements[left]) {
      return false;
    }
    if (right < size && elements[i] < elements[right]) {
      return false;
    }
  }
  return true;
}

// Heapify builds a max heap from the current vector.

template <typename Data>
void HeapVec<Data>::Heapify() noexcept {
  if (size <= 1) return;
  
  // Start from the last parent node and heapify down
  for (long i = (size / 2) - 1; i >= 0; --i) {
    HeapifyDown(i);
  }
}

/* ************************************************************************** */

// Specific member function (inherited from SortableLinearContainer)

template <typename Data>
void HeapVec<Data>::Sort() noexcept {
  // HeapSort algorithm
  ulong originalSize = size;
  
  // Build max heap
  Heapify();
  
  // Extract elements one by one
  for (ulong i = size - 1; i > 0; --i) {
    std::swap(elements[0], elements[i]);
    size--; // Temporarily reduce size
    HeapifyDown(0);
  }
  
  size = originalSize; // Restore original size
}

/* ************************************************************************** */

// Specific member functions for Heap operations

template <typename Data>
const Data& HeapVec<Data>::Top() const {
  if (this->Empty()) {
    throw std::length_error("Top: Empty heap");
  }
  return elements[0];
}

template <typename Data>
Data HeapVec<Data>::TopNRemove() {
  if (this->Empty()) {
    throw std::length_error("TopNRemove: Empty heap");
  }

  Data top = std::move(elements[0]);
  elements[0] = std::move(elements[size - 1]);
  Resize(size - 1);

  if (!this->Empty()) {
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

// HeapifyUp restores the heap property by moving the element at index up the tree.
template <typename Data>
void HeapVec<Data>::HeapifyUp(ulong index) {
  while (index > 0) {
    ulong parent = Parent(index);
    if (elements[index] > elements[parent]) {
      std::swap(elements[index], elements[parent]);
      index = parent;
    } else {
      break;
    }
  }
}

// HeapifyDown restores the heap property by moving the element at index down the tree.
template <typename Data>
void HeapVec<Data>::HeapifyDown(ulong index) {
  while (true) {
    ulong largest = index;
    ulong left = LeftChild(index);
    ulong right = RightChild(index);

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

template <typename Data>
ulong HeapVec<Data>::Parent(ulong index) const noexcept {
  return (index - 1) / 2;
}

template <typename Data>
ulong HeapVec<Data>::LeftChild(ulong index) const noexcept {
  return 2 * index + 1;
}

template <typename Data>
ulong HeapVec<Data>::RightChild(ulong index) const noexcept {
  return 2 * index + 2;
}

/* ************************************************************************** */

}
