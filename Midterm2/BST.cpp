#include"BST.h"
#include <iostream>
#include <queue>

using namespace std;



Node* BST::Search(int value) {
    //TODO: search the node with value
    //if the node does't exist, return NULL
    //otherwise return the node
    Node* a = root;
    while (a != NULL && value != a->value) {
        if (value < a->value) {
            a = a->leftchild;
        }
        else {
            a = a->rightchild;
        }
    }
    return a;

}

Node* BST::Successor(Node* node) {
    //TODO: find the successor of the given node and return it
    if (node->rightchild != NULL) {
        while (node->leftchild != NULL) {
            node = node->leftchild;
        }
        return node;
    }
    Node* a = node->parent;
    while (a != NULL && node == a->rightchild) {
        node = a;
        a = a->parent;
    }
    return a;

}

void BST::InsertNode(int value) {
    //TODO: insert a node with value to the BST
    Node* parent=new Node;
    Node* child=new Node;
    Node* answer = new Node;
    answer->value = value;
    
    child = root;
    while (child != NULL) {
        parent = child;
        if (answer->value < answer->value) {
            child = child->leftchild;
        }
        else {
            child = child->rightchild;
        }
    }
    answer->parent = parent;
    if (parent == NULL) {
        root = answer;
    }
    else if (answer->value < parent->value) {
        parent->leftchild = answer;
    }
    else {
        parent->rightchild = answer;
    }

}

void BST::DeleteNode(int value) {
    Node* delete_node = Search(value);
    if (delete_node == NULL) {
        cout << value << " not found.\n";
        return;
    }

    Node* d = new Node;
    Node* child = new Node;

    //Case 1:
    if (delete_node->leftchild == NULL && delete_node->rightchild == NULL) {
        cout << "Delete case 1\n";
        //TODO: delete node with case 1
        d = delete_node;

    }
    else {
        d = Successor(delete_node);
    }
    //Case 2:
    if (delete_node->leftchild != NULL && delete_node->rightchild != NULL) {
        cout << "Delete case 2\n";
        //TODO: delete node with case 2

    }

    //Case 3:
    cout << "Delete case 3\n";
    if (delete_node->leftchild != NULL) {
        //TODO: delete node with case 3 (left)

    }
    else {
        //TODO: delete node with case 3 (right)

    }
}

int BST::ComputeHeight(Node* node) {
    //TODO: compute the height of the BST
    return 0;
}

void BST::InOrderPrint(Node* node) {
    //TODO: print the BST in in-order method
    if (node != NULL) {
        InOrderPrint(node->leftchild);
        cout << node->value << " ";
        InOrderPrint(node->rightchild);
   }

}

void BST::LevelOrderPrint() {
    //TODO: print the BST in level-order method
    queue<Node*>a;
    a.push(root);
    while (a.empty() == false) {
        Node* answer = a.front();
        a.pop();
        cout << answer->value << " ";
        if (answer->leftchild != NULL) {
            a.push(answer->leftchild);
        }
        if (answer->rightchild != NULL) {
            a.push(answer->rightchild);
        }
    }
}

void BST::Destroy(Node* node) {
    //TODO: delete all node in the BST
    //TODO: print node value in post-order method before delete it

}