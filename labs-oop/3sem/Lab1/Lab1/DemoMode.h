#pragma once
#include "PriorityQueue.h"
#include "Date.h"
#include <iostream>
#include <string>
#include <random>


class DemoMode {
private:

    void _ListDemo() {
        PriorityQueue<Date>* queue = new PriorityQueue_List<Date>();
        std::cout << "Pushing" << std::endl;
        queue->push(Date(12, 3, 2005, 3, 25, 1, 0), 1);
        queue->push(Date(1, 5, 1995, 0, 4, 3), 1);
        queue->push(Date(12, 3, 1789, 3, 25, 55), 1);
        queue->push(Date(2, 7, 998, 1, 15, 22), 2);
        queue->push(Date(21, 11, 1544, 18, 40, 45), 0);
        queue->push(Date(1, 5, 1995, 10, 4, 55), 0);
        std::cout << "Queue : "; queue->print();

        std::cout << "\nQueue top: " << queue->top() << std::endl;
        std::cout << "Queue pop "; queue->pop();
        std::cout << "\nQueue top: " << queue->top() << std::endl;
    }

    void _TreeDemo() {
        PriorityQueue<Date>* queue = new PriorityQueue_Tree<Date>();
        std::cout << "Pushing" << std::endl;
        queue->push(Date(12, 3, 2005, 3, 25, 1, 0), 1);
        queue->push(Date(1, 5, 1995, 0, 4, 3), 1);
        queue->push(Date(12, 3, 1789, 3, 25, 55), 1);
        queue->push(Date(2, 7, 998, 1, 15, 22), 2);
        queue->push(Date(21, 11, 1544, 18, 40, 45), 0);
        queue->push(Date(1, 5, 1995, 10, 4, 55), 0);
        std::cout << "Queue : "; queue->print();

        std::cout << "\nQueue top: " << queue->top() << std::endl;
        std::cout << "Queue pop "; queue->pop();
        std::cout << "\nQueue top: " << queue->top() << std::endl;
    }

    void _VectorDemo() {
        PriorityQueue<Date>* queue = new PriorityQueue_Vector<Date>();
        std::cout << "Pushing" << std::endl;
        queue->push(Date(12,3,2005,3,25,1,0), 1);
        queue->push(Date(1,5,1995,0,4,3), 1);
        queue->push(Date(12,3,1789,3,25,55), 1);
        queue->push(Date(2,7,998,1,15,22), 2);
        queue->push(Date(21,11,1544,18,40,45), 0);
        queue->push(Date( 1,5,1995,10,4 ,55), 0);
        std::cout << "Queue : "; queue->print();

        std::cout << "\nQueue top: " << queue->top() << std::endl;
        std::cout << "Queue pop "; queue->pop();
        std::cout << "\nQueue top: " << queue->top() << std::endl;
    }

    void _HeapDemo() {
        PriorityQueue<Date>* queue = new PriorityQueue_Heap<Date>();
        std::cout << "Pushing" << std::endl;
        queue->push(Date(12, 3, 2005, 3, 25, 1, 0), 1);
        queue->push(Date(1, 5, 1995, 0, 4, 3), 1);
        queue->push(Date(12, 3, 1789, 3, 25, 55), 1);
        queue->push(Date(2, 7, 998, 1, 15, 22), 2);
        queue->push(Date(21, 11, 1544, 18, 40, 45), 0);
        queue->push(Date(1, 5, 1995, 10, 4, 55), 0);
        std::cout << "Queue : "; queue->print();

        std::cout << "\nQueue top: " << queue->top() << std::endl;
        std::cout << "Queue pop "; queue->pop();
        std::cout << "\nQueue top: " << queue->top() << std::endl;
    }


public: 

    void startDemoMode() {
        int queueType;

        std::cout << "Choose queue type: 1 - List, 2 - Vector, 3 - Tree, 4 - Heap" << std::endl;
        std::cin >> queueType;

        //TODO: check if input is valid; 

        switch (queueType) {
        case 1: {
            _ListDemo();
            break;
        }
        case 2: {
            _VectorDemo();
            break;
        }
        case 3: {
            _TreeDemo();
            break;
        }
        case 4: {
            _HeapDemo();
            break;
        }
        }

    }




};

