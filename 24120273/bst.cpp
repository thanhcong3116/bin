#include <climits>
#include <algorithm>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}

NODE* Search(NODE* pRoot, int x) {
    if (pRoot == nullptr || pRoot->key == x) return pRoot;
    
    if (x < pRoot->key) return Search(pRoot->p_left, x);
    return Search(pRoot->p_right, x);
}

void Insert(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }
    
    if (x < pRoot->key) Insert(pRoot->p_left, x);
    else Insert(pRoot->p_right, x);
}

NODE* minValueNode(NODE* node) {
    NODE* current = node;
    while (current && current->p_left) current = current->p_left;
    return current;
}

void Remove(NODE* &pRoot, int x) {
    if (pRoot == nullptr) return;
    
    if (x < pRoot->key) Remove(pRoot->p_left, x);
    else if (x > pRoot->key) Remove(pRoot->p_right, x);
    else {
        if (pRoot->p_left == nullptr) {
            NODE* temp = pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else if (pRoot->p_right == nullptr) {
            NODE* temp = pRoot->p_left;
            delete pRoot;
            pRoot = temp;
        }
        else {
            NODE* temp = minValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
}

NODE* createTree(int a[], int n) {
    NODE* pRoot = nullptr;
    for (int i = 0; i < n; ++i) {
        Insert(pRoot, a[i]);
    }
    return pRoot;
}

void removeTree(NODE* &pRoot) {
    if (pRoot == nullptr) return;
    
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE* pRoot) {
    if (pRoot == nullptr) return -1;
    return 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));
} 

int countLess(NODE* pRoot, int x) {
    if (pRoot == nullptr) return 0;
    
    if (pRoot->key < x) {
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    }
    return countLess(pRoot->p_left, x);
}

int countGreater(NODE* pRoot, int x) {
    if (pRoot == nullptr) return 0;
    
    if (pRoot->key > x) {
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    }
    return countGreater(pRoot->p_right, x);
}

bool isBSTUtil(NODE* pRoot, long long min, long long max) {
    if (pRoot == nullptr) return true;
    
    if (pRoot->key <= min || pRoot->key >= max) return false;
    
    return isBSTUtil(pRoot->p_left, min, pRoot->key) &&
           isBSTUtil(pRoot->p_right, pRoot->key, max);
}

bool isBST(NODE* pRoot) {
    return isBSTUtil(pRoot, LLONG_MIN, LLONG_MAX);
}

bool isFullBSTUtil(NODE* pRoot) {
    if (pRoot == nullptr) return true;
    
    if ((pRoot->p_left == nullptr && pRoot->p_right != nullptr) ||
        (pRoot->p_left != nullptr && pRoot->p_right == nullptr)) {
        return false;
    }
    
    return isFullBSTUtil(pRoot->p_left) && isFullBSTUtil(pRoot->p_right);
}

bool isFullBST(NODE* pRoot) {
    return isBST(pRoot) && isFullBSTUtil(pRoot);
}