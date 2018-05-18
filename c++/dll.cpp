/*
 * Filename:		dll.cpp
 *
 * Author:			Santiago Pagola
 * Brief:			Implementation of the Doubly Linked List defined in header file
 dll.h. 
 * Last modified:	tor 28 dec 2017 10:48:22 CET
*/

#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "dll.h"

static std::string listStr{""};

DoublyLinkedList::Node::Node() :
    next{nullptr},
    prev{nullptr},
    value{0}
{
}

DoublyLinkedList::Node & DoublyLinkedList::Node::operator=(const Node & rhs)
{
    next = rhs.next;
    prev = rhs.prev;
    value = rhs.value;
}

DoublyLinkedList::Node::Node(int _value, Node* _next, Node* _prev) :
    next{_next},
    prev{_prev},
    value{_value}

{
}

DoublyLinkedList::DoublyLinkedList(std::initializer_list<int> rhs) :
    DoublyLinkedList()
{
    for (auto item : rhs)
    {
        append(item);
    }
}

DoublyLinkedList::DoublyLinkedList() :
    head{new Node()},
    tail{new Node()},
    n{0}
{
    // Make head and tail's next and prev point to each other
    head->next = tail;
    tail->prev = head;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList & rhs) :
    DoublyLinkedList()
{
    Node *nd = head;
    for (DoublyLinkedListIterator it = rhs.begin(); it != rhs.end(); ++it)
    {
        nd->next = new Node(*it, tail, nd);
        nd = nd->next;
        ++n;
        // No need to add n count since the count is done when calling
        // the DoublyLinkedList(const DoublyLinkedList & rhs) constructor ... 
    }
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList && rhs) :
    DoublyLinkedList()
{
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    std::swap(n, rhs.n);
}

DoublyLinkedList::~DoublyLinkedList()
{
    clear();
    delete head;
    delete tail;
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList & rhs)
{
    // Clear it if rhs is not a reference to this object
    if (&rhs != this)
    {
        clear();
        Node *nd = head;
        for (DoublyLinkedListIterator it = rhs.begin(); it != rhs.end(); ++it)
        {
            nd->next = new Node(*it, tail, nd);
            nd = nd->next;
        }
    }
    return *this;
}

DoublyLinkedList & DoublyLinkedList::operator+(const DoublyLinkedList & rhs)
{
    insertListAt(rhs, n - 1);
    return *this;
}

DoublyLinkedList & DoublyLinkedList::operator/(const DoublyLinkedList & rhs)
{
    if (rhs.count() != n)
        throw std::invalid_argument("Error: both lists must have the same length");

    Node *current = head->next;
    dllcnt_t index{0};
    while (current != tail)
    {
        current->value /= rhs.at(index);
        current = current->next;
        ++index;
    }
    return *this;
}

dllcnt_t DoublyLinkedList::count() const
{
    return n;
}

dllcnt_t DoublyLinkedList::size() const
{
    return n;
}

bool DoublyLinkedList::fromEnd(dllcnt_t pos)
{
    if (n > 2)
    {
        if (pos > n - pos - 1)
            return true;
    }
    else
    {
        return false;
    }
    return false;
}

void DoublyLinkedList::insertAt(int value, dllcnt_t pos)
{
    // Check range
    if (pos < 0 or pos > n - 1)
        throw std::out_of_range("Error: index out of range");

// Be smart: if pos is closer to the start or end, start looping from that part 


    Node *nd, *current;
    // Insert new node
    if (!fromEnd(pos))
    {
        current = head->next;
        dllcnt_t cnt = 0;
        while (current != tail)
        {
            if (cnt == pos)
            {
                nd = new Node(value, current, current->prev);
                current->prev->next = nd;
                current->prev = nd;
                break;
            }
            ++cnt;
            current = current->next;
        }
    }
    else
    {
        current = tail->prev;
        dllcnt_t cnt = n - 1;
        while (current != head)
        {
            if (cnt == pos)
            {
                nd = new Node(value, current, current->prev);
                current->prev->next = nd;
                current->prev = nd;
                break;
            }
            --cnt;
            current = current->prev;
        }
    }
    // Add up count
    ++n;
}

