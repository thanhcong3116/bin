#include <iostream>
#include <cassert>
using namespace std;

struct d_NODE {
    int key;
    d_NODE* p_next;
    d_NODE* p_prev;
};

struct d_List {
    d_NODE* p_head;
    d_NODE* p_tail;
    d_List(d_NODE* head = nullptr, d_NODE* tail = nullptr) : p_head(head), p_tail(tail) {}
};

d_NODE* createNode(int data) {
    d_NODE* newNode = new d_NODE{data, nullptr, nullptr};
    return newNode;
}


bool areListsEqual(d_List* list1, d_List* list2) {
    d_NODE* curr1 = list1->p_head;
    d_NODE* curr2 = list2->p_head;

    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->key != curr2->key) {
            return false;
        }
        curr1 = curr1->p_next;
        curr2 = curr2->p_next;
    }

    return curr1 == nullptr && curr2 == nullptr;
}

bool addTail(d_List*& L, int data);

d_List* createListFromArray(int arr[], int size) {
    d_List* list = new d_List();
    for (int i = 0; i < size; i++) {
        addTail(list, arr[i]);
    }
    return list;
}

d_List* createList(d_NODE* p_node) {
    return new d_List(p_node, p_node);
}

bool addHead(d_List*& L, int data) {
    d_NODE* newNode = createNode(data);
    if (!newNode) return false;

    if (L->p_head == nullptr) {
        L->p_head = L->p_tail = newNode;
    } else {
        newNode->p_next = L->p_head;
        L->p_head->p_prev = newNode;
        L->p_head = newNode;
    }
    return true;
}

bool addTail(d_List*& L, int data) {
    d_NODE* newNode = createNode(data);
    if (!newNode) return false;

    if (L->p_tail == nullptr) {
        L->p_head = L->p_tail = newNode;
    } else {
        L->p_tail->p_next = newNode;
        newNode->p_prev = L->p_tail;
        L->p_tail = newNode;
    }
    return true;
}

bool removeHead(d_List*& L) {
    if (L->p_head == nullptr) return false;
    d_NODE* temp = L->p_head;
    L->p_head = L->p_head->p_next;
    if (L->p_head != nullptr) L->p_head->p_prev = nullptr;
    else L->p_tail = nullptr;
    delete temp;
    return true;
}

void removeTail(d_List*& L) {
    if (L->p_tail == nullptr) return;
    d_NODE* temp = L->p_tail;
    L->p_tail = L->p_tail->p_prev;
    if (L->p_tail != nullptr) L->p_tail->p_next = nullptr;
    else L->p_head = nullptr;
    delete temp;
}

// Remove all nodes
void removeAll(d_List*& L) {
    while (L->p_head != nullptr) {
        removeHead(L);
    }
}

void removeBefore(d_List*& L, int val) {
    if (L->p_head == nullptr || L->p_head->key == val) return;

    d_NODE* curr = L->p_head->p_next;

    while (curr != nullptr && curr->key != val) {
        curr = curr->p_next;
    }
    if (curr == nullptr || curr->p_prev == nullptr) return;

    d_NODE* toDelete = curr->p_prev;

    if (toDelete == L->p_head) {
        L->p_head = curr;
        curr->p_prev = nullptr;
    } else {
        toDelete->p_prev->p_next = curr;
        curr->p_prev = toDelete->p_prev;
    }
    delete toDelete;
}

void removeAfter(d_List*& L, int val) {
    d_NODE* curr = L->p_head;

    while (curr != nullptr && curr->key != val) {
        curr = curr->p_next;
    }

    if (curr == nullptr || curr->p_next == nullptr) {
        return;
    }

    d_NODE* toDelete = curr->p_next;
    curr->p_next = toDelete->p_next;

    if (toDelete->p_next != nullptr) {
        toDelete->p_next->p_prev = curr;
    } else {
        L->p_tail = curr;
    }

    delete toDelete;
}

bool addPos(d_List*& L, int data, int pos) {
    if (pos < 0) return false;

    d_NODE* newNode = createNode(data);
    if (!newNode) return false;

    if (pos == 0) {
        newNode->p_next = L->p_head;
        if (L->p_head != nullptr) {
            L->p_head->p_prev = newNode;
        } else {
            L->p_tail = newNode;
        }
        L->p_head = newNode;
        return true;
    }

    d_NODE* curr = L->p_head;
    int index = 0;

    while (curr != nullptr && index < pos - 1) {
        curr = curr->p_next;
        index++;
    }

    if (curr == nullptr) return false;

    newNode->p_next = curr->p_next;
    newNode->p_prev = curr;

    if (curr->p_next != nullptr) {
        curr->p_next->p_prev = newNode;
    } else {
        L->p_tail = newNode;
    }

    curr->p_next = newNode;
    return true;
}
void removePos(d_List*& L, int data, int pos) {
    if (pos < 0 || L->p_head == nullptr) return;
    if (pos == 0) {
        removeHead(L);
        return;
    }
    d_NODE* curr = L->p_head;
    int index = 0;
    while (curr != nullptr && index < pos) {
        curr = curr->p_next;
        index++;
    }
    if (curr == nullptr) return;
    if (curr->p_prev != nullptr)
        curr->p_prev->p_next = curr->p_next;
    if (curr->p_next != nullptr)
        curr->p_next->p_prev = curr->p_prev;
    if (curr == L->p_tail) L->p_tail = curr->p_prev;
    delete curr;
}

