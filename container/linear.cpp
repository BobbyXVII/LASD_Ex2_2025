
namespace lasd {

  /* ************************************************************************** */
  
  template <typename Data>
  bool LinearContainer<Data>::operator==(const LinearContainer<Data>& con) const noexcept {
      if (size != con.size) {
          return false;
      }
  
      for (unsigned long i = 0; i < size; ++i) {
          if ((*this)[i] != con[i]) {
              return false;
          }
      }
      return true;
  }
  
  template <typename Data>
  bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& con) const noexcept {
      return !(*this == con);
  }
  
  /* ************************************************************************** */
  
  // Specific member functions (LinearContainer)
  
  // Front()
  template <typename Data> 
  inline const Data& LinearContainer<Data>::Front() const {
      if (size == 0) {
          throw std::length_error("Empty structure.");
      }
      return (*this)[0];
  }
  
  // Back()
  template <typename Data>
  inline const Data& LinearContainer<Data>::Back() const {
      if (size == 0) {
          throw std::length_error("Empty structure.");
      }
      return (*this)[size - 1];
  }
  
  /* ************************************************************************** */
  
  // Specific member functions (LinearContainer) (inherited from TraversableContainer)
  
  template <typename Data>
  inline void LinearContainer<Data>::Traverse(const TraverseFun fun) const {
      PreOrderTraverse(fun);
  }
  
  /* ************************************************************************** */
  
  // Specific member functions (LinearContainer) (inherited from PreOrderTraversableContainer)
  
  template <typename Data>
  void LinearContainer<Data>::PreOrderTraverse(const TraverseFun fun) const {
      for (unsigned long i = 0; i < size; ++i) {
          fun((*this)[i]);
      }
  }
  
  /* ************************************************************************** */
  
  // Specific member functions (LinearContainer) (inherited from PostOrderTraversableContainer)
  
  template <typename Data>
  void LinearContainer<Data>::PostOrderTraverse(const TraverseFun fun) const {
      for (unsigned long i = size; i > 0;) {
          fun((*this)[--i]);
      }
  }
  
  /* ************************************************************************** */
  
// Specific member functions (MutableLinearContainer) (inherited from MappableContainer)
  
// Front()
template <typename Data> 
Data& MutableLinearContainer<Data>::Front() {
      if (size == 0) {
          throw std::length_error("Empty structure.");
      }
      return (*this)[0];
  }
  
// Back()
template <typename Data> 
Data& MutableLinearContainer<Data>::Back() {
      if (size == 0) {
          throw std::length_error("Empty structure.");
      }
      return (*this)[size - 1];
  }
  
// Override MappableContainer member
template <typename Data> 
void MutableLinearContainer<Data>::Map(MapFun fun) {
      PreOrderMap(fun);
  }
  
  /* ************************************************************************** */
  
  // Specific member functions (MutableLinearContainer) (inherited from PreOrderMappableContainer)
  
template <typename Data> 
void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
      for (unsigned long i = 0; i < size; ++i) {
          fun((*this)[i]);
      }
  }
  
  /* ************************************************************************** */
  
  // Specific member functions (MutableLinearContainer) (inherited from PostOrderMappableContainer)
  
template <typename Data> 
void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
      for (unsigned long i = size; i > 0;) {
          fun((*this)[--i]);
      }
  }
  
  /* ************************************************************************** */

template <typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
    for (long i = 1; i < static_cast<long>(this->Size()); ++i) {
        Data key = std::move((*this)[i]);
        long j = i - 1;
        while (j >= 0 && (*this)[j] > key) {
            (*this)[j + 1] = std::move((*this)[j]);
            --j;
        }
        (*this)[j + 1] = std::move(key);
    }
}
  
  } // namespace lasd
  