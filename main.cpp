#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#include "BinaryTreeNode.h"
#include "Node.h"

void printTree(BinaryTreeNode<int> *root) {
  if (root == NULL) {
    return;
  }
  cout << root->data << ':';
  if (root->left != NULL) {
    cout << 'L' << root->left->data;
  }
  if (root->right != NULL) {
    cout << 'R' << root->right->data;
  }
  cout << endl;
  printTree(root->left);
  printTree(root->right);
}

BinaryTreeNode<int> *takeInput() {
  int rootData;
  cout << "Enter data" << endl;
  cin >> rootData;
  if (rootData == -1) {
    return NULL;
  }
  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
  root->left = takeInput();
  root->right = takeInput();
  return root;
}

BinaryTreeNode<int> *takeInputLevelWise() {
  int rootData;
  cout << "Enter root data" << endl;
  cin >> rootData;

  if (rootData == -1) {
    return NULL;
  }

  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  while (!q.empty()) {
    BinaryTreeNode<int> *front = q.front();
    q.pop();
    int left, right;
    cout << "Enter left child of " << front->data << endl;
    cin >> left;
    cout << "Enter right child of " << front->data << endl;
    cin >> right;
    if (left != -1) {
      BinaryTreeNode<int> *leftNode = new BinaryTreeNode<int>(left);
      front->left = leftNode;
      q.push(leftNode);
    }
    if (right != -1) {
      BinaryTreeNode<int> *rightNode = new BinaryTreeNode<int>(right);
      front->right = rightNode;
      q.push(rightNode);
    }
  }
  return root;
}

void printLevelWise(BinaryTreeNode<int> *root) {
  if (root == NULL) {
    return;
  }
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  while (!q.empty()) {
    BinaryTreeNode<int> *front = q.front();
    q.pop();
    cout << front->data << ':';
    if (front->left != NULL) {
      cout << "L:" << front->left->data << ',';
      q.push(front->left);
    } else {
      cout << "L:" << -1 << ',';
    }
    if (front->right != NULL) {
      cout << "R:" << front->right->data;
      q.push(front->right);
    } else {
      cout << "R:" << -1;
    }
    cout << endl;
  }
}

int countNodes(BinaryTreeNode<int> *root) {
  return (root) ? (1 + countNodes(root->left) + countNodes(root->right)) : 0;
}

bool isNodePresent(BinaryTreeNode<int> *root, int x) {
  if (root == NULL) {
    return false;
  }
  if (root->data == x) {
    return true;
  }
  return isNodePresent(root->left, x) || isNodePresent(root->right, x);
}

int height(BinaryTreeNode<int> *root) {
  if (root == NULL) return 0;
  return 1 + max(height(root->left), height(root->right));
}

