#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;

struct Node {
    Node* leftchild;
    Node* rightchild;
    Node* parent;
    int value;
};

class BST
{
private:
    Node* root;

public:
    BST() :root(0) {};
    ~BST() {
        cout << "Delete all nodes (Post-Order): ";
        Destroy(root);
        cout << endl << endl;
    };

    Node* GetRoot() { return root; }
    Node* Successor(Node* node);
    Node* Search(int value);
    void InsertNode(int value);
    void DeleteNode(int value);
    int ComputeHeight(Node* node);
    void InOrderPrint(Node* node);
    void LevelOrderPrint();
    void Destroy(Node* node);
};

#endif // !BST_H

#pragma once
