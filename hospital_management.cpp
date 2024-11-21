#include <iostream>
#include<iomanip>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

// Class representing a Person (Abstarct base class)
class Person
{
public:
  string name;
  Person(string n) : name(n) {}
  virtual void display_info() const = 0; // Pure virtual function for displaying info
};

// Class representing a Doctor (Inherits from Person)
class Doctor : public Person
{
public:
  int doctor_id;
  string specialization;

  Doctor(string n, int id, string spec) : Person(n), doctor_id(id), specialization(spec) {}

  void display_info() const override
  {
    cout << "Doctor Name: " << name << "\n";
    cout << "Doctor ID: " << doctor_id << "\n";
    cout << "Specialization: " << specialization << "\n";
  }
};

// Class representing a Patient (Inherits from Person)
class Patient : public Person
{
public:
  int patient_id;
  int age;
  string disease;
  string medical_history;
  int room;
  Doctor *treating_doctor;
  vector<string> reports; // Attribute to store patient reports

  Patient(string n, int id, int a, string d, string history, int r, Doctor *doctor)
      : Person(n), patient_id(id), age(a), disease(d), medical_history(history), room(r), treating_doctor(doctor) {}

  void display_info() const override{
    cout << "Patient Name: " << name << "\n";
    cout << "Patient ID: " << patient_id << "\n";
    cout << "Age: " << age << "\n";
    cout << "Disease: " << disease << "\n";
    cout << "Medical History: " << medical_history << "\n";
    cout << "Room number: " << room << "\n";
    cout << "Reports: \n";
    if (reports.empty())
    {
      cout << "No reports available.\n";
    }
    else
    {
      for (const auto &report : reports)
      {
        cout << "- " << report << "\n";
      }
    }
  }
  
  void show_patients(){
    cout << "Patient Name: " << name << "\n";
    cout << "Disease: " << disease << "\n";
    cout << "Patient ID: " << patient_id << "\n";
    cout << "Room number: " << room << "\n";
  }

  void add_report(const string &report)
  {
    reports.push_back(report);
  }

  void update_history(string new_history)
  {
    medical_history = medical_history + " | " + new_history;
  }
};
// Class representing a Medicine (for dispensing)
class Medicine
{
public:
  string name;
  float price;
  int quantity;

  Medicine(string n, float p, int q) : name(n), price(p), quantity(q) {}

  void display_info() const
  {
    cout << "Medicine Name: " << name << "\n";
    cout << "Price: " << price << "\n";
    cout << "Quantity Available: " << quantity << "\n";
  }
};

// Class representing a Staff member (e.g., Nurse, Receptionist)
class Staff : public Person
{
public:
  int staff_id;
  string role;

  Staff(string n, int id, string r) : Person(n), staff_id(id), role(r) {}

  void display_info() const override
  {
    cout << "Staff Name: " << name << "\n";
    cout << "Staff ID: " << staff_id << "\n";
    cout << "Role: " << role << "\n";
  }
};

// Class representing an Appointment
class Appointment
{
public:
  int patient_id;
  int doctor_id;
  string date;

  Appointment(int p_id, int d_id, string d) : patient_id(p_id), doctor_id(d_id), date(d) {}

  void display_info() const
  {
    cout << "Appointment for Patient ID: " << patient_id << "\n";
    cout << "Doctor ID: " << doctor_id << "\n";
    cout << "Date: " << date << "\n";
  }
};

// Billing class to calculate and generate the bill
class Billing
{
public:
  float consultation_fee;
  float medicine_cost;

  Billing(float fee, float cost) : consultation_fee(fee), medicine_cost(cost) {}

  void displayBill() const
  {
    cout << "Consultation Fee: " << consultation_fee << endl;
    cout << "Medicine Cost: " << medicine_cost << endl;
    cout << "Total Cost: " << consultation_fee + medicine_cost << endl;
  }
};

vector<Doctor> doctors;
vector<Patient> patients;
vector<Staff> staff;
vector<Medicine> medicines;
vector<Appointment> appointments;

void add_doctor()
{
  string name, specialization;
  int id;

  cout << "Enter Doctor's Name: ";
  cin >> name;
  cout << "Enter Doctor's ID: ";
  cin >> id;
  cout << "Enter Doctor's Specialization: ";
  cin >> specialization;

  Doctor new_doc(name, id, specialization);
  doctors.push_back(new_doc);
  cout << "Doctor added successfully!\n";
}

