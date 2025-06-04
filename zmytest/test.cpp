
#include "../pq/heap/pqheap.hpp"
#include "../heap/vec/heapvec.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::is_sorted
#include <functional> // Required for std::function
#include <limits>     // For numeric_limits
#include <random>     // For std::random_device, std::mt19937, std::uniform_int_distribution


/* ************************************************************************** */

using namespace std;
using namespace lasd;

/* ************************************************************************** */

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

// Helper for fold operation (sum for numeric types)
template <typename Data>
Data SumFold(const Data& acc, const Data& val) {
    return acc + val;
}

// Helper for fold operation (concatenation for strings)
template <>
std::string SumFold<std::string>(const std::string& acc, const std::string& val) {
    return acc + val;
}

// --- Common Operations Tests (for any container) ---
template <typename Data>
void run_common_container_tests(const string& type_name) {
    cout << "\n--- Common Container Operations Test for " << type_name << " ---" << endl;

    Vector<Data> vec_common(5);
    // Initialize with some data based on type
    if constexpr (std::is_same_v<Data, int>) {
        vec_common[0] = 5; vec_common[1] = 2; vec_common[2] = 8; vec_common[3] = 1; vec_common[4] = 9;
    } else if constexpr (std::is_same_v<Data, float>) {
        vec_common[0] = 5.5f; vec_common[1] = 2.2f; vec_common[2] = 8.8f; vec_common[3] = 1.1f; vec_common[4] = 9.9f;
    } else if constexpr (std::is_same_v<Data, double>) {
        vec_common[0] = 5.5; vec_common[1] = 2.2; vec_common[2] = 8.8; vec_common[3] = 1.1; vec_common[4] = 9.9;
    } else if constexpr (std::is_same_v<Data, string>) {
        vec_common[0] = "apple"; vec_common[1] = "banana"; vec_common[2] = "cherry"; vec_common[3] = "date"; vec_common[4] = "elderberry";
    }

    HeapVec<Data> common_hv(vec_common);
    cout << "Testing common_hv (" << type_name << "):" << endl;
    PrintContainer("common_hv", common_hv);

    // Test of emptiness
    cout << "common_hv is empty: " << (common_hv.Empty() ? "true" : "false") << endl;
    // Reading the dimension
    cout << "common_hv dimension: " << common_hv.Size() << endl;

    // Non-destructive access to initial, final, and specific index
    if (common_hv.Size() > 0) {
        try {
            cout << "common_hv[0] (initial): " << common_hv[0] << endl;
            cout << "common_hv[common_hv.Size() - 1] (final): " << common_hv[common_hv.Size() - 1] << endl;
            if (common_hv.Size() > 2) {
                cout << "common_hv[2] (index 2): " << common_hv[2] << endl;
                // Test mutable access (only if Data is assignable and makes sense)
                if constexpr (std::is_same_v<Data, int>) {
                    Data old_val = common_hv[2];
                    common_hv[2] = 100;
                    cout << "common_hv[2] after change (" << old_val << " -> 100): " << common_hv[2] << endl;
                } else if constexpr (std::is_same_v<Data, float>) {
                    Data old_val = common_hv[2];
                    common_hv[2] = 100.5f;
                    cout << "common_hv[2] after change (" << old_val << " -> 100.5f): " << common_hv[2] << endl;
                } else if constexpr (std::is_same_v<Data, double>) {
                    Data old_val = common_hv[2];
                    common_hv[2] = 100.5;
                    cout << "common_hv[2] after change (" << old_val << " -> 100.5): " << common_hv[2] << endl;
                } else if constexpr (std::is_same_v<Data, string>) {
                    std::string old_val = common_hv[2];
                    common_hv[2] = "zebra";
                    cout << "common_hv[2] after change (" << old_val << " -> zebra): " << common_hv[2] << endl;
                }
                PrintContainer("common_hv after index change", common_hv);
            }
        } catch (const std::out_of_range& e) {
            cerr << "Error accessing element: " << e.what() << endl;
        }
    }

    // Existence control of a given data value
    if constexpr (std::is_same_v<Data, int>) {
        cout << "common_hv contains 8: " << (common_hv.Exists(8) ? "true" : "false") << endl;
        cout << "common_hv contains 77: " << (common_hv.Exists(77) ? "true" : "false") << endl;
    } else if constexpr (std::is_same_v<Data, string>) {
        cout << "common_hv contains 'banana': " << (common_hv.Exists("banana") ? "true" : "false") << endl;
        cout << "common_hv contains 'grape': " << (common_hv.Exists("grape") ? "true" : "false") << endl;
    }


    // Traversal operation
    cout << "Traversing common_hv: ";
    common_hv.Traverse([](const Data& val) { cout << val << " "; });
    cout << endl;

    // Fold operation
    Data initial_fold_val{}; // Default construction for accumulation
    if constexpr (std::is_same_v<Data, std::string>) {
        initial_fold_val = "";
    }
    Data total_fold_result = common_hv.Fold(std::function<Data(const Data&, const Data&)>(SumFold<Data>), initial_fold_val);
    if constexpr (std::is_same_v<Data, std::string>) {
        cout << "Fold (concatenation) of common_hv: " << total_fold_result << endl;
    } else {
        cout << "Fold (sum) of common_hv: " << total_fold_result << endl;
    }


    // Emptying the structure
    common_hv.Clear();
    cout << "common_hv after Clear(): Empty: " << (common_hv.Empty() ? "true" : "false") << ", Size: " << common_hv.Size() << endl;
    cout << endl;
}


