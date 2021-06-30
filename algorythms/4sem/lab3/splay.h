//
// Created by User on 015 15.04.21.
//

#ifndef LAB3_SPLAY_H
#define LAB3_SPLAY_H
#define COUNT 10
#include <iostream>
#include <string>
class SplayTree{
public:
    class Node{
    public:
        int value;
        Node *parent;
        Node *left;
        Node *right;
        Node(){

            parent=left=right= nullptr;
        }
        Node(int _data){
            value=_data;
            parent=left=right= nullptr;
        }


    };

    Node *root;
    SplayTree(){
        root= nullptr;
    }
    SplayTree(Node* rt){
        root= rt;
    }
    void splay(Node *x);
    void merge(Node* rootL,Node* rootR);
    void split(int t);
    void zig(Node *x);
    void zigzig(Node *x);
    void zigzag(Node *x);
    Node* find(int x);
    void insert(int x);
    void Delete(int x);
    Node* max(Node* subroot);
    Node* min(Node* subroot);


    void printBT(const std::string& prefix, const Node* node, bool isLeft)
    {
        if( node != nullptr )
        {
            std::cout << prefix;

            std::cout << (isLeft ? "|->" : "|_" );

            // print the value of the node
            std::cout << node->value << std::endl;
            std::string pr1;
            pr1 = prefix + (isLeft ? "I   " : "    ");

            // enter the next tree level - left and right branch
            printBT( pr1, node->left, true);
            printBT( pr1, node->right, false);
        }
    }

    void printBT(const Node* node)
    {
        printBT("", node, false);
    }


};
#endif //LAB3_SPLAY_H