void DoublyLinkedList::insertListAt(const DoublyLinkedList & list,
        dllcnt_t pos) 
{
    if (pos < 0 or pos > n - 1)
        throw std::out_of_range("Error: index out of range");

    for (auto item : list)
    {
        append(item);
    }
}

void DoublyLinkedList::append(int value)
{
    // When appending, our new node will always sit between tail's prev and tail
    Node *nd = new Node(value, tail, tail->prev);
    // And make next and prev nodes point to 'n'
    tail->prev->next = nd;
    tail->prev = nd;
    // Add up count
    ++n;
}
void DoublyLinkedList::prepend(int value)
{
    Node *nd = new Node(value, head->next, head);
    // Reorder ptrs
    head->next->prev = nd;
    head->next = nd;
    // Add up count
    ++n;
}
void DoublyLinkedList::removeLast()
{
    if (n == 0)
        throw std::out_of_range("Error: list empty");

    Node *last = tail->prev;
    last->prev->next = tail;
    tail->prev = last->prev;
    delete last;
    // Decrease count
    --n;
}
void DoublyLinkedList::removeFirst()
{
    if (n == 0)
        throw std::out_of_range("Error: list empty");

    Node *first = head->next;
    first->next->prev = head;
    head->next = first->next;
    delete first;
    // Decrease count
    --n;
}

void DoublyLinkedList::removeAt(dllcnt_t pos)
{
    if (n == 0 or (pos < 0 or pos > n - 1))
        throw std::out_of_range("Error: index out of range");

    // Idea: start looping from end / start depending on pos
    Node* current = head->next;
    Node* deleteNode;
    dllcnt_t c{0};

    while (current != tail)
    {
        if (c == pos)
        {
            deleteNode = current;
            deleteNode->prev->next = deleteNode->next;
            deleteNode->next->prev = deleteNode->prev;
            // Delete it
            delete deleteNode;
            break;
        }
        current = current->next;
        c++;
    }
    // Decrease count
    --n;
}
std::string const & DoublyLinkedList::toString() const 
{
    Node *current = head->next;
    listStr.clear();
    listStr += "[";
    while (current != tail)
    {
        listStr += std::to_string(current->value);
        if (current->next != tail)
            listStr += ",";
        current = current->next;
    }
    listStr += "]";
    return listStr;
}

std::string const & DoublyLinkedList::toReverseString() const
{
    Node *current = tail->prev;
    listStr.clear();
    listStr += "[";
    while (current != head)
    {
        listStr += std::to_string(current->value);
        if (current->prev != head)
            listStr += ",";
        current = current->prev;
    }
    listStr += "]";
    return listStr;
}

void DoublyLinkedList::print()
{
    Node *current = head->next;
    std::string strlist{""};
    while (current->next != nullptr)
    {
        strlist += std::to_string(current->value);
        if (current->next != tail)
            strlist += ",";
        current = current->next;
    }
    std::cout << "[" << strlist << "]" << std::endl;
}

void DoublyLinkedList::reversePrint()
{
    Node *current = tail->prev;
    std::string strlist{""};
    while (current != head)
    {
        strlist += std::to_string(current->value);
        if (current->prev != head)
            strlist += ",";
        current = current->prev;
    }
    std::cout << "[" << strlist << "]" << std::endl;
}

void DoublyLinkedList::clear()
{
    Node *current = head->next;
    while (current != tail)
    {
        Node *current_cpy = current;
        current = current->next;
        delete current_cpy;
        --n;
    }
    head->next = tail;
    tail->prev = head;
}

// Must-have: at()
int DoublyLinkedList::at(dllcnt_t pos) const
{
    // Check range
    if (pos < 0 or pos > n - 1)
        throw std::out_of_range("Error: index out of range");
    auto it = begin();
    for (int i = 0; i < pos; ++i)
    {
        it++;
    }
    return *it;
}

// Just for fun!
void DoublyLinkedList::reverseClear()
{
    Node *current = tail->prev;
    while (current != head)
    {
        Node *current_cpy = current;
        current = current->prev;
        delete current_cpy;
        --n;
    }
    tail->prev = head;
    head->next = tail;
}

// Own-defined iterator class
DoublyLinkedList::DoublyLinkedListIterator::DoublyLinkedListIterator(Node*
node) : 
    current{node}
{
}