int maxDepth(BinaryTreeNode<int> *root) {
  if (root == NULL) return 0;
  return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

void mirrorBinaryTree(BinaryTreeNode<int> *root) {
  if (root == NULL) {
    return;
  }
  mirrorBinaryTree(root->left);
  mirrorBinaryTree(root->right);
  BinaryTreeNode<int> *temp = root->left;
  root->left = root->right;
  root->right = temp;
}

void preOrder(BinaryTreeNode<int> *root) {
  if (root == NULL) {
    return;
  }
  cout << root->data << " ";
  preOrder(root->left);
  preOrder(root->right);
}

void postOrder(BinaryTreeNode<int> *root) {
  if (root == NULL) {
    return;
  }
  postOrder(root->left);
  postOrder(root->right);
  cout << root->data << " ";
}

BinaryTreeNode<int> *buildTreeHelper(int *preorder, int preStart, int preEnd,
                                     int *inorder, int inStart, int inEnd) {
  if (inStart > inEnd) {
    return NULL;
  }

  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(preorder[preStart]);
  int rootIndex = -1;
  for (int i = inStart; i <= inEnd; i++) {
    if (inorder[i] == root->data) {
      rootIndex = i;
      break;
    }
  }

  int leftInStart = inStart;
  int leftInEnd = rootIndex - 1;
  int leftPreStart = preStart + 1;
  int leftPreEnd = leftInEnd - leftInStart + leftPreStart;

  int rightInStart = rootIndex + 1;
  int rightInEnd = inEnd;
  int rightPreStart = leftPreEnd + 1;
  int rightPreEnd = preEnd;

  root->left = buildTreeHelper(preorder, leftPreStart, leftPreEnd, inorder,
                               leftInStart, leftInEnd);
  root->right = buildTreeHelper(preorder, rightPreStart, rightPreEnd, inorder,
                                rightInStart, rightInEnd);
  return root;
}

BinaryTreeNode<int> *buildTree(int *preorder, int preLenght, int *inorder,
                               int inLength) {
  return buildTreeHelper(preorder, 0, preLenght - 1, inorder, 0, inLength - 1);
}

pair<int, int> heightDiameter(BinaryTreeNode<int> *root) {
  if (root == NULL) return pair<int, int>(0, 0);
  pair<int, int> leftAns = heightDiameter(root->left);
  pair<int, int> rightAns = heightDiameter(root->right);
  int height = 1 + max(leftAns.first, rightAns.first);
  int diameter =
      max(leftAns.first + rightAns.first, max(leftAns.second, rightAns.second));
  return pair<int, int>(height, diameter);
}

int diameter(BinaryTreeNode<int> *root) { return heightDiameter(root).second; }

class PairAns {
 public:
  int min;
  int max;
};

PairAns minMax(BinaryTreeNode<int> *root) {
  if (root == NULL) {
    PairAns p;
    p.min = 0;
    p.max = 0;
    return p;
  }
  if (root->left == NULL && root->right == NULL) {
    PairAns p;
    p.min = root->data;
    p.max = root->data;
    return p;
  }
  PairAns leftAns;
  if (root->left != NULL) {
    leftAns = minMax(root->left);
  } else {
    leftAns.min = INT_MAX;
    leftAns.max = INT_MIN;
  }
  PairAns rightAns;
  if (root->right != NULL) {
    rightAns = minMax(root->right);
  } else {
    rightAns.min = INT_MAX;
    rightAns.max = INT_MIN;
  }
  PairAns ans;
  ans.min = min(leftAns.min, min(rightAns.min, root->data));
  ans.max = max(leftAns.max, max(rightAns.max, root->data));
  return ans;
}

int sumOfAllNodes(BinaryTreeNode<int> *root) {
  if (root == NULL) return 0;
  return root->data + sumOfAllNodes(root->left) + sumOfAllNodes(root->right);
}

bool isBalanced(BinaryTreeNode<int> *root, int &height) {
  if (!root) return true;
  int leftHeight = 0, rightHeight = 0;
  bool leftAns = isBalanced(root->left, leftHeight);
  bool rightAns = isBalanced(root->right, rightHeight);
  if (abs(leftHeight - rightHeight) > 1) return false;
  height = max(leftHeight, rightHeight) + 1;
  return leftAns && rightAns;
}

bool isBalanced(BinaryTreeNode<int> *root) {
  int height = 0;
  return isBalanced(root, height);
}

void printLevelATNewLine(BinaryTreeNode<int> *root) {
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  q.push(NULL);
  while (!q.empty()) {
    BinaryTreeNode<int> *first = q.front();
    q.pop();
    if (first == NULL) {
      if (q.empty()) {
        break;
      }
      cout << endl;
      q.push(NULL);
      continue;
    }
    cout << first->data << " ";
    if (first->left != NULL) {
      q.push(first->left);
    }
    if (first->right != NULL) {
      q.push(first->right);
    }
  }
}

BinaryTreeNode<int> *removeLeafNodes(BinaryTreeNode<int> *root) {
  if (root == NULL) return NULL;
  if (root->left == NULL && root->right == NULL) {
    delete root;
    return NULL;
  }
  root->left = removeLeafNodes(root->left);
  root->right = removeLeafNodes(root->right);
  return root;
}

template <typename T>
class node {
 public:
  T data;
  node<T> *next;
  node(T data) {
    this->data = data;
    this->next = NULL;
  }
};

vector<node<int> *> createLLForEachLevel(BinaryTreeNode<int> *root) {
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  q.push(NULL);
  vector<node<int> *> ans;
  node<int> *head = NULL;
  node<int> *tempHead = NULL;
  while (!q.empty()) {
    BinaryTreeNode<int> *first = q.front();
    q.pop();
    if (first == NULL) {
      tempHead->next = NULL;
      tempHead = tempHead->next;
      ans.push_back(head);
      head = NULL;
      if (q.empty()) {
        break;
      }
      q.push(NULL);
      continue;
    }
    if (head == NULL) {
      head = new node<int>(first->data);
      tempHead = head;
    } else {
      tempHead->next = new node<int>(first->data);
      tempHead = tempHead->next;
    }
    if (first->left != NULL) {
      q.push(first->left);
    }
    if (first->right != NULL) {
      q.push(first->right);
    }
  }
  return ans;
}

// Using vector
void zigZagOrder(BinaryTreeNode<int> *root) {
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  q.push(NULL);
  vector<int> v;
  bool flag = true;
  while (!q.empty()) {
    BinaryTreeNode<int> *first = q.front();
    q.pop();
    if (first == NULL) {
      if (flag) {
        for (int i = 0; i < v.size(); i++) {
          cout << v.at(i) << ' ';
        }
      } else {
        for (int i = v.size() - 1; i >= 0; i--) {
          cout << v.at(i) << ' ';
        }
      }
      v.clear();
      cout << endl;
      flag = !flag;
      if (q.empty()) {
        break;
      }
      q.push(NULL);
      continue;
    }
    v.push_back(first->data);
    if (first->left != NULL) {
      q.push(first->left);
    }
    if (first->right != NULL) {
      q.push(first->right);
    }
  }
}

// Better space complexity using stack
void zigZagOrderBetter(BinaryTreeNode<int> *root) {
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  q.push(NULL);
  stack<int> s;
  bool flag = true;
  while (!q.empty()) {
    BinaryTreeNode<int> *first = q.front();
    q.pop();
    if (first == NULL) {
      if (flag) {
        cout << endl;
      } else {
        while (!s.empty()) {
          cout << s.top() << ' ';
          s.pop();
        }
      }
      flag = !flag;
      if (q.empty()) {
        break;
      }
      q.push(NULL);
      continue;
    }
    if (flag) {
      cout << first->data << ' ';
    } else {
      s.push(first->data);
    }
    if (first->left != NULL) {
      q.push(first->left);
    }
    if (first->right != NULL) {
      q.push(first->right);
    }
  }
}

BinaryTreeNode<int> *getTreeFromPostorderAndInorderHelper(
    int *postorder, int postStart, int postEnd, int *inorder, int inStart,
    int inEnd) {
  if (inStart > inEnd || postStart > postEnd) return NULL;

  int rootData = postorder[postEnd];
  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);

  int rootIndex = 0;
  for (int i = 0; i <= inEnd; i++) {
    if (rootData == inorder[i]) {
      rootIndex = i;
      break;
    }
  }
  int leftInStart = inStart;
  int leftInEnd = rootIndex - 1;
  int leftPostStart = postStart;
  int leftPostEnd = postStart + rootIndex - (inStart + 1);

  int rightInStart = rootIndex + 1;
  int rightInEnd = inEnd;
  int rightPostStart = postStart + rootIndex - inStart;
  int rightPostEnd = postEnd - 1;

  root->left = getTreeFromPostorderAndInorderHelper(
      postorder, leftPostStart, leftPostEnd, inorder, leftInStart, leftInEnd);
  root->right = getTreeFromPostorderAndInorderHelper(postorder, rightPostStart,
                                                     rightPostEnd, inorder,
                                                     rightInStart, rightInEnd);
  return root;
}

