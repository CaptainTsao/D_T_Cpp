cmake_minimum_required(VERSION 3.15)

project(DataStructure CXX C)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(DataStructure
        ArrayQueue.h
        BinaryTree.h
        BinaryTreeNode.h
        BinaryTreeTraversals.cc
        Booster.h
#        LinkedBinaryTree.cc
        LinkedBinaryTree.h
        MyExceptions.h
        Queue.h
        LinearList.h
        Chain.h
        ChainNode.h
#        infix.cpp
        Dictionary.h
        BsTree.h
        IndexedBsTree.h
        BinarySearchTree.h
#        dBinarySearchTree.h
        BiTree_LevelOrder.cpp
        DynamicProgramming.cpp
        maxPriorityQueue.hpp maxHeap.hpp changeLength1D.hpp LinkedQueue.h GraphLibrary/Node.cpp GraphLibrary/Node.hpp)