bool addBefore(d_List*& L, int data, int val) {
    d_NODE* curr = L->p_head;
    while (curr != nullptr && curr->key != val) {
        curr = curr->p_next;
    }
    if (curr == nullptr) return false;
    d_NODE* newNode = createNode(data);
    newNode->p_next = curr;
    newNode->p_prev = curr->p_prev;
    if (curr->p_prev != nullptr)
        curr->p_prev->p_next = newNode;
    else
        L->p_head = newNode;
    curr->p_prev = newNode;
    return true;
}

bool addAfter(d_List*& L, int data, int val) {
    d_NODE* curr = L->p_head;
    while (curr != nullptr && curr->key != val) {
        curr = curr->p_next;
    }
    if (curr == nullptr) return false;
    d_NODE* newNode = createNode(data);
    newNode->p_prev = curr;
    newNode->p_next = curr->p_next;
    if (curr->p_next != nullptr)
        curr->p_next->p_prev = newNode;
    else
        L->p_tail = newNode;
    curr->p_next = newNode;
    return true;
}

void printList(d_List* L) {
    d_NODE* curr = L->p_head;
    while (curr != nullptr) {
        cout << curr->key << " ";
        curr = curr->p_next;
    }
    cout << endl;
}

int countElements(d_List* L) {
    int count = 0;
    d_NODE* curr = L->p_head;
    while (curr != nullptr) {
        count++;
        curr = curr->p_next;
    }
    return count;
}


d_List* reverseList(d_List* L) {
    d_List* rev = new d_List();
    d_NODE* curr = L->p_tail;
    while (curr != nullptr) {
        addTail(rev, curr->key);
        curr = curr->p_prev;
    }
    return rev;
}


void removeDuplicate(d_List*& L) {
    for (d_NODE* i = L->p_head; i != nullptr; i = i->p_next) {
        d_NODE* j = i->p_next;
        while (j != nullptr) {
            if (j->key == i->key) {
                d_NODE* temp = j;
                j = j->p_next;
                if (temp->p_prev != nullptr)
                    temp->p_prev->p_next = temp->p_next;
                if (temp->p_next != nullptr)
                    temp->p_next->p_prev = temp->p_prev;
                if (temp == L->p_tail) L->p_tail = temp->p_prev;
                delete temp;
            } else {
                j = j->p_next;
            }
        }
    }
}


bool removeElement(d_List*& L, int key) {
    d_NODE* curr = L->p_head;
    while (curr != nullptr && curr->key != key) {
        curr = curr->p_next;
    }
    if (curr == nullptr) return false;
    if (curr->p_prev != nullptr)
        curr->p_prev->p_next = curr->p_next;
    else
        L->p_head = curr->p_next;
    if (curr->p_next != nullptr)
        curr->p_next->p_prev = curr->p_prev;
    else
        L->p_tail = curr->p_prev;
    delete curr;
    return true;
}


void freeList(d_List*& L) {
    removeAll(L);
    delete L;
    L = nullptr;
}


// --- Function main to test the above functions ---

