#include "Patient.hpp"
#include "BST.hpp"
#include "AVLTree.hpp"

#include <cassert>
#include <iostream>

void testBSTOperations() {
    std::cout << "[Test 1] Running BST Operations Test...\n";
    BST bst;

    // Test Add
    bst.addPatient(Patient(10, "Alpha", 30, "Flu", false));
    bst.addPatient(Patient(5, "Beta", 40, "Fever", false));
    bst.addPatient(Patient(15, "Gamma", 50, "Cough", false));

    Patient p;
    assert(bst.searchPatient(10, &p) == true);
    assert(p.name == "Alpha");
    assert(bst.searchPatient(99, &p) == false);

    // Test Deletion (Leaf Node)
    bst.removePatient(5);
    assert(bst.searchPatient(5) == false);

    // Test Deletion (Node with 2 Children)
    bst.addPatient(Patient(5, "Beta", 40, "Fever", false));
    bst.addPatient(Patient(3, "Delta", 20, "Cold", false));
    bst.addPatient(Patient(7, "Epsilon", 22, "Asthma", false));
    bst.removePatient(5); // deletes node with 2 children
    assert(bst.searchPatient(5) == false);
    assert(bst.searchPatient(7) == true);

    std::cout << "  ✓ BST Test Passed!\n";
}

void testAVLTreeBalancing() {
    std::cout << "[Test 2] Running AVL Tree Balancing Test...\n";
    AVLTree avl;

    // Test Left-Left Rotation (Right Rotate)
    avl.addPatient(Patient(30, "Patient30", 30, "A", true));
    avl.addPatient(Patient(20, "Patient20", 20, "B", true));
    avl.addPatient(Patient(10, "Patient10", 10, "C", true)); // triggers right rotation

    assert(avl.getTreeHeight() == 2);
    Patient p;
    assert(avl.searchPatient(20, &p) == true);

    // Test Right-Right Rotation (Left Rotate)
    AVLTree avl2;
    avl2.addPatient(Patient(10, "Patient10", 10, "A", true));
    avl2.addPatient(Patient(20, "Patient20", 20, "B", true));
    avl2.addPatient(Patient(30, "Patient30", 30, "C", true)); // triggers left rotation
    assert(avl2.getTreeHeight() == 2);

    std::cout << "  ✓ AVL Tree Balancing Test Passed!\n";
}

void testDuplicateInsertion() {
    std::cout << "[Test 3] Running Duplicate Insertion Test...\n";
    BST bst;
    bst.addPatient(Patient(10, "Alpha", 30, "Flu", false));
    bst.addPatient(Patient(10, "DuplicateAlpha", 30, "Flu", false)); // Duplicate ID

    Patient p;
    assert(bst.searchPatient(10, &p) == true);
    assert(p.name == "Alpha"); // First patient retained

    std::cout << "  ✓ Duplicate Insertion Test Passed!\n";
}

int main() {
    std::cout << "=== HOSPITAL PATIENT MANAGEMENT DSA UNIT TESTS ===\n";
    testBSTOperations();
    testAVLTreeBalancing();
    testDuplicateInsertion();
    std::cout << "=== ALL DATA STRUCTURE UNIT TESTS PASSED SUCCESSFULLY! ===\n";
    return 0;
}
