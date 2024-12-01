#include <iostream>
#include <chrono>
#include <random>
#include <unordered_set>
using namespace std;
using namespace std::chrono;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
//From examples in class
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void add(int key) {
        root = add(root, key);
    }

    TreeNode* add(TreeNode* node, int key) {
        if (node == nullptr) return new TreeNode(key);
        if (key < node->val)
            node->left = add(node->left, key);
        else if (key > node->val)
            node->right = add(node->right, key);
        return node;
    }

    void inorder_traverse() {
        inorder_traverse(root);
        cout << endl;
    }

    void inorder_traverse(TreeNode* node) {
        if (node != nullptr) {
            inorder_traverse(node->left);
            cout << node->val << " ";
            inorder_traverse(node->right);
        }
    }
    //Teams discussion/class
private:
    TreeNode* root;
};
//in class
void add_unique_random_values(BinarySearchTree& bst, int num_values) {
    unordered_set<int> values;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);

    while (values.size() < num_values) {
        int value = dis(gen);
        if (values.find(value) == values.end()) {
            bst.add(value);
            values.insert(value);
        }
    }
}
//from past project
void add_nodes_and_measure_time(int num_values) {// Measures the time taken to add a specified number of unique nodes to the BST.
    BinarySearchTree bst;
    auto start = high_resolution_clock::now();
    add_unique_random_values(bst, num_values);// function generates unique random values using a unordered_set to ensure no duplicates are added.
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Time taken to add " << num_values << " unique nodes: " << duration << " milliseconds" << endl;

    // Display all values in the BST
    cout << "Inorder traversal of " << num_values << " nodes: ";
    bst.inorder_traverse();
}


int main() {//from example in https://stackoverflow.com/questions/4736485/srandtime0-and-random-number-generation, for random number generation (100x)
    srand(time(0)); // Seed for random number generation

    add_nodes_and_measure_time(100);//added add_nodes from bst.add
    add_nodes_and_measure_time(1000);
    add_nodes_and_measure_time(10000);
    add_nodes_and_measure_time(100000);

    return 0;
}