#include <iostream>
#include "splay.h"
int main() {
    SplayTree tree,tree1;
    int ar[10] = { 7, 5, 3, 6, 8, 4, 9, 1, 2, 10};

    for(int i=0;i<=10 ;i++){

        tree.insert(rand()%20);
        std::cout<<std::endl << "------------insert---------" << std::endl;
        tree.printBT(tree.root);


}
   // tree.split(8);


    for(int i=11;i<=20 ;i++){

        tree1.insert(rand()%20);
        std::cout<<std::endl << "------------insert---------" << std::endl;
        tree1.printBT(tree.root);


    }
    SplayTree tree2;
    tree2.merge(tree.root,tree1.root);
    tree2.printBT(tree2.root);
}
