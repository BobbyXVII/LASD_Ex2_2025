
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQ : virtual public LinearContainer<Data>,
             virtual public ClearableContainer {

private:

protected:

public:

  // Destructor
  virtual ~PQ() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline PQ & operator=(const PQ &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  inline PQ & operator=(PQ &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions


  Tip() const noexcept; // (concrete function must throw std::length_error when empty)
  RemoveTip() noexcept; // (concrete function must throw std::length_error when empty)
  TipNRemove() noexcept; // (concrete function must throw std::length_error when empty)


  Insert(const Data &); // Copy of the value
  Insert(Data &&); // Move of the value

  Change(const Data &); // Copy of the value
  Change(Data &&); // Move of the value

};

/* ************************************************************************** */

}

#endif
