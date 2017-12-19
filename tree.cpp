// James Mathew
// tree.cpp
// This class takes in integers and put them in a binart tree.

#include "tree.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <stack>
using namespace std;

Tree :: Tree(int val)
{
  maxHeight = 0;
  root = nullptr;
  insertVal(root, val);
}

Tree :: Tree(const Tree& t)
{
  if (t.root == nullptr) {
    root = nullptr;
  } else {
    root = makeCopy(t.root);
  }
}

Tree& Tree :: operator = (const Tree& rhs)
{
  if (this != &rhs) {
    deleteTree(root);
    root = makeCopy(rhs.root);  
  }
  return *this;
}

Tree :: ~Tree()
{
  deleteTree(root);
}

Tree :: TreeNode* Tree :: makeCopy(TreeNode* r)
{  
  if (r == nullptr) {
    return nullptr;
  } else {    
    TreeNode* temp = new TreeNode;
    temp->data = r->data;
    temp->left = makeCopy(r->left);
    temp->right = makeCopy(r->right);
    return temp;  
  } 
}

void Tree :: deleteTree(TreeNode*& root)
{ 
  if (root != nullptr) {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
  }
}

bool Tree :: insertVal(int val)
{
  return insertVal(root, val);
}

bool Tree :: insertVal(TreeNode*& root, int val)
{
  if(root == nullptr) {
    root = new TreeNode;
    root->data = val;
    return true;
  } else if (val > root->data) {
    return insertVal(root->right, val);
  } else if (val < root->data) {
    return insertVal(root->left, val);
  }
  return false;
}

bool Tree :: findVal(int val)
{
  return findVal(root, val);
}

bool Tree :: findVal(TreeNode* root, int val)
{
  if (root!= nullptr) {
		if (root->data == val) {
          return true;
		} else if (val < root->data) {
          return findVal(root->left, val);
		} else if (val > root->data) {
          return findVal(root->right, val);
		}
  }
  return false;
}

int Tree :: min() 
{
  return min(root);
}

int Tree :: min(TreeNode* root)
{
  if (root != nullptr && root->left == nullptr) {
    return root->data;
  } else if (root != nullptr) {
    return min(root->left);
  }
  return 0;
}

int Tree :: max()
{
  return max(root);
}

int Tree :: max(TreeNode* root)
{
  if (root != nullptr && root->right == nullptr) {
    return root->data;
  } else if (root != nullptr) {
    return max(root->right);
  }
  return 0;
}


int Tree :: height()
{
  height(root,0);
  return maxHeight;
}

void Tree :: height(TreeNode* root,int maxH)
{
  if (root != nullptr && root->left == nullptr && root->right == nullptr) {
    maxH++;
    if (maxH > maxHeight) {
      maxHeight = maxH;
    }
  } else if (root != nullptr) {
    maxH++; 
    height(root->left, maxH);
    height(root->right, maxH);
  }
  
}

void Tree ::  printInOrder(){
  printInOrder(root);
}

void Tree :: printInOrder(TreeNode* root)
{
  stack<TreeNode*> nodes;
  TreeNode* current = root;
  TreeNode* temp;
  // bool x = true;
  while(current != nullptr && !nodes.empty()) {
    while(current != nullptr) {
      nodes.push(current);
      current = current->left;
    }
    while (current == nullptr && !nodes.empty()) {
      temp = nodes.top();
      nodes.pop();
      cout << temp->data << endl;
      current = temp->right;
    }
    // if (current == nullptr && nodes.empty()) {
      // x = false;
    // }
  }
}

void Tree :: printPreOrder()
{
  printPreOrder(root);
}

void Tree :: printPreOrder(TreeNode* root)
{
  if (root != nullptr) {
    cout << root->data << endl;
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

void Tree :: remove(int val)
{
  if (findVal(val)) {
    TreeNode* parent;
    if (root == nullptr) {
      return;
    }
    if (root->data == val) {
      makeDeletion(root);
    } else { 
      parent = findParent(root, val);
      if (parent != nullptr){
        if (parent->left != nullptr && parent->left->data == val) {
          makeDeletion(parent->left);
        } else {
          makeDeletion(parent->right);
        }	
		
      }  
    }
  }
}

Tree :: TreeNode* Tree :: findParent(TreeNode* root, int val)
{
  if (root != nullptr)  {
    if (val < root->data){
      if (val == root->left->data) {
        return root;
      } else {
        return findParent(root->left, val);
      }
    } else {
      if (val == root->right->data) {
        return root;
      } else {
        return findParent(root->right, val);
      }			
    }
  }
  return root;
}

void Tree :: makeDeletion(TreeNode*& root)
{
  TreeNode* tempRoot;
  if (root->right == nullptr) {
    // only left child or none
    tempRoot = root;
    root = root->left;
    delete tempRoot;
  } else if (root->left == nullptr) {
    // only right child
    tempRoot = root;
    root = root->right;
    delete tempRoot;
  } else {
    // there are two children
    tempRoot = root->right;
    while (tempRoot->left) {
      tempRoot = tempRoot->left;
    }
    tempRoot->left = root->left;
    tempRoot = root;
    root = root->right;
    delete tempRoot;  
  }
}
