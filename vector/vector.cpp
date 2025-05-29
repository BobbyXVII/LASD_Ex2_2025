namespace lasd {

/* ******************************* Costruttore con dimensione iniziale ******************************* */

// Costruttore con dimensione iniziale
template<typename Data>
Vector<Data>::Vector(const unsigned long newsize) {
    size = newsize;
    elements = new Data[size]{};
}

/* ******************************* Costruttore da TraversableContainer ******************************* */
template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& container)
  : Vector(container.Size()) {
    unsigned long index = 0;
    container.Traverse(
        [this, &index](const Data& dat) {
            elements[index++] = dat;
        }
    );
}

/* ******************************* Mappable ******************************* */
template<typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& container)
  : Vector(container.Size()) {
    unsigned long index = 0;
    container.Map(
        [this, &index](Data& dat) {
            elements[index++] = std::move(dat);
        }
    );
}


/* ******************************* Copy constructor ******************************* */
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& vector)
  : Vector(vector.size) {
    std::uninitialized_copy(vector.elements, vector.elements + size, elements);
}


/* ******************************* Move constructor ******************************* */
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vector) noexcept {
    std::swap(size, vector.size);
    std::swap(elements, vector.elements);
}

/* ************************************************************************** */


/* ******************************* Destructor ******************************* */
template<typename Data>
Vector<Data>::~Vector() {
    delete[] elements;
}

/* ************************************************************************** */


/* ******************************* Copy assignment ******************************* */
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vector) {
    Vector<Data> temp{vector};
    std::swap(*this, temp);
    return *this;
}


/* ******************************* Move assignment ******************************* */
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vector) noexcept {
    std::swap(size, vector.size);
    std::swap(elements, vector.elements);
    return *this;
}

/* ************************************************************************** */


/* ******************************* Comparison operators ******************************* */

template<typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vector) const noexcept {
    if (size != vector.size) return false;
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] != vector.elements[i]) return false;
    }
    return true;
}

template<typename Data>
bool Vector<Data>::operator!=(const Vector<Data>& vector) const noexcept {
    return !(*this == vector);
}

/* ************************************************************************** */


/* ******************************* Mutable ******************************* */

template<typename Data>
Data& Vector<Data>::operator[](const unsigned long index) {
    return const_cast<Data&>(static_cast<const Vector<Data>*>(this)->operator[](index));
}

template<typename Data>
Data& Vector<Data>::Front() {
    return const_cast<Data&>(static_cast<const Vector<Data>*>(this)->Front());
}

template<typename Data>
Data& Vector<Data>::Back() {
    return const_cast<Data&>(static_cast<const Vector<Data>*>(this)->Back());
}

/* ************************************************************************** */


/* ******************************* Immutable ******************************* */

template<typename Data>
const Data& Vector<Data>::operator[](const unsigned long index) const {
    if (index < size) {
        return elements[index];
    } else {
        throw std::out_of_range("Access at index " + std::to_string(index) + "; vector size " + std::to_string(size) + ".");
    }
}

template<typename Data>
const Data& Vector<Data>::Front() const {
    if (size > 0) {
        return elements[0];
    } else {
        throw std::length_error("Access to an empty vector.");
    }
}

template<typename Data>
const Data& Vector<Data>::Back() const {
    if (size > 0) {
        return elements[size - 1];
    } else {
        throw std::length_error("Access to an empty vector.");
    }
}

/* ************************************************************************** */


/* ******************************* Resize ******************************* */
template<typename Data>
void Vector<Data>::Resize(unsigned long newSize) {
    if (newSize != size) {
        Data* newElements = new Data[newSize]{};
        unsigned long minSize = (newSize < size) ? newSize : size;
        for (unsigned long i = 0; i < minSize; ++i) {
            newElements[i] = std::move(elements[i]);
        }
        delete[] elements;
        elements = newElements;
        size = newSize;
    }
}


/* ******************************* Clear ******************************* */
template<typename Data>
void Vector<Data>::Clear() {
    delete[] elements;
    elements = nullptr;
    size = 0;
}

/* ************************************************************************** */


/* ******************************* SortableVector copy assignment ******************************* */
template<typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& vec) {
    Vector<Data>::operator=(vec);
    return *this;
}


/* ******************************* SortableVector move assignment ******************************* */
template<typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vec) noexcept {
    Vector<Data>::operator=(std::move(vec));
    return *this;
}

}