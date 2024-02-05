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



    // Deletes node from BST
    void BST::deleteNode(int value) {
        if (root == nullptr) {
            cout << "Tree is empty. Cannot delete value: " << value << endl;
            return;
        }
        operations = 0;
        root = deleteNodeRecursive(root, value);
        cout << "Deleted value: " << value << ", Tree Height: " << height(root) << endl;
    }



    // Recursive delete function
    Node* BST::deleteNodeRecursive(Node* current, int value) {
        operations++;
        if (current == nullptr) {
            return current;
        }

        if (value < current->data) {
            current->left = deleteNodeRecursive(current->left, value);
        }
        else if (value > current->data) {
            current->right = deleteNodeRecursive(current->right, value);
        }
        else {
            // Handle twin chaining
            if (current->next != nullptr) {
                // Subtract one from the twin chain
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
            }
            else {
                // If not a twin chain, perform regular deletion
                if (current->left == nullptr) {
                    Node* temp = current->right;
                    delete current;
                    return temp;
                }
                else if (current->right == nullptr) {
                    Node* temp = current->left;
                    delete current;
                    return temp;
                }

                // Node with two children, get the inorder successor
                Node* temp = minValueNode(current->right);

                // Copy the inorder successor's data to this node
                current->data = temp->data;

                // Delete the inorder successor
                current->right = deleteNodeRecursive(current->right, temp->data);
            }
        }

        return current;
    }



    // Inserts a new node into the BST
    void BST::insert(int value) {
        operations = 0;
        root = insertRecursive(root, value);
        cout << "Inserted value: " << value << ", Tree Height: " << height(root) << endl;
    }



    // Finds node of minimum value in any specified subtree
    Node* BST::minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }



    // Recursive insertion
    Node* BST::insertRecursive(Node* current, int value) {
        operations++;
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



    // Searches for value in the tree
    bool BST::search(int value) {
        operations = 0;
        return searchRecursive(root, value);
    }



    // Iterative search function
    bool BST::searchRecursive(Node* current, int value) {
        while (current != nullptr) {
            operations++;
            if (value == current->data) {
                return true;
            }
            else if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return false;
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