BinaryTreeNode<int> *getTreeFromPostorderAndInorder(int *postorder,
                                                    int postLength,
                                                    int *inorder,
                                                    int inLength) {
  return getTreeFromPostorderAndInorderHelper(postorder, 0, postLength - 1,
                                              inorder, 0, inLength - 1);
}

vector<int> *findPath(BinaryTreeNode<int> *root, int data) {
  if (root == NULL) return NULL;
  if (root->data == data) {
    vector<int> *ans = new vector<int>();
    ans->push_back(root->data);
    return ans;
  }
  vector<int> *leftAns = findPath(root->left, data);
  if (leftAns != NULL) {
    leftAns->push_back(root->data);
    return leftAns;
  }
  vector<int> *rightAns = findPath(root->right, data);
  if (rightAns != NULL) {
    rightAns->push_back(root->data);
    return rightAns;
  }
  return NULL;
}

void insertDuplicateNode(BinaryTreeNode<int> *root) {
  if (root == NULL) return;
  if (!root->left && !root->right) {
    root->left = new BinaryTreeNode<int>(root->data);
  } else {
    insertDuplicateNode(root->left);
    insertDuplicateNode(root->right);
    BinaryTreeNode<int> *toBeInserted = new BinaryTreeNode<int>(root->data);
    toBeInserted->left = root->left;
    root->left = toBeInserted;
  }
}

template <typename T>
bool isLeaf(BinaryTreeNode<T> *root) {
  return root->left == NULL && root->right == NULL;
}

// Naive Approach
void nodesSumToSNaive(BinaryTreeNode<int> *root, int sum) {
  queue<BinaryTreeNode<int> *> nodes;
  vector<int> v;
  nodes.push(root);
  while (!nodes.empty()) {
    BinaryTreeNode<int> *front = nodes.front();
    nodes.pop();
    if (front->left) {
      nodes.push(front->left);
    }
    if (front->right) {
      nodes.push(front->right);
    }
    v.push_back(front->data);
  }
  for (int i = 0; i < v.size(); i++) {
    for (int j = i; j < v.size(); j++) {
      if ((v.at(i) + v.at(j) == sum) && (i != j)) {
        cout << min(v.at(i), v.at(j)) << " " << max(v.at(i), v.at(j)) << endl;
      }
    }
  }
}

void insertElements(BinaryTreeNode<int> *root, vector<int> *v) {
  if (root == NULL) return;
  insertElements(root->left, v);
  v->push_back(root->data);
  insertElements(root->right, v);
}

