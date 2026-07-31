#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ──────────────────────────────────────────────
//  PATIENT RECORD STRUCTURE
// ──────────────────────────────────────────────
struct Patient {
    int    id;            // Unique patient ID
    string name;
    int    age;
    string disease;
    bool   isEmergency;   // true = emergency, false = normal
};

// ──────────────────────────────────────────────
//  ===== PART 1: BST (Binary Search Tree) =====
//  Used for: Normal patient storage & search
// ──────────────────────────────────────────────

struct BSTNode {
    Patient data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Patient p) : data(p), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // Helper: Insert into BST by patient ID
    BSTNode* insert(BSTNode* node, Patient p) {
        if (node == nullptr)
            return new BSTNode(p);

        if (p.id < node->data.id)
            node->left = insert(node->left, p);
        else if (p.id > node->data.id)
            node->right = insert(node->right, p);
        else
            cout << "  [!] Patient ID " << p.id << " already exists!\n";

        return node;
    }

    // Helper: Find minimum node (used in deletion)
    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Helper: Delete a patient by ID
    BSTNode* deleteNode(BSTNode* node, int id) {
        if (node == nullptr) {
            cout << "  [!] Patient ID " << id << " not found.\n";
            return nullptr;
        }

        if (id < node->data.id)
            node->left = deleteNode(node->left, id);
        else if (id > node->data.id)
            node->right = deleteNode(node->right, id);
        else {
            // Case 1: No children
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            else if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children — replace with in-order successor
            else {
                BSTNode* successor = findMin(node->right);
                node->data = successor->data;
                node->right = deleteNode(node->right, successor->data.id);
            }
        }
        return node;
    }

    // Helper: Search by ID
    BSTNode* search(BSTNode* node, int id) {
        if (node == nullptr || node->data.id == id)
            return node;
        if (id < node->data.id)
            return search(node->left, id);
        return search(node->right, id);
    }

    // Helper: In-order traversal = sorted by ID
    void inOrder(BSTNode* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        printPatient(node->data);
        inOrder(node->right);
    }

    void printPatient(const Patient& p) {
        cout << "  | " << setw(5) << p.id
             << " | " << setw(20) << left << p.name
             << " | Age: " << setw(3) << p.age
             << " | " << setw(20) << p.disease
             << " | " << (p.isEmergency ? "EMERGENCY" : "Normal   ")
             << " |\n";
    }

public:
    BST() : root(nullptr) {}

    void addPatient(Patient p) {
        root = insert(root, p);
        cout << "  [+] Normal patient '" << p.name << "' added successfully.\n";
    }

    void removePatient(int id) {
        root = deleteNode(root, id);
    }

    void searchPatient(int id) {
        BSTNode* result = search(root, id);
        if (result) {
            cout << "\n  Patient Found (BST):\n";
            cout << "                                                 \n";
            printPatient(result->data);
            cout << "                                                  \n";
        } else {
            cout << "  [!] Patient with ID " << id << " not found in BST.\n";
        }
    }

    void displayAll() {
        if (root == nullptr) {
            cout << "  [!] No normal patients in the system.\n";
            return;
        }
        cout << "\n         Normal Patients (Sorted by ID)       \n";
        cout << "                                                                 \n";
        inOrder(root);
        cout << "                                                                 \n";
    }
};


// ──────────────────────────────────────────────
//  ===== PART 2: AVL Tree =====
//  Used for: Emergency patients (self-balancing
//  for very fast search & sort)
// ──────────────────────────────────────────────

struct AVLNode {
    Patient data;
    AVLNode* left;
    AVLNode* right;
    int height;  // Height of node (used for balancing)

    AVLNode(Patient p) : data(p), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:

