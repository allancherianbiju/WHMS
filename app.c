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


int main() {   
    struct  doctor
    {
        /* data */
        int doctorID;
        char doctorName[50];
    };

    struct patient
    {
        /* data */
        int patientID;
        char patientName[50];
        int patientAge;
    };
    
    struct visitor
    {
        /* data */
        int visitorID;
        char visitorName[50];
        int visitingPatientID;
    };
    
    // Initializing patient ID counter
    int patientIDCounter = 0;
    // User choice variable
    int choice = 0;
    // Initializing time's object
    time_t t;
    time(&t);
    // Clearing console
    while(choice != 6) {
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
                    printf("Enter Patient Details\n--------------------------\nPatient Name: ");
                    scanf("%s",x.patientName);
                    printf("Patient Age: ");
                    scanf("%d", &x.patientAge);
                    x.patientID = patientIDCounter;
                    ++patientIDCounter;
                    printf("\n--------------------------\nNew Patient Registered\n");
                    printf("ID: %d \nName: %s \nAge: %d \n", x.patientID, x.patientName, x.patientAge);
                    printf("\n\nPress ENTER to continue...");
                    getch();
                    break;
                }

            default:
                break;
        }
    }
}