// Best Approach
void nodesSumToS(BinaryTreeNode<int> *root, int sum) {
  vector<int> *v = new vector<int>();
  sort(v->begin(), v->end());
  insertElements(root, v);
  int i = 0, j = v->size() - 1;
  while (i < j) {
    int res = v->at(i) + v->at(j);
    if (res > sum) {
      j--;
    } else if (res < sum) {
      i++;
    } else {
      cout << v->at(i) << " " << v->at(j) << endl;
      i++;
      j--;
    }
  }
}

void pathSumHelper(BinaryTreeNode<int> *root, int k, vector<int> *v) {
  if (root == NULL) return;
  k = k - root->data;
  v->push_back(root->data);
  if (isLeaf(root) && k == 0) {
    for (int i = 0; i < v->size(); i++) {
      cout << v->at(i) << " ";
    }
    cout << endl;
  }
  pathSumHelper(root->left, k, v);
  pathSumHelper(root->right, k, v);
  v->pop_back();
}

void rootToLeafPathsSumToK(BinaryTreeNode<int> *root, int k) {
  if (root == NULL) return;
  vector<int> *v = new vector<int>();
  pathSumHelper(root, k, v);
}

int pathSum(BinaryTreeNode<int> *node, int &maxSum) {
  if (node == NULL) return 0;
  int left = max(0, pathSum(node->left, maxSum));
  int right = max(0, pathSum(node->right, maxSum));
  maxSum = max(maxSum, left + right + node->data);
  return max(left, right) + node->data;
}

int maxPathSum(BinaryTreeNode<int> *root) {
  int maxSum = INT_MIN;
  pathSum(root, maxSum);
  return maxSum;
}

int evaluate(int val1, int val2, char op) {
  switch (op) {
    case '+':
      return val1 + val2;
    case '-':
      return val1 - val2;
    case '*':
      return val1 * val2;
    case '/':
      return val1 / val2;
    case '%':
      return val1 % val2;
    case '^':
      return int(pow(val1, val2));
    default:
      return 0;
  }
}

int evaluationOfExpressionTree(BinaryTreeNode<char> *node) {
  if (node == NULL) return 0;
  if (isLeaf(node)) return node->data - 48;
  int left = evaluationOfExpressionTree(node->left);
  int right = evaluationOfExpressionTree(node->right);
  return evaluate(left, right, node->data);
}

bool isHalf(BinaryTreeNode<int> *node) {
  return (node->left && !node->right) || (!node->left && node->right);
}

int noOfHalfNodes(BinaryTreeNode<int> *node) {
  if (node == NULL || isLeaf(node)) return 0;
  int left = noOfHalfNodes(node->left);
  int right = noOfHalfNodes(node->right);
  int ans = left + right;
  if (isHalf(node)) {
    ans++;
  }
  return ans;
}

// From Array
BinaryTreeNode<int> *buildHeap(int *arr, int size) {
  if (size == 0) return NULL;
  queue<BinaryTreeNode<int> *> nodes;
  int start = 0;
  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(arr[start]);
  nodes.push(root);
  while (start < size) {
    BinaryTreeNode<int> *front = nodes.front();
    nodes.pop();
    start++;
    if (start < size) {
      BinaryTreeNode<int> *node = new BinaryTreeNode<int>(arr[start]);
      front->left = node;
      nodes.push(node);
      start++;
    }
    if (start < size) {
      BinaryTreeNode<int> *node = new BinaryTreeNode<int>(arr[start]);
      front->right = node;
      nodes.push(node);
      start++;
    }
  }
  return root;
}

// From Linked List
BinaryTreeNode<int> *buildHeap(Node<int> *head) {
  if (head == NULL) return NULL;
  Node<int> *tempHead = head;
  queue<BinaryTreeNode<int> *> nodes;
  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(tempHead->data);
  nodes.push(root);
  while (tempHead) {
    BinaryTreeNode<int> *front = nodes.front();
    nodes.pop();
    tempHead = tempHead->next;
    if (tempHead) {
      BinaryTreeNode<int> *node = new BinaryTreeNode<int>(tempHead->data);
      front->left = node;
      nodes.push(node);
      tempHead = tempHead->next;
    }
    if (tempHead) {
      BinaryTreeNode<int> *node = new BinaryTreeNode<int>(tempHead->data);
      front->right = node;
      nodes.push(node);
      tempHead = tempHead->next;
    }
  }
  return root;
}

int lcaBinaryTree(BinaryTreeNode<int> *root, int val1, int val2) {
  if (root == NULL) return -1;
  int left = lcaBinaryTree(root->left, val1, val2);
  int right = lcaBinaryTree(root->right, val1, val2);
  if (root->data == val1 || root->data == val2) {
    return root->data;
  }
  if (left != -1 && right != -1) {
    return root->data;
  } else if (left != -1 && right == -1) {
    return left;
  } else if (left == -1 && right != -1) {
    return right;
  } else {
    return -1;
  }
}

