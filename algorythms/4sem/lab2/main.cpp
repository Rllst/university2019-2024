#include "tree.h"
#include <iostream>
int main() {
    Tree tree;
    for(int i=1;i<=10;i++){
tree.insert(i);
std::cout<<"insertion "<<i<<"-------------------------------------------"<<std::endl;
        tree.print2D(tree.root);}


    for(int i=10;i>=1;i--){
        tree.erase(tree.search(i));
        std::cout<<"deleting "<<i<<"-------------------------------------------"<<std::endl;
        tree.print2D(tree.root);}
    return 0;
}