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

#include "BinTree.h"
using namespace std;


// --------------------- Default Constructor --------------------
// Creates an empty Binary Search Tree with the root set to NULL.
// --------------------------------------------------------------
BinTree::BinTree(){
    root = NULL;
} // end of BinTree

// --------------------- Copy Constructor -----------------------------------
// Creates a deep copy of the Binary Search tree passed into the constructor.
// --------------------------------------------------------------------------
BinTree::BinTree(const BinTree &rhsTree){
    assignmentHelper(rhsTree.root, root);

} // end of BinTree

// --------------------- Destructor -----------------------------
// Calls makeEmpty() to delete a Binary Search Tree.
// --------------------------------------------------------------
BinTree::~BinTree(){
    makeEmpty();
}// end of ~BinTree

// --------------------- isEmpty --------------------------------
// Checks if a Binary Search Tree is empty.
// --------------------------------------------------------------
bool BinTree::isEmpty() const{
    return root == NULL;

} // end of isEmpty

// --------------------- makeEmpty ------------------------------
// Deletes Binary Search Tree.
// --------------------------------------------------------------
void BinTree::makeEmpty(){
    if(!isEmpty()){
        makeEmptyHelper(root);
    }

} // end of makeEmpty

// --------------------- makeEmptyHelper ------------------------
// Helper function for makeEmpty.
// --------------------------------------------------------------
void BinTree::makeEmptyHelper(Node*& currentNode){
   if(currentNode->left != NULL) {
       makeEmptyHelper(currentNode->left);
   }
   if (currentNode->right != NULL) {
       makeEmptyHelper(currentNode->right);
   }

   delete currentNode->data;
   delete currentNode;
   currentNode = NULL;

} // end of makeEmptyHelper

// --------------------- Overloaded << --------------------------
// Displays data from the BSTree in order.
// --------------------------------------------------------------
ostream &operator<<(ostream &output, const BinTree &tree) {
    tree.inorderHelper(tree.root);
    output << endl;
    return output;
} // end of operator<<

// --------------------- inorderHelper --------------------------
// Helper function for overloaded operator<<.
// --------------------------------------------------------------
void BinTree::inorderHelper(Node* currentNode) const {
    // traverses inorder and outputs data
    if (currentNode != NULL) {
        inorderHelper(currentNode->left);
        cout << *currentNode->data << " ";
        inorderHelper(currentNode->right);
    }
} // end of inorderHelper


// --------------------- Overloaded = --------------------------
// Makes the left Binary Search Tree a deep copy
// of the right Binary Search Tree.
// -------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &rightTree){
    // check if both trees are equivalent
    if (*this == rightTree){
        return *this;
    }

    makeEmpty();  // deletes the left tree
    assignmentHelper(rightTree.root, root);
    return *this;   // returns leftTree when  leftTree == rightTree
} // end of operator=

// --------------------- assignmentHelper -----------------------
// Helper function to overloaded assignment operator
// --------------------------------------------------------------
void BinTree::assignmentHelper(Node* rhsTree, Node* &lhsTree){
    // checks if rhsTrees pointer is Null
    if (rhsTree != NULL){

        Node * temp = new Node;
        // Copies rhsTree Node to tempNode
        NodeData *tempNode = new NodeData(*rhsTree->data);
        temp->data = tempNode;
        // set left tree data to temp
        lhsTree = temp;

        // traverse left
        assignmentHelper(rhsTree->left, lhsTree->left);
        // traverse right
        assignmentHelper(rhsTree->right, lhsTree->right);
    } else {
        lhsTree = rhsTree;  //
    }
} // end of assignmentHelper

// --------------------- Overloaded == --------------------------
// Checks if two Binary Search Trees are the equivalent.
// --------------------------------------------------------------
bool BinTree::operator==(const BinTree &rhsTree) const {
        return equalityComparisonHelper(root, rhsTree.root);

} // end of operator==

