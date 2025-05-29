#ifndef SETLST_HPP
#define SETLST_HPP

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {


    template<typename Data>
    class SetLst : virtual public Set<Data>,
                   virtual public List<Data> {
    protected:
        using Container::size;
        using List<Data>::head;
        using List<Data>::tail;

        // Funzione ausiliaria per mantenere elementi ordinati
        void InsertInOrder(const Data &);
        void InsertInOrder(Data &&);

        Data BackNRemove();
        void RemoveFromBack();

    public:
        // Default constructor
        SetLst() = default;

        /* ************************************************************************ */

        // Specific constructors
        SetLst(const TraversableContainer<Data> &); // A set obtained from a TraversableContainer
        SetLst(MappableContainer<Data> &&); // A set obtained from a MappableContainer

        /* ************************************************************************ */

        // Copy constructor
        SetLst(const SetLst &);

        // Move constructor
        SetLst(SetLst &&) noexcept;

        /* ************************************************************************ */

        // Destructor
        virtual ~SetLst() = default;

        /* ************************************************************************ */

        // Copy assignment
        SetLst &operator=(const SetLst &);

        // Move assignment
        SetLst &operator=(SetLst &&) noexcept;

        /* ************************************************************************ */

        using LinearContainer<Data>::operator==;
        using LinearContainer<Data>::operator!=;

        // Comparison operators
        bool operator==(const SetLst &) const noexcept;

        bool operator!=(const SetLst &) const noexcept;

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
        // Auxiliary functions, if necessary!
        typename List<Data>::Node *FindPointerToMin() const;

        typename List<Data>::Node *FindPointerToMax() const;

        typename List<Data>::Node *FindPointerToPredecessor(const Data &) const;

        typename List<Data>::Node *FindPointerToSuccessor(const Data &) const;

        typename List<Data>::Node *FindPointerTo(const Data &) const;
        
        typename List<Data>::Node *Reach(typename List<Data>::Node* startNode, unsigned int steps) const;
        
        typename List<Data>::Node *BinarySearch(const Data& data) const;
    };

    /* ************************************************************************** */
}

#include "setlst.cpp"

#endif