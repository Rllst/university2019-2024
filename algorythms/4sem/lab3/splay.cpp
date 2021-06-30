//
// Created by User on 015 15.04.21.
//
#include "splay.h"

void SplayTree::splay(Node *x) {
    {
        while (x -> parent != nullptr)
        {
            Node *p = x -> parent;
            Node *g = p -> parent;
            if (g == nullptr) zig(x);
            else if (g -> left == p && p -> left == x) zigzig(x);
            else if (g -> right == p && p -> right == x) zigzig(x);
            else zigzag(x);
        }
        this -> root = x;
    }
}



void SplayTree::zig(Node *x) {
    Node *p = x -> parent;
    if (p -> left == x)
    {
        Node *A = x -> left;
        Node *B = x -> right;
        Node *C = p -> right;

        x -> parent = nullptr;
        x -> right = p;

        p -> parent = x;
        p -> left = B;

        if (B != nullptr) B -> parent = p;
    }
    else
    {
        Node *A = p -> left;
        Node *B = x -> left;
        Node *C = x -> right;

        x -> parent = nullptr;
        x -> left = p;

        p -> parent = x;
        p -> right = B;

        if (B != nullptr) B -> parent = p;
    }
}

void SplayTree::zigzig(Node *x) {
    Node *p = x -> parent;
      Node *g = p -> parent;
    if (p -> left == x)
    {
        Node *A = x -> left;
        Node *B = x -> right;
        Node *C = p -> right;
        Node *D = g -> right;

        x -> parent = g -> parent;
        x -> right = p;

        p -> parent = x;
        p -> left = B;
        p -> right = g;

        g -> parent = p;
        g -> left = C;


        if (x -> parent != nullptr)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }

        if (B != nullptr) B -> parent = p;

        if (C != nullptr) C -> parent = g;
    }
    else
    {
        Node *A = g -> left;
        Node *B = p -> left;
        Node *C = x -> left;
        Node *D = x -> right;

        x -> parent = g -> parent;
        x -> left = p;

        p -> parent = x;
        p -> left = g;
        p -> right = C;

        g -> parent = p;
        g -> right = B;

        if (x -> parent != nullptr)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }

        if (B != nullptr) B -> parent = g;

        if (C != nullptr) C -> parent = p;
    }
}

void SplayTree::zigzag(Node *x) {
    Node *p = x -> parent;
    Node *g = p -> parent;
    if (p -> right == x)
    {
        Node *A = p -> left;
        Node *B = x -> left;
        Node *C = x -> right;
        Node *D = g -> right;

        x -> parent = g -> parent;
        x -> left = p;
        x -> right = g;

        p -> parent = x;
        p -> right = B;

        g -> parent = x;
        g -> left = C;

        if (x -> parent != nullptr)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }

        if (B != nullptr) B -> parent = p;

        if (C != nullptr) C -> parent = g;
    }
    else
    {
        Node *A = g -> left;
        Node *B = x -> left;
        Node *C = x -> right;
        Node *D = p -> right;

        x -> parent = g -> parent;
        x -> left = g;
        x -> right = p;

        p -> parent = x;
        p -> left = C;

        g -> parent = x;
        g -> right = B;

        if (x -> parent != nullptr)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }

        if (B != nullptr) B -> parent = g;

        if (C != nullptr) C -> parent = p;
    }
}

void SplayTree::insert(int x) {
    if (root == nullptr)
    {
        root = new Node(x);
        return;
    }
    Node *curr = this -> root;
    while (curr != nullptr)
    {
        if (x < curr -> value)
        {
            if (curr -> left == nullptr)
            {
                Node *newNode = new Node(x);
                curr -> left = newNode;
                newNode -> parent = curr;
                splay(newNode);
                return;
            }
            else curr = curr -> left;
        }
        else if (x > curr -> value)
        {
            if (curr -> right == nullptr)
            {
                Node *newNode = new Node(x);
                curr -> right = newNode;
                newNode -> parent = curr;
                splay(newNode);
                return;
            }
            else curr = curr -> right;
        }
        else
        {
            splay(curr);
            return;
        }
    }
}

SplayTree::Node* SplayTree::find(int x) {
    Node *ret = nullptr;
    Node *curr = this -> root;
    Node *prev = nullptr;
    while (curr != nullptr)
    {
        prev = curr;
        if (x < curr -> value) curr = curr -> left;
        else if (x > curr -> value) curr = curr -> right;
        else
        {
            ret = curr;
            break;
        }
    }
    if (ret != nullptr) splay(ret);
    else if (prev != nullptr) splay(prev);
    return ret;
}

void SplayTree::Delete(int x) {
    Node *del = find(x);
    if (del == nullptr)
    {
        return;
    }
    Node *L = del -> left;
    Node *R = del -> right;
    if (L == nullptr && R == nullptr)
    {
        this -> root = nullptr;
    }
    else if (L == nullptr)
    {
        Node *M = min(R);
        splay(M);
    }
    else if (R == nullptr)
    {
        Node *M = max(L);
        splay(M);
    }
    else
    {
        Node *M = max(L);
        splay(M);
        M -> right = R;
        R -> parent = M;
    }
    delete del;

}

SplayTree::Node *SplayTree::max(SplayTree::Node *subroot) {
    Node *curr = subroot;
    while (curr -> right != nullptr) curr = curr -> right;
    return curr;
}

SplayTree::Node *SplayTree::min(SplayTree::Node *subroot) {
    Node *curr = subroot;
    while (curr -> left != nullptr) curr = curr -> left;
    return curr;
}

void SplayTree::split(int t) {
    Node* successor = nullptr;
    Node* temp = root;

    while(temp != nullptr){
        if(temp->value == t) {
            successor = temp;
            break;
        }
        if(temp->value > t) {
            successor = temp;
            temp = temp->left;
        } else
            temp = temp->right;
    }


    if (successor == nullptr) {
        successor = root;
        while (successor->right != nullptr)
            successor = successor->right;
    }

    splay(successor);

    Node* toInsert = new Node(t);

    if(successor->value >= toInsert->value) {

        toInsert->left = successor->left;
        if (toInsert->left != nullptr)
            toInsert->left->parent = toInsert;
        successor->left = nullptr;
        toInsert->right = successor;

    } else
        toInsert->left = successor;

    successor->parent = toInsert;
    root = toInsert;
}

void SplayTree::merge(SplayTree::Node *rootL, SplayTree::Node *rootR) {
    if(rootL == nullptr && rootR == nullptr){
        root = nullptr;
        return;
    }
    if(rootL == nullptr){
        root = rootR;
        return;
    }
    if(rootR == nullptr){
        root = rootL;
        return;
    }

    Node* maxLeft = rootL->right;

    if(maxLeft == nullptr) {
        rootL->right = rootR;
        rootR->parent = root;
        this->root = rootL;
        return;
    }

    while (maxLeft->right != nullptr)
        maxLeft = maxLeft->right;

   SplayTree tr(rootL);
   tr.splay(maxLeft);



    //splay(maxLeft, rootLeft);

   tr.root->right = rootR;
    rootR->parent = tr.root;
   this->root = tr.root;

}