bool isBSTHelper(BinaryTreeNode<int> *root, int from, int to) {
  if (root == NULL) return true;
  if (root->data < from && root->data > to) return false;
  bool leftAns = isBSTHelper(root->left, from, root->data - 1);
  bool rightAns = isBSTHelper(root->right, root->data, to);
  return leftAns && rightAns;
}

bool isBST(BinaryTreeNode<int> *root) {
  return isBSTHelper(root, INT_MIN, INT_MAX);
}

int largestBSTSubtreeHelper(BinaryTreeNode<int> *root, int &maxHeight) {
  int tempHeight = 0;
  int leftHeight = 0;
  int rightHeight = 0;
  if (isBST(root)) {
    tempHeight = height(root);
    if (tempHeight > maxHeight) {
      maxHeight = tempHeight;
    }
  } else {
    leftHeight = largestBSTSubtreeHelper(root->left, maxHeight);
    rightHeight = largestBSTSubtreeHelper(root->right, maxHeight);
  }
  return maxHeight;
}

int largestBSTSubtree(BinaryTreeNode<int> *root) {
  int maxHeight = 0;
  return largestBSTSubtreeHelper(root, maxHeight);
}

int binary_search_find_index(vector<int> v, int data) {
  auto it = lower_bound(v.begin(), v.end(), data);
  if (it == v.end() || *it != data) {
    return -1;
  } else {
    std::size_t index = std::distance(v.begin(), it);
    return index;
  }
}

void fillVector(BinaryTreeNode<int> *root, vector<int> &v) {
  if (root == NULL) return;
  fillVector(root->left, v);
  v.push_back(root->data);
  fillVector(root->right, v);
}

void replaceWithLargerHelper(BinaryTreeNode<int> *root, vector<int> &v1,
                             vector<int> &v2) {
  if (root == NULL) return;
  root->data = v2.at(binary_search_find_index(v1, root->data));
  replaceWithLargerHelper(root->left, v1, v2);
  replaceWithLargerHelper(root->right, v1, v2);
}

void replaceWithLargerNodesSum(BinaryTreeNode<int> *root) {
  vector<int> v1;
  fillVector(root, v1);
  vector<int> v2 = v1;
  for (int i = v1.size() - 2; i >= 0; i--) {
    v2.at(i) += v2.at(i + 1);
  }
  replaceWithLargerHelper(root, v1, v2);
}

// **************************************************************************************
void printNodesAtDepthK(BinaryTreeNode<int> *root, int k) {
  if (root == NULL || k < 0) {
    return;
  }
  if (k == 0) {
    cout << root->data << endl;
    return;
  }
  printNodesAtDepthK(root->left, k - 1);
  printNodesAtDepthK(root->right, k - 1);
}
int nodesAtDistanceKHelper(BinaryTreeNode<int> *root, int node, int k) {
  if (root == NULL) {
    return -1;
  }
  if (root->data == node) {
    printNodesAtDepthK(root, k);
    return 0;
  }
  int leftDistance = nodesAtDistanceKHelper(root->left, node, k);
  if (leftDistance != -1) {
    if (leftDistance + 1 == k) {
      cout << root->data << endl;
    } else {
      printNodesAtDepthK(root->right, k - leftDistance - 2);
    }
    return 1 + leftDistance;
  }
  int rightDistance = nodesAtDistanceKHelper(root->right, node, k);
  if (rightDistance != -1) {
    if (rightDistance + 1 == k) {
      cout << root->data << endl;
    } else {
      printNodesAtDepthK(root->left, k - rightDistance - 2);
    }
    return 1 + rightDistance;
  }
  return -1;
}
void nodesAtDistanceK(BinaryTreeNode<int> *root, int node, int k) {
  nodesAtDistanceKHelper(root, node, k);
}
// **************************************************************************************

// **************************************************************************************
// Given two binary trees and imagine that when you put one of them to cover the
// other, some nodes of the two trees are overlapped while the others are not.

// You need to merge them into a new binary tree. The merge rule is that if two
// nodes overlap, then sum node values up as the new value of the merged node.
// Otherwise, the NOT null node will be used as the node of new tree.

// Example :

// Input:
// 	Tree 1                     Tree 2
//           1                         2
//          / \                       / \                            
//         3   2                     1   3
//        /                           \   \                      
//       5                             4   7
// Output:
// Merged tree:
// 	     3
// 	    / \
// 	   4   5
// 	  / \   \ 
// 	 5   4   7
BinaryTreeNode<int> *mergeTrees(BinaryTreeNode<int> *t1,
                                BinaryTreeNode<int> *t2) {
  if (!t1 && !t2) return nullptr;
  if (t1 && !t2) return t1;
  if (!t1 && t2) return t2;
  BinaryTreeNode<int> *root = new BinaryTreeNode<int>(t1->data + t2->data);
  root->left = mergeTrees(t1->left, t2->left);
  root->right = mergeTrees(t1->right, t2->right);
  return root;
}
// **************************************************************************************

