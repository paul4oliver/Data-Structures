//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Paul Kenaga
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;

    // Declare child node less than parent
    struct Node* leftChild;

    // Declare child node greater than parent
    struct Node* rightChild;

    // Default constructor new for node
    Node() {

        // Initialize children nodes
        leftChild = nullptr;
        rightChild = nullptr;
    }

    // Call default constructor and assign bid to node
    Node(Bid bid) : Node() { 
        this->bid = bid;
    }
};


//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);
    void preOrder(Node* node);
    void postOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void PostOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {

    // Set root equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {

    // Call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    
    // Call postOrder fuction and pass root 
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    
    // Call preOrder fuction and pass root 
    this->preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {

    // If root is empty, assign root to new bid
    if (root == nullptr) {
        root = new Node(bid);
    }

    // Call addNode, passing root and bid as parameters
    else {
        this->addNode(root, bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    
    // Call removeNode, passing root and bid as parameters
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    Bid bid;

    // Set current node equal to root
    Node* currentNode = root;
    
    // While currentnode is not equal to nullptr
    while (currentNode != nullptr) {

        // If bid matches current node bid, return bid
        if (currentNode->bid.bidId.compare(bidId) == 0) {
            return currentNode->bid; 
        }

        // If bid is smaller than current node then set current node to left child
        if (bidId.compare(currentNode->bid.bidId) < 0) {
            currentNode = currentNode->leftChild;
        }

        // If bid is bigger than current node then set current node to left child
        else {
            currentNode = currentNode->rightChild;
        }
    }

    // Return empty bid if no matching bid found
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    
    // If node bid ID is larger than new node bid ID
    if (node->bid.bidId.compare(bid.bidId) > 0) {

        // If left child is empty, set new node to left child
        if (node->leftChild == nullptr) {
            node->leftChild = new Node(bid);
        }

        // Else set node to left child and to recurse down tree
        else {
            this->addNode(node->leftChild, bid);
        }
    }

    else {

        // If right child is empty, set new node to right child
        if (node->rightChild == nullptr) {
            node->rightChild = new Node(bid);
        }

        // Else set node to right child and to recurse down tree
        else {
            this->addNode(node->rightChild, bid);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {

    // If node is not equal to null ptr
    if (node != nullptr) {

        // Traverse left side 
        inOrder(node->leftChild);

        // Output bid ID, title, amount, and fund
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
            << node->bid.fund << endl;

        // Traverse right side 
        inOrder(node->rightChild);
    }
}
void BinarySearchTree::postOrder(Node* node) {

    // If node is not equal to null ptr
    if (node != nullptr) {

        // Traverse left side 
        postOrder(node->leftChild);

        // Traverse right side 
        postOrder(node->rightChild);

        // Output bid ID, title, amount, and fund
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
            << node->bid.fund << endl;
    }

}

void BinarySearchTree::preOrder(Node* node) {

    // If node is not equal to null ptr
    if (node != nullptr) {

        // Output bid ID, title, amount, and fund
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
            << node->bid.fund << endl;

        // Traverse left side 
        postOrder(node->leftChild);

        // Traverse right side 
        postOrder(node->rightChild);
    }
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {

    // If node is equal to nullptr, return - no bid to remove
    if (node == nullptr) {
        return node;
    }

    // If bid ID is less than bid ID at node, traverse left side
    if (bidId.compare(node->bid.bidId) < 0) {
        node->leftChild = removeNode(node->leftChild, bidId);
    }

    // If bid ID is greater than bid ID at node, traverse right side
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->rightChild = removeNode(node->rightChild, bidId);
    }

    else {

        // If node has no children, delete node
        if (node->leftChild == nullptr && node->rightChild == nullptr) {
            delete node;
            node = nullptr;
        }
        
        // If node has only left child, set left child to parent node and delete node
        else if (node->leftChild != nullptr && node->rightChild == nullptr) {
            Node* tempNode = node;
            node = node->leftChild;
            delete tempNode;
        }
        
        // If node has only right child, set right child to parent node and delete node
        else if (node->leftChild == nullptr && node->rightChild != nullptr) {
            Node* tempNode = node;
            node = node->rightChild;
            delete tempNode;
        }
       
        // If node has two children
        else {

            // Traverse to find leftmost child of right subtree
            Node* tempNode = node->rightChild;
            while (tempNode->leftChild != nullptr) {
                tempNode = tempNode->leftChild;
            }

            // Copy bid, then remove duplicate child
            node->bid = tempNode->bid;
            node->rightChild = removeNode(node->rightChild, tempNode->bid.bidId);
        }
    }

    // Return node 
    return node;
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "97988";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "97988";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst = nullptr;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
