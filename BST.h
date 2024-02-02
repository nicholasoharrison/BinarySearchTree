#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int COUNT = 5; // For 2D tree printing and spacing

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* next; // Pointer for twin chaining

    Node(int value) : data(value), left(nullptr), right(nullptr), next(nullptr) {}
};



class BST {
private:
    
    Node* root;

    // Print the BST using 2D representation
    void print2D(Node* root, int space, ostream& out);

      

    // Counts the number of twins in a twin chain
    int countTwins(Node* node);

public:
    BST() : root(nullptr) {} //Constructor sets the root node to null

    // Inserts a new node into the BST
   void insert(int value);

    // Recursive insertion
    Node* insertRecursive(Node* current, int value);

    // Calculates the height of the tree
    int height(Node* node);

    // Prints the BST to a file and the console
    void printTree(ofstream& outputFile);

    // Printing with inorder traversal
    void printTreeRecursive(Node* current);

    // Printing twin chain duplicates
    void printTwinChain(Node* node);

    // Inorder traversal to print to file
    void printTreeRecursiveToFile(Node* current, ofstream& outputFile);

    // Prints twin chain values to file
    void printTwinChainToFile(Node* node, ofstream& outputFile);

    // Prints the BST using 2D representation to the console
    void print2DConsole();

    // Prints the BST using 2D representation to a specified output stream
    void print2DToFile(ofstream& outputFile);


};

