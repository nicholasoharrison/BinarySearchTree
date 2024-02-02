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

// Binary Search Tree class
class BST {
private:
    Node* root;

    // Function to print the BST using 2D representation
    void print2D(Node* root, int space, ostream& out) {
        // Base case
        if (root == nullptr)
            return;

        // Increase distance between levels
        space += COUNT;

        // Process right child first
        print2D(root->right, space, out);

        // Print current node after space count
        out << endl;
        for (int i = COUNT; i < space; i++)
            out << " ";

        // Check for twin chain and print the node value along with the number of twins
        if (root->next != nullptr) {
            int twinCount = countTwins(root);
            out << root->data << "-" << twinCount << "\n";
        }
        else {
            out << root->data << "\n";
        }

        // Process left child
        print2D(root->left, space, out);
    }

    // Function to count the number of twins in a twin chain
    int countTwins(Node* node) {
        int count = 0;
        while (node != nullptr) {
            count++;
            node = node->next;
        }
        return count;
    }

public:
    BST() : root(nullptr) {}

    // Function to insert a new node into the BST
    void insert(int value) {
        root = insertRecursive(root, value);
        cout << "Inserted value: " << value << ", Tree Height: " << height(root) << endl;
    }

    // Function to perform recursive insertion
    Node* insertRecursive(Node* current, int value) {
        if (current == nullptr) {
            return new Node(value);
        }

        if (value < current->data) {
            current->left = insertRecursive(current->left, value);
        }
        else if (value > current->data) {
            current->right = insertRecursive(current->right, value);
        }
        else {
            // Handle duplicates using twin chaining
            Node* newNode = new Node(value);
            newNode->next = current->next;
            current->next = newNode;
        }

        return current;
    }

    // Function to calculate the height of the tree
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        else {
            int leftHeight = height(node->left);
            int rightHeight = height(node->right);

            return max(leftHeight, rightHeight) + 1;
        }
    }

    // Function to print the BST to a file and the console
    void printTree(ofstream& outputFile) {
        cout << "BST elements: ";
        printTreeRecursive(root);
        cout << ", Tree Height: " << height(root) << endl;

        outputFile << "BST elements: ";
        printTreeRecursiveToFile(root, outputFile);
        outputFile << ", Tree Height: " << height(root) << endl;
    }

    // Function to perform recursive inorder traversal
    void printTreeRecursive(Node* current) {
        if (current != nullptr) {
            printTreeRecursive(current->left);
            printTwinChain(current);
            printTreeRecursive(current->right);
        }
    }

    // Function to print twin chain (for duplicates)
    void printTwinChain(Node* node) {
        while (node != nullptr) {
            cout << node->data << " ";
            node = node->next;
        }
    }

    // Function to perform recursive inorder traversal and print to file
    void printTreeRecursiveToFile(Node* current, ofstream& outputFile) {
        if (current != nullptr) {
            printTreeRecursiveToFile(current->left, outputFile);
            printTwinChainToFile(current, outputFile);
            printTreeRecursiveToFile(current->right, outputFile);
        }
    }

    // Function to print twin chain to file (for duplicates)
    void printTwinChainToFile(Node* node, ofstream& outputFile) {
        while (node != nullptr) {
            outputFile << node->data << " ";
            node = node->next;
        }
    }

    // Function to print the BST using 2D representation to the console
    void print2DConsole() {
        cout << "Printing BST using 2D representation:" << endl;
        print2D(root, 0, cout);
    }

    // Function to print the BST using 2D representation to a specified output stream
    void print2DToFile(ofstream& outputFile) {
        outputFile << "Printing BST using 2D representation:" << endl;
        print2D(root, 0, outputFile);
    }


};



// Function to check if a string represents a valid integer
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
    // Get input and output file names from the user
    string inputFileName, operationFileName, outputFileName;

    cout << "Enter the name of the input file: ";
    cin >> inputFileName;

    //Operation File cout and cin

    cout << "Enter the name of the output file: ";
    cin >> outputFileName;

    // Open the input file
    ifstream inputFile(inputFileName);

    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    // Open the output file
    ofstream outputFile(outputFileName);

    if (!outputFile) {
        cerr << "Error opening output file!" << endl;
        inputFile.close();
        return 1;
    }

    // Create a BST object
    BST bst;

    int value;
    string line;

    // Read lines from the input file
    while (getline(inputFile, line)) {
        // Check if the line represents a valid integer
        if (isValidInteger(line)) {
            // Convert the string to an integer and insert into the BST
            value = stoi(line);
            bst.insert(value);

            // Print the BST to the console and the output file after each insertion
            bst.printTree(outputFile);
            bst.print2DConsole();
            bst.print2DToFile(outputFile);
        }
        else {
            // Print an error message for invalid integer
            cerr << "Error: Invalid integer - skipping line: " << line << endl;
        }
    }

    // Check if the operation file is empty and valid and perform operations
    
    // Close the files
    inputFile.close();
    outputFile.close();
    //Close operation file

    return 0;
}
