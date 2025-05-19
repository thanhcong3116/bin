#include <climits>
#include <algorithm>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    newNode->height = 1;
    return newNode;
}

int getHeight(NODE* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int getBalance(NODE* node) {
    if (node == nullptr) return 0;
    return getHeight(node->p_left) - getHeight(node->p_right);
}

NODE* rightRotate(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;
    
    x->p_right = y;
    y->p_left = T2;
    
    y->height = max(getHeight(y->p_left), getHeight(y->p_right)) + 1;
    x->height = max(getHeight(x->p_left), getHeight(x->p_right)) + 1;
    
    return x;
}

NODE* leftRotate(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;
    
    y->p_left = x;
    x->p_right = T2;
    
    x->height = max(getHeight(x->p_left), getHeight(x->p_right)) + 1;
    y->height = max(getHeight(y->p_left), getHeight(y->p_right)) + 1;
    
    return y;
}

void Insert(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }
    
    if (x < pRoot->key) Insert(pRoot->p_left, x);
    else Insert(pRoot->p_right, x);
    
    pRoot->height = max(getHeight(pRoot->p_left), getHeight(pRoot->p_right)) + 1;
    
    int balance = getBalance(pRoot);
    
    if (balance > 1 && x < pRoot->p_left->key) {
        pRoot = rightRotate(pRoot);
        return;
    }
    
    if (balance < -1 && x > pRoot->p_right->key) {
        pRoot = leftRotate(pRoot);
        return;
    }
    
    if (balance > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
        return;
    }
    
    if (balance < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
        return;
    }
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
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            if (temp == nullptr) {
                temp = pRoot;
                pRoot = nullptr;
            } else {
                *pRoot = *temp;
            }
            delete temp;
        } else {
            NODE* temp = minValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
    
    if (pRoot == nullptr) return;
    
    pRoot->height = max(getHeight(pRoot->p_left), getHeight(pRoot->p_right)) + 1;
    
    int balance = getBalance(pRoot);
    
    if (balance > 1 && getBalance(pRoot->p_left) >= 0) {
        pRoot = rightRotate(pRoot);
        return;
    }
    
    if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
        return;
    }
    
    if (balance < -1 && getBalance(pRoot->p_right) <= 0) {
        pRoot = leftRotate(pRoot);
        return;
    }
    
    if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
        return;
    }
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

bool isAVLUtil(NODE* pRoot, int& height) {
    if (pRoot == nullptr) {
        height = 0;
        return true;
    }
    
    int leftHeight, rightHeight;
    bool left = isAVLUtil(pRoot->p_left, leftHeight);
    bool right = isAVLUtil(pRoot->p_right, rightHeight);
    
    height = max(leftHeight, rightHeight) + 1;
    
    if (!left || !right || abs(leftHeight - rightHeight) > 1) return false;
    
    return true;
}

bool isAVL(NODE* pRoot) {
    if (!isBST(pRoot)) return false;
    
    int height;
    return isAVLUtil(pRoot, height);
}