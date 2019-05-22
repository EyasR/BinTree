// ----------------------------- BinTree.cpp/h ----------------------------------
// Eyas Rashid Assignment 2, CSS 343 B, Spring 2019
// Created on: 23/04/2019
// Last Modified on: 28/04/2019
// -----------------------------------------------------------------------------
// Purpose: Creates a binary search tree class with additional functionality
// by overloading or implementing Accessors (input, retrieve, getHeight ),
// operators (= , == , !=), and others ( BSTree to Array, Array to BSTree) as well
// as utility helper functions to support recursive functionality.
// -----------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
// Binary Tree has a MAX of 100 elements
// ------------------------------------------------------------------------------

#ifndef ASG2_EYASRASHID_BINTREE_H
#define ASG2_EYASRASHID_BINTREE_H
#include "nodedata.h"
using namespace std;
class BinTree {

// operator<< overload
friend ostream& operator<<(ostream &outStream, const BinTree &);

public:
    // constructors
    BinTree();								// constructor
    BinTree(const BinTree &);				// copy constructor

    // destructor
    ~BinTree();								// destructor, calls makeEmpty
    bool isEmpty() const;					// true if tree is empty, otherwise false
    void makeEmpty();						// make the tree empty so isEmpty returns true

    // Assignment operator overload
    BinTree& operator=(const BinTree &);

    // Comparison operator overload
    bool operator==(const BinTree &) const;
    bool operator!=(const BinTree &) const;

    // insertion function
    bool insert(NodeData*);

    // retrieve function
    bool retrieve(const NodeData &, NodeData* &);

    // Display tree side ways
    void displaySideways() const;			// provided below, displays the tree sideways1

    //get height of node in tree
    int getHeight(const NodeData &) const;

    // Creates an array from BSTree
    void bstreeToArray(NodeData* []);

    //Creates a BSTree from array
    void arrayToBSTree(NodeData* []);

private:
    struct Node {
        NodeData* data;						// pointer to data object
        Node* left;							// left subtree pointer
        Node* right;						// right subtree pointer
    };
    Node* root = NULL;								// root of the tree

    // utility functions
    void inorderHelper( Node*) const;

    void sideways(Node*, int) const;			// provided below, helper for displaySideways()

    void makeEmptyHelper( Node* & currentNode);

    void assignmentHelper ( Node*, Node* &);

    bool equalityComparisonHelper(Node*, Node*) const;

    bool retrieveHelper(Node* &, const NodeData &, NodeData* &) const;

    int getHeightHelper( const NodeData&, Node*) const;

    int recursiveGetHeightHelper( Node*) const;

    int bstreeToArrayHelper(Node*, NodeData* []);

    void arrayToBSTreeHelper(Node*, NodeData* [], int, int);

};


#endif //ASG2_EYASRASHID_BINTREE_H
