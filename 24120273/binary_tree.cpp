#include <vector>
#include <queue>
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

vector<int> NLR(NODE* pRoot) {
    vector<int> result;
    if (pRoot == nullptr) return result;
    
    result.push_back(pRoot->key);
    vector<int> left = NLR(pRoot->p_left);
    vector<int> right = NLR(pRoot->p_right);
    
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}

vector<int> LNR(NODE* pRoot) {
    vector<int> result;
    if (pRoot == nullptr) return result;
    
    vector<int> left = LNR(pRoot->p_left);
    result.insert(result.end(), left.begin(), left.end());
    
    result.push_back(pRoot->key);
    
    vector<int> right = LNR(pRoot->p_right);
    result.insert(result.end(), right.begin(), right.end());
    
    return result;
}

vector<int> LRN(NODE* pRoot) {
    vector<int> result;
    if (pRoot == nullptr) return result;
    
    vector<int> left = LRN(pRoot->p_left);
    vector<int> right = LRN(pRoot->p_right);
    
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    result.push_back(pRoot->key);
    
    return result;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
    vector<vector<int>> result;
    if (pRoot == nullptr) return result;
    
    queue<NODE*> q;
    q.push(pRoot);
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; ++i) {
            NODE* node = q.front();
            q.pop();
            currentLevel.push_back(node->key);
            
            if (node->p_left) q.push(node->p_left);
            if (node->p_right) q.push(node->p_right);
        }
        
        result.push_back(currentLevel);
    }
    
    return result;
}

int countNode(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int height(NODE* pRoot) {
    if (pRoot == nullptr) return -1;
    return 1 + max(height(pRoot->p_left), height(pRoot->p_right));
}

int heightNode(NODE* pRoot, int value) {
    if (pRoot == nullptr) return -1;
    
    if (pRoot->key == value) {
        return height(pRoot);
    }
    
    int left = heightNode(pRoot->p_left, value);
    if (left != -1) return left;
    
    return heightNode(pRoot->p_right, value);
}

int Level(NODE* pRoot, NODE* p) {
    if (pRoot == nullptr || p == nullptr) return -1;
    
    if (pRoot == p) return 1;
    
    int left = Level(pRoot->p_left, p);
    if (left != -1) return left + 1;
    
    int right = Level(pRoot->p_right, p);
    if (right != -1) return right + 1;
    
    return -1;
}

int countLeaf(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}