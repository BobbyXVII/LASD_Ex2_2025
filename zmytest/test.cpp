#include "../pq/heap/pqheap.hpp"
#include "../heap/vec/heapvec.hpp"
#include "../vector/vector.hpp"
#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>  // Aggiungi questa riga

using namespace std;
using namespace lasd;

// Helper function to print test results
void printTestResult(const string& testName, bool success) {
    cout << (success ? " [PASS] " : "[FAIL] ") << testName << endl;
}

// Helper function to print elements of a container
template <typename Data>
void PrintContainer(const string& name, const TraversableContainer<Data>& con) {
    cout << name << ": [";
    bool first = true;
    con.Traverse([&](const Data& val) {
        if (!first) {
            cout << ", ";
        }
        cout << val;
        first = false;
    });
    cout << "]" << endl;
}

// Test HeapVec con interi
void testHeapVecInt() {
    cout << "\n======= TESTS FOR HEAPVEC CLASS (INT) =======" << endl;
    
    // Test costruttori
    cout << "\n=== HeapVec Constructors Test ===" << endl;
    bool allConstructorsPassed = true;
    
    HeapVec<int> h1;
    bool defaultConstructorTest = (h1.Size() == 0 && h1.Empty());
    printTestResult("Default constructor", defaultConstructorTest);
    cout << "  - Expected size: 0, Actual size: " << h1.Size() << endl;
    allConstructorsPassed &= defaultConstructorTest;
    
    Vector<int> sourceVec(7);
    sourceVec[0] = 4; sourceVec[1] = 1; sourceVec[2] = 3; sourceVec[3] = 2;
    sourceVec[4] = 16; sourceVec[5] = 9; sourceVec[6] = 10;
    
    HeapVec<int> h2(sourceVec);
    bool containerConstructorTest = (h2.Size() == 7 && !h2.Empty());
    printTestResult("TraversableContainer constructor", containerConstructorTest);
    cout << "  - Expected size: 7, Actual size: " << h2.Size() << endl;
    allConstructorsPassed &= containerConstructorTest;
    
    cout << "Original vector: ";
    sourceVec.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    
    cout << "HeapVec after construction: ";
    PrintContainer("h2", h2);
    
    // Test IsHeap dopo costruzione
    bool isHeapAfterConstruction = h2.IsHeap();
    printTestResult("IsHeap after construction", isHeapAfterConstruction);
    cout << "  - Is heap: " << (isHeapAfterConstruction ? "true" : "false") << endl;
    
    cout << "Overall constructors test result: " << (allConstructorsPassed && isHeapAfterConstruction ? "SUCCESS" : "FAILURE") << endl;
    
    // Test operazioni base
    cout << "\n=== HeapVec Basic Operations Test ===" << endl;
    bool allBasicTestsPassed = true;
    
    bool frontTest = (h2.Front() == h2[0]);
    bool backTest = (h2.Back() == h2[h2.Size() - 1]);
    printTestResult("Front and Back access", frontTest && backTest);
    cout << "  - Front: " << h2.Front() << ", Back: " << h2.Back() << endl;
    
    bool existsTest1 = h2.Exists(16);
    bool existsTest2 = !h2.Exists(100);
    printTestResult("Exists(16) [element present]", existsTest1);
    printTestResult("Exists(100) [element not present]", existsTest2);
    
    allBasicTestsPassed &= (frontTest && backTest && existsTest1 && existsTest2);
    
    // Test Fold
    int sum = h2.Fold<int>([](const int& x, const int& acc) -> int {
        return acc + x;
    }, 0);
    
    bool foldTest = (sum == 45); // 4+1+3+2+16+9+10 = 45
    printTestResult("Fold (sum)", foldTest);
    cout << "  - Expected sum: 45, Actual sum: " << sum << endl;
    allBasicTestsPassed &= foldTest;
    
    cout << "Overall basic operations test result: " << (allBasicTestsPassed ? "SUCCESS" : "FAILURE") << endl;
    
    // Test Heapify
    cout << "\n=== HeapVec Heapify Test ===" << endl;
    bool allHeapifyTestsPassed = true;
    
    // Creo un array non-heap
    Vector<int> unheapVec(5);
    unheapVec[0] = 1; unheapVec[1] = 5; unheapVec[2] = 2;
    unheapVec[3] = 8; unheapVec[4] = 3;
    
    HeapVec<int> h3(unheapVec);
    cout << "Before Heapify: ";
    PrintContainer("h3", h3);
    
    bool isHeapBefore = h3.IsHeap();
    cout << "Is heap before Heapify: " << (isHeapBefore ? "true" : "false") << endl;
    
    h3.Heapify();
    cout << "After Heapify: ";
    PrintContainer("h3", h3);
    
    bool isHeapAfter = h3.IsHeap();
    printTestResult("IsHeap after Heapify", isHeapAfter);
    cout << "Is heap after Heapify: " << (isHeapAfter ? "true" : "false") << endl;
    
    allHeapifyTestsPassed &= isHeapAfter;
    cout << "Overall Heapify test result: " << (allHeapifyTestsPassed ? "SUCCESS" : "FAILURE") << endl;
    
    // Test Sort
    cout << "\n=== HeapVec Sort Test ===" << endl;
    bool allSortTestsPassed = true;
    
    HeapVec<int> h4(sourceVec);
    cout << "Before Sort: ";
    PrintContainer("h4", h4);
    
    h4.Sort();
    cout << "After Sort: ";
    PrintContainer("h4", h4);
    
    // Verifica se è ordinato
    bool isSorted = true;
    for (unsigned long i = 0; i < h4.Size() - 1; i++) {
        if (h4[i] > h4[i + 1]) {
            isSorted = false;
            break;
        }
    }
    printTestResult("Array sorted correctly", isSorted);
    
    allSortTestsPassed &= isSorted;
    cout << "Overall Sort test result: " << (allSortTestsPassed ? "SUCCESS" : "FAILURE") << endl;
    
    // Test eccezioni
    cout << "\n=== HeapVec Exceptions Test ===" << endl;
    bool allExceptionsPassed = true;
    
    HeapVec<int> emptyHeap;
    
    bool isHeapExceptionTest = false;
    try {
        emptyHeap.IsHeap();
        cout << "ERROR: IsHeap did not throw exception on empty heap" << endl;
    } catch (const std::length_error& e) {
        isHeapExceptionTest = true;
        cout << "OK: IsHeap threw the expected exception: " << e.what() << endl;
    }
    printTestResult("IsHeap() exception on empty heap", isHeapExceptionTest);
    
    bool heapifyExceptionTest = false;
    try {
        emptyHeap.Heapify();
        cout << "ERROR: Heapify did not throw exception on empty heap" << endl;
    } catch (const std::length_error& e) {
        heapifyExceptionTest = true;
        cout << "OK: Heapify threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Heapify() exception on empty heap", heapifyExceptionTest);
    
    allExceptionsPassed &= (isHeapExceptionTest && heapifyExceptionTest);
    cout << "Overall exceptions test result: " << (allExceptionsPassed ? "SUCCESS" : "FAILURE") << endl;
    
    cout << "\n======= END OF HEAPVEC INT TESTS =======" << endl;
}

