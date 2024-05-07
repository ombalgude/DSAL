#include <iostream>
#include <string>

using namespace std;

// Node structure to represent a keyword and its meaning
struct Node {
    string keyword;
    string meaning;
    Node* right;
    Node* left;
};

// Class to represent a Dictionary using a Binary Search Tree
class Dictionary {
public:
    Node* root;

    // Constructor to initialize the dictionary
    Dictionary() {
        root = nullptr;
    }

    // Function to insert a keyword and its meaning into the dictionary
    void insertKeyword(const string& keyword, const string& meaning);

    // Function to delete a keyword from the dictionary
    void deleteKeyword(const string& keyword);

    // Function to update the meaning of a keyword in the dictionary
    void updateMeaning(const string& keyword, const string& newMeaning);

    // Function to display the dictionary in ascending order of keywords
    void displayAscending();

    // Function to display the dictionary in descending order of keywords
    void displayDescending();

    // Function to find the maximum number of comparisons required to find a keyword
    int maxComparisons(const string& keyword);

    // Function to display the inorder traversal of the dictionary
    void displayInorder();

    // Function to calculate the height of the dictionary (longest path from root to any leaf node)
    int height();

    // Function to search for a keyword in the dictionary
    bool search(const string& keyword);

private:
    // Helper function to insert a keyword into the dictionary
    void insertNode(Node*& root, const string& keyword, const string& meaning);

    // Helper function to delete a keyword from the dictionary
    void deleteNode(Node*& root, const string& keyword);

    // Helper function to find the minimum node in a subtree
    Node* findMin(Node* node);

    // Helper function to perform inorder traversal of the dictionary
    void inorder(Node* node);

    // Helper function to perform reverse inorder traversal of the dictionary
    void reverseInorder(Node* node);

    // Helper function to find the maximum number of comparisons recursively
    int maxComparisonsHelper(Node* node, const string& keyword, int count);

    // Helper function to calculate the height of the dictionary recursively
    int heightHelper(Node* node);

    // Helper function to search for a keyword recursively
    bool searchHelper(Node* node, const string& keyword);
};

// Function to insert a keyword and its meaning into the dictionary
void Dictionary::insertKeyword(const string& keyword, const string& meaning) {
    insertNode(root, keyword, meaning);
}

// Helper function to insert a keyword into the dictionary
void Dictionary::insertNode(Node*& root, const string& keyword, const string& meaning) {
    if (root == nullptr) {
        root = new Node;
        root->keyword = keyword;
        root->meaning = meaning;
        root->left = nullptr;
        root->right = nullptr;
    } else if (keyword < root->keyword) {
        insertNode(root->left, keyword, meaning);
    } else if (keyword > root->keyword) {
        insertNode(root->right, keyword, meaning);
    }
    // If keyword is already present, update its meaning
    else {
        root->meaning = meaning;
    }
}

// Function to delete a keyword from the dictionary
void Dictionary::deleteKeyword(const string& keyword) {
    deleteNode(root, keyword);
}

// Helper function to delete a keyword from the dictionary
void Dictionary::deleteNode(Node*& root, const string& keyword) {
    if (root == nullptr)
        return;
    if (keyword < root->keyword)
        deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        deleteNode(root->right, keyword);
    else {
        // Node to delete found
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left == nullptr) {
            Node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            Node* temp = root;
            root = root->left;
            delete temp;
        } else {
            Node* temp = findMin(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            deleteNode(root->right, temp->keyword);
        }
    }
}

