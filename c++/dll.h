/*
 * Filename:		dll.h
 *
 * Author:			Santiago Pagola
 * Brief:			A simple Doubly Linked List implementation.
 * Last modified:	tor 28 dec 2017 10:44:33 CET
*/

#ifndef __DLL_H_
#define __DLL_H_

#include <string>
#include <initializer_list>

using dllcnt_t = int;

class DoublyLinkedList
{
    public:
        DoublyLinkedList();
        DoublyLinkedList(const DoublyLinkedList& rhs);
        DoublyLinkedList(DoublyLinkedList&& rhs);
        DoublyLinkedList(std::initializer_list<int> rhs);
        DoublyLinkedList& operator=(DoublyLinkedList && rhs);
        ~DoublyLinkedList();

    public:
        // Some operators
        DoublyLinkedList & operator=(const DoublyLinkedList & rhs);
        DoublyLinkedList & operator+(const DoublyLinkedList & rhs);
        DoublyLinkedList & operator/(const DoublyLinkedList & rhs);

    private:
        struct Node
        {
            public:
                Node();
                Node(int _value, Node* _next, Node* _prev);
                Node & operator=(const Node & rhs);
                Node* next;
                Node* prev;
                int value;
        };

        Node* head;
        Node* tail;
        dllcnt_t n;

    private:
        DoublyLinkedList::Node* nodeAt(dllcnt_t pos);
        bool fromEnd(dllcnt_t pos);

    public:
        int at(dllcnt_t pos) const;
        dllcnt_t count() const;
        dllcnt_t size() const;
        void insertAt(int value, dllcnt_t pos);
        void insertListAt(const DoublyLinkedList & list, dllcnt_t pos);
        void append(int value);
        void prepend(int value);
        void removeAt(dllcnt_t pos);
        void removeLast();
        void removeFirst();
        inline bool isEmpty()
        {
            // No need for static_cast ...
            return !static_cast<bool>(n);
        }
        void clear();
        void reverseClear();
        std::string const & toString() const;
        std::string const & toReverseString() const;
        void print();
        void reversePrint();
        void swap(dllcnt_t pos1, dllcnt_t pos2);
    public:
        // Iterators
        class DoublyLinkedListIterator :
            public std::iterator<std::bidirectional_iterator_tag, int>
    {
        public:
            friend DoublyLinkedList;
            bool operator==(const DoublyLinkedListIterator & rhs) const;
            bool operator!=(const DoublyLinkedListIterator & rhs) const;
            DoublyLinkedListIterator & operator++();
            DoublyLinkedListIterator & operator++(int);
            DoublyLinkedListIterator & operator--();
            DoublyLinkedListIterator & operator--(int);
            int operator*() const;
        private:
            DoublyLinkedListIterator(Node*);
            Node* current;
    };
        DoublyLinkedListIterator const begin() const;
        DoublyLinkedListIterator const end() const;
};

// Outside of the class: overload operator<<
std::ostream & operator<<(std::ostream & out, const DoublyLinkedList & list);

#endif  /* _DLL_H_ */