void add_patient()
{
  string name, disease, medical_history, report;
  int age, id, room, doctor_index;

  cout << "Enter Patient's Name: ";
  cin >> name;
  cout << "Assign Patient ID: ";
  cin >> id;
  cout << "Enter Patient's Age: ";
  cin >> age;
  cout << "Enter Patient's Disease: ";
  cin >> disease;
  cout << "Enter Patient's Medical History: ";
  cin >> medical_history;
  cout << "Enter Patient's Room Number: ";
  cin >> room;

  if (!doctors.empty())
  {
    cout << "Assign a doctor (0 to " << doctors.size() - 1 << "): ";
    cin >> doctor_index;
    if (doctor_index >= 0 && doctor_index < doctors.size())
    {
      Doctor *assigned_doc = &doctors[doctor_index];
      Patient new_patient(name, id, age, disease, medical_history, room, assigned_doc);

      char add_reportChoice;
      do
      {
        cout << "Would you like to add a report for this patient? (y/n): ";
        cin >> add_reportChoice;
        if (add_reportChoice == 'y' || add_reportChoice == 'Y')
        {
          cout << "Enter report details: ";
          cin.ignore();         // To clear the buffer
          getline(cin, report); // Read full report details
          new_patient.add_report(report);
        }
      } while (add_reportChoice == 'y' || add_reportChoice == 'Y');

      patients.push_back(new_patient);
      cout << "Patient added successfully!\n";
    }
    else
    {
      cout << "Invalid doctor index!\n";
    }
  }
  else
  {
    cout << "No doctors available. Cannot assign a doctor to patient\n";
    Patient new_patient(name, id, age, disease, medical_history, room, nullptr);

    patients.push_back(new_patient);
    cout << "Patient added without treating doctor.\n";
  }
}

// Function to add Staff
void add_staff()
{
  string name, role;
  int id;

  cout << "Enter Staff's Name: ";
  cin >> name;
  cout << "Enter Staff's ID: ";
  cin >> id;
  cout << "Enter Staff's Role (e.g., Nurse, Administrator): ";
  cin >> role;

  Staff new_staff(name, id, role);
  staff.push_back(new_staff);
  cout << "Staff added successfully!\n";
}

// Function to add Medicine
void add_medicine()
{
  string name;
  float price;
  int quantity;

  cout << "Enter Medicine Name: ";
  cin >> name;
  cout << "Enter Medicine Price: ";
  cin >> price;
  cout << "Enter Medicine Quantity: ";
  cin >> quantity;

  Medicine new_medicine(name, price, quantity);
  medicines.push_back(new_medicine);
  cout << "Medicine added successfully!\n";
}

// Function to schedule an appointment
void schedule_appointment()
{
  int patient_id, doctor_id;
  string date;

  cout << "Enter Patient ID: ";
  cin >> patient_id;
  cout << "Enter Doctor ID: ";
  cin >> doctor_id;
  cout << "Enter Appointment Date: ";
  cin >> date;

  Appointment new_appointment(patient_id, doctor_id, date);
  appointments.push_back(new_appointment);
  cout << "Appointment scheduled successfully!\n";
}

// Function to view a patient's details

void view_patient_details()
{
  int patientID;
  cout << "Enter Patient ID: ";
  cin >> patientID;

  for (const auto &patient : patients)
  {
    if (patient.patient_id == patientID)
    {
<<<<<<< Updated upstream
      cout << "Patient Details:\n";
      patient.display_info();
      cout << "----------------------\n";
      Billing bill(200.0, 0.0); // example fixed billing amount
      cout << "Billing Details:\n";
      bill.displayBill();
      return;
=======
        if (patient.patient_id == patientID)
        {   
            cout << "Patient Details:\n";
            patient.display_info();
            cout<<setfill('-')<<setw(50)<<"-"<<endl;
            Billing bill(200.0, 0.0);  // example fixed billing amount
            cout << "Billing Details:\n";
            bill.displayBill();
            return;
        }
>>>>>>> Stashed changes
    }
  }
  cout << "Patient not found.\n";
}

// Function to view Doctors
void view_doctors()
{
<<<<<<< Updated upstream
  for (const auto &d : doctors)
  {
    d.display_info();
    cout << "----------------------\n";
  }
=======
    for (const auto &doctor : doctors)
    {   cout<<setfill('-')<<setw(50)<<"-"<<endl;
        doctor.display_info();
        cout<<setfill('-')<<setw(50)<<"-"<<endl;
    }
>>>>>>> Stashed changes
}

// Function to view Patients
void view_patients()
{
<<<<<<< Updated upstream
  for ( auto &p : patients)
  {
    p.show_patients();
    cout << "----------------------\n";
  }
=======
    for (const auto &patient : patients)
    {   cout<<setfill('-')<<setw(50)<<"-"<<endl;
        patient.display_info();
        cout<<setfill('-')<<setw(50)<<"-"<<endl;
    }
>>>>>>> Stashed changes
}

// Function to view Appointments
void view_appointments()
{
<<<<<<< Updated upstream
  for (const auto &a : appointments)
  {
    a.display_info();
    cout << "----------------------\n";
  }
=======
    for (const auto &appointment : appointments)
    {   cout<<setfill('-')<<setw(50)<<"-"<<endl;
        appointment.display_info();
        cout<<setfill('-')<<setw(50)<<"-"<<endl;
    }
>>>>>>> Stashed changes
}