    // Get height of a node
    int height(AVLNode* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Get balance factor (left height - right height)
    int getBalance(AVLNode* node) {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    // Update height of a node
    void updateHeight(AVLNode* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    // ── Rotations (to keep tree balanced) ──

    // Right Rotation (fixes Left-Left imbalance)
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x  = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left  = T2;

        updateHeight(y);
        updateHeight(x);

        return x; // x becomes new root of this subtree
    }

    // Left Rotation (fixes Right-Right imbalance)
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y  = x->right;
        AVLNode* T2 = y->left;

        y->left  = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y; // y becomes new root of this subtree
    }

    // Balance the node after insertion/deletion
    AVLNode* balance(AVLNode* node) {
        updateHeight(node);
        int bf = getBalance(node);

        // Left-Left Case → Right Rotation
        if (bf > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        // Left-Right Case → Left then Right Rotation
        if (bf > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Right Case → Left Rotation
        if (bf < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        // Right-Left Case → Right then Left Rotation
        if (bf < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // Already balanced
    }

    AVLNode* insert(AVLNode* node, Patient p) {
        if (node == nullptr)
            return new AVLNode(p);

        if (p.id < node->data.id)
            node->left = insert(node->left, p);
        else if (p.id > node->data.id)
            node->right = insert(node->right, p);
        else {
            cout << "  [!] Emergency Patient ID " << p.id << " already exists!\n";
            return node;
        }

        return balance(node);
    }

    AVLNode* findMin(AVLNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    AVLNode* deleteNode(AVLNode* node, int id) {
        if (node == nullptr) {
            cout << "  [!] Emergency Patient ID " << id << " not found.\n";
            return nullptr;
        }

        if (id < node->data.id)
            node->left = deleteNode(node->left, id);
        else if (id > node->data.id)
            node->right = deleteNode(node->right, id);
        else {
            if (!node->left || !node->right) {
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

    AVLNode* search(AVLNode* node, int id) {
        if (node == nullptr || node->data.id == id)
            return node;
        if (id < node->data.id)
            return search(node->left, id);
        return search(node->right, id);
    }

    void inOrder(AVLNode* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        printPatient(node->data);
        inOrder(node->right);
    }

    void printPatient(const Patient& p) {
        cout << "  | " << setw(5) << p.id
             << " | " << setw(20) << left << p.name
             << " | Age: " << setw(3) << p.age
             << " | " << setw(20) << p.disease
             << " | EMERGENCY |\n";
    }

public:
    AVLNode* root;
    AVLTree() : root(nullptr) {}

    void addPatient(Patient p) {
        root = insert(root, p);
        cout << "  [+] Emergency patient '" << p.name << "' added successfully.\n";
    }

    void removePatient(int id) {
        root = deleteNode(root, id);
    }

    void searchPatient(int id) {
        AVLNode* result = search(root, id);
        if (result) {
            cout << "\n  Emergency Patient Found (AVL):\n";
            cout << "                                                  \n";
            printPatient(result->data);
            cout << "                                                  \n";
        } else {
            cout << "  [!] Emergency Patient with ID " << id << " not found in AVL Tree.\n";
        }
    }

    void displayAll() {
        if (root == nullptr) {
            cout << "  [!] No emergency patients in the system.\n";
            return;
        }
        cout << "\n         Emergency Patients (Sorted by ID)       \n";
        cout << "                                                                \n";
        inOrder(root);
        cout << "                                                                 \n";
    }
};


// ──────────────────────────────────────────────
//  HOSPITAL MANAGEMENT SYSTEM (Main Controller)
// ──────────────────────────────────────────────

class HospitalSystem {
private:
    BST     normalPatients;     // BST for normal patients
    AVLTree emergencyPatients;  // AVL Tree for emergency patients

    void printHeader() {
        cout << "                                                  \n";
        cout << "                                                  \n";
        cout << "       HOSPITAL PATIENT MANAGEMENT SYSTEM         \n";
        cout << "            BST (Normal) + AVL (Emergency)        \n";
        cout << "                                                  \n";
    }

    void printMenu() {

        cout << "             MAIN MENU             \n";

        cout << "    1. Add Normal Patient (BST)    \n";
        cout << "    2. Add Emergency Patient (AVL) \n";
        cout << "    3. Search Patient by ID        \n";
        cout << "    4. Display Normal Patients     \n";
        cout << "    5. Display Emergency Patients  \n";
        cout << "    6. Display ALL Patients        \n";
        cout << "    7. Discharge (Delete) Patient  \n";
        cout << "    8. Exit                        \n";

        cout << "  Enter your choice: ";
    }

    Patient getPatientDetails(bool emergency) {
        Patient p;
        p.isEmergency = emergency;

        cout << "\n      Enter Patient Details    \n";
        cout << "  Patient ID   : ";
        cin  >> p.id;
        cin.ignore();

        cout << "  Patient Name : ";
        getline(cin, p.name);

        cout << "  Age          : ";
        cin  >> p.age;
        cin.ignore();

        cout << "  Disease      : ";
        getline(cin, p.disease);

        return p;
    }

public:
    void run() {
        printHeader();

        // Preload some sample patients
        cout << "\n  Loading sample data   \n";

        // Normal patients (BST)
        normalPatients.addPatient({101, "Ali Hassan",    30, "Flu",           false});
        normalPatients.addPatient({105, "Sara Ahmed",    25, "Migraine",       false});
        normalPatients.addPatient({103, "Usman Khan",    45, "Diabetes",       false});

        // Emergency patients (AVL Tree)
        emergencyPatients.addPatient({202, "Fatima Malik",  60, "Heart Attack",   true});
        emergencyPatients.addPatient({205, "Bilal Raza",    35, "Brain Stroke",   true});
        emergencyPatients.addPatient({201, "Ayesha Noor",   50, "Severe Injury",  true});

        cout << "  Sample data loaded!\n";

        int choice;
        do {
            printMenu();
            cin >> choice;

            switch (choice) {

                case 1: { // Add normal patient
                    Patient p = getPatientDetails(false);
                    normalPatients.addPatient(p);
                    break;
                }

                case 2: { // Add emergency patient
                    Patient p = getPatientDetails(true);
                    emergencyPatients.addPatient(p);
                    break;
                }

                case 3: { // Search patient
                    int id;
                    cout << "\n  Enter Patient ID to search: ";
                    cin >> id;
                    cout << "\n  Searching in Normal Patients (BST)   \n";
                    normalPatients.searchPatient(id);
                    cout << "\n  Searching in Emergency Patients (AVL)   \n";
                    emergencyPatients.searchPatient(id);
                    break;
                }

                case 4: // Display normal patients
                    normalPatients.displayAll();
                    break;

                case 5: // Display emergency patients
                    emergencyPatients.displayAll();
                    break;

                case 6: // Display all
                    normalPatients.displayAll();
                    emergencyPatients.displayAll();
                    break;

                case 7: { // Discharge (delete) patient
                    int id;
                    char type;
                    cout << "\n  Is patient Emergency or Normal? (E/N): ";
                    cin >> type;
                    cout << "  Enter Patient ID to discharge: ";
                    cin >> id;

                    if (type == 'E' || type == 'e') {
                        emergencyPatients.removePatient(id);
                        cout << "  [yes] Emergency patient " << id << " discharged.\n";
                    } else {
                        normalPatients.removePatient(id);
                        cout << "  [yes] Normal patient " << id << " discharged.\n";
                    }
                    break;
                }

                case 8:
                    cout << "\n  Thank you for using Hospital Management System!\n";
                    cout << "  Stay healthy. Goodbye!\n\n";
                    break;

                default:
                    cout << "  [!] Invalid choice. Please enter 1-8.\n";
            }

        } while (choice != 8);
    }
};


// ──────────────────────────────────────────────
//  MAIN FUNCTION
// ──────────────────────────────────────────────
int main() {
    HospitalSystem hospital;
    hospital.run();
    return 0;
}