// Test HeapVec con stringhe
void testHeapVecString() {
    cout << "\n======= TESTS FOR HEAPVEC CLASS (STRING) =======" << endl;
    
    Vector<string> stringVec(5);
    stringVec[0] = "d"; stringVec[1] = "a"; stringVec[2] = "c";
    stringVec[3] = "b"; stringVec[4] = "e";
    
    HeapVec<string> hs(stringVec);
    
    cout << "Original string vector: ";
    stringVec.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;
    
    cout << "HeapVec after construction: ";
    PrintContainer("hs", hs);
    
    bool isHeapTest = hs.IsHeap();
    printTestResult("IsHeap with strings", isHeapTest);
    
    bool existsTest = hs.Exists("c");
    printTestResult("Exists('c')", existsTest);
    
    string concatenated = hs.Fold<string>([](const string& s, const string& acc) -> string {
        return acc + s;
    }, "");
    
    cout << "Fold (concatenation): " << concatenated << endl;
    
    hs.Sort();
    cout << "After Sort: ";
    PrintContainer("hs", hs);
    
    // Verifica ordinamento alfabetico
    bool isSorted = true;
    for (unsigned long i = 0; i < hs.Size() - 1; i++) {
        if (hs[i] > hs[i + 1]) {
            isSorted = false;
            break;
        }
    }
    printTestResult("Alphabetical sorting", isSorted);
    
    cout << "\n======= END OF HEAPVEC STRING TESTS =======" << endl;
}