// **************************************************************************************
// A binary tree is univalued if every node in the tree has the same value.
// Return true if and only if the given tree is univalued.
// Input: [1,1,1,1,1,null,1]
// Output: true
// Input: [2,2,2,5,2]
// Output: false
bool isUnivalTree(BinaryTreeNode<int> *root) {
  if (!root) return true;
  if (root->left && root->left->data != root->data) return false;
  if (root->right && root->right->data != root->data) return false;
  return isUnivalTree(root->left) && isUnivalTree(root->right);
}
// **************************************************************************************

// **************************************************************************************
// Given a binary search tree, rearrange the tree in in-order so that the
// leftmost node in the tree is now the root of the tree, and every node has no
// left child and only 1 right child.

// Example :
// Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

//        5
//       / \
//     3    6
//    / \    \
//   2   4    8
//  /        / \ 
// 1        7   9

// Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
BinaryTreeNode<int> *addDataInRight(BinaryTreeNode<int> *root,
                                    BinaryTreeNode<int> *newTree) {
  if (!root) return newTree;
  root->right = addDataInRight(root->right, newTree);
  return root;
}
BinaryTreeNode<int> *increasingBST(BinaryTreeNode<int> *root) {
  if (!root) return nullptr;
  BinaryTreeNode<int> *leftAns = increasingBST(root->left);
  BinaryTreeNode<int> *newRoot = new BinaryTreeNode<int>(root->data);
  BinaryTreeNode<int> *rightAns = increasingBST(root->right);
  newRoot->right = rightAns;
  return addDataInRight(leftAns, newRoot);
}
// **************************************************************************************

// **************************************************************************************
// Given a binary tree, each node has value 0 or 1.  Each root-to-leaf path
// represents a binary number starting with the most significant bit.  For
// example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent
// 01101 in binary, which is 13.
// For all leaves in the tree, consider the numbers represented by the path from
// the root to that leaf.
// Return the sum of these numbers.
// Input: [1,0,1,0,1,0,1]
// Output: 22
// Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
int sumRootToLeaf(BinaryTreeNode<int> *root, int val = 0) {
  if (!root) return 0;
  val = (val * 2 + root->data);
  return root->left == root->right
             ? val
             : sumRootToLeaf(root->left, val) + sumRootToLeaf(root->right, val);
}
// **************************************************************************************

// **************************************************************************************
// Given a non-empty binary tree, return the average value of the nodes on each
// level in the form of an array. Example 1:

// Input:
//     3
//    / \
//   9  20
//     /  \
//    15   7
// Output: [3, 14.5, 11]
// Explanation:
// The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level
// 2 is 11. Hence return [3, 14.5, 11].

vector<double> averageOfLevelsNaive(BinaryTreeNode<int> *root) {
  vector<double> ans;
  queue<BinaryTreeNode<int> *> q;
  q.push(root);
  q.push(nullptr);
  double sum = 0, count = 0;
  while (!q.empty()) {
    BinaryTreeNode<int> *first = q.front();
    q.pop();
    if (!first) {
      ans.push_back(sum / count);
      sum = count = 0;
      if (!q.empty()) {
        q.push(nullptr);
      }
    } else {
      sum += first->data;
      count++;
      if (first->left) {
        q.push(first->left);
      }
      if (first->right) {
        q.push(first->right);
      }
    }
  }
  return ans;
}
void average(BinaryTreeNode<int> *root, vector<int> &sums, vector<int> &counts,
             int index = 0) {
  if (!root) return;
  if (sums.size() > index) {
    sums[index] += root->data;
    counts[index]++;
  } else {
    sums.push_back(root->data);
    counts.push_back(1);
  }
  average(root->left, sums, counts, index + 1);
  average(root->right, sums, counts, index + 1);
}
vector<double> averageOfLevels(BinaryTreeNode<int> *root) {
  vector<int> sums;
  vector<int> counts;
  vector<double> results;
  average(root, sums, counts);
  for (int i = 0; i < sums.size(); i++) {
    results.push_back(double(sums.at(i)) / double(counts.at(i)));
  }
  return results;
}
// **************************************************************************************

