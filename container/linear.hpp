#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"
#include <algorithm>
#include <climits>
#include <random>
#include <utility>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer 
: virtual public PreOrderTraversableContainer<Data>, 
  virtual public PostOrderTraversableContainer<Data> {

private:

protected:
  using Container::size;

public:
  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************** */

  // Copy assignment
  LinearContainer & operator=(const LinearContainer &) = delete;

  // Move assignment
  LinearContainer & operator=(LinearContainer &&) noexcept = delete;

  /* ************************************************************************** */

  // Comparison operators
  bool operator==(const LinearContainer &) const noexcept;
  bool operator!=(const LinearContainer &) const noexcept;

  /* ************************************************************************** */

  // Specific member functions
  virtual const Data & operator[](unsigned long) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  virtual const Data & Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  virtual const Data & Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************** */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override;

  /* ************************************************************************** */

  // Specific member function (inherited from PreOrderTraversableContainer)
  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************** */

  // Specific member function (inherited from PostOrderTraversableContainer)
  inline void PostOrderTraverse(TraverseFun) const override;
};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer: virtual public LinearContainer<Data>,
  virtual public PreOrderMappableContainer<Data>,
  virtual public PostOrderMappableContainer<Data> {

private:
protected:
  using Container::size;

public:

  using LinearContainer<Data>::operator[];
  
  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************** */

  // Copy assignment
  MutableLinearContainer & operator=(const MutableLinearContainer &) = delete;

  // Move assignment
  MutableLinearContainer & operator=(MutableLinearContainer &&) noexcept = delete;

  /* ************************************************************************** */

  // Specific member functions
  inline virtual Data & operator[](unsigned long) = 0;
  virtual Data &Front() = 0;
  virtual Data &Back() = 0;

  /* ************************************************************************** */

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;
  inline void Map(MapFun fun) override;

  /* ************************************************************************** */

  // Specific member function (inherited from PreOrderMappableContainer)
  void PreOrderMap(MapFun) override;

  /* ************************************************************************** */

  // Specific member function (inherited from PostOrderMappableContainer)
  void PostOrderMap(MapFun) override;

  /* ************************************************************************** */
};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data> {

private:
protected:
  using Container::size;

public:
  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************** */

  // Copy assignment
  SortableLinearContainer & operator=(const SortableLinearContainer &) = delete;

  // Move assignment
  SortableLinearContainer & operator=(SortableLinearContainer &&) noexcept = delete;

  /* ************************************************************************** */

  // Specific member function
  virtual void Sort() noexcept;
};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
