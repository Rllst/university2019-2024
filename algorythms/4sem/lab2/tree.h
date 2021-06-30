//
// Created by User on 027 27.03.21.
//

#ifndef LAB2_TREE_H
#define LAB2_TREE_H
#define COUNT 10
#include <iostream>
class Tree {
public:
    class Node {
    public:
        int value;
        int size;
        bool color;
        Node *right;
        Node *left;
        Node *parent;

        Node(){
            size=1;
            color=1;
            left=right=parent=nullptr;
        }
        Node(int value) {
            this->value = value;
            left = right = parent = nullptr;
            color= false;
            size = 0;
        }
    };
Node *root;
Tree(){
        root= nullptr;
    }


    void leftRotate(Node *rotated){
    Node *rightSon = rotated->right;
    rotated->right = rightSon->left;

    if (rightSon->left != nullptr)
        rightSon->left->parent = rotated;
    rightSon->parent = rotated->parent;
    if (rotated->parent == nullptr){
        root = rightSon;
    } else if (rotated == rotated->parent->left)
        rotated->parent->left = rightSon;
    else
        rotated->parent->right = rightSon;

    rightSon->left = rotated;
    rotated->parent = rightSon;

    rightSon->size = rotated->size;
    rotated->size = 1;
    if (rotated->left != nullptr)
        rotated->size += rotated->left->size;
    if (rotated->right != nullptr)
        rotated->size += rotated->right->size;
}
    void rightRotate(Node *rotated){
        Node *leftSon = rotated->left;
        rotated->left = leftSon->right;

        if (leftSon->right != nullptr)
            leftSon->right->parent = rotated;
        leftSon->parent = rotated->parent;
        if (rotated->parent == nullptr){
            root = leftSon;
        } else if (rotated== rotated->parent->left)
            rotated->parent->left = leftSon;
        else
            rotated->parent->right = leftSon;

        leftSon->right = rotated;
        rotated->parent = leftSon;

        leftSon->size = rotated->size;
        rotated->size = 1;
        if (rotated->left != nullptr)
            rotated->size += rotated->left->size;
        if (rotated->right != nullptr)
            rotated->size += rotated->right->size;
    }