// --- Heap Specific Tests ---
template <typename Data>
void run_heap_specific_tests(const string& type_name) {
    cout << "\n--- Heap Specific Operations Test for " << type_name << " ---" << endl;

    Vector<Data> heap_test_vec(7);
    if constexpr (std::is_same_v<Data, int>) {
        heap_test_vec[0] = 4; heap_test_vec[1] = 1; heap_test_vec[2] = 3; heap_test_vec[3] = 2;
        heap_test_vec[4] = 16; heap_test_vec[5] = 9; heap_test_vec[6] = 10;
    } else if constexpr (std::is_same_v<Data, float>) {
        heap_test_vec[0] = 4.4f; heap_test_vec[1] = 1.1f; heap_test_vec[2] = 3.3f; heap_test_vec[3] = 2.2f;
        heap_test_vec[4] = 16.6f; heap_test_vec[5] = 9.9f; heap_test_vec[6] = 10.0f;
    } else if constexpr (std::is_same_v<Data, double>) {
        heap_test_vec[0] = 4.4; heap_test_vec[1] = 1.1; heap_test_vec[2] = 3.3; heap_test_vec[3] = 2.2;
        heap_test_vec[4] = 16.6; heap_test_vec[5] = 9.9; heap_test_vec[6] = 10.0;
    } else if constexpr (std::is_same_v<Data, string>) {
        heap_test_vec[0] = "d"; heap_test_vec[1] = "a"; heap_test_vec[2] = "c"; heap_test_vec[3] = "b";
        heap_test_vec[4] = "p"; heap_test_vec[5] = "i"; heap_test_vec[6] = "j"; // "p" should be largest
    }

    HeapVec<Data> myHeap(heap_test_vec);
    cout << "Initial HeapVec from input vector:" << endl;
    PrintContainer("myHeap (after initial BuildHeap)", myHeap);
    cout << "Is myHeap a heap? " << (myHeap.IsHeap() ? "true" : "false") << endl;

    // Heapify (reconstruction)
    Vector<Data> unheapified_vec(5);
    if constexpr (std::is_same_v<Data, int>) {
        unheapified_vec[0] = 1; unheapified_vec[1] = 5; unheapified_vec[2] = 2;
        unheapified_vec[3] = 8; unheapified_vec[4] = 3;
    } else if constexpr (std::is_same_v<Data, float>) {
        unheapified_vec[0] = 1.1f; unheapified_vec[1] = 5.5f; unheapified_vec[2] = 2.2f;
        unheapified_vec[3] = 8.8f; unheapified_vec[4] = 3.3f;
    } else if constexpr (std::is_same_v<Data, double>) {
        unheapified_vec[0] = 1.1; unheapified_vec[1] = 5.5; unheapified_vec[2] = 2.2;
        unheapified_vec[3] = 8.8; unheapified_vec[4] = 3.3;
    } else if constexpr (std::is_same_v<Data, string>) {
        unheapified_vec[0] = "a"; unheapified_vec[1] = "e"; unheapified_vec[2] = "b";
        unheapified_vec[3] = "h"; unheapified_vec[4] = "c";
    }

    HeapVec<Data> anotherHeap(unheapified_vec);
    cout << "AnotherHeap initially (from non-heap array):" << endl;
    PrintContainer("anotherHeap", anotherHeap);
    cout << "Is anotherHeap a heap? " << (anotherHeap.IsHeap() ? "true" : "false") << endl;
    cout << "Calling Heapify() on anotherHeap..." << endl;
    anotherHeap.Heapify();
    PrintContainer("anotherHeap (after Heapify)", anotherHeap);
    cout << "Is anotherHeap a heap? " << (anotherHeap.IsHeap() ? "true" : "false") << endl;

    // Heap Sort
    cout << "Sorting myHeap..." << endl;
    myHeap.Sort();
    PrintContainer("myHeap (after Sort)", myHeap);
    // Check if sorted
    bool sorted = true;
    for (unsigned long i = 0; i < myHeap.Size() - 1; ++i) {
        if (myHeap[i] > myHeap[i+1]) { // Assumes operator> is defined for Data
            sorted = false;
            break;
        }
    }
    cout << "Is myHeap sorted? " << (sorted ? "true" : "false") << endl;
    cout << endl;
}

