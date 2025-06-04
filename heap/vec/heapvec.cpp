namespace lasd {

/* ************************************************************************** */

template <typename Data>
void HeapVec<Data>::BuildHeap() {
  for (long index = (this->size / 2) - 1; index >= 0; --index) {
    HeapifyDown(index);
  }
}

template <typename Data>
void HeapVec<Data>::HeapifyUp(ulong index) {
  while (HasParent(index) && this->elements[index] > this->elements[Parent(index)]) {
    Swap(index, Parent(index));
    index = Parent(index);
  }
}

template <typename Data>
void HeapVec<Data>::HeapifyDown(ulong index) {
  ulong largest = index;

  if (HasLeftChild(index) && this->elements[LeftChild(index)] > this->elements[largest]) {
    largest = LeftChild(index);
  }
  if (HasRightChild(index) && this->elements[RightChild(index)] > this->elements[largest]) {
    largest = RightChild(index);
  }
  if (largest != index) {
    Swap(index, largest);
    HeapifyDown(largest);
  }
}

template <typename Data>
ulong HeapVec<Data>::Parent(ulong index) const {
  if (index == 0) {
    throw std::out_of_range("No parent for root element");
  }
  return (index - 1) / 2;
}

template <typename Data>
ulong HeapVec<Data>::LeftChild(ulong index) const {
  return 2 * index + 1;
}

template <typename Data>
ulong HeapVec<Data>::RightChild(ulong index) const {
  return 2 * index + 2;
}

template <typename Data>
bool HeapVec<Data>::HasParent(ulong index) const noexcept {
  return index > 0;
}

template <typename Data>
bool HeapVec<Data>::HasLeftChild(ulong index) const noexcept {
  return LeftChild(index) < this->size;
}

template <typename Data>
bool HeapVec<Data>::HasRightChild(ulong index) const noexcept {
  return RightChild(index) < this->size;
}

template <typename Data>
void HeapVec<Data>::Swap(ulong index1, ulong index2) {
  std::swap(this->elements[index1], this->elements[index2]);
}

template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& con) : Heap<Data>(), SortableVector<Data>(con) {
  BuildHeap();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& con) : Heap<Data>(), SortableVector<Data>(std::move(con)) {
  BuildHeap();
}

template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec& other) : Heap<Data>(), SortableVector<Data>(other) {
  BuildHeap();
}

template <typename Data>
HeapVec<Data>::HeapVec(HeapVec&& other) noexcept : Heap<Data>(), SortableVector<Data>(std::move(other)) {
  BuildHeap();
}

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec& other) {
  SortableVector<Data>::operator=(other);
  return *this;
}

template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec&& other) noexcept {
  SortableVector<Data>::operator=(std::move(other));
  return *this;
}

template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec& other) const noexcept {
  if (this->size != other.size) {
    return false;
  }
  for (ulong index = 0; index < this->size; ++index) {
    if (this->elements[index] != other.elements[index]) {
      return false;
    }
  }
  return true;
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec& other) const noexcept {
  return !(*this == other);
}

template <typename Data>
bool HeapVec<Data>::IsHeap() const noexcept {
  for (ulong index = 0; index < this->size / 2; ++index) {
    if (HasLeftChild(index) && this->elements[index] < this->elements[LeftChild(index)]) {
      return false;
    }
    if (HasRightChild(index) && this->elements[index] < this->elements[RightChild(index)]) {
      return false;
    }
  }
  return true;
}

template <typename Data>
void HeapVec<Data>::Heapify() {
  if (this->size == 0) {
    throw std::length_error("Heap is empty");
  }
  BuildHeap();
}

template <typename Data>
void HeapVec<Data>::Sort() noexcept {
  if (this->size == 0) {
    return; // Change from throw to early return for noexcept compatibility
  }

  ulong originalSize = this->size;
  BuildHeap();

  for (long index = this->size - 1; index > 0; --index) {
    Swap(0, index);
    this->size--;
    HeapifyDown(0);
  }
  this->size = originalSize;
}

template <typename Data>
void HeapVec<Data>::Clear() {
  SortableVector<Data>::Clear();
}

template <typename Data>
const Data& HeapVec<Data>::Top() const {
  if (this->size == 0) {
    throw std::length_error("Heap is empty");
  }
  return this->elements[0]; // Root element is always at index 0
}

template <typename Data>
Data HeapVec<Data>::TopNRemove() {
  if (this->size == 0) {
    throw std::length_error("Heap is empty");
  }
  
  Data top = this->elements[0];
  this->elements[0] = this->elements[this->size - 1];
  this->size--;
  
  if (this->size > 0) {
    HeapifyDown(0);
  }
  
  return top;
}

template <typename Data>
void HeapVec<Data>::Insert(const Data& value) {
  SortableVector<Data>::Resize(this->size + 1);
  this->elements[this->size - 1] = value;
  HeapifyUp(this->size - 1);
}

template <typename Data>
void HeapVec<Data>::Insert(Data&& value) {
  SortableVector<Data>::Resize(this->size + 1);
  this->elements[this->size - 1] = std::move(value);
  HeapifyUp(this->size - 1);
}

/* ************************************************************************** */

}