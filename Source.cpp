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

    cout << "Enter the name of the operation file: ";
    cin >> operationFileName;

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

    //IMPLEMENT INSERT, DELETE, AND SEARCH COUNTERS

    //FIX INSERT AND DELETE OPERATIONS SIMILAR TO SEARCH

    // Check if the operation file is empty and valid and perform operations
    ifstream operationFile(operationFileName);
    if (operationFile.peek() == ifstream::traits_type::eof()) {
        cout << "Empty Operation File – No Operations Performed" << endl;
    }
    else {
        // Perform operations from the operation file
        while (getline(operationFile, line)) {
            char actionCode;
            int numOperations;
            

            istringstream iss(line);
            if (iss >> actionCode >> numOperations) {
                switch (actionCode) {
                case 'I':
                    for (int i = 0; i < numOperations; ++i) {
                        // Read the integer to insert
                        getline(operationFile, line);
                        if (isValidInteger(line)) {
                            value = stoi(line);
                            
                            // Insert the value into the BST
                            bst.insert(value);
                            // Print the BST to the console and the output file after each insertion
                            bst.printTree(outputFile);
                            bst.print2DConsole();
                            bst.print2DToFile(outputFile);
                        }
                        else {
                            cerr << "Error: Invalid integer for insertion - skipping line: " << line << endl;
                        }
                    }
                    break;

                case 'D':
                    for (int i = 0; i < numOperations; ++i) {
                        // Read the integer to delete
                        getline(operationFile, line);
                        if (isValidInteger(line)) {
                            value = stoi(line);
                            // Check if the value is in the tree before attempting deletion
                            if (bst.search(value)) {
                                // Delete the value from the BST
                                bst.deleteNode(value);
                                // Print the BST to the console and the output file after each deletion
                                bst.printTree(outputFile);
                                bst.print2DConsole();
                                bst.print2DToFile(outputFile);
                            }
                            else {
                                cout << "Value " << value << " not found in the tree - skipping deletion." << endl;
                            }
                        }
                        else {
                            cerr << "Error: Invalid integer for deletion - skipping line: " << line << endl;
                        }
                    }
                    break;

                case 'S':
                    
                            value = numOperations;
                            // Search for the value in the BST
                            if (bst.search(value)) {
                                cout << "Value " << value << " found in the tree." << endl;
                            }
                            else {
                                cout << "Value " << value << " not found in the tree." << endl;
                            }
                       
                    break;

                default:
                    cerr << "Error: Invalid Action Code - skipping line: " << line << endl;
                    break;
                }
            }
            else {
                cerr << "Error: Invalid format for operation - skipping line: " << line << endl;
            }
        }
    }


    // Print analysis data
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
    operationFile.close();

    return 0;
}
