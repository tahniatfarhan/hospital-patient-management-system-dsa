#ifndef BST_HPP
#define BST_HPP

#include "Patient.hpp"
#include <iostream>

struct BSTNode {
    Patient data;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(const Patient& p) : data(p), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, const Patient& p) {
        if (node == nullptr) {
            return new BSTNode(p);
        }
        if (p.id < node->data.id) {
            node->left = insert(node->left, p);
        } else if (p.id > node->data.id) {
            node->right = insert(node->right, p);
        } else {
            std::cout << "  [!] Patient ID " << p.id << " already exists in BST!\n";
        }
        return node;
    }

    BSTNode* findMin(BSTNode* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* deleteNode(BSTNode* node, int id) {
        if (node == nullptr) {
            std::cout << "  [!] Patient ID " << id << " not found in BST.\n";
            return nullptr;
        }
        if (id < node->data.id) {
            node->left = deleteNode(node->left, id);
        } else if (id > node->data.id) {
            node->right = deleteNode(node->right, id);
        } else {
            // Case 1: No children
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children — replace with in-order successor
            BSTNode* successor = findMin(node->right);
            node->data = successor->data;
            node->right = deleteNode(node->right, successor->data.id);
        }
        return node;
    }

    const BSTNode* search(const BSTNode* node, int id) const {
        if (node == nullptr || node->data.id == id) {
            return node;
        }
        if (id < node->data.id) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

    void inOrder(const BSTNode* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        printPatientRecord(node->data);
        inOrder(node->right);
    }

    void clear(BSTNode* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void addPatient(const Patient& p) {
        root = insert(root, p);
    }

    void removePatient(int id) {
        root = deleteNode(root, id);
    }

    bool searchPatient(int id, Patient* foundPatient = nullptr) const {
        const BSTNode* result = search(root, id);
        if (result != nullptr) {
            if (foundPatient) *foundPatient = result->data;
            return true;
        }
        return false;
    }

    void displayAll() const {
        if (root == nullptr) {
            std::cout << "  [!] No normal patients in BST.\n";
            return;
        }
        std::cout << "\n         Normal Patients (Sorted by ID in BST)       \n";
        inOrder(root);
    }

    bool isEmpty() const { return root == nullptr; }
};

#endif // BST_HPP
