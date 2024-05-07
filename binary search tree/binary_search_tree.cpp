#include <iostream>

using namespace std;

struct Node {
    // Creating Structure Node.
    int data;
    Node* right;
    Node* left;
};

class BinarySearchTree {
    // Binary search tree & its iterators
public:
    Node* root, * temp; // Root & temp iterators.

    BinarySearchTree() {
        // Initially root is null.
        root = NULL;
    }

    // Declare create, insertNode, and inorder functions.
    void createTree();
    void insertNode(Node*, Node*);
    void inorder(Node*);
    int longestPath(); // Function to find the number of nodes in the longest path from root
    int minValue();    // Function to find the minimum data value found in the tree
    void swapRoles(Node*); // Function to swap left and right pointers at every node
    Node* search(Node*, int); // Function to search for a value in the tree

private:
    // Helper function to find the longest path recursively
    int longestPathHelper(Node*);
};

void BinarySearchTree::createTree() {
    // At first the num of nodes in tree are 0.
    int numberOfNodes = 0;
    int data;

    // Declare num of nodes to insert
    cout << "\n Enter number of Nodes :: ";
    cin >> numberOfNodes;
    root = NULL;

    for (int i = 0; i < numberOfNodes; i++) {
        // Until the number of nodes is reached we are able to insert the data

        temp = new Node;
        cout << " \n Enter the data : ";
        cin >> data; // data is currently in the data variable now.

        temp->data = data;
        temp->right = NULL;
        temp->left = NULL;

        // root is Null so root is temp else insert the data by help of root , temp
        if (root == NULL) {
            root = temp;
        }
        else {
            insertNode(root, temp);
        }
    }
}

// operations happening inside the root insertNode function
void BinarySearchTree::insertNode(Node* root, Node* temp) {
    if (temp->data < root->data) // if data is less than value/data of root then....
    {
        if (root->left == NULL) // left side of root is empty then it is temp & insert data there.
        {
            root->left = temp;
            cout << "left " << temp->data;
        }
        else {
            insertNode(root->left, temp);
        }
    }
    else // data is not less than root data then it goes to right.
    {
        if (root->right == NULL)
            // If right of root is empty then it's temp and insert new value to that temp right.
        {
            root->right = temp;
            cout << "right " << temp->data;
        }
        else // Otherwise insert it there only.
        {
            insertNode(root->right, temp);
        }
    }
}

// Function to perform inorder traversal of the tree
void BinarySearchTree::inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
}

// Function to find the number of nodes in the longest path from root
int BinarySearchTree::longestPath() {
    // Call a helper function to find the longest path recursively
    return longestPathHelper(root);
}

// Helper function to find the longest path recursively
int BinarySearchTree::longestPathHelper(Node* node) {
    if (node == NULL)
        return 0;
    else {
        // Compute the depth of left and right subtrees
        int leftDepth = longestPathHelper(node->left);
        int rightDepth = longestPathHelper(node->right);
        // Return the maximum depth + 1 (for the current node)
        return max(leftDepth, rightDepth) + 1;
    }
}

// Function to find the minimum data value found in the tree
int BinarySearchTree::minValue() {
    Node* current = root;
    // Traverse the leftmost node to find the minimum value
    while (current->left != NULL)
        current = current->left;
    return current->data;
}

// Function to swap left and right pointers at every node
void BinarySearchTree::swapRoles(Node* node) {
    if (node == NULL)
        return;
    else {
        // Swap left and right pointers
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
        // Recursively swap left and right pointers for left and right subtrees
        swapRoles(node->left);
        swapRoles(node->right);
    }
}

// Function to search for a value in the tree
Node* BinarySearchTree::search(Node* node, int value) {
    if (node == NULL || node->data == value)
        return node;
    // If the value is less than current node's data, search left subtree
    if (value < node->data)
        return search(node->left, value);
    // If the value is greater than current node's data, search right subtree
    return search(node->right, value);
}

int main() {

    BinarySearchTree a;
    a.createTree();

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert new node\n";
        cout << "2. Find number of nodes in the longest path from root\n";
        cout << "3. Minimum data value found in the tree\n";
        cout << "4. Change the tree so that the roles of the left and right pointers are swapped at every node\n";
        cout << "5. Search for a value\n";
        cout << "6. Display inorder traversal of the tree\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Insert new node
            Node* newNode = new Node;
            newNode->data = 10;
            newNode->left = newNode->right = NULL;
            a.insertNode(a.root, newNode);
            break;
        }
        case 2: {
            // Find number of nodes in the longest path from root
            int longest = a.longestPath();
            cout << "Number of nodes in the longest path from root: " << longest << endl;
            break;
        }
        case 3: {
            // Minimum data value found in the tree
            int minVal = a.minValue();
            cout << "Minimum data value found in the tree: " << minVal << endl;
            break;
        }
        case 4: {
            // Change the tree so that the roles of the left and right pointers are swapped at every node
            a.swapRoles(a.root);
            cout << "Roles of left and right pointers swapped at every node." << endl;
            break;
        }
        case 5: {
            // Search for a value
            int value;
            cout << "Enter a value to search: ";
            cin >> value;
            Node* result = a.search(a.root, value);
            if (result != NULL)
                cout << "Value found in the tree." << endl;
            else
                cout << "Value not found in the tree." << endl;
            break;
        }
        case 6: {
            // Display inorder traversal of the tree
            cout << "Inorder traversal of the tree: ";
            a.inorder(a.root);
            cout << endl;
            break;
        }
        case 7: {
            cout << "Exiting program..." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 7);

    return 0;
}
