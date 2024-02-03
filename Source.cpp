#include <iostream>
#include <fstream>
#include <sstream>
#include "BST.h"

using namespace std;


// Checks if a string represents a valid integer
bool isValidInteger(const string str) {
    try {
        // Attempt to convert the string to an integer
        stoi(str);
        return true;
    }
    catch (const invalid_argument& ia) {
        return false;
    }
    catch (const out_of_range& oor) {
        return false;
    }
}

int main() {

    int creation = 0;
    int search = 0;
    int deletion = 0;
    int insert = 0;

    string inputFileName, operationFileName, outputFileName;

    cout << "Enter the name of the input file: ";
    cin >> inputFileName;

    //Operation File cout and cin to be coded------------------------------

    cout << "Enter the name of the output file: ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName);

    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }


    ofstream outputFile(outputFileName);

    if (!outputFile) {
        cerr << "Error opening output file!" << endl;
        inputFile.close();
        return 1;
    }


    BST bst;

    int value;
    string line;


    while (getline(inputFile, line)) {
        
        if (isValidInteger(line)) {
            // Convert the string to an integer and insert into the BST
            value = stoi(line);
            bst.insert(value);
            creation++;
            // Print the BST to the console and the output file after each insertion
            bst.printTree(outputFile);
            bst.print2DConsole();
            bst.print2DToFile(outputFile);
        }
        else {
            cerr << "Error: Invalid integer - skipping line: " << line << endl;
        }
    }

    // Check if the operation file is empty and valid and perform operations to be coded-------------------------------------
    

    cout << "\n              BST";
    cout << "\nCreation      "<< creation;
    cout << "\nSearch        " << search;
    cout << "\nInsert        " << insert;
    cout << "\nDelete        " << deletion;
    cout << "\n         -------------";
    cout << "\nTotal         " << (creation+search+insert+deletion);



    outputFile << "\n              BST";
    outputFile << "\nCreation      " << creation;
    outputFile << "\nSearch        " << search;
    outputFile << "\nInsert        " << insert;
    outputFile << "\nDelete        " << deletion;
    outputFile << "\n         -------------";
    outputFile << "\nTotal         " << (creation + search + insert + deletion);


    // Close the files
    inputFile.close();
    outputFile.close();
    //Close operation file

    return 0;
}
