#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include <iostream>
#include <iomanip>

struct Patient {
    int         id;
    std::string name;
    int         age;
    std::string disease;
    bool        isEmergency;

    Patient() : id(0), name(""), age(0), disease(""), isEmergency(false) {}
    Patient(int p_id, const std::string& p_name, int p_age, const std::string& p_disease, bool p_emergency)
        : id(p_id), name(p_name), age(p_age), disease(p_disease), isEmergency(p_emergency) {}
};

inline void printPatientRecord(const Patient& p) {
    std::cout << "  | " << std::setw(5) << p.id
              << " | " << std::setw(20) << std::left << p.name
              << " | Age: " << std::setw(3) << p.age
              << " | " << std::setw(20) << p.disease
              << " | " << (p.isEmergency ? "EMERGENCY" : "Normal   ")
              << " |\n";
}

#endif // PATIENT_HPP
