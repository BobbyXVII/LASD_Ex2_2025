namespace lasd {

/* ************************************************************************** */
/* NODE - CONSTRUCTORS, DESTRUCTOR AND OPERATORS                               */
/* ************************************************************************** */

// Data copy constructor
template <typename Data>
List<Data>::Node::Node(const Data &d) : val(d) {}

// Data move constructor
template <typename Data>
List<Data>::Node::Node(Data &&d) noexcept { std::swap(val, d); }

// Copy constructor
template <typename Data>
List<Data>::Node::Node(const Node &other) : val(other.val) {}

// Move constructor
template <typename Data>
List<Data>::Node::Node(Node &&other) noexcept {
    std::swap(other.val, val);
    std::swap(other.next, next);
}

// Destructor
template <typename Data> List<Data>::Node::~Node() {}

// Comparison operators
template <typename Data>
inline bool List<Data>::Node::operator==(const Node &other) const noexcept {
    return (val == other.val);
}

template <typename Data>
inline bool List<Data>::Node::operator!=(const Node &other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */
/* LIST - CONSTRUCTORS                                                         */
/* ************************************************************************** */

// Copy constructor from TraversableContainer
template <typename Data>
List<Data>::List(const TraversableContainer<Data> &con) {
    con.Traverse([this](const Data &d) {
        InsertAtBack(d);
    });
}

// Move constructor from MappableContainer
template <typename Data>
List<Data>::List(MappableContainer<Data> &&con) {
    con.Map([this](Data &d) {
        InsertAtBack(std::move(d));
    });
}

//Copy constructor
template <typename Data> List<Data>::List(const List<Data> &l) {
  if (!(size = l.size))
    return;

  head = new Node(*(l.head));
  tail = head;

  Node *temp = l.head->next;

  while (temp) {
    tail->next = new Node(*temp);
    tail = tail->next;
    temp = temp->next;
  }
}

// Move constructor
template <typename Data> List<Data>::List(List &&l) {
  std::swap(size, l.size);
  std::swap(head, l.head);
  std::swap(tail, l.tail);
}

/* ************************************************************************** */
/* LIST - DESTRUCTOR                                                           */
/* ************************************************************************** */

// Destructor
template <typename Data> List<Data>::~List() {
    Clear();
}

/* ************************************************************************** */
/* LIST - ASSIGNMENT OPERATORS                                                 */
/* ************************************************************************** */

// Copy assignment
template <typename Data>
List<Data> &List<Data>::operator=(const List<Data> &l) {
    if (!l.size) {
        Clear();
        return *this;
    }

    if (!size) {
        List<Data> temp(l);
        std::swap(temp, *this);
        return *this;
    }

    Node *wl{l.head};
    tail = head;

    tail->val = wl->val;

    while (tail->next && wl->next) {
        tail = tail->next;
        wl = wl->next;
        tail->val = wl->val;
    }

    if (tail->next) {
        Node* temp = tail->next;
        tail->next = nullptr;
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    } else
        for (wl = wl->next; wl; wl = wl->next) {
            InsertAtBack(wl->val);
        }
    size = l.size;
    return *this;
}

// Move assignment
template <typename Data>
List<Data> &List<Data>::operator=(List<Data> &&l) noexcept {
    std::swap(size, l.size);
    std::swap(head, l.head);
    std::swap(tail, l.tail);
    return *this;
}

/* ************************************************************************** */
/* LIST - COMPARISON OPERATORS                                                 */
/* ************************************************************************** */

template <typename Data>
inline bool List<Data>::operator==(const List<Data> &l) const noexcept {
    if (size != l.size)
        return false;

    Node *tmp = head, *tmp2 = l.head;

    while (tmp != nullptr) {
        if (tmp->val != tmp2->val)
            return false;
        tmp = tmp->next;
        tmp2 = tmp2->next;
    }
    return true;
}

template <typename Data>
inline bool List<Data>::operator!=(const List<Data> &l) const noexcept {
    return !(*this == l);
}

/* ************************************************************************** */
/* LIST - SPECIFIC MEMBER FUNCTIONS                                            */
/* ************************************************************************** */

template <typename Data>
void List<Data>::InsertAtFront(const Data &data) {
    Node* newNode = new Node(data);
    
    if (size == 0) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    
    ++size;
}

template <typename Data>
void List<Data>::InsertAtFront(Data &&data) {
    Node* newNode = new Node(std::move(data));
    
    if (size == 0) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    
    ++size;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
    if (size == 0)
        throw std::length_error("Empty list");
    
    Node* tmp = head;
    head = head->next;
    
    if (head == nullptr)
        tail = nullptr;
    
    tmp->next = nullptr;
    delete tmp;
    
    --size;
}

template <typename Data>
Data List<Data>::FrontNRemove() {
    if (size == 0)
        throw std::length_error("Empty list");
    
    Data value = head->val;
    RemoveFromFront();
    return value;
}

template <typename Data>
void List<Data>::InsertAtBack(const Data &data) {
    Node* newNode = new Node(data);
    
    if (size == 0) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    
    ++size;
}

template <typename Data>
void List<Data>::InsertAtBack(Data &&data) {
    Node* newNode = new Node(std::move(data));
    
    if (size == 0) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    
    ++size;
}

/* ************************************************************************** */
/* LIST - MUTABLE LINEAR CONTAINER FUNCTIONS                                   */
/* ************************************************************************** */

template <typename Data>
Data &List<Data>::operator[](const unsigned long index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    
    Node *tmp = head;
    for (unsigned long i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return tmp->val;
}

template <typename Data>
Data &List<Data>::Front() {
    if (size == 0)
        throw std::length_error("Empty list");
    return head->val;
}

template <typename Data>
Data &List<Data>::Back() {
    if (size == 0)
        throw std::length_error("Empty list");
    return tail->val;
}

/* ************************************************************************** */
/* LIST - LINEAR CONTAINER FUNCTIONS                                           */
/* ************************************************************************** */

template <typename Data>
const Data& List<Data>::operator[](const unsigned long index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node* tmp = head;
    for (unsigned long i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return tmp->val;
}

template <typename Data>
const Data& List<Data>::Front() const {
    if (size == 0) {
        throw std::length_error("Empty list");
    }
    return head->val;
}

template <typename Data>
const Data& List<Data>::Back() const {
    if (size == 0) {
        throw std::length_error("Empty list");
    }
    return tail->val;
}

/* ************************************************************************** */
/* LIST - MAPPABLE CONTAINER FUNCTIONS                                         */
/* ************************************************************************** */

template <typename Data>
inline void List<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}

/* ************************************************************************** */
/* LIST - PRE-ORDER MAPPABLE CONTAINER FUNCTIONS                               */
/* ************************************************************************** */

template <typename Data>
inline void List<Data>::PreOrderMap(MapFun fun) {
    Node* current = head;
    while (current != nullptr) {
        fun(current->val);
        current = current->next;
    }
}

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node* current) const {
    if (current != nullptr) {
        fun(current->val);
        PreOrderMap(fun, current->next);
    }
}

/* ************************************************************************** */
/* LIST - POST-ORDER MAPPABLE CONTAINER FUNCTIONS                              */
/* ************************************************************************** */

template <typename Data>
inline void List<Data>::PostOrderMap(MapFun fun) {
    PostOrderMap(fun, head);
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node* current) const {
    if (current != nullptr) {
        PostOrderMap(fun, current->next);
        fun(current->val);
    }
}

/* ************************************************************************** */
/* LIST - TRAVERSABLE CONTAINER FUNCTIONS                                      */
/* ************************************************************************** */

template <typename Data>
inline void List<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

/* ************************************************************************** */
/* LIST - PRE-ORDER TRAVERSABLE CONTAINER FUNCTIONS                            */
/* ************************************************************************** */

template <typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) const {
    PreOrderTraverse(fun, head);
}

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, Node* current) const {
    if (current != nullptr) {
        fun(current->val);
        PreOrderTraverse(fun, current->next);
    }
}

/* ************************************************************************** */
/* LIST - POST-ORDER TRAVERSABLE CONTAINER FUNCTIONS                           */
/* ************************************************************************** */

template <typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun) const {
    PostOrderTraverse(fun, head);
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, Node* current) const {
    if (current != nullptr) {
        PostOrderTraverse(fun, current->next);
        fun(current->val);
    }
}

/* ************************************************************************** */
/* LIST - CLEARABLE CONTAINER FUNCTIONS                                        */
/* ************************************************************************** */

template <typename Data>
inline void List<Data>::Clear() {
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        tmp->next = nullptr;
        delete tmp;
    }
    tail = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