// **************************************************************************************
// You need to construct a string consists of parenthesis and integers from a
// binary tree with the preorder traversing way.
// The null node needs to be represented by empty parenthesis pair "()". And you
// need to omit all the empty parenthesis pairs that don't affect the one-to-one
// mapping relationship between the string and the original binary tree.
// Example 1:
// Input: Binary tree: [1,2,3,4]
//        1
//      /   \
//     2     3
//    /
//   4
// Output: "1(2(4))(3)"
// Explanation: Originallay it needs to be "1(2(4)())(3()())",
// but you need to omit all the unnecessary empty parenthesis pairs.
// And it will be "1(2(4))(3)".
// Example 2:
// Input: Binary tree: [1,2,3,null,4]
//        1
//      /   \
//     2     3
//      \  
//       4
// Output: "1(2()(4))(3)"
// Explanation: Almost the same as the first example,
// except we can't omit the first parenthesis pair to break the one-to-one
// mapping relationship between the input and the output.
string tree2str(BinaryTreeNode<int> *t) {
  if (!t) return "";
  string left = tree2str(t->left);
  string right = tree2str(t->right);
  string ans = to_string(t->data);
  if (left.size() == 0 && right.size() == 0) return ans;
  if (left.size() == 0)
    ans += "()";
  else
    ans += "(" + left + ")";
  if (right.size() > 0) ans += "(" + right + ")";
  return ans;
}
// **************************************************************************************

// **************************************************************************************
// Given two binary trees, write a function to check if they are the same or
// not.

// Two binary trees are considered the same if they are structurally identical
// and the nodes have the same value.

// Example 1:

// Input:     1         1
//           / \       / \
//          2   3     2   3

//         [1,2,3],   [1,2,3]

// Output: true

bool isSameTree(BinaryTreeNode<int> *p, BinaryTreeNode<int> *q) {
  if (!p && !q) return true;
  if (!p || !q) return false;
  return isSameTree(p->left, q->left) && isSameTree(p->right, q->right) &&
         p->data == q->data;
}
// **************************************************************************************

// **************************************************************************************
// Given a Binary Search Tree and a target number, return true if there exist
// two elements in the BST such that their sum is equal to the given target.

// Example 1:

// Input:
//     5
//    / \
//   3   6
//  / \   \
// 2   4   7

// Target = 9

// Output: True

bool findTarget(BinaryTreeNode<int> *root, int k, unordered_set<int> &set) {
  if (!root) return false;
  int val = root->data;
  if (set.find(k - val) != set.end()) {
    return true;
  }
  set.insert(val);
  return findTarget(root->left, k, set) || findTarget(root->right, k, set);
}
bool findTarget(BinaryTreeNode<int> *root, int k) {
  unordered_set<int> set;
  return findTarget(root, k, set);
}
// **************************************************************************************

// **************************************************************************************
// Given a binary tree, return the bottom-up level order traversal of its nodes'
// values. (ie, from left to right, level by level from leaf to root).

// For example:
// Given binary tree [3,9,20,null,null,15,7],

//     3
//    / \
//   9  20
//     /  \
//    15   7
// return its bottom-up level order traversal as:

// [
//   [15,7],
//   [9,20],
//   [3]
// ]

void levelOrderBottom(BinaryTreeNode<int> *root, vector<vector<int>> &ans,
                      int index = 0) {
  if (!root) return;
  if (ans.size() > index) {
    ans.at(index).push_back(root->data);
  } else {
    vector<int> v;
    v.push_back(root->data);
    ans.push_back(v);
  }
  levelOrderBottom(root->left, ans, index + 1);
  levelOrderBottom(root->right, ans, index + 1);
}
vector<vector<int>> levelOrderBottom(BinaryTreeNode<int> *root, int index = 0) {
  vector<vector<int>> ans;
  if (!root) return ans;
  levelOrderBottom(root, ans);
  reverse(ans.begin(), ans.end());
  return ans;
}
// **************************************************************************************

// **************************************************************************************
// Find the sum of all left leaves in a given binary tree.

// Example:

//     3
//    / \
//   9  20
//     /  \
//    15   7

// There are two left leaves in the binary tree, with values 9 and 15
// respectively. Return 24.

int sumOfLeftLeaves(BinaryTreeNode<int> *root, bool isLeft = false) {
  if (!root) return 0;
  if (isLeaf(root) && isLeft) return root->data;
  return sumOfLeftLeaves(root->left, true) +
         sumOfLeftLeaves(root->right, false);
}
// **************************************************************************************

// **************************************************************************************
// Given a binary tree, return the tilt of the whole tree.

// The tilt of a tree node is defined as the absolute difference between the sum
// of all left subtree node values and the sum of all right subtree node values.
// Null node has tilt 0.

// The tilt of the whole tree is defined as the sum of all nodes' tilt.

// Example:

// Input:
//          1
//        /   \
//       2     3
// Output: 1
// Explanation:
// Tilt of node 2 : 0
// Tilt of node 3 : 0
// Tilt of node 1 : |2-3| = 1
// Tilt of binary tree : 0 + 0 + 1 = 1

int findTilt(BinaryTreeNode<int> *root, int &sum) {
  if (!root) return 0;
  if (!root->left && !root->right) {
    sum = root->data;
    return 0;
  }
  int leftSum = 0, rightSum = 0;
  int leftTilt = findTilt(root->left, leftSum);
  int rightTilt = findTilt(root->right, rightSum);
  int tilt = abs(leftSum - rightSum);
  sum = leftSum + rightSum + root->data;
  return tilt + leftTilt + rightTilt;
}
int findTilt(BinaryTreeNode<int> *root) {
  if (!root) return 0;
  int sum = 0;
  return findTilt(root, sum);
}
// **************************************************************************************

