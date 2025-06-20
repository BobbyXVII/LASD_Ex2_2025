
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"
#include "../container/mappable.hpp"
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data>, 
             virtual public ClearableContainer {
private:

  // ...

protected:

  using Container::size;

  struct Node {

    Data val{};

    Node* next{nullptr};

    Node() = default;

    /* ********************************************************************** */

    // Specific constructors
    
    Node(const Data&);
    
    Node(Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node &);

    // Move constructor
    Node(Node &&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    
    inline bool operator==(const Node &) const noexcept;
    inline bool operator!=(const Node &) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  Node *head{nullptr};
  Node *tail{nullptr};

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> &);
  List(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List &);

  // Move constructor
  List(List &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  inline List & operator=(const List &);

  // Move assignment
  inline List & operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const List &) const noexcept;
  inline bool operator!=(const List &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data &);

  void InsertAtFront(Data &&);

  void RemoveFromFront();

  Data FrontNRemove();

  void InsertAtBack(const Data &);

  void InsertAtBack(Data &&);

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data& operator[](const unsigned long) override;
  Data& Front() override;
  Data& Back() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](const unsigned long) const override;
  const Data& Front() const override;
  const Data& Back() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override;

  using TestableContainer<Data>::Exists;

protected:

  void PreOrderMap(MapFun, Node *) const;

  void PostOrderMap(MapFun, Node *) const;
  
  void PreOrderTraverse(TraverseFun, Node *) const;

  void PostOrderTraverse(TraverseFun, Node *) const;
};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