int main()
{
    std::cout << "--- Begin running test cases ---" << std::endl;

    // Test case 1: createNode /////////////////////////////////////////////////
    std::cout << "Test createNode: ";
    d_NODE *node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->p_next == nullptr);
    std::cout << "Passed" << std::endl;
    delete node1;

    // Test case 2: createList //////////////////////////////////////////////////
    std::cout << "Test createList: ";
    d_NODE *head2 = createNode(20);
    d_List *list2 = createList(head2);
    assert(list2 != nullptr && list2->p_head == head2 && list2->p_tail == head2);
    std::cout << "Passed" << std::endl;
    freeList(list2);

    // Test case 3: addHead //////////////////////////////////////////////////////
    std::cout << "Test addHead: ";
    d_List *list3 = new d_List();
    assert(addHead(list3, 30));
    assert(list3->p_head != nullptr && list3->p_head->key == 30 && list3->p_tail->key == 30);
    assert(addHead(list3, 40));
    assert(list3->p_head->key == 40 && list3->p_head->p_next->key == 30 && list3->p_tail->key == 30);
    std::cout << "Passed" << std::endl;
    freeList(list3);

    // Test case 4: addTail /////////////////////////////////////////////////////////
    std::cout << "Test addTail: ";
    d_List *list4 = new d_List();
    assert(addTail(list4, 50));
    assert(list4->p_head != nullptr && list4->p_head->key == 50 && list4->p_tail->key == 50);
    assert(addTail(list4, 60));
    assert(list4->p_head->key == 50 && list4->p_tail->key == 60 && list4->p_head->p_next->key == 60);
    std::cout << "Passed" << std::endl;
    freeList(list4);

    // Test case 5: removeHead //////////////////////////////////////////////////////////////////
    std::cout << "Test removeHead: ";
    int arr1[3] = {70, 80, 90};
    d_List *list5 = createListFromArray(arr1, 3);
    assert(removeHead(list5) && list5->p_head->key == 80);
    assert(removeHead(list5) && list5->p_head->key == 90);
    assert(removeHead(list5) && list5->p_head == nullptr && list5->p_tail == nullptr);
    assert(!removeHead(list5)); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(list5);

    // Test case 6: removeTail ///////////////////////////////////////////////////////////////////
    std::cout << "Test removeTail: ";
    int arr2[3] = {100, 110, 120};
    d_List *list6 = createListFromArray(arr2, 3);
    removeTail(list6);
    assert(list6->p_tail->key == 110 && list6->p_tail->p_next == nullptr);
    removeTail(list6);
    assert(list6->p_tail->key == 100 && list6->p_tail->p_next == nullptr && list6->p_head == list6->p_tail);
    removeTail(list6);
    assert(list6->p_head == nullptr && list6->p_tail == nullptr);
    d_List *emptyList6 = new d_List();
    removeTail(emptyList6); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(emptyList6);
    freeList(list6);

    // Test case 7: removeAll /////////////////////////////////////////////////////////////////////
    std::cout << "Test removeAll: ";
    int arr3[3] = {130, 140, 150};
    d_List *list7 = createListFromArray(arr3, 3);
    removeAll(list7);
    assert(list7->p_head == nullptr && list7->p_tail == nullptr);
    d_List *emptyList7 = new d_List();
    removeAll(emptyList7); // Remove from empty list
    assert(emptyList7->p_head == nullptr && emptyList7->p_tail == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(emptyList7);
    freeList(list7);

    // Test case 8: removeBefore //////////////////////////////////////////////////////////////////////
    std::cout << "Test removeBefore: ";
    int arr4[5] = {160, 170, 180, 190, 200};
    d_List *list8 = createListFromArray(arr4, 5);

    // testcase 1
    removeBefore(list8, 180);
    int expectedArr8[4] = {160, 180, 190, 200};
    d_List *expectedList8 = createListFromArray(expectedArr8, 4);
    assert(areListsEqual(list8, expectedList8));

    // testcase 2
    removeBefore(list8, 200);
    int expectedArr8_2[3] = {160, 180, 200};
    d_List *expectedList8_2 = createListFromArray(expectedArr8_2, 3);
    assert(areListsEqual(list8, expectedList8_2));

    // testcase 3
    removeBefore(list8, 170); // Don't have any element before
    int expectedArr8_2_2[3] = {160, 180, 200};
    d_List *expectedList8_2_2 = createListFromArray(expectedArr8_2_2, 3);
    assert(areListsEqual(list8, expectedList8_2_2));

    // free memory
    freeList(expectedList8);
    freeList(expectedList8_2);
    freeList(expectedList8_2_2);
    freeList(list8);
    std::cout << "Passed" << std::endl;

    // Test case 9: removeAfter ////////////////////////////////////////////////////////////
    std::cout << "Test removeAfter: ";
    int arr5[4] = {220, 230, 240, 250};
    d_List *list9 = createListFromArray(arr5, 4);
    // testcase 1
    removeAfter(list9, 220);
    int expectedArr9[3] = {220, 240, 250};
    d_List *expectedList9 = createListFromArray(expectedArr9, 3);
    assert(areListsEqual(list9, expectedList9));
    // testcase 2
    removeAfter(list9, 250); // Don't have any element after
    int expectedArr9_2[3] = {220, 240, 250};
    d_List *expectedList9_2 = createListFromArray(expectedArr9_2, 3);
    assert(areListsEqual(list9, expectedList9_2));
    // testcase 3
    removeAfter(list9, 240);
    int expectedArr9_3[2] = {220, 240};
    d_List *expectedList9_3 = createListFromArray(expectedArr9_3, 2);
    assert(areListsEqual(list9, expectedList9_3));
    // testcase 4
    int arr9_single[1] = {260};
    d_List *list9_single = createListFromArray(arr9_single, 1);
    removeAfter(list9_single, 260);
    int expectedArr9_single[1] = {260};
    d_List *expectedList9_single = createListFromArray(expectedArr9_single, 1);
    assert(areListsEqual(list9_single, expectedList9_single));
    // testcase 5
    d_List *emptyList9 = new d_List();
    removeAfter(emptyList9, 270);
    assert(areListsEqual(emptyList9, new d_List()));
    // free memory
    freeList(expectedList9);
    freeList(expectedList9_2);
    freeList(expectedList9_3);
    freeList(expectedList9_single);
    freeList(list9);
    freeList(list9_single);
    freeList(emptyList9);
    std::cout << "Passed" << std::endl;

    std::cout << "--- End running test cases ---" << std::endl;
    return 0;
}