// --------------------- equalityComparisonHelper ---------------
// Helper function for overloaded operator ==.
// --------------------------------------------------------------
bool BinTree::equalityComparisonHelper(Node* leftNode, Node* rightNode) const {
    // if compared nodes == NULL
    if (leftNode == NULL && rightNode == NULL){
        return true;
    }
    // if one node is NULL and other is not
    if (leftNode == NULL || rightNode == NULL){
        return false;
    }

    // Compared Nodes contain the same Data
    // continue traversal of both trees
    return (*leftNode->data == *rightNode->data
            && equalityComparisonHelper(leftNode->left, rightNode->left)
            && equalityComparisonHelper(leftNode->right, rightNode->right));
} // end of equalityComparisonHelper

// --------------------- Overloaded != --------------------------
// Checks if two Binary Search Trees are not equivalent.
// --------------------------------------------------------------
bool BinTree::operator!=(const BinTree &rhsTree) const{
    return !(*this == rhsTree);
} // end of operator!=

// --------------------- insert -----------------------------------
// Inserts a new node containing NodeData into a Binary Search Tree
// ----------------------------------------------------------------
bool BinTree::insert(NodeData* insertNode){
    // temp n=Node to store insert Node
    Node* temp = new Node;
    // points temp data to insert Node
    temp->data = insertNode;
    //insertNode = NULL;
    temp->left = NULL;
    temp->right = NULL;

    if (isEmpty()) {
        root = temp;
    } else {
        Node* current = root;
        bool inserted = false;

        while (!inserted) {
            // if node is a duplicate of a node in the tree
            if (*temp->data == *current->data) {
                delete temp;
                return false;
            }

            else if (*temp->data < *current->data) {
                // if current Nodes left child is NULL insert Node
                if (current->left == NULL) {
                    current->left = temp;
                    inserted = true;
                }
                // traverse to left
                else
                    current = current->left;
            } else {
                // if current Nodes right child is NULL insert Node
                if (current->right == NULL) {
                    current->right = temp;
                    inserted = true;
                }
                // traverse to right
                else
                    current = current->right;
            }
        }
    }
    return true;

} // end of insert

// --------------------- retrieve -------------------------------
// Checks whether or not a Node is in a Binary Search Tree.
// --------------------------------------------------------------
bool BinTree::retrieve(const NodeData &retrieveNode, NodeData* &nodeRetrieved){
    retrieveHelper(this->root, retrieveNode, nodeRetrieved);

    if (nodeRetrieved != NULL){
        return true;    // Node is found
    }

    return false;   // Node is not found
} // end of retrieve

// --------------------- retrieveHelper ------------------------- checked
// Helper function for retrieve.
// --------------------------------------------------------------
bool BinTree::retrieveHelper(Node* &currentNode, const NodeData &retrieveNode,
                             NodeData* &nodeRetrieved) const {
    // if Node is not found
    if (currentNode == NULL){
        nodeRetrieved = NULL;
        return false;
    }
    // if Node is found
    if (*currentNode->data == retrieveNode){
        nodeRetrieved = currentNode->data;
        return true;
     // if current node < retrieved node then traverse right
    } else if (*currentNode->data < retrieveNode){
        retrieveHelper(currentNode->right, retrieveNode, nodeRetrieved);
    // if current node > retrieve node then traverse left
    } else if (*currentNode->data > retrieveNode){

        retrieveHelper(currentNode->left, retrieveNode, nodeRetrieved);

    } else {

        return false;
    }
} // end of retrieveHelper

// --------------------- getHeight ------------------------------
// Returns the height of a node in a Binary Tree
// --------------------------------------------------------------
int BinTree::getHeight(const NodeData &findNode) const{
    return getHeightHelper(findNode, root);
} // end of getHeight

