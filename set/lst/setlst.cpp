namespace lasd {


  /* ******************************* Auxiliary protected functions ******************************* */
  template <typename Data>
  void SetLst<Data>::InsertInOrder(const Data& data) {
    if (size == 0 || data <= head->val) {
      this->InsertAtFront(data);
      return;
    }
    typename List<Data>::Node* current = head;
    while (current->next != nullptr && current->next->val < data) {
      current = current->next;
    }
    typename List<Data>::Node* newNode = new typename List<Data>::Node(data);
    newNode->next = current->next;
    current->next = newNode;
    if (newNode->next == nullptr) {
      tail = newNode;
    }
    size++;
  }

  template <typename Data>
  void SetLst<Data>::InsertInOrder(Data&& data) {
    if (size == 0 || data <= head->val) {
      this->InsertAtFront(std::move(data));
      return;
    }
    typename List<Data>::Node* current = head;
    while (current->next != nullptr && current->next->val < data) {
      current = current->next;
    }
    typename List<Data>::Node* newNode = new typename List<Data>::Node(std::move(data));
    newNode->next = current->next;
    current->next = newNode;
    if (newNode->next == nullptr) {
      tail = newNode;
    }
    size++;
  }


  /* ******************************* Specific Constructors ******************************* */
  // Construct from TraversableContainer
  template <typename Data>
  SetLst<Data>::SetLst(const TraversableContainer<Data>& container) {
    container.Traverse([this](const Data& data) {
      this->Insert(data);
    });
  }

  // Construct from MappableContainer (move)
  template <typename Data>
  SetLst<Data>::SetLst(MappableContainer<Data>&& container) {
    container.Map([this](Data& data) {
      this->Insert(std::move(data));
    });
  }


  /* ******************************* Copy/move constructors ******************************* */
  // Copy constructor
  template <typename Data>
  SetLst<Data>::SetLst(const SetLst<Data>& other) : List<Data>() {
    other.Traverse([this](const Data& data) {
      this->Insert(data);
    });
  }

  // Move constructor
  template <typename Data>
  SetLst<Data>::SetLst(SetLst<Data>&& other) noexcept : List<Data>(std::move(other)) {}


  /* ******************************* Assignment operators ******************************* */
  // Copy assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other) {
    if (this != &other) {
      this->Clear();
      other.Traverse([this](const Data& data) {
        this->Insert(data);
      });
    }
    return *this;
  }

  // Move assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept {
    List<Data>::operator=(std::move(other));
    return *this;
  }


  /* ******************************* Comparison operators ******************************* */
  template <typename Data>
  bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept {
    return List<Data>::operator==(other);
  }

  template <typename Data>
  inline bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept {
    return !(*this == other);
  }

  /* ******************************* Ordered Dictionary Functions ******************************* */
  // Min/Max functions
  template <typename Data>
  const Data& SetLst<Data>::Min() const {
    if (size == 0) throw std::length_error("Empty set");
    return head->val;
  }

  template <typename Data>
  Data SetLst<Data>::MinNRemove() {
    if (size == 0) throw std::length_error("Empty set");
    return this->FrontNRemove();
  }

  template <typename Data>
  void SetLst<Data>::RemoveMin() {
    if (size == 0) throw std::length_error("Empty set");
    this->RemoveFromFront();
  }

  template <typename Data>
  const Data& SetLst<Data>::Max() const {
    if (size == 0) throw std::length_error("Empty set");
    return tail->val;
  }

  template <typename Data>
  Data SetLst<Data>::MaxNRemove() {
    if (size == 0) throw std::length_error("Empty set");
    return this->BackNRemove();
  }

  template <typename Data>
  void SetLst<Data>::RemoveMax() {
    if (size == 0) throw std::length_error("Empty set");
    this->RemoveFromBack();
  }


  /* ******************************* List Auxiliary operations ******************************* */
  // BackNRemove
  template <typename Data>
  Data SetLst<Data>::BackNRemove() {
    if (size == 0) throw std::length_error("Empty list");

    Data value = tail->val;

    if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      typename List<Data>::Node* current = head;
      while (current->next != tail) {
        current = current->next;
      }
      delete tail;
      tail = current;
      current->next = nullptr;
    }

    size--;
    return value;
  }

  // RemoveFromBack
  template <typename Data>
  void SetLst<Data>::RemoveFromBack() {
    if (size == 0) throw std::length_error("Empty list");

    if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      typename List<Data>::Node* current = head;
      while (current->next != tail) {
        current = current->next;
      }
      delete tail;
      tail = current;
      current->next = nullptr;
    }

    size--;
  }


  /* ******************************* Successor/Predecessor operations ******************************* */
  // Predecessor operations
  template <typename Data>
  const Data& SetLst<Data>::Predecessor(const Data& data) const {
    if (size == 0) throw std::length_error("Empty set");
    typename List<Data>::Node* pred = FindPointerToPredecessor(data);
    if (pred == nullptr) throw std::length_error("Predecessor not found");
    return pred->val;
  }

  template <typename Data>
  Data SetLst<Data>::PredecessorNRemove(const Data& data) {
    if (size == 0) throw std::length_error("Empty set");
    typename List<Data>::Node* pred = FindPointerToPredecessor(data);
    if (pred == nullptr) throw std::length_error("Predecessor not found");
    
    Data value = pred->val;
    
    if (pred == head) {
      return this->FrontNRemove();
    } else {
      typename List<Data>::Node* current = head;
      while (current->next != pred) {
        current = current->next;
      }
      current->next = pred->next;
      if (pred == tail) {
        tail = current;
      }
      delete pred;
      size--;
    }
    return value;
  }

  template <typename Data>
  void SetLst<Data>::RemovePredecessor(const Data& data) {
    if (size == 0) throw std::length_error("Empty set");
    typename List<Data>::Node* pred = FindPointerToPredecessor(data);
    if (pred == nullptr) throw std::length_error("Predecessor not found");
    
    if (pred == head) {
      this->RemoveFromFront();
    } else {
      typename List<Data>::Node* current = head;
      while (current->next != pred) {
        current = current->next;
      }
      current->next = pred->next;
      if (pred == tail) {
        tail = current;
      }
      delete pred;
      size--;
    }
  }

  // Successor operations
  template <typename Data>
  const Data& SetLst<Data>::Successor(const Data& data) const {
    if (size == 0) throw std::length_error("Empty set");
    typename List<Data>::Node* succ = FindPointerToSuccessor(data);
    if (succ == nullptr) throw std::length_error("Successor not found");
    return succ->val;
  }

  template <typename Data>
  Data SetLst<Data>::SuccessorNRemove(const Data& data) {
    if (size == 0) throw std::length_error("Empty set");
    typename List<Data>::Node* succ = FindPointerToSuccessor(data);
    if (succ == nullptr) throw std::length_error("Successor not found");
    
    Data value = succ->val;
    
    if (succ == head) {
      return this->FrontNRemove();
    } else {
      typename List<Data>::Node* current = head;
      while (current->next != succ) {
        current = current->next;
      }
      current->next = succ->next;
      if (succ == tail) {
        tail = current;
      }
      delete succ;
      size--;
    }
    return value;
  }

  template <typename Data>
  void SetLst<Data>::RemoveSuccessor(const Data& data) {
    if (size == 0) throw std::length_error("Empty set");
    typename List<Data>::Node* succ = FindPointerToSuccessor(data);
    if (succ == nullptr) throw std::length_error("Successor not found");
    
    if (succ == head) {
      this->RemoveFromFront();
    } else {
      typename List<Data>::Node* current = head;
      while (current->next != succ) {
        current = current->next;
      }
      current->next = succ->next;
      if (succ == tail) {
        tail = current;
      }
      delete succ;
      size--;
    }
  }


  /* ******************************* Dictionary Container  ******************************* */
  // Insert operations
  template <typename Data>
  bool SetLst<Data>::Insert(const Data& data) {
    if (this->Exists(data)) return false;
    InsertInOrder(data);
    return true;
  }

  template <typename Data>
  bool SetLst<Data>::Insert(Data&& data) {
    if (this->Exists(data)) return false;
    InsertInOrder(std::move(data));
    return true;
  }

  // Remove operation
  template <typename Data>
  bool SetLst<Data>::Remove(const Data& data) {
    if (size == 0) return false;
    if (head->val == data) {
      this->RemoveFromFront();
      return true;
    }
    
    typename List<Data>::Node* current = head;
    while (current->next != nullptr && current->next->val != data) {
      current = current->next;
    }
    
    if (current->next == nullptr) return false;
    
    typename List<Data>::Node* temp = current->next;
    current->next = temp->next;
    
    if (temp == tail) {
      tail = current;
    }
    
    delete temp;
    size--;
    return true;
  }


  /* ******************************* Auxiliary finder methods ******************************* */
  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::FindPointerToMin() const {
    return head;
  }

  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::FindPointerToMax() const {
    return tail;
  }

  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::FindPointerToPredecessor(const Data& data) const {
    if (size == 0 || data <= head->val) return nullptr;
    
    typename List<Data>::Node* current = head;
    typename List<Data>::Node* predecessor = nullptr;
    
    while (current != nullptr && current->val < data) {
      predecessor = current;
      current = current->next;
    }
    
    return predecessor;
  }

  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::FindPointerToSuccessor(const Data& data) const {
    if (size == 0 || data >= tail->val) return nullptr;
    
    typename List<Data>::Node* current = head;
    while (current != nullptr && current->val <= data) {
      current = current->next;
    }
    
    return current;
  }

  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::FindPointerTo(const Data& data) const {
    return BinarySearch(data);
  }


  /* ******************************* Binary search auxiliary functions ******************************* */
  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::Reach(typename List<Data>::Node* startNode, unsigned int steps) const {
    if (startNode == nullptr) return nullptr;
    
    typename List<Data>::Node* current = startNode;
    for (unsigned int i = 0; i < steps && current != nullptr; ++i) {
        current = current->next;
    }
    return current;
  }

  template <typename Data>
  typename List<Data>::Node* SetLst<Data>::BinarySearch(const Data& data) const {
    if (size == 0) return nullptr;
    
    unsigned int length = size;
    typename List<Data>::Node* current = head;
    
    while (length > 0) {
        unsigned int step = length / 2;
        typename List<Data>::Node* mid = Reach(current, step);
        
        if (mid == nullptr) break;
        
        if (mid->val == data) {
            return mid;
        } else if (mid->val < data) {
            current = mid->next;
            length = length - step - 1;
        } else {
            length = step;
        }
    }
    
    return nullptr;  // Element not found
  }

}