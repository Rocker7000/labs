#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;


// Вузол бінарного дерева
struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const string& val)
        : value(val), left(nullptr), right(nullptr) {}
};

// Клас бінарного дерева
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    // Вставка значення в бінарне дерево
    void insert(const string& value) {
        root = insertRecursive(root, value);
    }

    // Пошук значення в бінарному дереві
    bool search(const string& value) const {
        return searchRecursive(root, value);
    }

private:
    TreeNode* root;

    // Рекурсивна функція для вставки значення в бінарне дерево
    TreeNode* insertRecursive(TreeNode* node, const string& value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->value) {
            node->left = insertRecursive(node->left, value);
        }
        else if (value > node->value) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    // Рекурсивна функція для пошуку значення в бінарному дереві
    bool searchRecursive(const TreeNode* node, const string& value) const {
        if (node == nullptr) {
            return false;
        }

        if (value == node->value) {
            return true;
        }
        else if (value < node->value) {
            return searchRecursive(node->left, value);
        }
        else {
            return searchRecursive(node->right, value);
        }
    }
};

// Клас простого списку
class SimpleList {
public:
    SimpleList() {}

    // Вставка значення в список
    void insert(const string& value) {
        items.push_back(value);
    }

    // Пошук значення в списку
    bool search(const string& value) const {
        for (const auto& item : items) {
            if (item == value) {
                return true;
            }
        }

        return false;
    }

private:
    vector<string> items;
};

// Функція для зчитування списку ідентифікаторів з файлу
vector<string> readIdentifiers(const string& filename) {
    vector<string> identifiers;

    ifstream infile(filename);
    string line;
    while (getline(infile, line)) {
        identifiers.push_back(line);
    }

    return identifiers;
}

int main() {
    // Зчитування списку ідентифікаторів з файлу
    vector<string> identifiers = readIdentifiers("identifiers.txt");

    // Створення бінарного дерева та простого списку
    BinaryTree binaryTree;
    SimpleList simpleList;

    // Вставка ідентифікаторів в бінарне дерево та простий список
    for (const auto& identifier : identifiers) {
        binaryTree.insert(identifier);
        simpleList.insert(identifier);
    }

    // Пошук довільного ідентифікатора в бінарному дереві
    string searchValue = "identifier7";
    auto start = chrono::high_resolution_clock::now();
    bool found = binaryTree.search(searchValue);
    auto end = chrono::high_resolution_clock::now();
    cout << "Binary tree search for '" << searchValue << "' took "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " microseconds. Found: " << (found ? "yes" : "no") << endl;

    // Пошук довільного ідентифікатора в простому списку
    start = chrono::high_resolution_clock::now();
    found = simpleList.search(searchValue);
    end = chrono::high_resolution_clock::now();
    cout << "Simple list search for '" << searchValue << "' took "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " microseconds. Found: " << (found ? "yes" : "no") << endl;

    return 0;
}