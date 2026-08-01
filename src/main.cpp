#include "Patient.hpp"
#include "BST.hpp"
#include "AVLTree.hpp"

#include <iostream>
#include <string>

class HospitalSystem {
private:
    BST     normalPatients;     // Binary Search Tree for Outpatient Normal Storage
    AVLTree emergencyPatients;  // Self-Balancing AVL Tree for Emergency Ward Records

    void printHeader() const {
        std::cout << "===================================================\n";
        std::cout << "       HOSPITAL PATIENT MANAGEMENT SYSTEM          \n";
        std::cout << "         BST (Normal) + AVL Tree (Emergency)       \n";
        std::cout << "===================================================\n";
    }

    void printMenu() const {
        std::cout << "\n------------------ MAIN MENU ------------------\n";
        std::cout << "  1. Add Normal Patient (BST)\n";
        std::cout << "  2. Add Emergency Patient (AVL Tree)\n";
        std::cout << "  3. Search Patient by ID\n";
        std::cout << "  4. Display Normal Patients (BST)\n";
        std::cout << "  5. Display Emergency Patients (AVL Tree)\n";
        std::cout << "  6. Display ALL Patients\n";
        std::cout << "  7. Discharge (Delete) Patient\n";
        std::cout << "  8. Exit\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << "Enter choice (1-8): ";
    }

    Patient getPatientDetails(bool emergency) const {
        Patient p;
        p.isEmergency = emergency;

        std::cout << "\n--- Enter Patient Details ---\n";
        std::cout << "Patient ID   : ";
        while (!(std::cin >> p.id) || p.id <= 0) {
            std::cout << "  [!] Invalid ID. Enter positive integer: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cin.ignore();

        std::cout << "Patient Name : ";
        std::getline(std::cin, p.name);

        std::cout << "Age          : ";
        while (!(std::cin >> p.age) || p.age < 0) {
            std::cout << "  [!] Invalid Age. Enter positive integer: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cin.ignore();

        std::cout << "Disease      : ";
        std::getline(std::cin, p.disease);

        return p;
    }

public:
    void preloadSampleData() {
        std::cout << "Preloading sample patient records...\n";
        normalPatients.addPatient(Patient(101, "Ali Hassan", 30, "Flu", false));
        normalPatients.addPatient(Patient(105, "Sara Ahmed", 25, "Migraine", false));
        normalPatients.addPatient(Patient(103, "Usman Khan", 45, "Diabetes", false));

        emergencyPatients.addPatient(Patient(202, "Fatima Malik", 60, "Heart Attack", true));
        emergencyPatients.addPatient(Patient(205, "Bilal Raza", 35, "Brain Stroke", true));
        emergencyPatients.addPatient(Patient(201, "Ayesha Noor", 50, "Severe Injury", true));
        std::cout << "Sample data loaded successfully!\n";
    }

    void run() {
        printHeader();
        preloadSampleData();

        int choice = 0;
        do {
            printMenu();
            if (!(std::cin >> choice)) {
                std::cout << "  [!] Invalid menu choice. Please enter 1-8.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            switch (choice) {
                case 1: {
                    Patient p = getPatientDetails(false);
                    normalPatients.addPatient(p);
                    break;
                }
                case 2: {
                    Patient p = getPatientDetails(true);
                    emergencyPatients.addPatient(p);
                    break;
                }
                case 3: {
                    int id;
                    std::cout << "Enter Patient ID to search: ";
                    std::cin >> id;
                    Patient p;
                    if (normalPatients.searchPatient(id, &p)) {
                        std::cout << "\nFound in Normal Patients (BST):\n";
                        printPatientRecord(p);
                    } else if (emergencyPatients.searchPatient(id, &p)) {
                        std::cout << "\nFound in Emergency Patients (AVL Tree):\n";
                        printPatientRecord(p);
                    } else {
                        std::cout << "  [!] Patient ID " << id << " not found in system.\n";
                    }
                    break;
                }
                case 4:
                    normalPatients.displayAll();
                    break;
                case 5:
                    emergencyPatients.displayAll();
                    break;
                case 6:
                    normalPatients.displayAll();
                    emergencyPatients.displayAll();
                    break;
                case 7: {
                    int id;
                    char type;
                    std::cout << "Is patient Emergency or Normal? (E/N): ";
                    std::cin >> type;
                    std::cout << "Enter Patient ID to discharge: ";
                    std::cin >> id;
                    if (type == 'E' || type == 'e') {
                        emergencyPatients.removePatient(id);
                    } else {
                        normalPatients.removePatient(id);
                    }
                    break;
                }
                case 8:
                    std::cout << "\nExiting Hospital System. Stay healthy!\n";
                    break;
                default:
                    std::cout << "  [!] Invalid choice. Please enter 1-8.\n";
            }
        } while (choice != 8);
    }
};

int main() {
    HospitalSystem hospital;
    hospital.run();
    return 0;
}
