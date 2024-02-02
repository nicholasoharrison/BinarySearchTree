#include "BST.h"






    // Print the BST using 2D representation
    void BST::print2D(Node* root, int space, ostream& out) {
        if (root == nullptr) {
            return;
        }
        // Increase distance between levels of BST
        space += COUNT;

        print2D(root->right, space, out);

        // Print current node after space count is correct
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

        print2D(root->left, space, out);
    }

    // Counts the number of twins in a twin chain
    int BST::countTwins(Node* node) {
        int count = 0;
        while (node != nullptr) {
            count++;
            node = node->next;
        }
        return count;
    }



    // Inserts a new node into the BST
    void BST::insert(int value) {
        root = insertRecursive(root, value);
        cout << "Inserted value: " << value << ", Tree Height: " << height(root) << endl;
    }

    // Recursive insertion
    Node* BST::insertRecursive(Node* current, int value) {
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
            // Twin chaining handling
            Node* newNode = new Node(value);
            newNode->next = current->next;
            current->next = newNode;
        }

        return current;
    }

    // Calculates the height of the tree
    int BST::height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        else {
            int leftHeight = height(node->left);
            int rightHeight = height(node->right);

            return max(leftHeight, rightHeight) + 1;
        }
    }

    // Prints the BST to a file and the console
    void BST::printTree(ofstream& outputFile) {
        cout << "BST elements: ";
        printTreeRecursive(root);
        cout << ", Tree Height: " << height(root) << endl;

        outputFile << "BST elements: ";
        printTreeRecursiveToFile(root, outputFile);
        outputFile << ", Tree Height: " << height(root) << endl;
    }

    // Printing with inorder traversal
    void BST::printTreeRecursive(Node* current) {
        if (current != nullptr) {
            printTreeRecursive(current->left);
            printTwinChain(current);
            printTreeRecursive(current->right);
        }
    }

    // Printing twin chain duplicates
    void BST::printTwinChain(Node* node) {
        while (node != nullptr) {
            cout << node->data << " ";
            node = node->next;
        }
    }

    // Inorder traversal to print to file
    void BST::printTreeRecursiveToFile(Node* current, ofstream& outputFile) {
        if (current != nullptr) {
            printTreeRecursiveToFile(current->left, outputFile);
            printTwinChainToFile(current, outputFile);
            printTreeRecursiveToFile(current->right, outputFile);
        }
    }

    // Prints twin chain values to file
    void BST::printTwinChainToFile(Node* node, ofstream& outputFile) {
        while (node != nullptr) {
            outputFile << node->data << " ";
            node = node->next;
        }
    }

    // Prints the BST using 2D representation to the console
    void BST::print2DConsole() {
        cout << "Printing BST using 2D representation:" << endl;
        print2D(root, 0, cout);
    }

    // Prints the BST using 2D representation to a specified output stream
    void BST::print2DToFile(ofstream& outputFile) {
        outputFile << "Printing BST using 2D representation:" << endl;
        print2D(root, 0, outputFile);
    }