// Helper function to find the minimum node in a subtree
Node* Dictionary::findMin(Node* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

// Function to update the meaning of a keyword in the dictionary
void Dictionary::updateMeaning(const string& keyword, const string& newMeaning) {
    Node* node = root;
    while (node != nullptr) {
        if (keyword < node->keyword)
            node = node->left;
        else if (keyword > node->keyword)
            node = node->right;
        else {
            node->meaning = newMeaning;
            return;
        }
    }
    cout << "Keyword not found." << endl;
}

// Function to display the dictionary in ascending order of keywords
void Dictionary::displayAscending() {
    inorder(root);
}

// Helper function to perform inorder traversal of the dictionary
void Dictionary::inorder(Node* node) {
    if (node != nullptr) {
        inorder(node->left);
        cout << node->keyword << " : " << node->meaning << endl;
        inorder(node->right);
    }
}

// Function to display the dictionary in descending order of keywords
void Dictionary::displayDescending() {
    reverseInorder(root);
}

// Helper function to perform reverse inorder traversal of the dictionary
void Dictionary::reverseInorder(Node* node) {
    if (node != nullptr) {
        reverseInorder(node->right);
        cout << node->keyword << " : " << node->meaning << endl;
        reverseInorder(node->left);
    }
}

// Function to find the maximum number of comparisons required to find a keyword
int Dictionary::maxComparisons(const string& keyword) {
    return maxComparisonsHelper(root, keyword, 0);
}

// Helper function to find the maximum number of comparisons recursively
int Dictionary::maxComparisonsHelper(Node* node, const string& keyword, int count) {
    if (node == nullptr)
        return count;
    else if (node->keyword == keyword)
        return count + 1;
    else if (keyword < node->keyword)
        return maxComparisonsHelper(node->left, keyword, count + 1);
    else
        return maxComparisonsHelper(node->right, keyword, count + 1);
}

// Function to display the inorder traversal of the dictionary
void Dictionary::displayInorder() {
    cout << "Inorder traversal of the dictionary:" << endl;
    inorder(root);
    cout << endl;
}

// Function to calculate the height of the dictionary (longest path from root to any leaf node)
int Dictionary::height() {
    return heightHelper(root);
}

// Helper function to calculate the height of the dictionary recursively
int Dictionary::heightHelper(Node* node) {
    if (node == nullptr)
        return 0;
    int leftHeight = heightHelper(node->left);
    int rightHeight = heightHelper(node->right);
    return 1 + max(leftHeight, rightHeight);
}

// Function to search for a keyword in the dictionary
bool Dictionary::search(const string& keyword) {
    return searchHelper(root, keyword);
}

// Helper function to search for a keyword recursively
bool Dictionary::searchHelper(Node* node, const string& keyword) {
    if (node == nullptr)
        return false;
    if (node->keyword == keyword)
        return true;
    if (keyword < node->keyword)
        return searchHelper(node->left, keyword);
    else
        return searchHelper(node->right, keyword);
}

// Main function to test the Dictionary class
int main() {
    Dictionary dict;
    int choice;
    string keyword, meaning, newMeaning;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add a keyword\n";
        cout << "2. Delete a keyword\n";
        cout << "3. Update meaning of a keyword\n";
        cout << "4. Display dictionary in ascending order\n";
        cout << "5. Display dictionary in descending order\n";
        cout << "6. Find maximum comparisons for a keyword\n";
        cout << "7. Display inorder traversal of the dictionary\n";
        cout << "8. Display height of the dictionary\n";
        cout << "9. Search for a keyword\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.insertKeyword(keyword, meaning);
                break;
            }
            case 2: {
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                dict.deleteKeyword(keyword);
                break;
            }
            case 3: {
                cout << "Enter keyword to update: ";
                cin >> keyword;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, newMeaning);
                dict.updateMeaning(keyword, newMeaning);
                break;
            }
            case 4: {
                cout << "Dictionary in ascending order:" << endl;
                dict.displayAscending();
                break;
            }
            case 5: {
                cout << "Dictionary in descending order:" << endl;
                dict.displayDescending();
                break;
            }
            case 6: {
                cout << "Enter keyword to find maximum comparisons: ";
                cin >> keyword;
                cout << "Maximum comparisons required for '" << keyword << "': " << dict.maxComparisons(keyword) << endl;
                break;
            }
            case 7: {
                dict.displayInorder();
                break;
            }
            case 8: {
                cout << "Height of the dictionary: " << dict.height() << endl;
                break;
            }
            case 9: {
                cout << "Enter keyword to search: ";
                cin >> keyword;
                if (dict.search(keyword))
                    cout << "Keyword found in the dictionary." << endl;
                else
                    cout << "Keyword not found in the dictionary." << endl;
                break;
            }
            case 10: {
                cout << "Exiting program..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 10);

    return 0;
}