// --------------------- getHeightHelper ------------------------
// Helper function to getHeight
// --------------------------------------------------------------
int BinTree::getHeightHelper(const NodeData &findNode, Node* currentNode) const {
    // if current node is not in tree then height = 0
    if (currentNode == NULL) {
        return 0;

     // if node is found
    } else if (*currentNode->data == findNode){
        return recursiveGetHeightHelper(currentNode);

    } else {
        // searches left node
        int left = getHeightHelper(findNode, currentNode->left);
        // searches right node
        int right = getHeightHelper(findNode, currentNode->right);

        return max(left, right);
    }
} // end of getHeightHelper

// --------------------- secondGetHeightHelper -----------------
// Helper function to getHeightHelper
// -------------------------------------------------------------
int BinTree::recursiveGetHeightHelper(Node* currentNode) const{
    // leaf node
    if (currentNode == NULL){
        return 0;
    }
    // finds the height of node
    else {
        // counts the amount of levels in the tree from root node
        return 1 + max(recursiveGetHeightHelper(currentNode->left),
                recursiveGetHeightHelper(currentNode->right));
    }
} // end of recursiveGetheightHelper

// --------------------- bstreeToArrayHelper -------------------------
// Transfers all of the nodes from a Binary Search Tree into an array.
// -------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* bstreeArray[]){
    bstreeToArrayHelper(root, bstreeArray);
    makeEmpty();
} // end of bstreeToArray

// --------------------- bstreeToArrayHelper --------------------
// Helper function to bstreeToArrayHelper.
// --------------------------------------------------------------
int BinTree::bstreeToArrayHelper(Node* currentNode, NodeData* bstreeArray[]){
    // end of Binary Search Tree
    if (currentNode == NULL){
        return 0;
    }

    int left = bstreeToArrayHelper(currentNode->left, bstreeArray);

    // saves current Node to temp node
    NodeData *temp;
    temp = currentNode->data;
    currentNode->data = NULL; // currentNode no longer points to node
    *(bstreeArray + left) = temp; //bstreeArray points to temp
    temp = NULL;

    int right = bstreeToArrayHelper(currentNode->right, bstreeArray + left + 1);

    return left + right + 1; // return position
} // end of bstreeToArrayHelper

// --------------------- arrayToBSTree --------------------------
// Builds a balanced Binary Search Tree from a sorted array
// --------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* sourceArray[]){
    // deletes Binary Search Tree
    makeEmpty();

    int high = 0;

    // Binary Search tree of 100 elements
    for(int i = 0; i < 100; i++){
        if (sourceArray[i] != NULL){
            high++; // find how many elements points to NodeData

        }else{
            sourceArray[i] = NULL;
        }
    }

    arrayToBSTreeHelper(root, sourceArray, 0, high - 1);
} // end of arrayToBSTree

// --------------------- arrayToBSTreeHelper --------------------
// Helper function to arrayToBSTree
// --------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(Node *currentNode, NodeData* sourceArray[], int low, int high){
    if (low > high){
        currentNode = NULL; // end of array NodeData

    }else{
        int root = (low + high) / 2; // picks NodeData from array to build balanced tree

        NodeData* temp; // temp NodeData pointer
        temp = sourceArray[root];    // assigns root element from array section to temp
        sourceArray[root] = NULL;    // sets that array element to NULL

        insert(temp);   // inserts NodeData int BST
        arrayToBSTreeHelper(currentNode, sourceArray, low, root - 1);    // fill left
        arrayToBSTreeHelper(currentNode, sourceArray, root + 1, high);   // fill right
    }
} // end of arrayToBSTreeHelper

// --------------------- displaySideways ------------------------
// Displays Binary Search Tree Sideways
// --------------------------------------------------------------
void BinTree::displaySideways() const{
    sideways(root, 0);  // get her comments
} // end of displaySideways

// --------------------- sideways -------------------------------
// Helper function for displaySideways
// --------------------------------------------------------------
void BinTree::sideways(Node* currentNode, int level) const{
    if (currentNode != NULL) {
        level++;
        sideways(currentNode->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *currentNode->data << endl;        // display information of object
        sideways(currentNode->left, level);
    }
} // end of sideways