// Test PQHeap con interi
void testPQHeapInt() {
    cout << "\n======= TESTS FOR PQHEAP CLASS (INT) =======" << endl;
    
    // Test costruttori
    cout << "\n=== PQHeap Constructors Test ===" << endl;
    bool allConstructorsPassed = true;
    
    PQHeap<int> pq1;
    bool defaultConstructorTest = (pq1.Size() == 0 && pq1.Empty());
    printTestResult("Default constructor", defaultConstructorTest);
    cout << "  - Expected size: 0, Actual size: " << pq1.Size() << endl;
    allConstructorsPassed &= defaultConstructorTest;
    
    Vector<int> sourceVec(5);
    sourceVec[0] = 10; sourceVec[1] = 20; sourceVec[2] = 5;
    sourceVec[3] = 30; sourceVec[4] = 15;
    
    PQHeap<int> pq2(sourceVec);
    bool containerConstructorTest = (pq2.Size() == 5 && !pq2.Empty());
    printTestResult("TraversableContainer constructor", containerConstructorTest);
    cout << "  - Expected size: 5, Actual size: " << pq2.Size() << endl;
    allConstructorsPassed &= containerConstructorTest;
    
    cout << "Original vector: ";
    sourceVec.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    
    cout << "PQHeap after construction: ";
    PrintContainer("pq2", pq2);
    
    cout << "Overall constructors test result: " << (allConstructorsPassed ? "SUCCESS" : "FAILURE") << endl;
    
    // Test operazioni priority queue
    cout << "\n=== PQHeap Priority Queue Operations Test ===" << endl;
    bool allPQTestsPassed = true;
    
    PQHeap<int> pq;
    
    // Test Insert
    cout << "Inserting elements: 10, 20, 5, 30, 15" << endl;
    pq.Insert(10);
    pq.Insert(20);
    pq.Insert(5);
    pq.Insert(30);
    pq.Insert(15);
    
    bool insertTest = (pq.Size() == 5);
    printTestResult("Multiple insertions", insertTest);
    cout << "  - Expected size: 5, Actual size: " << pq.Size() << endl;
    
    PrintContainer("PQ after insertions", pq);
    
    // Test Tip (massimo elemento)
    int tip = pq.Tip();
    bool tipTest = (tip == 30); // Dovrebbe essere il massimo
    printTestResult("Tip (highest priority)", tipTest);
    cout << "  - Expected tip: 30, Actual tip: " << tip << endl;
    
    // Test RemoveTip
    pq.RemoveTip();
    bool removeTipTest = (pq.Size() == 4);
    printTestResult("RemoveTip", removeTipTest);
    cout << "  - Expected size after RemoveTip: 4, Actual size: " << pq.Size() << endl;
    
    int newTip = pq.Tip();
    cout << "  - New tip after RemoveTip: " << newTip << endl;
    
    // Test TipNRemove
    int removedTip = pq.TipNRemove();
    bool tipNRemoveTest = (pq.Size() == 3);
    printTestResult("TipNRemove", tipNRemoveTest);
    cout << "  - Expected size after TipNRemove: 3, Actual size: " << pq.Size() << endl;
    cout << "  - Removed element: " << removedTip << endl;
    
    PrintContainer("PQ after TipNRemove", pq);
    
    // Test Insert con move
    int valueToMove = 25;
    pq.Insert(std::move(valueToMove));
    bool moveInsertTest = (pq.Size() == 4);
    printTestResult("Insert with move", moveInsertTest);
    
    PrintContainer("PQ after move insert", pq);
    
    allPQTestsPassed &= (insertTest && tipTest && removeTipTest && tipNRemoveTest && moveInsertTest);
    
    // Test Change (se disponibile)
    cout << "\n--- Change Priority Test ---" << endl;
    cout << "Current PQ state: ";
    PrintContainer("PQ before change", pq);
    
    if (pq.Size() > 2) {
        cout << "Changing element at index 2 (current value: " << pq[2] << ") to 40..." << endl;
        try {
            pq.Change(2, 40);
            cout << "After change: ";
            PrintContainer("PQ after change", pq);
            cout << "New tip: " << pq.Tip() << endl;
            printTestResult("Change operation", true);
        } catch (const std::out_of_range& e) {
            cout << "Change failed: " << e.what() << endl;
            printTestResult("Change operation", false);
        }
    }
    
    cout << "Overall PQ operations test result: " << (allPQTestsPassed ? "SUCCESS" : "FAILURE") << endl;
    
    // Test eccezioni
    cout << "\n=== PQHeap Exceptions Test ===" << endl;
    bool allExceptionsPassed = true;
    
    PQHeap<int> emptyPQ;
    
    bool tipExceptionTest = false;
    try {
        emptyPQ.Tip();
        cout << "ERROR: Tip did not throw exception on empty PQ" << endl;
    } catch (const std::length_error& e) {
        tipExceptionTest = true;
        cout << "OK: Tip threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Tip() exception on empty PQ", tipExceptionTest);
    
    bool removeTipExceptionTest = false;
    try {
        emptyPQ.RemoveTip();
        cout << "ERROR: RemoveTip did not throw exception on empty PQ" << endl;
    } catch (const std::length_error& e) {
        removeTipExceptionTest = true;
        cout << "OK: RemoveTip threw the expected exception: " << e.what() << endl;
    }
    printTestResult("RemoveTip() exception on empty PQ", removeTipExceptionTest);
    
    bool tipNRemoveExceptionTest = false;
    try {
        emptyPQ.TipNRemove();
        cout << "ERROR: TipNRemove did not throw exception on empty PQ" << endl;
    } catch (const std::length_error& e) {
        tipNRemoveExceptionTest = true;
        cout << "OK: TipNRemove threw the expected exception: " << e.what() << endl;
    }
    printTestResult("TipNRemove() exception on empty PQ", tipNRemoveExceptionTest);
    
    allExceptionsPassed &= (tipExceptionTest && removeTipExceptionTest && tipNRemoveExceptionTest);
    cout << "Overall exceptions test result: " << (allExceptionsPassed ? "SUCCESS" : "FAILURE") << endl;
    
    // Test Clear
    cout << "\n=== PQHeap Clear Test ===" << endl;
    pq.Clear();
    bool clearTest = (pq.Size() == 0 && pq.Empty());
    printTestResult("Clear", clearTest);
    cout << "  - Expected size: 0, Actual size: " << pq.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (pq.Empty() ? "true" : "false") << endl;
    
    cout << "\n======= END OF PQHEAP INT TESTS =======" << endl;
}