    void insert(int data) {
    Node *node = new Node(data);
    if (root == nullptr){
        root = node;
        root->parent = nullptr;
        fixInsertion(root);
        return;
    }

    Node* x = root;
    Node* parent = nullptr;
    while (x != nullptr){
        parent = x;
        if (x->value < node->value)
            x = x->right;
        else
            x = x->left;
    }
    node->parent = parent;
    if (parent == nullptr)
        root = node;
    else{
        if (parent->value > node->value)
            parent->left = node;
        else
            parent->right = node;
    }

    while (parent != nullptr){
        parent->size++;
        parent = parent->parent;
    }
    fixInsertion(node);
}
    void fixInsertion(Node *node) {
    if (node == root) {
        root->color = 1;
        return;
    }
    while(node->parent != nullptr && node->parent->color == 0){
        if (node->parent == node->parent->parent->left){
            Node* uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == 0){
                node->parent->color = 1;
                uncle->color = 1;
                node->parent->parent->color = 0;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right){
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                rightRotate(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == 0){
                node->parent->color = 1;
                uncle->color = 1;
                node->parent->parent->color = 0;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left){
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = 1;
}

    void print2DUtil(Node *root, int space)
    {
        // Base case
        if (root == NULL)
            return;

        // Increase distance between levels
        space += COUNT;

        // Process right child first
        print2DUtil(root->right, space);

        // Print current node after space
        // count
        std::cout<<std::endl;
        for (int i = COUNT; i < space; i++)
            std::cout<<" ";
        std::cout<<root->value;
        if(root->color) std::cout<<" black"; else  std::cout<<" red";
        std::cout<<" "<< root->size<<std::endl;

        // Process left child
        print2DUtil(root->left, space);
    }
    void print2D(Node *root)
    {
        // Pass initial space count as 0
        print2DUtil(root, 0);
    }

    void fixErasing(Node *node) {
        while (node != root && node->color == 1) {
            Node* parent = node->parent;
            if (parent->left == node) {
                Node* brother = parent->right;
                if (brother->color == 0) {
                    brother->color = 1;
                    parent->color = 0;

                    leftRotate(parent);
                    brother = parent->right;
                }
                if ((brother->left == nullptr || brother->left->color == 1) &&
                    (brother->right == nullptr || brother->right->color == 1)) {
                    brother->color = 0;
                    node = node->parent;

                } else {
                    if (brother->right == nullptr || brother->right->color == 1) {
                        brother->color = 0;
                        brother->left->color = 1;

                        rightRotate(brother);
                        brother = parent->right;
                    }

                    brother->color = parent->color;
                    parent->color = 1;

                    if (brother->right)
                        brother->right->color = 1;

                    leftRotate(parent);

                    node = root;
                }
            } else {
                Node* brother = parent->left;
                if (brother->color == 0) {
                    brother->color = 1;
                    parent->color = 0;

                    rightRotate(parent);
                    brother = parent->left;
                }

                if ((brother->left == nullptr || brother->left->color == 1) &&
                    (brother->right == nullptr || brother->right->color == 1)) {
                    brother->color = 0;
                    node = node->parent;

                } else {
                    if (brother->left == nullptr || brother->left->color == 1) {
                        brother->color = 0;
                        brother->right->color = 1;

                        leftRotate(brother);
                        brother = parent->left;
                    }

                    brother->color = parent->color;
                    parent->color = 1;

                    if (brother->left)
                        brother->left->color = 1;

                    rightRotate(parent);

                    node = root;
                }
            }
        }
        node->color = 1;
    }
    void erase(Node *node) {
    if (root== nullptr){
        std::cout<<"tree is empty"<<std::endl;
        return;
    }
    if(root->left== nullptr && root->right== nullptr){
        root= nullptr;
        return;
    }
        if (node == root && node->size == 1){
            clearMemory(root);
            root = nullptr;
            return;
        }
        Node* tempNode;
        Node* parent = node->parent;
        if (node->color == 0){
            if (node->right == nullptr && node->left == nullptr){ // R0
                if (parent->right == node)
                    parent->right = nullptr;
                else
                    parent->left = nullptr;

                clearMemory(node);
                while (parent != nullptr){
                    parent->size--;
                    parent = parent->parent;
                }
                return;
                // R1 not exist
            } else {                                               // R2
                tempNode = getSuccessor(node);
                node->value = tempNode->value;
                erase(tempNode);
                return;
            }

        } else {
            if (node->right == nullptr && node->left == nullptr){ //B0
                fixErasing(node);
                if (parent->left == node)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;


                clearMemory(node);
                while (parent != nullptr){
                    parent->size--;
                    parent = parent->parent;
                }
                return;
            }

            if (node->right == nullptr || node->left == nullptr){ //B1
                parent = node;
                if (node->right != nullptr) {
                    node->value = node->right->value;

                    clearMemory(node->right);
                    node->right = nullptr;
                } else {
                    node->value = node->left->value;

                    clearMemory(node->left);
                    node->left = nullptr;
                }

                while (parent != nullptr){
                    parent->size--;
                    parent = parent->parent;
                }
                return;
            }
            if (node->right != nullptr && node->left != nullptr){ //B2
                tempNode = getSuccessor(node);
                node->value = tempNode->value;
                erase(tempNode);
                return;
            }
        }
    }

    void clearMemory(Node* node) {
        if (node != nullptr){
            if (node->right)
                clearMemory(node->right);
            if (node->left)
                clearMemory(node->left);
            delete node;
        }
    }
    Node* search(int data) {
        Node* temp = root;
        while (temp != nullptr && temp->value != data){
            if (temp->value > data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return temp;
    }
    Node* getSuccessor(Node *node) {
        if (node->right)
            return getMinNode(node->right);

        Node* successor = node->parent;

        while (successor && successor->right == node) {
            node = successor;
            successor = successor->parent;
        }

        return successor;
    }
    Node* getMinNode(Node *node) const{
        while (node && node->left)
            node = node->left;

        return node;
    }

    Node* getStat(Node* node, int index){
        int curPos = 1;
        if (node->left != nullptr)
            curPos += node->left->size;

        if(curPos == index)
            return node;
        if(curPos > index)
            return getStat(node->left, index);
        else
            return getStat(node->right, index - curPos);

    }


};

#endif //LAB2_TREE_H