// Function to view Staff
void view_staff()
{
<<<<<<< Updated upstream
  for (const auto &s : staff)
  {
    s.display_info();
    cout << "----------------------\n";
  }
=======
    for (const auto &staffMember : staff)
    {   cout<<setfill('-')<<setw(50)<<"-"<<endl;
        staffMember.display_info();
        cout<<setfill('-')<<setw(50)<<"-"<<endl;
    }
>>>>>>> Stashed changes
}

// Function to view Medicines
void view_medicines()
{
<<<<<<< Updated upstream
  for (const auto &m : medicines)
  {
    m.display_info();
    cout << "----------------------\n";
  }
=======
    for (const auto &medicine : medicines)
    {   cout<<setfill('-')<<setw(50)<<"-"<<endl;
        medicine.display_info();
        cout<<setfill('-')<<setw(50)<<"-"<<endl;
    }
>>>>>>> Stashed changes
}

// Generate billing
void billing()
{
  int patientID;
  cout << "Enter Patient ID to generate billing: ";
  cin >> patientID;

  for (const auto &p : patients)
  {
    if (p.patient_id == patientID)
    {
      Billing bill(200.0, 0.0); // example fixed billing amount
      cout << "Billing Details for Patient " << p.name << ":\n";
      bill.displayBill();
      return;
    }
  }
  cout << "Patient with ID " << patientID << " not found.\n";
}

// Exit system
void exit_system()
{
<<<<<<< Updated upstream
  cout << "Exiting system...\n";
  exit(0);
=======
    cout << "Exiting system...\n";
    exit(0);
    cout<<setfill('-')<<setw(50)<<"-"<<endl;
>>>>>>> Stashed changes
}

int main()
{
  int choice;

<<<<<<< Updated upstream
  while (true)
  {
    cout << "\nHospital Management System\n";
    cout << "1. Add Doctor\n";
    cout << "2. Add Patient\n";
    cout << "3. Add Staff\n";
    cout << "4. Add Medicine\n";
    cout << "5. Schedule Appointment\n";
    cout << "6. View Patient's Details\n";
    cout << "7. Dispense Medicine\n";
    cout << "8. Generate Billing\n";
    cout << "9. View Doctors\n";
    cout << "10. View Patients\n";
    cout << "11. View Appointments\n";
    cout << "12. View Staff\n";
    cout << "13. View Medicines\n";
    cout << "14. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      add_doctor();
      break;
    case 2:
      add_patient();
      break;
    case 3:
      add_staff();
      break;
    case 4:
      add_medicine();
      break;
    case 5:
      schedule_appointment();
      break;
    case 6:
      view_patient_details();
      break;
    case 7:
      // Implement Dispense Medicine logic here (if required)
      break;
    case 8:
      billing();
      break;
    case 9:
      view_doctors();
      break;
    case 10:
      view_patients();
      break;
    case 11:
      view_appointments();
      break;
    case 12:
      view_staff();
      break;
    case 13:
      view_medicines();
      break;
    case 14:
      exit_system();
      break;
    default:
      cout << "Invalid choice, please try again.\n";
=======
    while (true)
    {   cout<<setfill('-')<<setw(50)<<"-"<<endl;
        cout << "\nHospital Management System\n";
        cout << "1. Add Doctor\n";
        cout << "2. Add Patient\n";
        cout << "3. Add Staff\n";
        cout << "4. Add Medicine\n";
        cout << "5. Schedule Appointment\n";
        cout << "6. View Patient's Details\n";
        cout << "7. Dispense Medicine\n";
        cout << "8. Generate Billing\n";
        cout << "9. View Doctors\n";
        cout << "10. View Patients\n";
        cout << "11. View Appointments\n";
        cout << "12. View Staff\n";
        cout << "13. View Medicines\n";
        cout << "14. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout<<setfill('-')<<setw(50)<<"-"<<endl;

        switch (choice)
        {
        case 1:
            add_doctor();
            break;
        case 2:
            add_patient();
            break;
        case 3:
            add_staff();
            break;
        case 4:
            add_medicine();
            break;
        case 5:
            schedule_appointment();
            break;
        case 6:
            view_patient_details();
            break;
        case 7:
            // Implement Dispense Medicine logic here (if required)
            break;
        case 8:
            billing();
            break;
        case 9:
            view_doctors();
            break;
        case 10:
            view_patients();
            break;
        case 11:
            view_appointments();
            break;
        case 12:
            view_staff();
            break;
        case 13:
            view_medicines();
            break;
        case 14:
            exit_system();
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
>>>>>>> Stashed changes
    }
  }

  return 0;
}