// Test PQHeap con stringhe
void testPQHeapString() {
    cout << "\n======= TESTS FOR PQHEAP CLASS (STRING) =======" << endl;
    
    PQHeap<string> pqStr;
    
    cout << "Inserting string elements: 'banana', 'apple', 'cherry', 'date'" << endl;
    pqStr.Insert("banana");
    pqStr.Insert("apple");
    pqStr.Insert("cherry");
    pqStr.Insert("date");
    
    cout << "PQHeap with strings: ";
    PrintContainer("pqStr", pqStr);
    
    string tip = pqStr.Tip();
    cout << "Tip (lexicographically largest): " << tip << endl;
    
    // Rimuovi tutti gli elementi in ordine di priorità
    cout << "Removing elements in priority order:" << endl;
    while (!pqStr.Empty()) {
        string removed = pqStr.TipNRemove();
        cout << "Removed: " << removed << ", Remaining size: " << pqStr.Size() << endl;
    }
    
    cout << "\n======= END OF PQHEAP STRING TESTS =======" << endl;
}

// Funzione principale per eseguire tutti i test Heap e PQ
void runHeapPQTests() {
    cout << "======= STARTING HEAP AND PRIORITY QUEUE TESTS =======" << endl;
    
    testHeapVecInt();
    testHeapVecString();
    testPQHeapInt();
    testPQHeapString();
    
    cout << "\n======= ALL HEAP AND PQ TESTS COMPLETED =======" << endl;
}

// Menu per i test
void allTests() {
    int choice = -1;
    while (choice != 0) {
        cout << endl << "Heap and Priority Queue Test Menu" << endl
             << "0. Exit" << endl
             << "1. Test HeapVec (int)" << endl
             << "2. Test HeapVec (string)" << endl
             << "3. Test PQHeap (int)" << endl
             << "4. Test PQHeap (string)" << endl
             << "5. Run All Heap and PQ Tests" << endl;
        
        string input;
        cin >> input;
        try {
            choice = stoi(input);
        } catch (const std::invalid_argument& e) {
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        if (choice == 0) {
            cout << "Exiting test menu." << endl;
        } else if (choice == 1) {
            testHeapVecInt();
        } else if (choice == 2) {
            testHeapVecString();
        } else if (choice == 3) {
            testPQHeapInt();
        } else if (choice == 4) {
            testPQHeapString();
        } else if (choice == 5) {
            runHeapPQTests();
        } else {
            cout << "Invalid input" << endl;
        }
    }
}