// --- PQ Specific Tests (only for int, for simplicity in a combined test) ---
void run_pq_specific_tests() {
    cout << "\n--- Priority Queue Specific Operations Test (int) ---" << endl;
    PQHeap<int> pq;

    // Insert elements
    cout << "Inserting elements into PQHeap: 10, 20, 5, 30, 15" << endl;
    pq.Insert(10);
    pq.Insert(20);
    pq.Insert(5);
    pq.Insert(30);
    pq.Insert(15);
    PrintContainer("PQ after insertions", pq); // Print its underlying heap structure

    // Tip (non-destructive)
    try {
        cout << "Tip (highest priority): " << pq.Tip() << endl;
    } catch (const std::length_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // RemoveTip
    cout << "Removing tip..." << endl;
    try {
        pq.RemoveTip();
        cout << "New Tip after RemoveTip: " << pq.Tip() << endl;
    } catch (const std::length_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    PrintContainer("PQ after RemoveTip", pq);

    // TipNRemove
    cout << "Calling TipNRemove..." << endl;
    try {
        int removed_tip = pq.TipNRemove();
        cout << "Removed element: " << removed_tip << endl;
        cout << "New Tip after TipNRemove: " << pq.Tip() << endl;
    } catch (const std::length_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    PrintContainer("PQ after TipNRemove", pq);

    // Insert (move)
    int val_to_insert = 25;
    cout << "Inserting " << val_to_insert << " (move)..." << endl;
    pq.Insert(std::move(val_to_insert));
    PrintContainer("PQ after move insert", pq);

    // Change priority
    // At this point, pq.Size() should be 4 (5 initial inserts - 1 RemoveTip - 1 TipNRemove + 1 Insert = 4).
    // Valid indices are 0, 1, 2, 3. Index 4 would be out of range.
    cout << "Changing element at index 2 (current value: " << pq[2] << ") to 40..." << endl;
    try {
        pq.Change(2, 40); // Valid index, e.g., 2
    } catch (const std::out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }
    PrintContainer("PQ after change at index 2 to 40", pq);
    cout << "New Tip after change: " << pq.Tip() << endl;

    cout << "Changing element at index 3 (current value: " << pq[3] << ") to 1..." << endl;
    try {
        pq.Change(3, 1); // Valid index, e.g., 3
    } catch (const std::out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }
    PrintContainer("PQ after change at index 3 to 1", pq);
    cout << "New Tip after change: " << pq.Tip() << endl;


    // Clear PQ
    pq.Clear();
    cout << "PQ after Clear(): Empty: " << (pq.Empty() ? "true" : "false") << ", Size: " << pq.Size() << endl;
    cout << endl;
}


// Unified List Tests
void testListAll() {
    cout << "\n======= TESTS FOR LIST CLASS =======" << endl;

    // List Constructors Test
    cout << "\n=== List Constructors Test ===" << endl;
    bool allConstructorsPassed = true;

    List<int> list1;
    bool defaultConstructorTest = (list1.Size() == 0 && list1.Empty());
    printTestResult("Default constructor", defaultConstructorTest);
    cout << "  - Expected size: 0, Actual size: " << list1.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (list1.Empty() ? "true" : "false") << endl;
    allConstructorsPassed &= defaultConstructorTest;

    List<int> sourceList;
    for (unsigned long i = 0; i < 5; i++) {
        sourceList.InsertAtBack(i);
    }

    List<int> list2(sourceList);
    bool copyConstructorSizeTest = (list2.Size() == 5 && !list2.Empty());
    printTestResult("Copy constructor (size)", copyConstructorSizeTest);
    cout << "  - Expected size: 5, Actual size: " << list2.Size() << endl;

    bool elementsCorrect = true;
    for (unsigned long i = 0; i < list2.Size(); i++) {
        if (list2[i] != static_cast<int>(i)) {
            elementsCorrect = false;
            break;
        }
    }
    printTestResult("Copy constructor (content)", elementsCorrect);
    cout << "  - Expected elements: 0 1 2 3 4" << endl;
    cout << "  - Actual elements: ";
    list2.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allConstructorsPassed &= (copyConstructorSizeTest && elementsCorrect);

    List<int> list3(std::move(sourceList));
    bool moveConstructorTest = (list3.Size() == 5 && sourceList.Size() == 0);
    printTestResult("Move constructor", moveConstructorTest);
    cout << "  - Expected size of new list: 5, Actual size: " << list3.Size() << endl;
    cout << "  - Expected size of original list: 0, Actual size: " << sourceList.Size() << endl;
    cout << "  - Elements of new list: ";
    list3.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allConstructorsPassed &= moveConstructorTest;

    cout << "Overall constructors test result: " << (allConstructorsPassed ? "SUCCESS" : "FAILURE") << endl;

    // List Basic Operations Test
    cout << "\n=== List Basic Operations Test ===" << endl;
    bool allOperationsPassed = true;

    List<int> list;

    cout << "Inserting elements..." << endl;
    for (int i = 0; i < 3; i++) {
        list.InsertAtFront(i);
    }
    for (int i = 3; i < 6; i++) {
        list.InsertAtBack(i);
    }

    bool insertTest = (list.Size() == 6);
    printTestResult("Element insertion", insertTest);
    cout << "  - Expected size: 6, Actual size: " << list.Size() << endl;
    cout << "  - Expected elements (pre-order): 2 1 0 3 4 5" << endl;
    cout << "  - Actual elements (pre-order): ";
    list.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    int preOrderExpected[] = {2, 1, 0, 3, 4, 5};
    bool preOrderCorrect = true;
    for (unsigned long i = 0; i < list.Size(); i++) {
        if (list[i] != preOrderExpected[i]) {
            preOrderCorrect = false;
            break;
        }
    }
    printTestResult("Pre-order traversal verification", preOrderCorrect);

    cout << "  - Expected elements (post-order): 5 4 3 0 1 2" << endl;
    cout << "  - Actual elements (post-order): ";
    list.PostOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allOperationsPassed &= (insertTest && preOrderCorrect);

    bool frontTest = (list.Front() == 2);
    bool backTest = (list.Back() == 5);
    printTestResult("Front and Back", frontTest && backTest);
    cout << "  - Expected Front: 2, Actual Front: " << list.Front() << endl;
    cout << "  - Expected Back: 5, Actual Back: " << list.Back() << endl;
    allOperationsPassed &= (frontTest && backTest);

    int frontValue = list.FrontNRemove();
    bool frontRemoveTest = (frontValue == 2 && list.Size() == 5);
    printTestResult("FrontNRemove", frontRemoveTest);
    cout << "  - Expected removed value: 2, Actual value: " << frontValue << endl;
    cout << "  - Expected new size: 5, Actual size: " << list.Size() << endl;

    list.RemoveFromBack();
    bool backRemoveTest = (list.Size() == 4);
    printTestResult("RemoveFromBack", backRemoveTest);
    cout << "  - Expected new size: 4, Actual size: " << list.Size() << endl;

    int afterRemovalExpected[] = {1, 0, 3, 4};
    bool afterRemovalCorrect = true;
    for (unsigned long i = 0; i < list.Size(); i++) {
        if (list[i] != afterRemovalExpected[i]) {
            afterRemovalCorrect = false;
            break;
        }
    }
    printTestResult("List after removals", afterRemovalCorrect);
    cout << "  - Expected elements: 1 0 3 4" << endl;
    cout << "  - Actual elements: ";
    list.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    allOperationsPassed &= (frontRemoveTest && backRemoveTest && afterRemovalCorrect);
    cout << "Overall operations test result: " << (allOperationsPassed ? "SUCCESS" : "FAILURE") << endl;

    // List Map Test
    cout << "\n=== List Map Test ===" << endl;
    bool allMapTestsPassed = true;

    List<int> listMap;
    for (int i = 1; i <= 5; i++) {
        listMap.InsertAtBack(i);
    }

    cout << "Original list: ";
    listMap.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    cout << "Applying PreOrderMap (element * 2)..." << endl;
    listMap.PreOrderMap([](int& x) { x *= 2; });

    int expectedAfterPreMap[] = {2, 4, 6, 8, 10};
    bool preMapCorrect = true;
    for (unsigned long i = 0; i < listMap.Size(); i++) {
        if (listMap[i] != expectedAfterPreMap[i]) {
            preMapCorrect = false;
            break;
        }
    }
    printTestResult("PreOrderMap", preMapCorrect);
    cout << "  - Expected elements: 2 4 6 8 10" << endl;
    cout << "  - Actual elements: ";
    listMap.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    cout << "Applying PostOrderMap (element + 1)..." << endl;
    listMap.PostOrderMap([](int& x) { x += 1; });

    int expectedAfterPostMap[] = {3, 5, 7, 9, 11};
    bool postMapCorrect = true;
    for (unsigned long i = 0; i < listMap.Size(); i++) {
        if (listMap[i] != expectedAfterPostMap[i]) {
            postMapCorrect = false;
            break;
        }
    }
    printTestResult("PostOrderMap", postMapCorrect);
    cout << "  - Expected elements: 3 5 7 9 11" << endl;
    cout << "  - Actual elements: ";
    listMap.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    allMapTestsPassed &= (preMapCorrect && postMapCorrect);
    cout << "Overall Map test result: " << (allMapTestsPassed ? "SUCCESS" : "FAILURE") << endl;

    // List Exceptions Test
    cout << "\n=== List Exceptions Test ===" << endl;
    bool allExceptionsPassed = true;

    List<int> emptyList;

    bool frontExceptionTest = false;
    try {
        emptyList.Front();
        cout << "ERROR: Front did not throw exception on empty list" << endl;
    } catch (const std::length_error& e) {
        frontExceptionTest = true;
        cout << "OK: Front threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Front() exception on empty list", frontExceptionTest);

    bool backExceptionTest = false;
    try {
        emptyList.Back();
        cout << "ERROR: Back did not throw exception on empty list" << endl;
    } catch (const std::length_error& e) {
        backExceptionTest = true;
        cout << "OK: Back threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Back() exception on empty list", backExceptionTest);

    bool removeExceptionTest = false;
    try {
        emptyList.RemoveFromFront();
        cout << "ERROR: RemoveFromFront did not throw exception on empty list" << endl;
    } catch (const std::length_error& e) {
        removeExceptionTest = true;
        cout << "OK: RemoveFromFront threw the expected exception: " << e.what() << endl;
    }
    printTestResult("RemoveFromFront() exception on empty list", removeExceptionTest);

    List<int> smallList;
    smallList.InsertAtBack(1);

    bool indexExceptionTest = false;
    try {
        smallList[1];
        cout << "ERROR: operator[] did not throw exception on out of range index" << endl;
    } catch (const std::out_of_range& e) {
        indexExceptionTest = true;
        cout << "OK: operator[] threw the expected exception: " << e.what() << endl;
    }
    printTestResult("operator[] exception with out of range index", indexExceptionTest);

    allExceptionsPassed &= (frontExceptionTest && backExceptionTest && removeExceptionTest && indexExceptionTest);
    cout << "Overall exceptions test result: " << (allExceptionsPassed ? "SUCCESS" : "FAILURE") << endl;

    // List with Strings Test
    cout << "\n=== List with Strings Test ===" << endl;
    bool allStringTestsPassed = true;

    List<string> stringList;

    stringList.InsertAtBack("one");
    stringList.InsertAtBack("two");
    stringList.InsertAtFront("zero");

    bool stringInsertTest = (stringList.Size() == 3);
    printTestResult("String insertion", stringInsertTest);
    cout << "  - Expected size: 3, Actual size: " << stringList.Size() << endl;
    cout << "  - Expected elements: zero one two" << endl;
    cout << "  - Actual elements: ";
    stringList.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    stringList.Map([](string& s) {
        for (char& c : s) {
            c = toupper(c);
        }
    });

    string expectedAfterMap[] = {"ZERO", "ONE", "TWO"};
    bool mapCorrect = true;
    for (unsigned long i = 0; i < stringList.Size(); i++) {
        if (stringList[i] != expectedAfterMap[i]) {
            mapCorrect = false;
            break;
        }
    }
    printTestResult("Map on strings (uppercase transformation)", mapCorrect);
    cout << "  - Expected elements: ZERO ONE TWO" << endl;
    cout << "  - Actual elements: ";
    stringList.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    string result = stringList.Fold<string>([](const string& s, const string& acc) -> string {
        return acc + s;
    }, "");

    bool foldCorrect = (result == "ZEROONETWO");
    printTestResult("Fold on strings (concatenation)", foldCorrect);
    cout << "  - Expected result: ZEROONETWO, Actual result: " << result << endl;

    allStringTestsPassed &= (stringInsertTest && mapCorrect && foldCorrect);
    cout << "Overall strings test result: " << (allStringTestsPassed ? "SUCCESS" : "FAILURE") << endl;

    // List Fold Test
    cout << "\n=== List Fold Test ===" << endl;
    bool allFoldTestsPassed = true;

    List<int> listFold;
    for (int i = 1; i <= 5; i++) {
        listFold.InsertAtBack(i);
    }

    int sum = listFold.PreOrderFold<int>([](const int& x, const int& acc) -> int {
        return acc + x;
    }, 0);

    bool sumCorrect = (sum == 15);
    printTestResult("PreOrderFold (sum)", sumCorrect);
    cout << "  - Expected sum: 15, Actual sum: " << sum << endl;

    int product = listFold.PostOrderFold<int>([](const int& x, const int& acc) -> int {
        return acc * x;
    }, 1);

    bool productCorrect = (product == 120);
    printTestResult("PostOrderFold (product)", productCorrect);
    cout << "  - Expected product: 120, Actual product: " << product << endl;

    bool existsTest1 = listFold.Exists(3);
    bool existsTest2 = !listFold.Exists(10);
    printTestResult("Exists(3) [element present]", existsTest1);
    cout << "  - Expected result: true, Actual result: " << (existsTest1 ? "true" : "false") << endl;

    printTestResult("Exists(10) [element not present]", existsTest2);
    cout << "  - Expected result: false, Actual result: " << (!existsTest2 ? "true" : "false") << endl;

    allFoldTestsPassed &= (sumCorrect && productCorrect && existsTest1 && existsTest2);
    cout << "Overall Fold test result: " << (allFoldTestsPassed ? "SUCCESS" : "FAILURE") << endl;

    cout << "\n======= END OF LIST TESTS =======" << endl;
}

// Unified Vector Tests
void testVectorAll() {
    cout << "\n======= TESTS FOR VECTOR CLASS =======" << endl;

    // Vector Constructors Test
    cout << "\n=== Vector Constructors Test ===" << endl;
    bool allConstructorsPassed = true;

    Vector<int> v1;
    bool defaultConstructorTest = (v1.Size() == 0 && v1.Empty());
    printTestResult("Default constructor", defaultConstructorTest);
    cout << "  - Expected size: 0, Actual size: " << v1.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (v1.Empty() ? "true" : "false") << endl;
    allConstructorsPassed &= defaultConstructorTest;

    Vector<int> v2(5);
    bool sizeConstructorTest = (v2.Size() == 5 && !v2.Empty());
    printTestResult("Size constructor", sizeConstructorTest);
    cout << "  - Expected size: 5, Actual size: " << v2.Size() << endl;
    cout << "  - Expected empty: false, Actual empty: " << (v2.Empty() ? "true" : "false") << endl;

    bool initializationCorrect = true;
    for (unsigned long i = 0; i < v2.Size(); i++) {
        if (v2[i] != 0) {
            initializationCorrect = false;
            break;
        }
    }
    printTestResult("Element initialization", initializationCorrect);
    cout << "  - All elements should be 0" << endl;
    allConstructorsPassed &= (sizeConstructorTest && initializationCorrect);

    List<int> sourceList;
    for (unsigned long i = 0; i < 5; i++) {
        sourceList.InsertAtBack(static_cast<int>(i));
    }

    Vector<int> v3(sourceList);
    bool containerConstructorTest = (v3.Size() == 5);
    printTestResult("TraversableContainer constructor (size)", containerConstructorTest);
    cout << "  - Expected size: 5, Actual size: " << v3.Size() << endl;

    bool elementsCorrect = true;
    for (unsigned long i = 0; i < v3.Size(); i++) {
        if (v3[i] != static_cast<int>(i)) {
            elementsCorrect = false;
            break;
        }
    }
    printTestResult("TraversableContainer constructor (content)", elementsCorrect);
    cout << "  - Expected elements: 0 1 2 3 4" << endl;
    cout << "  - Actual elements: ";
    v3.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allConstructorsPassed &= (containerConstructorTest && elementsCorrect);

    Vector<int> v4(v3);
    bool copyConstructorTest = (v4.Size() == v3.Size() && v4 == v3);
    printTestResult("Copy constructor", copyConstructorTest);
    cout << "  - Expected size: " << v3.Size() << ", Actual size: " << v4.Size() << endl;
    cout << "  - Identical elements: " << (v4 == v3 ? "true" : "false") << endl;
    allConstructorsPassed &= copyConstructorTest;

    Vector<int> v5(std::move(v4));
    bool moveConstructorTest = (v5.Size() == 5 && v4.Size() == 0);
    printTestResult("Move constructor", moveConstructorTest);
    cout << "  - Expected size of new vector: 5, Actual size: " << v5.Size() << endl;
    cout << "  - Expected size of original vector: 0, Actual size: " << v4.Size() << endl;
    cout << "  - Elements of new vector: ";
    v5.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allConstructorsPassed &= moveConstructorTest;

    cout << "Overall constructors test result: " << (allConstructorsPassed ? "SUCCESS" : "FAILURE") << endl;

    // Vector Basic Operations Test
    cout << "\n=== Vector Basic Operations Test ===" << endl;
    bool allOperationsPassed = true;

    Vector<int> v(5);
    for (unsigned long i = 0; i < v.Size(); i++) {
        v[i] = static_cast<int>(i) + 1;
    }

    bool operatorAccessTest = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != static_cast<int>(i) + 1) {
            operatorAccessTest = false;
            break;
        }
    }
    printTestResult("operator[] (read)", operatorAccessTest);
    cout << "  - Expected elements: 1 2 3 4 5" << endl;
    cout << "  - Actual elements: ";
    for (unsigned long i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    allOperationsPassed &= operatorAccessTest;

    for (unsigned long i = 0; i < v.Size(); i++) {
        v[i] = v[i] * 2;
    }

    bool operatorWriteTest = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2) {
            operatorWriteTest = false;
            break;
        }
    }
    printTestResult("operator[] (write)", operatorWriteTest);
    cout << "  - Expected elements after modification: 2 4 6 8 10" << endl;
    cout << "  - Actual elements: ";
    for (unsigned long i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    allOperationsPassed &= operatorWriteTest;

    bool frontTest = (v.Front() == 2);
    bool backTest = (v.Back() == 10);
    printTestResult("Front", frontTest);
    cout << "  - Expected Front: 2, Actual Front: " << v.Front() << endl;

    printTestResult("Back", backTest);
    cout << "  - Expected Back: 10, Actual Back: " << v.Back() << endl;
    allOperationsPassed &= (frontTest && backTest);

    v.Resize(7);
    bool resizeGrowTest = (v.Size() == 7);
    printTestResult("Resize (grow)", resizeGrowTest);
    cout << "  - Expected size: 7, Actual size: " << v.Size() << endl;
    cout << "  - Initial elements preserved: ";
    bool elementsPreservedGrow = true;
    for (unsigned long i = 0; i < 5; i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2) {
            elementsPreservedGrow = false;
            break;
        }
    }
    printTestResult("Initial elements preserved after growth", elementsPreservedGrow);
    cout << "  - Elements: ";
    for (unsigned long i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    allOperationsPassed &= (resizeGrowTest && elementsPreservedGrow);

    v.Resize(3);
    bool resizeShrinkTest = (v.Size() == 3);
    printTestResult("Resize (shrink)", resizeShrinkTest);
    cout << "  - Expected size: 3, Actual size: " << v.Size() << endl;

    bool elementsPreservedShrink = true;
    for (unsigned long i = 0; i < v.Size(); i++) {
        if (v[i] != (static_cast<int>(i) + 1) * 2) {
            elementsPreservedShrink = false;
            break;
        }
    }
    printTestResult("Initial elements preserved after shrinking", elementsPreservedShrink);
    cout << "  - Expected elements: 2 4 6" << endl;
    cout << "  - Actual elements: ";
    for (unsigned long i = 0; i < v.Size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    allOperationsPassed &= (resizeShrinkTest && elementsPreservedShrink);

    v.Clear();
    bool clearTest = (v.Size() == 0 && v.Empty());
    printTestResult("Clear", clearTest);
    cout << "  - Expected size: 0, Actual size: " << v.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (v.Empty() ? "true" : "false") << endl;
    allOperationsPassed &= clearTest;

    cout << "Overall operations test result: " << (allOperationsPassed ? "SUCCESS" : "FAILURE") << endl;

    // Vector Exceptions Test
    cout << "\n=== Vector Exceptions Test ===" << endl;
    bool allExceptionsPassed = true;

    Vector<int> emptyVector;

    bool frontExceptionTest = false;
    try {
        emptyVector.Front();
        cout << "ERROR: Front did not throw exception on empty vector" << endl;
    } catch (const std::length_error& e) {
        frontExceptionTest = true;
        cout << "OK: Front threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Front() exception on empty vector", frontExceptionTest);

    bool backExceptionTest = false;
    try {
        emptyVector.Back();
        cout << "ERROR: Back did not throw exception on empty vector" << endl;
    } catch (const std::length_error& e) {
        backExceptionTest = true;
        cout << "OK: Back threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Back() exception on empty vector", backExceptionTest);

    Vector<int> smallVector(1);
    smallVector[0] = 1;

    bool indexExceptionTest = false;
    try {
        smallVector[1];
        cout << "ERROR: operator[] did not throw exception on out of range index" << endl;
    } catch (const std::out_of_range& e) {
        indexExceptionTest = true;
        cout << "OK: operator[] threw the expected exception: " << e.what() << endl;
    }
    printTestResult("operator[] exception with out of range index", indexExceptionTest);

    allExceptionsPassed &= (frontExceptionTest && backExceptionTest && indexExceptionTest);
    cout << "Overall exceptions test result: " << (allExceptionsPassed ? "SUCCESS" : "FAILURE") << endl;

    // Vector Traverse and Map Test
    cout << "\n=== Vector Traverse and Map Test ===" << endl;
    bool allTraverseMapTestsPassed = true;

    Vector<int> vTM(5);
    for (unsigned long i = 0; i < vTM.Size(); i++) {
        vTM[i] = static_cast<int>(i) + 1;
    }

    cout << "PreOrderTraverse test:" << endl;
    cout << "  - Expected elements: 1 2 3 4 5" << endl;
    cout << "  - Actual elements: ";
    vTM.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    cout << "PostOrderTraverse test:" << endl;
    cout << "  - Expected elements: 5 4 3 2 1" << endl;
    cout << "  - Actual elements: ";
    vTM.PostOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    vTM.Map([](int& x) { x *= 2; });

    bool mapTest = true;
    for (unsigned long i = 0; i < vTM.Size(); i++) {
        if (vTM[i] != (static_cast<int>(i) + 1) * 2) {
            mapTest = false;
            break;
        }
    }
    printTestResult("Map (element * 2)", mapTest);
    cout << "  - Expected elements: 2 4 6 8 10" << endl;
    cout << "  - Actual elements: ";
    vTM.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    vTM.PreOrderMap([](int& x) { x += 1; });

    bool preOrderMapTest = true;
    for (unsigned long i = 0; i < vTM.Size(); i++) {
        if (vTM[i] != (static_cast<int>(i) + 1) * 2 + 1) {
            preOrderMapTest = false;
            break;
        }
    }
    printTestResult("PreOrderMap (element + 1)", preOrderMapTest);
    cout << "  - Expected elements: 3 5 7 9 11" << endl;
    cout << "  - Actual elements: ";
    vTM.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    vTM.PostOrderMap([](int& x) { x -= 1; });

    bool postOrderMapTest = true;
    for (unsigned long i = 0; i < vTM.Size(); i++) {
        if (vTM[i] != (static_cast<int>(i) + 1) * 2) {
            postOrderMapTest = false;
            break;
        }
    }
    printTestResult("PostOrderMap (element - 1)", postOrderMapTest);
    cout << "  - Expected elements: 2 4 6 8 10" << endl;
    cout << "  - Actual elements: ";
    vTM.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    allTraverseMapTestsPassed &= (mapTest && preOrderMapTest && postOrderMapTest);
    cout << "Overall Traverse and Map test result: " << (allTraverseMapTestsPassed ? "SUCCESS" : "FAILURE") << endl;

    // Vector Fold Test
    cout << "\n=== Vector Fold Test ===" << endl;
    bool allFoldTestsPassed = true;

    Vector<int> vFold(5);
    for (unsigned long i = 0; i < vFold.Size(); i++) {
        vFold[i] = static_cast<int>(i) + 1;
    }

    int sum = vFold.Fold<int>([](const int& x, const int& acc) -> int {
        return acc + x;
    }, 0);

    bool sumCorrect = (sum == 15);
    printTestResult("Fold (sum)", sumCorrect);
    cout << "  - Expected sum: 15, Actual sum: " << sum << endl;

    int product = vFold.PreOrderFold<int>([](const int& x, const int& acc) -> int {
        return acc * x;
    }, 1);

    bool productCorrect = (product == 120);
    printTestResult("PreOrderFold (product)", productCorrect);
    cout << "  - Expected product: 120, Actual product: " << product << endl;

    string indices = vFold.PostOrderFold<string>([](const int& x, const string& acc) -> string {
        return acc + to_string(x);
    }, "");

    bool indicesCorrect = (indices == "54321");
    printTestResult("PostOrderFold (index concatenation)", indicesCorrect);
    cout << "  - Expected indices: 54321, Actual indices: " << indices << endl;

    bool existsTest1 = vFold.Exists(3);
    bool existsTest2 = !vFold.Exists(10);
    printTestResult("Exists(3) [element present]", existsTest1);
    cout << "  - Expected result: true, Actual result: " << (existsTest1 ? "true" : "false") << endl;

    printTestResult("Exists(10) [element not present]", existsTest2);
    cout << "  - Expected result: false, Actual result: " << (!existsTest2 ? "true" : "false") << endl;

    allFoldTestsPassed &= (sumCorrect && productCorrect && existsTest1 && existsTest2);
    cout << "Overall Fold test result: " << (allFoldTestsPassed ? "SUCCESS" : "FAILURE") << endl;

    // SortableVector Test
    cout << "\n=== SortableVector Test ===" << endl;
    bool allSortableVectorTestsPassed = true;

    SortableVector<int> sv(7); // Assuming SortableVector is a concrete class derived from Vector
    sv[0] = 7;
    sv[1] = 3;
    sv[2] = 1;
    sv[3] = 5;
    sv[4] = 2;
    sv[5] = 6;
    sv[6] = 4;

    cout << "Unsorted vector: ";
    sv.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    sv.Sort();

    bool sortTest = true;
    for (unsigned long i = 0; i < sv.Size(); i++) {
        if (sv[i] != static_cast<int>(i) + 1) {
            sortTest = false;
            break;
        }
    }
    printTestResult("Sort", sortTest);
    cout << "  - Expected elements after sorting: 1 2 3 4 5 6 7" << endl;
    cout << "  - Actual elements: ";
    sv.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    SortableVector<string> svStr(4);
    svStr[0] = "zebra";
    svStr[1] = "alpha";
    svStr[2] = "delta";
    svStr[3] = "beta";

    cout << "Unsorted string vector: ";
    svStr.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    svStr.Sort();

    string expectedOrderStr[] = {"alpha", "beta", "delta", "zebra"};
    bool sortStrTest = true;
    for (unsigned long i = 0; i < svStr.Size(); i++) {
        if (svStr[i] != expectedOrderStr[i]) {
            sortStrTest = false;
            break;
        }
    }
    printTestResult("String sort", sortStrTest);
    cout << "  - Expected elements after sorting: alpha beta delta zebra" << endl;
    cout << "  - Actual elements: ";
    svStr.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    allSortableVectorTestsPassed &= (sortTest && sortStrTest);
    cout << "Overall SortableVector test result: " << (allSortableVectorTestsPassed ? "SUCCESS" : "FAILURE") << endl;

    cout << "\n======= END OF VECTOR TESTS =======" << endl;
}

template <typename SetType>
void testSetGeneric(const std::string& setName) {
    cout << "\n======= TESTS FOR " << setName << " CLASS =======" << endl;

    // Constructors and Basic Operations Test
    cout << "\n=== Constructors and Basic Operations Test ===" << endl;
    bool allBasicTestsPassed = true;

    SetType s1;
    bool defaultConstructorTest = (s1.Size() == 0 && s1.Empty());
    printTestResult("Default constructor", defaultConstructorTest);
    cout << "  - Expected size: 0, Actual size: " << s1.Size() << endl;
    cout << "  - Expected empty: true, Actual empty: " << (s1.Empty() ? "true" : "false") << endl;
    allBasicTestsPassed &= defaultConstructorTest;

    bool insertionTest = true;
    s1.Insert(5);
    s1.Insert(3);
    s1.Insert(7);
    s1.Insert(1);
    s1.Insert(9);

    bool sizeAfterInsertTest = (s1.Size() == 5);
    printTestResult("Size after insertions", sizeAfterInsertTest);
    cout << "  - Expected size: 5, Actual size: " << s1.Size() << endl;

    int expectedOrderInt[] = {1, 3, 5, 7, 9};
    cout << "  - Expected elements (in order): 1 3 5 7 9" << endl;
    cout << "  - Actual elements: ";
    s1.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    bool orderTestInt = true;
    for (unsigned long i = 0; i < s1.Size(); i++) {
        if (s1[i] != expectedOrderInt[i]) {
            orderTestInt = false;
            break;
        }
    }
    printTestResult("Element order", orderTestInt);
    allBasicTestsPassed &= (insertionTest && sizeAfterInsertTest && orderTestInt);

    bool duplicateTest = !s1.Insert(5);
    bool sizeAfterDuplicateTest = (s1.Size() == 5);
    printTestResult("Duplicate insertion (should fail)", duplicateTest);
    printTestResult("Size after duplicate insertion attempt", sizeAfterDuplicateTest);
    cout << "  - Expected size: 5, Actual size: " << s1.Size() << endl;
    allBasicTestsPassed &= (duplicateTest && sizeAfterDuplicateTest);

    bool removeTest = s1.Remove(3);
    bool sizeAfterRemoveTest = (s1.Size() == 4);
    printTestResult("Element removal", removeTest);
    printTestResult("Size after removal", sizeAfterRemoveTest);
    cout << "  - Expected size: 4, Actual size: " << s1.Size() << endl;

    int expectedOrderAfterRemoveInt[] = {1, 5, 7, 9};
    bool orderAfterRemoveTestInt = true;
    for (unsigned long i = 0; i < s1.Size(); i++) {
        if (s1[i] != expectedOrderAfterRemoveInt[i]) {
            orderAfterRemoveTestInt = false;
            break;
        }
    }
    printTestResult("Order after removal", orderAfterRemoveTestInt);
    cout << "  - Expected elements: 1 5 7 9" << endl;
    cout << "  - Actual elements: ";
    s1.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    bool removeNonExistentTest = !s1.Remove(3);
    printTestResult("Non-existent element removal", removeNonExistentTest);
    allBasicTestsPassed &= (removeTest && sizeAfterRemoveTest && orderAfterRemoveTestInt && removeNonExistentTest);

    bool existsTest1 = s1.Exists(5);
    bool existsTest2 = !s1.Exists(3);
    printTestResult("Exists(5) [element present]", existsTest1);
    printTestResult("Exists(3) [element not present]", existsTest2);
    allBasicTestsPassed &= (existsTest1 && existsTest2);

    SetType s2(s1);
    bool copyConstructorTest = (s2.Size() == s1.Size());
    printTestResult("Copy constructor (size)", copyConstructorTest);
    cout << "  - Expected size: " << s1.Size() << ", Actual size: " << s2.Size() << endl;

    bool copyElementsTest = true;
    for (unsigned long i = 0; i < s2.Size(); i++) {
        if (s2[i] != s1[i]) {
            copyElementsTest = false;
            break;
        }
    }
    printTestResult("Copy constructor (content)", copyElementsTest);
    cout << "  - Expected elements: 1 5 7 9" << endl;
    cout << "  - Actual elements: ";
    s2.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allBasicTestsPassed &= (copyConstructorTest && copyElementsTest);

    s2.Clear();
    bool clearTest = (s2.Size() == 0 && s2.Empty());
    printTestResult("Clear", clearTest);
    cout << "  - Expected size: 0, Actual size: " << s2.Size() << endl;
    allBasicTestsPassed &= clearTest;

    cout << "Overall constructors and basic operations test result: " << (allBasicTestsPassed ? "SUCCESS" : "FAILURE") << endl;

    // OrderedDictionary Operations Test
    cout << "\n=== OrderedDictionary Operations Test ===" << endl;
    bool allOrderedDictTestsPassed = true;

    SetType sOrdered;
    int values[] = {10, 5, 15, 3, 7, 12, 20};
    for (int val : values) {
        sOrdered.Insert(val);
    }

    cout << "Test set: ";
    sOrdered.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    bool minTest = (sOrdered.Min() == 3);
    bool maxTest = (sOrdered.Max() == 20);
    printTestResult("Min", minTest);
    cout << "  - Expected Min: 3, Actual Min: " << sOrdered.Min() << endl;
    printTestResult("Max", maxTest);
    cout << "  - Expected Max: 20, Actual Max: " << sOrdered.Max() << endl;
    allOrderedDictTestsPassed &= (minTest && maxTest);

    bool predecessorTest = (sOrdered.Predecessor(10) == 7);
    bool successorTest = (sOrdered.Successor(10) == 12);
    printTestResult("Predecessor(10)", predecessorTest);
    cout << "  - Expected Predecessor: 7, Actual Predecessor: " << sOrdered.Predecessor(10) << endl;
    printTestResult("Successor(10)", successorTest);
    cout << "  - Expected Successor: 12, Actual Successor: " << sOrdered.Successor(10) << endl;
    allOrderedDictTestsPassed &= (predecessorTest && successorTest);

    int minValue = sOrdered.MinNRemove();
    bool minNRemoveTest = (minValue == 3 && sOrdered.Size() == 6 && !sOrdered.Exists(3));
    printTestResult("MinNRemove", minNRemoveTest);
    cout << "  - Expected removed Min: 3, Actual removed Min: " << minValue << endl;
    cout << "  - Elements after MinNRemove: ";
    sOrdered.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allOrderedDictTestsPassed &= minNRemoveTest;

    int maxValue = sOrdered.MaxNRemove();
    bool maxNRemoveTest = (maxValue == 20 && sOrdered.Size() == 5 && !sOrdered.Exists(20));
    printTestResult("MaxNRemove", maxNRemoveTest);
    cout << "  - Expected removed Max: 20, Actual removed Max: " << maxValue << endl;
    cout << "  - Elements after MaxNRemove: ";
    sOrdered.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allOrderedDictTestsPassed &= maxNRemoveTest;

    int predValue = sOrdered.PredecessorNRemove(12);
    bool predNRemoveTest = (predValue == 10 && sOrdered.Size() == 4 && !sOrdered.Exists(10));
    printTestResult("PredecessorNRemove(12)", predNRemoveTest);
    cout << "  - Expected removed Predecessor: 10, Actual removed Predecessor: " << predValue << endl;
    cout << "  - Elements after PredecessorNRemove: ";
    sOrdered.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allOrderedDictTestsPassed &= predNRemoveTest;

    int succValue = sOrdered.SuccessorNRemove(7);
    bool succNRemoveTest = (succValue == 12 && sOrdered.Size() == 3 && !sOrdered.Exists(12));
    printTestResult("SuccessorNRemove(7)", succNRemoveTest);
    cout << "  - Expected removed Successor: 12, Actual removed Successor: " << succValue << endl;
    cout << "  - Elements after SuccessorNRemove: ";
    sOrdered.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allOrderedDictTestsPassed &= succNRemoveTest;

    sOrdered.RemoveMin();
    bool removeMinTest = (sOrdered.Size() == 2 && !sOrdered.Exists(5) && sOrdered.Min() == 7);
    printTestResult("RemoveMin", removeMinTest);
    cout << "  - Elements after RemoveMin: ";
    sOrdered.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allOrderedDictTestsPassed &= removeMinTest;

    sOrdered.RemoveMax();
    bool removeMaxTest = (sOrdered.Size() == 1 && !sOrdered.Exists(15) && sOrdered.Max() == 7);
    printTestResult("RemoveMax", removeMaxTest);
    cout << "  - Elements after RemoveMax: ";
    sOrdered.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;
    allOrderedDictTestsPassed &= removeMaxTest;

    cout << "Overall OrderedDictionary operations test result: " << (allOrderedDictTestsPassed ? "SUCCESS" : "FAILURE") << endl;

    // Set Exceptions Test
    cout << "\n=== Exceptions Test ===" << endl;
    bool allExceptionsPassed = true;

    SetType emptySet;

    bool minExceptionTest = false;
    try {
        emptySet.Min();
        cout << "ERROR: Min did not throw exception on empty set" << endl;
    } catch (const std::length_error& e) {
        minExceptionTest = true;
        cout << "OK: Min threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Min() exception on empty set", minExceptionTest);

    bool maxExceptionTest = false;
    try {
        emptySet.Max();
        cout << "ERROR: Max did not throw exception on empty set" << endl;
    } catch (const std::length_error& e) {
        maxExceptionTest = true;
        cout << "OK: Max threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Max() exception on empty set", maxExceptionTest);

    bool removeMinExceptionTest = false;
    try {
        emptySet.RemoveMin();
        cout << "ERROR: RemoveMin did not throw exception on empty set" << endl;
    } catch (const std::length_error& e) {
        removeMinExceptionTest = true;
        cout << "OK: RemoveMin threw the expected exception: " << e.what() << endl;
    }
    printTestResult("RemoveMin() exception on empty set", removeMinExceptionTest);

    bool predecessorExceptionTest = false;
    try {
        emptySet.Predecessor(5);
        cout << "ERROR: Predecessor did not throw exception on empty set" << endl;
    } catch (const std::length_error& e) {
        predecessorExceptionTest = true;
        cout << "OK: Predecessor threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Predecessor() exception on empty set", predecessorExceptionTest);

    SetType nonEmptySet;
    nonEmptySet.Insert(5);
    nonEmptySet.Insert(10);

    bool predecessorNotFoundTest = false;
    try {
        nonEmptySet.Predecessor(5);
        cout << "ERROR: Predecessor did not throw exception when no predecessor exists" << endl;
    } catch (const std::length_error& e) {
        predecessorNotFoundTest = true;
        cout << "OK: Predecessor threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Predecessor() exception when no predecessor exists", predecessorNotFoundTest);

    bool successorNotFoundTest = false;
    try {
        nonEmptySet.Successor(10);
        cout << "ERROR: Successor did not throw exception when no successor exists" << endl;
    } catch (const std::length_error& e) {
        successorNotFoundTest = true;
        cout << "OK: Successor threw the expected exception: " << e.what() << endl;
    }
    printTestResult("Successor() exception when no successor exists", successorNotFoundTest);

    allExceptionsPassed &= (minExceptionTest && maxExceptionTest && removeMinExceptionTest &&
                     predecessorExceptionTest && predecessorNotFoundTest && successorNotFoundTest);

    cout << "Overall exceptions test result: " << (allExceptionsPassed ? "SUCCESS" : "FAILURE") << endl;

    // Constructors from Containers Test
    cout << "\n=== Constructors from Containers Test ===" << endl;
    bool allContainerConstructorsPassed = true;

    List<int> listSource;
    listSource.InsertAtBack(5);
    listSource.InsertAtBack(3);
    listSource.InsertAtBack(7);
    listSource.InsertAtBack(3);
    listSource.InsertAtBack(1);
    listSource.InsertAtBack(5);

    SetType setFromList(listSource);
    bool sizeTestFromList = (setFromList.Size() == 4);
    printTestResult("TraversableContainer constructor (duplicate removal)", sizeTestFromList);
    cout << "  - Expected size: 4, Actual size: " << setFromList.Size() << endl;

    int expectedOrderFromList[] = {1, 3, 5, 7};
    bool orderTestFromList = true;
    for (unsigned long i = 0; i < setFromList.Size(); i++) {
        if (setFromList[i] != expectedOrderFromList[i]) {
            orderTestFromList = false;
            break;
        }
    }
    printTestResult("Element order after construction from TraversableContainer", orderTestFromList);
    cout << "  - Expected elements: 1 3 5 7" << endl;
    cout << "  - Actual elements: ";
    setFromList.PreOrderTraverse([](const int& x) { cout << x << " "; });
    cout << endl;

    allContainerConstructorsPassed &= (sizeTestFromList && orderTestFromList);
    cout << "Overall constructors from containers test result: " << (allContainerConstructorsPassed ? "SUCCESS" : "FAILURE") << endl;

    cout << "\n======= END OF " << setName << " TESTS =======" << endl;
}

// Function to test Set implementations with strings specifically
template <typename SetType>
void testStringSetGeneric(const std::string& setName) {
    cout << "\n======= TESTS FOR " << setName << " CLASS with STRINGS =======" << endl;
    bool allStringTestsPassed = true;

    SetType stringSet;
    stringSet.Insert("banana");
    stringSet.Insert("apple");
    stringSet.Insert("cherry");
    stringSet.Insert("date");

    bool sizeTest = (stringSet.Size() == 4);
    printTestResult("Size after string insertion", sizeTest);
    cout << "  - Expected size: 4, Actual size: " << stringSet.Size() << endl;

    string expectedOrder[] = {"apple", "banana", "cherry", "date"};
    bool orderTest = true;
    for (unsigned long i = 0; i < stringSet.Size(); i++) {
        if (stringSet[i] != expectedOrder[i]) {
            orderTest = false;
            break;
        }
    }
    printTestResult("Alphabetical order", orderTest);
    cout << "  - Expected elements: apple banana cherry date" << endl;
    cout << "  - Actual elements: ";
    stringSet.PreOrderTraverse([](const string& s) { cout << s << " "; });
    cout << endl;

    bool minTest = (stringSet.Min() == "apple");
    bool maxTest = (stringSet.Max() == "date");
    printTestResult("Min (first string alphabetically)", minTest);
    cout << "  - Expected Min: apple, Actual Min: " << stringSet.Min() << endl;
    printTestResult("Max (last string alphabetically)", maxTest);
    cout << "  - Expected Max: date, Actual Max: " << stringSet.Max() << endl;

    bool predecessorTestStr = (stringSet.Predecessor("cherry") == "banana");
    bool successorTestStr = (stringSet.Successor("banana") == "cherry");
    printTestResult("Predecessor of 'cherry'", predecessorTestStr);
    cout << "  - Expected Predecessor: banana, Actual Predecessor: " << stringSet.Predecessor("cherry") << endl;
    printTestResult("Successor of 'banana'", successorTestStr);
    cout << "  - Expected Successor: cherry, Actual Successor: " << stringSet.Successor("banana") << endl;

    allStringTestsPassed &= (sizeTest && orderTest && minTest && maxTest && predecessorTestStr && successorTestStr);
    cout << "Overall strings test result: " << (allStringTestsPassed ? "SUCCESS" : "FAILURE") << endl;
    cout << "\n======= END OF " << setName << " TESTS with STRINGS =======" << endl;
}

void compareSetImplementations() {
    cout << "\n======= IMPLEMENTATION COMPARISON =======" << endl;

    SetLst<int> setLst;
    SetVec<int> setVec;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 1000);

    const int numElements = 1000;

    cout << "Inserting " << numElements << " elements in both implementations..." << endl;

    for (int i = 0; i < numElements; i++) {
        int value = distr(gen);
        setLst.Insert(value);
        setVec.Insert(value);
    }

    cout << "SetLst size: " << setLst.Size() << endl;
    cout << "SetVec size: " << setVec.Size() << endl;

    bool sameSizeTest = (setLst.Size() == setVec.Size());
    printTestResult("Same size after random insertions", sameSizeTest);

    bool sameMinTest = (setLst.Min() == setVec.Min());
    bool sameMaxTest = (setLst.Max() == setVec.Max());
    printTestResult("Same minimum value", sameMinTest);
    cout << "  - SetLst Min: " << setLst.Min() << ", SetVec Min: " << setVec.Min() << endl;
    printTestResult("Same maximum value", sameMaxTest);
    cout << "  - SetLst Max: " << setLst.Max() << ", SetVec Max: " << setVec.Max() << endl;

    cout << "\n======= END OF COMPARISON =======" << endl;
}


// --- Main Test Function (mytest) now contains the menu using if-else if ---
void mytest() {
    int choice = -1;
    while (choice != 0) {
        cout << endl << "Test menu' " << endl
             << "0. Esci" << endl
             << "1. Run Common Container Tests (int)" << endl
             << "2. Run Common Container Tests (float)" << endl
             << "3. Run Common Container Tests (double)" << endl
             << "4. Run Common Container Tests (string)" << endl
             << "5. Run Heap Specific Tests (int)" << endl
             << "6. Run Heap Specific Tests (float)" << endl
             << "7. Run Heap Specific Tests (double)" << endl
             << "8. Run Heap Specific Tests (string)" << endl
             << "9. Run Priority Queue Specific Tests (int only)" << endl
             << "10. Test su List" << endl
             << "11. Test su Vector" << endl
             << "12. Test su SetLst (int)" << endl
             << "13. Test su SetVec (int)" << endl
             << "14. Test su SetLst (string)" << endl
             << "15. Test su SetVec (string)" << endl
             << "16. Confronto tra implementazioni Set (int)" << endl
             << "17. Suite Completa (List, Vector, SetLst/Vec Int, SetLst/Vec String, Comparison, Prof's Test)" << endl;
        string input;
        cin >> input;
        try {
            choice = stoi(input);
        } catch (const std::invalid_argument& e) {
            cout << "Input non valido. Per favor, inserisci un numero." << endl;
            continue;
        } catch (const std::out_of_range& e) {
            cout << "Input troppo grande o troppo piccolo." << endl;
            continue;
        }

        // Refactored switch to if-else if-else
        if (choice == 0) {
            cout << "Uscita dal menu' di test." << endl;
        } else if (choice == 1) {
            run_common_container_tests<int>("int");
        } else if (choice == 2) {
            run_common_container_tests<float>("float");
        } else if (choice == 3) {
            run_common_container_tests<double>("double");
        } else if (choice == 4) {
            run_common_container_tests<string>("string");
        } else if (choice == 5) {
            run_heap_specific_tests<int>("int");
        } else if (choice == 6) {
            run_heap_specific_tests<float>("float");
        } else if (choice == 7) {
            run_heap_specific_tests<double>("double");
        } else if (choice == 8) {
            run_heap_specific_tests<string>("string");
        } else if (choice == 9) {
            run_pq_specific_tests();
        } else if (choice == 10) {
            testListAll();
        } else if (choice == 11) {
            testVectorAll();
        } else if (choice == 12) {
            testSetGeneric<SetLst<int>>("SETLST");
        } else if (choice == 13) {
            testSetGeneric<SetVec<int>>("SETVEC");
        } else if (choice == 14) {
            testStringSetGeneric<SetLst<string>>("SETLST");
        } else if (choice == 15) {
            testStringSetGeneric<SetVec<string>>("SETVEC");
        } else if (choice == 16) {
            compareSetImplementations();
        } else if (choice == 17) {
            testListAll();
            testVectorAll();
            testSetGeneric<SetLst<int>>("SETLST");
            testSetGeneric<SetVec<int>>("SETVEC");
            testStringSetGeneric<SetLst<string>>("SETLST");
            testStringSetGeneric<SetVec<string>>("SETVEC");
            compareSetImplementations();
            // Assuming lasdtest() is an existing function for professor's tests in zlasdtest/test.hpp
            // If it's not present or declared, this line will cause an error.
            // You might need to provide its definition or remove this line if it's not relevant.
            lasdtest();
        } else {
            cout << "Input non valido" << endl;
        }
    }
}