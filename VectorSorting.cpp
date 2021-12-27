//============================================================================
// Name        : VectorSorting.cpp
// Author      : Paul Kenaga
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================
#include <algorithm>
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
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}


/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
    // Declare local variables
    int low = 0;
    int high = 0;
    int pivot_point = 0; // Middle element point
    bool finished = false;

    // Set low and high equal to begin and end
    low = begin;
    high = end;

    // Declare middle element the pivot point
    pivot_point = begin + (end - begin) / 2;

    // Loop implements the quick sort logic over bid.title until done
    while (!finished) {

        // Loop increments low while less than the pivot point
        while (bids[low].title.compare(bids[pivot_point].title) < 0) {
            ++low;
        }

        // Loop decrements high while greater than the pivot point
        while (bids[pivot_point].title.compare(bids[high].title) < 0) {
            --high;
        }

        // If zero or one element remain, all elements are partitioned and loop ends
        // Return high
        if (low >= high) {
            finished = true;
        }

        // Else swap low and high 
        else {
            swap(bids.at(low), bids.at(high));

            // Increment low and decrement high to bring closer 
            ++low;
            --high;
        }
    }
    return high;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
    //Declared and set local variable mid equal to 0
    int mid = 0;

    // Stop when zero or one element left because partition is sorted, return
    if (begin >= end) {
        return;
    }

    /* Partition bids into low and high such that
     midpoint is location of last element in low */


    // Set mid to last element in low partition
    mid = partition(bids, begin, end);

    // Recursively sort low partition (begin to mid)
    quickSort(bids, begin, mid);

    // Recursively sort high partition (mid+1 to end)
    quickSort(bids, mid + 1, end);

}

// Implement the selection sort logic over bid.title
/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
    //Declared variable for index of the current minimum bid
    int minBid = 0;
    int i = 0;
    int j = 0;

    // Loop through bids
    for (i = 0; i < bids.size()-1; ++i) {

        // Set min bid to position that divides sorted/not sorted
        minBid = i;

        // Loop through elements to right of minBid
        // If element to right is less than minBid, set it to minBid
        for (j = i + 1; j < bids.size(); ++j) {
            if (bids.at(j).title.compare(bids.at(minBid).title) < 0) {
                minBid = j;
            }
        }

        // If new minBid found, swap the current minBid with smaller one found
        if (minBid != i) {
            swap(bids.at(i), bids.at(minBid));
        }
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
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        case 3:
            // Initialize timer variable
            ticks = clock();

            // Call method to perform selection sort and report timing results
            selectionSort(bids);

            // Display how many bids sorted
            cout << bids.size() << " bids sorted" << endl;

            // Calculate elapsed time in ticks and seconds and display them
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            
            // Return to menu
            break;

        case 4:
            // Initialize timer variable
            ticks = clock();

            // Call method to perform quick sort and report timing results
            quickSort(bids, 0, bids.size() - 1);

            // Display how many bids sorted
            cout << bids.size() << " bids sorted" << endl;

            // Calculate elapsed time in ticks and seconds and display them
            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            // Return to menu
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}