bool DoublyLinkedList::DoublyLinkedListIterator::operator==(const
DoublyLinkedListIterator & rhs) const 
{
    return current == rhs.current;
}

bool DoublyLinkedList::DoublyLinkedListIterator::operator!=(const
DoublyLinkedListIterator & rhs) const 
{
    return !(*this == rhs.current);
}

int DoublyLinkedList::DoublyLinkedListIterator::operator*() const
{
    if (current->next == nullptr)
        throw std::invalid_argument("Invalid dereference of end() iterator");
    return current->value;
}

DoublyLinkedList::DoublyLinkedListIterator &
DoublyLinkedList::DoublyLinkedListIterator::operator++() 
{
    current->next != nullptr ?
        current = current->next :
        throw std::invalid_argument("Invalid iterator index");
    return *this;
}

DoublyLinkedList::DoublyLinkedListIterator &
DoublyLinkedList::DoublyLinkedListIterator::operator++(int) 
{
    // We will return the iterator BEFORE incrementing its value
    DoublyLinkedListIterator iter = *this;
    current->next != nullptr ?
        current = current->next :
        throw std::invalid_argument("Invalid iterator index");
    return iter;
}

DoublyLinkedList::DoublyLinkedListIterator &
DoublyLinkedList::DoublyLinkedListIterator::operator--() 
{
    current->prev != nullptr ?
        current = current->prev :
        throw std::invalid_argument("Invalid iterator index");
    return *this;
}

DoublyLinkedList::DoublyLinkedListIterator &
DoublyLinkedList::DoublyLinkedListIterator::operator--(int) 
{
    // We will return the iterator BEFORE incrementing its value
    DoublyLinkedListIterator iter = *this;
    current->prev != nullptr ?
        current = current->prev :
        throw std::invalid_argument("Invalid iterator index");
    return iter;
}

DoublyLinkedList::DoublyLinkedListIterator const DoublyLinkedList::begin()
const 
{
    return DoublyLinkedListIterator(head->next);
}

DoublyLinkedList::DoublyLinkedListIterator const DoublyLinkedList::end() const
{
    return DoublyLinkedListIterator(tail);
}

/*
 * Function:	swap
 * Brief:	Swaps two nodes in the list
 * @param pos1:	Position of a node to swap
 * @param pos2:	Position of the other node to swap
 * Returns:	Nothing
 */
void DoublyLinkedList::swap(dllcnt_t pos1, dllcnt_t pos2)
{
    // Range checks
    if ((pos1 < 0 or pos1 > n - 1) or // Pos1 invalid
            (pos2 < 0 or pos2 > n - 1) or // Pos2 invalid
            (pos1 == pos2)) // Same pos
        throw std::out_of_range("Invalid range");

    // Get nodes
    Node* first = nodeAt(pos1);
    Node* second = nodeAt(pos2);

    Node *first_prev = first->prev;
    Node *first_next = first->next;

    Node *second_prev = second->prev;
    Node *second_next = second->next;

    // Swap them
    second->next = first_next;
    first_next->prev = second;
    second->prev = first_prev;
    first_prev->next = second;

    first->next = second_next;
    second_next->prev = first;
    first->prev = second_prev;
    second_prev->next = first;
}

DoublyLinkedList::Node* DoublyLinkedList::nodeAt(dllcnt_t pos)
{
    // Check range
    if (pos < 0 or pos > n - 1)
        throw std::out_of_range("ERROR: out of index");

    Node *target;
    dllcnt_t cnt;
    // Start from the beginning or end depending on the position
    if (!fromEnd(pos))
    {
        cnt = 0;
        auto it = begin();
        while (it != end() and cnt != pos)
        {
            ++it;
            ++cnt;
        }
        target = it.current;
    }
    else
    {
        cnt = n - 1;
        // end() is tail, so we want the previous one
        DoublyLinkedListIterator iter = end();
        auto it = --iter;
        while (it != head and cnt != pos)
        {
            --it;
            --cnt;
        }
        target = it.current;
    }
    return target;
}

std::ostream & operator<<(std::ostream & out, const DoublyLinkedList & list)
{
    std::string outlist{list.toString()};
    out << outlist;
    return out;
}

