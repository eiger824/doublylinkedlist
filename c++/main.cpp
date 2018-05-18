#include <iostream>
#include <ctime>
#include <cstdlib>

#include "dll.h"

using namespace std;

int main(int argc, char* argv[])
{
    DoublyLinkedList list;

    cout << "List: " << list.toString() << ", size of list: " << list.count()
        << ", list empty: " << list.isEmpty() <<  endl;
    srand(time(nullptr));
    for (unsigned i=0; i<10; ++i)
    {
        list.append(rand() % 500);
    }
    cout << "List: " << list.toString() << ", size of list: " << list.count() 
        << ", list empty: " << list.isEmpty() <<  endl;
    cout << "Printing list to stdout: " << endl;
    list.print();
    cout << "Reverse-List: " << list.toReverseString() << ", size of list: " <<
        list.count() << endl; 
    cout << "Printing reverse list to stdout: " << endl;
    list.reversePrint();
    cout << "Cleaning list ..." << endl;
    list.clear();
    cout << "List: " << list.toString() << ", size of list: " << list.count() <<
        endl; 
    cout << "Prepending some elements ..." << endl;
    list.prepend(130);
    list.prepend(780);
    list.prepend(824);
    list.prepend(1000);
    list.prepend(114);
    list.prepend(9);
    list.prepend(13);
    cout << "New list: " << list.toString() << ", size of list: " << list.count()
        << endl; 

    cout << "Will insert an element at position 2:" << endl;
    list.insertAt(2254, 2);
    cout << "List: " << list.toString() << ", size of list: " << list.count() <<
        endl; 

    cout << "Overloading << operator: " << list << endl;

    cout << "Element at 2: " << list.at(2) << endl;

    cout << "Removing first element ... " << endl;
    list.removeFirst();
    cout << "List now: " << list << " (size: " << list.count() << "). Removing last ..."
        << endl; 
    list.removeLast();
    cout << "List now: " << list << "(size: " << list.count() << "). Removing at index 4 ..."
        << endl; 
    list.removeAt(4);
    cout << "List now: " << list << "(size: " << list.count() << ")" << endl;

    cout << "Will swap elements 1 and 3:" << endl;
    list.swap(1, 3);
    cout << "List now: " << list << "(size: " << list.count() << ")" << endl;

    // Copy constructor!
    DoublyLinkedList list2{list};
    cout << "List2, created with a copy-constructor: " << list2 << ", points to: "
        << &list2 << endl; 
    // Move constructor!
    DoublyLinkedList list3{std::move(list2)};
    cout << "List3, created with the move-constructor: " << list3 << endl;
    cout << "See what happened with \"List2\" ;-) ? " << list2 << ", it still points to: "
        << &list2 << endl; 

    DoublyLinkedList list4;
    list4.append(7);
    list4.append(25);
    list4.append(2);
    list4.append(13);
    list4.append(8);

    DoublyLinkedList list5;
    list5.append(1);
    list5.append(2);
    list5.append(3);
    list5.append(4);

    DoublyLinkedList list6 = list5;
    list6.clear();
    list6.prepend(3);

    cout << "Expanding list4 = " << list4 << " with list5 = " << list5 << 
        ", inserting it at index 2" << endl; 
    list4.insertListAt(list5, 2);
    cout << "New list4 = " << list4 << " with size: " << list4.count() << endl;
    list4.insertListAt(list6, 0);
    cout << "New list4 = " << list4 << " with size: " << list4.count() << endl;
    try
    {
        list4.insertAt(11, 1000);
    }
    catch (const std::out_of_range ex)
    {
        cerr << "Exception was caught, are you out of your mind? Tried to access"
            << "index"
            << "out of bounds" << endl; 
        cerr << "(Reason: " << ex.what() << ")" << endl;
    }
    cout << "Adding list4 = " << list4 << " (size " << list4.count() << ") and "
        "list1 = " << list << " (size " << list.count() << ") ..." << endl; 
    list4 = list4 + list;
    cout << "New list4    = " << list4 << " with size: " << list4.count() << endl;
    DoublyLinkedList list7{list4 + list};
    cout << "List7        = " << list7 << " with size: " << list7.size() << endl;

    DoublyLinkedList divisors{initializer_list<int>{2,2,2,2,2}};
    DoublyLinkedList dividers{initializer_list<int>{8,8,8,8,8}};
    cout << "Will divide " << dividers << " between " << divisors << endl;
    DoublyLinkedList result {dividers / divisors};
    cout << "New result = " << result << " with size: " << result.size() << endl; 

    return 0;
}
