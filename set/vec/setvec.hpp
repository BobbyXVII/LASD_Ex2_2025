#ifndef SETVEC_HPP
#define SETVEC_HPP

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

    template<typename Data>
    class SetVec : virtual public Set<Data>,
                   virtual public Vector<Data>,
                   virtual public ResizableContainer {
    protected:
        using Container::size;

        unsigned long capacity = 0;
        unsigned long head = 0;
        unsigned long tail = 0;

        // Utility function for conversion
        inline ulong physicalIndex(ulong logicalIndex) const {
            return (head + logicalIndex) % capacity;
        }

        // Utility function to maintain sorted order
        ulong BinarySearch(const Data &) const;     // Finds a value in the array using binary search

    public:
        SetVec() = default;

        /* ************************************************************************ */

        // Specific constructors
        SetVec(const TraversableContainer<Data> &); // A set obtained from a TraversableContainer
        SetVec(MappableContainer<Data> &&); // A set obtained from a MappableContainer

        /* ************************************************************************ */

        // Copy constructor
        SetVec(const SetVec &);

        // Move constructor
        SetVec(SetVec &&) noexcept;

        /* ************************************************************************ */

        // Destructor
        virtual ~SetVec() = default;

        /* ************************************************************************ */

        // Copy assignment
        SetVec &operator=(const SetVec &);

        // Move assignment
        SetVec &operator=(SetVec &&) noexcept;

        /* ************************************************************************ */

        using LinearContainer<Data>::operator==;
        using LinearContainer<Data>::operator!=;

        // Comparison operators
        bool operator==(const SetVec &) const noexcept;

        inline bool operator!=(const SetVec &) const noexcept;

        /* ************************************************************************ */

        // Specific member functions (inherited from OrderedDictionaryContainer)

        const Data &Min() const override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
        Data MinNRemove() override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
        void RemoveMin() override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

        const Data &Max() const override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
        Data MaxNRemove() override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
        void RemoveMax() override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

        const Data &Predecessor(const Data &) const override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
        Data PredecessorNRemove(const Data &) override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
        void RemovePredecessor(const Data &) override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

        const Data &Successor(const Data &) const override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
        Data SuccessorNRemove(const Data &) override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
        void RemoveSuccessor(const Data &) override;

        // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

        /* ************************************************************************ */

        // Specific member functions (inherited from DictionaryContainer)

        bool Insert(const Data &) override; // Override DictionaryContainer member (copy of the value)
        bool Insert(Data &&) override; // Override DictionaryContainer member (move of the value)
        bool Remove(const Data &) override; // Override DictionaryContainer member

    protected:

        // Auxiliary functions for InsertOrder
        ulong BinarySearchInsertion(const Data &) const; // Finds a position where a value should be inserted in the array

        void ShiftRight(ulong);

        void ShiftLeft(ulong);
    };

    /* ************************************************************************** */
}

#include "setvec.cpp"

#endif