// **************************************************************************************
// Given a binary tree, check whether it is a mirror of itself (ie, symmetric
// around its center).

// For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3

bool isMirror(BinaryTreeNode<int> *tree1, BinaryTreeNode<int> *tree2) {
  if (!tree1 && !tree2) return true;
  if (!tree1 || !tree2) return false;
  return (tree1->data == tree2->data) && isMirror(tree1->left, tree2->right) &&
         isMirror(tree1->right, tree2->left);
}
bool isSymmetric(BinaryTreeNode<int> *root) { return isMirror(root, root); }
// **************************************************************************************

// **************************************************************************************
// Given a binary tree, return the sum of values of nodes with even-valued
// grandparent.  (A grandparent of a node is the parent of its parent, if it
// exists.)

// If there are no nodes with an even-valued grandparent, return 0.

// Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
// Output: 18

int getGrandChildrenSum(BinaryTreeNode<int> *root, int depth = 0) {
  if (!root) return 0;
  if (depth == 2) return root->data;
  return getGrandChildrenSum(root->left, depth + 1) +
         getGrandChildrenSum(root->right, depth + 1);
}
int sumEvenGrandparent(BinaryTreeNode<int> *root) {
  if (!root) return 0;
  int sum = 0;
  if (root->data % 2 == 0) {
    sum += getGrandChildrenSum(root);
  }
  sum += sumEvenGrandparent(root->left) + sumEvenGrandparent(root->right);
  return sum;
}
// **************************************************************************************

// **************************************************************************************
// Given a binary tree, return the sum of values of its deepest leaves.
// Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
// Output: 15

int deepestLeavesSum(BinaryTreeNode<int> *root, int depth, int max) {
  if (!root) return 0;
  if (depth == max) return root->data;
  return deepestLeavesSum(root->left, depth + 1, max) +
         deepestLeavesSum(root->right, depth + 1, max);
}
int deepestLeavesSum(BinaryTreeNode<int> *root) {
  int max = maxDepth(root);
  return deepestLeavesSum(root, 1, max);
}
// **************************************************************************************

// **************************************************************************************
// Given two binary trees original and cloned and given a reference to a node
// target in the original tree. The cloned tree is a copy of the original tree.
// Return a reference to the same node in the cloned tree.
// Note that you are not allowed to change any of the two trees or the target
// node and the answer must be a reference to a node in the cloned tree. Follow
// up: Solve the problem if repeated values on the tree are allowed.
// Input: tree = [7,4,3,null,null,6,19], target = 3
// Output: 3
// Explanation: In all examples the original and cloned trees are shown. The
// target node is a green node from the original tree. The answer is the yellow
// node from the cloned tree.
BinaryTreeNode<int> *getTargetCopy(BinaryTreeNode<int> *original,
                                   BinaryTreeNode<int> *cloned,
                                   BinaryTreeNode<int> *target) {
  if (!original || !cloned) return nullptr;
  if (target == original) return cloned;
  BinaryTreeNode<int> *left =
      getTargetCopy(original->left, cloned->left, target);
  BinaryTreeNode<int> *right =
      getTargetCopy(original->right, cloned->right, target);
  return left ? left : right;
}
// **************************************************************************************

// **************************************************************************************
// Given a binary tree, print it vertically. The following example illustrates vertical 
// order traversal.
//            1
//         /    \ 
//        2      3
//       / \   /   \
//      4   5  6   7
//                /  \ 
//               8   9 
               
              
// The output of print this tree vertically will be:
// 4
// 2
// 1 5 6
// 3 8
// 7
// 9

void fillLevelMap(BinaryTreeNode<int> *root,
                  unordered_map<int, vector<int>> &map, int level = 0) {
  if (!root) return;
  map[level].push_back(root->data);
  fillLevelMap(root->left, map, level + 1);
  fillLevelMap(root->right, map, level - 1);
}

void printVertically(BinaryTreeNode<int> *root) {
  unordered_map<int, vector<int>> map;
  fillLevelMap(root, map);
  for (pair<int, vector<int>> p : map) {
    for (int i = 0; i < p.second.size(); i++) cout << p.second.at(i) << " ";
    cout << endl;
  }
}
// **************************************************************************************

vector<int> *longestPath(BinaryTreeNode<int> *root) {
  if (!root) {
    vector<int> *v = new vector<int>();
    return v;
  }
  vector<int> *left = longestPath(root->left);
  vector<int> *right = longestPath(root->right);
  if (left->size() > right->size()) {
    left->push_back(root->data);
    return left;
  } else {
    right->push_back(root->data);
    return right;
  }
}