#include <iostream>
#include <queue>
#include <vector>
#include <string>

// Structure to represent a Patient
struct Patient {
    int id;
    std::string name;
    int age;
    std::string contact;
    int severity;  // Higher severity means higher priority

    // Overload the < operator to compare patients based on severity for the priority queue
    bool operator<(const Patient& other) const {
        return severity < other.severity;  // Max-Heap for priority queue (higher severity = higher priority)
    }
};

// Priority queue for emergency patients
std::priority_queue<Patient> emergencyQueue;

// Queue for regular patients
std::queue<Patient> regularQueue;

// Variable to keep track of available doctors
int availableDoctors = 5;

// Function to add a patient to the emergency queue
void addEmergencyPatient() {
    Patient patient;
    std::cout << "Enter Patient ID: ";
    std::cin >> patient.id;
    std::cout << "Enter Patient Name: ";
    std::cin.ignore();  // To ignore the leftover newline character
    std::getline(std::cin, patient.name);
    std::cout << "Enter Patient Age: ";
    std::cin >> patient.age;
    std::cout << "Enter Patient Contact: ";
    std::cin >> patient.contact;
    std::cout << "Enter Patient Severity (1-10): ";
    std::cin >> patient.severity;

    emergencyQueue.push(patient);
    std::cout << "Emergency patient added to queue.\n";
}

// Function to add a patient to the regular queue
void addRegularPatient() {
    Patient patient;
    std::cout << "Enter Patient ID: ";
    std::cin >> patient.id;
    std::cout << "Enter Patient Name: ";
    std::cin.ignore();  // To ignore the leftover newline character
    std::getline(std::cin, patient.name);
    std::cout << "Enter Patient Age: ";
    std::cin >> patient.age;
    std::cout << "Enter Patient Contact: ";
    std::cin >> patient.contact;

    // Regular patients have no severity so no need to input severity
    regularQueue.push(patient);
    std::cout << "Regular patient added to queue.\n";
}

// Function to assign doctors to patients
void assignDoctor() {
    if (availableDoctors == 0) {
        std::cout << "No doctors are currently available.\n";
        return;
    }

    while (availableDoctors > 0) {
        if (!emergencyQueue.empty()) {
            // Assign doctor to emergency patient
            Patient patient = emergencyQueue.top();
            emergencyQueue.pop();
            std::cout << "Assigned Doctor to Emergency Patient: " << patient.name << " (Severity: " << patient.severity << ")\n";
            availableDoctors--;
        } else if (!regularQueue.empty()) {
            // Assign doctor to regular patient
            Patient patient = regularQueue.front();
            regularQueue.pop();
            std::cout << "Assigned Doctor to Regular Patient: " << patient.name << "\n";
            availableDoctors--;
        } else {
            std::cout << "No patients in the queue.\n";
            break;
        }
    }

    if (availableDoctors == 0) {
        std::cout << "All doctors are currently busy.\n";
    }
}

// Function to release doctors (free up doctor slots)
void releaseDoctor() {
    int doctorsReleased;
    std::cout << "Enter number of doctors becoming available: ";
    std::cin >> doctorsReleased;
    availableDoctors += doctorsReleased;
    std::cout << doctorsReleased << " doctors are now available.\n";
}

// Function to display the patients in the emergency and regular queues
void displayQueues() {
    std::cout << "\n--- Emergency Queue ---\n";
    std::priority_queue<Patient> tempEmergencyQueue = emergencyQueue;  // Copy the queue to print without modifying the original
    while (!tempEmergencyQueue.empty()) {
        Patient patient = tempEmergencyQueue.top();
        tempEmergencyQueue.pop();
        std::cout << "Patient ID: " << patient.id << ", Name: " << patient.name
                  << ", Severity: " << patient.severity << "\n";
    }

    std::cout << "\n--- Regular Queue ---\n";
    std::queue<Patient> tempRegularQueue = regularQueue;  // Copy the queue to print without modifying the original
    while (!tempRegularQueue.empty()) {
        Patient patient = tempRegularQueue.front();
        tempRegularQueue.pop();
        std::cout << "Patient ID: " << patient.id << ", Name: " << patient.name << "\n";
    }
}

// Main function with menu-driven interface
int main() {
    int choice;
    do {
        std::cout << "\n--- Hospital Management System ---\n";
        std::cout << "1. Add Emergency Patient\n";
        std::cout << "2. Add Regular Patient\n";
        std::cout << "3. Assign Doctor\n";
        std::cout << "4. Release Doctors\n";
        std::cout << "5. Display Queues\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addEmergencyPatient();
                break;
            case 2:
                addRegularPatient();
                break;
            case 3:
                assignDoctor();
                break;
            case 4:
                releaseDoctor();
                break;
            case 5:
                displayQueues();
                break;
            case 6:
                std::cout << "Exiting the system...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

