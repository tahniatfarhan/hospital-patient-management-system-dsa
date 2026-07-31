# Hospital Patient Management System (HPMS - C++ Data Structures)

## Professional Overview
The **Hospital Patient Management System (HPMS)** is an advanced C++ application implementing optimized non-linear data structures for medical record management and emergency triage. Created as the *Data Structures & Algorithms* final project at UET Lahore, HPMS combines **Binary Search Trees (BST)** for sorted patient directory maintenance and **Priority Queues (Max-Heaps)** for real-time emergency room patient prioritization.

## Objectives
- Apply non-linear data structures (BST, Priority Queue / Heap) to solve real-world healthcare workflow challenges.
- Achieve $O(\log n)$ time complexity for patient search, insertion, and record deletion operations.
- Ensure emergency care triage prioritizes critical condition patients over standard appointments.

## Features
- **BST Patient Storage**: Binary Search Tree storing patient profiles indexed by unique Patient ID for fast logarithmic lookup and insertion.
- **Emergency Triage Queue**: Priority Queue structure organizing emergency patients by severity rating, guaranteeing immediate critical care dispatch.
- **Dynamic Record Operations**: Complete support for patient admission, condition updates, record searching, and node deletion (handling zero, one, or two child nodes).
- **In-Order Traversal Reporting**: Formatted console output generating sorted patient listings by ID.
- **Comprehensive Project Documentation**: Includes full technical report (`HPMS_Report_v2.docx`) and presentation slides (`HPMS_Presentation_v3.pptx`).

## Technologies Used
- **Primary Language**: C++ (C++11 standard)
- **Data Structures**: Binary Search Tree (BST), Priority Queue (Max-Heap), Structs, Pointers

## Architecture Overview
The system maintains dual structural engines:
- **`BST` Class**: Manages standard outpatient records with self-referential `BSTNode` pointers.
- **Triage Queue**: Handles emergency admissions with heap-based max-priority ordering.

## Folder Structure
```text
hospital-patient-management-system-dsa/
├── src/
│   └── hospital_management.cpp
├── docs/
│   ├── HPMS_Report_v2.docx
│   └── HPMS_Presentation_v3.pptx
├── .gitignore
├── LICENSE
└── README.md
```

## Installation Guide
1. Ensure a C++ compiler (`g++` or `clang++`) is installed.
2. Clone or download this repository.

## How to Run
1. Compile source code:
```bash
g++ -std=c++11 src/hospital_management.cpp -o hpms
```
2. Run executable:
```bash
./hpms
```

## Verification & Documentation
Project architecture, data structure benchmarks, and verification reports:
- [HPMS Full Technical Report (Word)](docs/HPMS_Report_v2.docx)
- [HPMS Project Presentation (PowerPoint)](docs/HPMS_Presentation_v3.pptx)

## Learning Outcomes
- Mastered dynamic memory management and pointer manipulations in C++ tree data structures.
- Implemented BST deletion algorithms handling node replacement with in-order successors.
- Designed hybrid data structure architectures balancing search efficiency with priority triage queueing.

## Future Improvements
- Upgrade BST structure to an AVL Tree or Red-Black Tree for guaranteed $O(\log n)$ balancing.
- Add file persistent storage for saving patient records across application restarts.
- Develop a modern Qt or Web frontend interface for hospital staff desktop workstations.

## License
Distributed under the MIT License. See `LICENSE` for more information.

## Author
**Tahniat Farhan**  
BS Cyber Security  
University of Engineering and Technology (UET) Lahore
