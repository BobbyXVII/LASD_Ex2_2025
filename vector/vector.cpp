namespace lasd {

/* ************************************************************************** */
/* VECTOR - SPECIFIC CONSTRUCTORS                                              */
/* ************************************************************************** */

template<typename Data>
Vector<Data>::Vector(const unsigned long newsize) {
    size = newsize;
    if (size > 0) {
        elements = new Data[size]{};
    } else {
        elements = nullptr;
    }
}

template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& container)
  : Vector(container.Size()) {
    try {
        unsigned long index = 0;
        container.Traverse(
            [this, &index](const Data& dat) {
                elements[index++] = dat;
            }
        );
    } catch (...) {
        delete[] elements;
        elements = nullptr;
        size = 0;
        throw;
    }
}

template<typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& container)
  : Vector(container.Size()) {
    try {
        unsigned long index = 0;
        container.Map(
            [this, &index](Data& dat) {
                elements[index++] = std::move(dat);
            }
        );
    } catch (...) {
        delete[] elements;
        elements = nullptr;
        size = 0;
        throw;
    }
}

/* ************************************************************************** */
/* VECTOR - COPY AND MOVE CONSTRUCTORS                                         */
/* ************************************************************************** */

// Copy constructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& vector)
  : Vector(vector.size) {
    try {
        std::uninitialized_copy(vector.elements, vector.elements + size, elements);
    } catch (...) {
        delete[] elements;
        elements = nullptr;
        size = 0;
        throw;
    }
}

// Move constructor
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vector) noexcept {
    std::swap(size, vector.size);
    std::swap(elements, vector.elements);
}

/* ************************************************************************** */
/* VECTOR - DESTRUCTOR                                                         */
/* ************************************************************************** */

template<typename Data>
Vector<Data>::~Vector() {
    delete[] elements;
}

/* ************************************************************************** */
/* VECTOR - ASSIGNMENT OPERATORS                                               */
/* ************************************************************************** */

// Copy assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vector) {
    if (this != &vector) {  // Aggiungi controllo auto-assegnamento
        Vector<Data> temp{vector};
        std::swap(*this, temp);
    }
    return *this;
}

// Move assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vector) noexcept {
    std::swap(size, vector.size);
    std::swap(elements, vector.elements);
    return *this;
}

/* ************************************************************************** */
/* VECTOR - COMPARISON OPERATORS                                               */
/* ************************************************************************** */

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
/* VECTOR - MUTABLE LINEAR CONTAINER FUNCTIONS                                 */
/* ************************************************************************** */

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
/* VECTOR - LINEAR CONTAINER FUNCTIONS                                         */
/* ************************************************************************** */

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
/* VECTOR - RESIZABLE CONTAINER FUNCTIONS                                      */
/* ************************************************************************** */

template<typename Data>
void Vector<Data>::Resize(unsigned long newSize) {
    if (newSize != size) {
        if (newSize == 0) {
            Clear();
            return;
        }
        
        Data* newElements = new Data[newSize]{};
        unsigned long minSize = (newSize < size) ? newSize : size;
        
        try {
            for (unsigned long i = 0; i < minSize; ++i) {
                newElements[i] = std::move_if_noexcept(elements[i]);
            }
        } catch (...) {
            delete[] newElements;
            throw;
        }
        
        delete[] elements;
        elements = newElements;
        size = newSize;
    }
}

/* ************************************************************************** */
/* VECTOR - CLEARABLE CONTAINER FUNCTIONS                                      */
/* ************************************************************************** */

template<typename Data>
void Vector<Data>::Clear() {
    delete[] elements;
    elements = nullptr;
    size = 0;
}

/* ************************************************************************** */
/* SORTABLE VECTOR - ASSIGNMENT OPERATORS                                      */
/* ************************************************************************** */

// SortableVector copy assignment
template<typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& vec) {
    Vector<Data>::operator=(vec);
    return *this;
}

// SortableVector move assignment
template<typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vec) noexcept {
    Vector<Data>::operator=(std::move(vec));
    return *this;
}

}