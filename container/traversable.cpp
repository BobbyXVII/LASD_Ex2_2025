namespace lasd {
  
  //TraversableContainer
  /* ************************************************************************** */
  
  template <typename Data, typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;
  
  //Fold
  template <typename Data>
  template <typename Accumulator>
  inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator accumulator) const noexcept {
      Traverse(
          [fun, &accumulator](const Data & data) { 
              accumulator = fun(data, accumulator);
          }
      );
      return accumulator;
  } 
  
  // Exists
  template <typename Data>
  inline bool TraversableContainer<Data>::Exists(const Data & value) const noexcept {
      bool exists = false;
      Traverse(
          [value, &exists](const Data & data) {
              exists |= (data == value); 
          }
      );
      return exists; 
  }
  
  
  
  //PreOrderTraversableContainer
  /* ************************************************************************** */
  
  //PreOrderFold
  template <typename Data>
    template <typename Accumulator>
    inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> func, Accumulator accumulator) const
    {
      PreOrderTraverse([&accumulator, func](const Data &currData)
                       { accumulator = func(currData, accumulator); });
      return accumulator;
    };
  
  
  //PostOrderTravesableContainer
  /* ************************************************************************** */
  
  //PostOrderFold
  template <typename Data>
  template <typename Accumulator>
  inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> func, Accumulator accumulator) const
    {
      PostOrderTraverse([&accumulator, &func](const Data &currData)
                        { accumulator = func(currData, accumulator); });
      return accumulator;
    };
  
  
  }
  