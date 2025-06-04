
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"
#include <stdexcept>

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
  PQ & operator=(const PQ & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PQ & operator=(PQ && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions


  virtual const Data& Tip() const = 0;
  virtual void RemoveTip() = 0;
  virtual Data TipNRemove() = 0;

  virtual void Insert(const Data & value) = 0; // Copy of the value
  virtual void Insert(Data && value) = 0; // Move of the value

  virtual void Change(ulong index, const Data & value) = 0; // Copy of the value
  virtual void Change(ulong index, Data && value) = 0; // Move of the value

};

/* ************************************************************************** */

}

#endif
