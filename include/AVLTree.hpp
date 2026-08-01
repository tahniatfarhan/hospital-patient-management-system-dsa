#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "Patient.hpp"
#include <iostream>
#include <algorithm>

struct AVLNode {
    Patient data;
    AVLNode* left;
    AVLNode* right;
    int height;

    explicit AVLNode(const Patient& p) : data(p), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(const AVLNode* node) const {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalanceFactor(const AVLNode* node) const {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    // Rotations for balancing
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x  = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left  = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y  = x->right;
        AVLNode* T2 = y->left;

        y->left  = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* balance(AVLNode* node) {
        if (node == nullptr) return nullptr;

        updateHeight(node);
        int bf = getBalanceFactor(node);

        // Left-Left Case
        if (bf > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        // Left-Right Case
        if (bf > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Right Case
        if (bf < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        // Right-Left Case
        if (bf < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, const Patient& p) {
        if (node == nullptr) {
            return new AVLNode(p);
        }
        if (p.id < node->data.id) {
            node->left = insert(node->left, p);
        } else if (p.id > node->data.id) {
            node->right = insert(node->right, p);
        } else {
            std::cout << "  [!] Emergency Patient ID " << p.id << " already exists in AVL Tree!\n";
            return node;
        }
        return balance(node);
    }

    AVLNode* findMin(AVLNode* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    AVLNode* deleteNode(AVLNode* node, int id) {
        if (node == nullptr) {
            std::cout << "  [!] Emergency Patient ID " << id << " not found in AVL Tree.\n";
            return nullptr;
        }
        if (id < node->data.id) {
            node->left = deleteNode(node->left, id);
        } else if (id > node->data.id) {
            node->right = deleteNode(node->right, id);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            AVLNode* successor = findMin(node->right);
            node->data = successor->data;
            node->right = deleteNode(node->right, successor->data.id);
        }
        return balance(node);
    }

    const AVLNode* search(const AVLNode* node, int id) const {
        if (node == nullptr || node->data.id == id) {
            return node;
        }
        if (id < node->data.id) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

    void inOrder(const AVLNode* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        printPatientRecord(node->data);
        inOrder(node->right);
    }

    void clear(AVLNode* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(root); }

    void addPatient(const Patient& p) {
        root = insert(root, p);
    }

    void removePatient(int id) {
        root = deleteNode(root, id);
    }

    bool searchPatient(int id, Patient* foundPatient = nullptr) const {
        const AVLNode* result = search(root, id);
        if (result != nullptr) {
            if (foundPatient) *foundPatient = result->data;
            return true;
        }
        return false;
    }

    void displayAll() const {
        if (root == nullptr) {
            std::cout << "  [!] No emergency patients in AVL Tree.\n";
            return;
        }
        std::cout << "\n         Emergency Patients (Sorted by ID in AVL)       \n";
        inOrder(root);
    }

    int getTreeHeight() const {
        return getHeight(root);
    }

    bool isEmpty() const { return root == nullptr; }
};

#endif // AVLTREE_HPP
