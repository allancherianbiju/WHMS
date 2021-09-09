// Dr. Kumar and two other doctors runs a hospital for senior citizens which sees a large number of;
// patients coming in every day. In order to avoid inconvenience to the aged patients, the rule is that the
// oldest patient is seen first by the doctor. As the patients keep coming and registering, they are added
// to a priority list from which patient’s names are called out for consultation. Some of the patients are
// admitted as in patients. Since it is not practical to implement this system using pen and paper, Dr.
// Kumar requested WIPRO to develop an appointment software.
// The software should be capable to do the following:
// 1. Registration of the patient: Take the patient’s name, age and create a patient ID.
// 2. Out-patient: Assign a doctor. Insert the patient id in the priority list based on the age of the
// patient. Display the next patient ID and name in line to meet the doctor and remove this patient
// from the priority list.
// 3. In-Patient: allocation of room, Doctor etc.
// 4. Manage patient history
// 5. Number of visitors for a in-patient
// 6. Details of in-patients and out-patients on a particular day
// 7. Doctor wise patient list

// Patient Registration
// In-Patient: Allocation of room, doctor, view number of visitors
// Out-Patient: 


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct patient
{
    /* data */
    int patientID;
    char patientName[50];
    int patientAge;
    char patientHistory[100];
} Patients[50];

struct  doctor
{
    /* data */
    int doctorID;
    char doctorName[50];
} Doctors[3];

struct visitor
{
    /* data */
    int visitorID;
    char visitorName[50];
    int visitingPatientID;
};

// Out-Patient Linked List
struct outPatientPriorityList
{
    /* data */
    int positionID;
    int patientID;
    int doctorID;
    int timeOfVisit;
    struct outPatientPriorityList* next;
};

// In-Patient Linked List
struct inPatientPriorityList
{
    /* data */
    int positionID;
    int patientID;
    int roomID;
    int doctorID;
    int timeOfEntry;
    struct inPatientPriorityList* next;
};

// Displaying details of a patient in Out-Patient queue
void printOutPatientInfo (struct outPatientPriorityList* n) 
{
    while(n!= NULL) 
    {
        printf("Rank: %d\nPatient ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor ID: %s\nTime of Visit: %s", n->positionID, n->patientID, Patients[n->patientID].patientName, Patients[n->patientID].patientAge, n->doctorID, n->timeOfVisit);
        n = n->next;
    }
}

// Init Doctors
void initDoctors () 
{
    Doctors[0].doctorID = 1;
    strncpy(Doctors[0].doctorName, "Dr. Kumar", 50);
    Doctors[1].doctorID = 2;
    strncpy(Doctors[1].doctorName, "Dr. House Fernandez", 50);
    Doctors[2].doctorID = 3;
    strncpy(Doctors[2].doctorName, "Dr. Shaun Murphy", 50);
}

int main() 
{    
    // Initializing patient ID counter
    int patientIDCounter = 0;
    // User choice variable
    int choice = 0;
    // Initializing time's object
    time_t t;
    time(&t);
    // Initializing doctors
    initDoctors();
    // Starting menu loop
    while(choice != 6) 
    {
        // Clearing console
        printf("\e[1;1H\e[2J");
        printf("Wipro Hospital Management System\n-------------------------------\nTime: %s", ctime(&t));
        printf("\n1) Patient Registration \n2) Out-Patient \n3) In-Patient \n4) Patient History \n5) Doctor Details \n6) Exit \nEnter your choice: ");
        scanf("%d", &choice);
        printf("\e[1;1H\e[2J");
        switch (choice)
        {
            case 1:
                {
                    struct patient x;
                    char name[50];
                    printf("Enter Patient Details\n--------------------------\nPatient Name: ");
                    // Removing leading new line in the buffer
                    getchar();
                    // Using fgets instead of gets due to security reasons
                    fgets(x.patientName, sizeof(x.patientName), stdin);
                    // Removing trailing new line from input
                    x.patientName[strcspn(x.patientName, "\n")] = 0;
                    // gets(x.patientName);
                    printf("Patient Age: ");
                    scanf("%d", &x.patientAge);
                    x.patientID = patientIDCounter;
                    Patients[patientIDCounter] = x;
                    printf("\n--------------------------\nNew Patient Registered\n");
                    printf("ID: %d \nName: %s \nAge: %d \n", Patients[patientIDCounter].patientID, Patients[patientIDCounter].patientName, Patients[patientIDCounter].patientAge);
                    ++patientIDCounter;
                    printf("\n\nPress any key to continue...");
                    getch();
                    break;
                }

            default:
                break;
        }
    }
}