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
#include<conio.h>
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
} Doctors[4];

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
    int patientID;
    int doctorID;
    char timeOfVisit[50];
    struct outPatientPriorityList* next;
    struct outPatientPriorityList* prev;
};

// In-Patient Linked List
struct inPatientPriorityList
{
    /* data */
    int patientID;
    int roomID;
    int doctorID;
    int timeOfEntry;
    struct inPatientPriorityList* next;
};

struct outPatientPriorityList *head = NULL;
struct outPatientPriorityList *last = NULL;
struct outPatientPriorityList *current = NULL;

// Check if Priority Linked list is empty
int isEmpty() 
{
   return head == NULL;
}

// Return length of Priorty Queue
int length() {
   int length = 0;
   struct outPatientPriorityList *current;
	
   for(current = head; current != NULL; current = current->next){
      length++;
   }	
   return length;
}

// Displaying details of a patient in Out-Patient queue
void printOutPatientInfo(struct outPatientPriorityList *n) 
{
    if(n == NULL)
    {
        printf("No patient details found. Press any key to continue...");
        getch();
    }
    int counter = 1;
    while(n!= NULL) 
    {
        printf("#%d\nPatient ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor: %s\nPatient History: %s\nTime of Visit: %s\n", counter, n->patientID, Patients[n->patientID].patientName, Patients[n->patientID].patientAge, Doctors[n->doctorID].doctorName, Patients[n->patientID].patientHistory, n->timeOfVisit);
        printf("-------------------------------\n");
        n = n->next;
        ++counter;
    }
}

// Init Doctors
void initDoctors() 
{
    Doctors[0].doctorID = 0;
    strncpy(Doctors[0].doctorName, "Unassigned", 50);
    Doctors[1].doctorID = 1;
    strncpy(Doctors[1].doctorName, "Dr. Kumar", 50);
    Doctors[2].doctorID = 2;
    strncpy(Doctors[2].doctorName, "Dr. House Fernandez", 50);
    Doctors[3].doctorID = 3;
    strncpy(Doctors[3].doctorName, "Dr. Shaun Murphy", 50);
}

// Add Patient to Out-Patient Queue, based on age
void addPatient(struct patient x, char currentTime[])
{
    
    int queueLength = length();
    struct outPatientPriorityList *temp;
    struct outPatientPriorityList *ptr = head;
    struct outPatientPriorityList *link = (struct outPatientPriorityList*) malloc(sizeof(struct outPatientPriorityList));
    link->doctorID = Doctors[0].doctorID;
    link->patientID = x.patientID;
    link->prev = NULL;
    link->next = NULL;
    strncpy(link->timeOfVisit, currentTime, 50);
    printf("Queue Length: %d\n", queueLength);
    if(queueLength != 0) 
    {
        printf("Head: %s, Last: %s\n", Patients[head->patientID].patientName, Patients[last->patientID].patientName);
        int counter = 0;
        if(queueLength > 1)
        {
            while(ptr!=NULL)
            {
                // printf("\nPtr ID: %d\n", ptr->patientID);
                if(Patients[ptr->patientID].patientAge < x.patientAge)
                {
                    // printf("\nCounter: %d\nPtr ID: %d\n", counter, ptr->patientID);
                    temp = ptr->prev;
                    // Inserting at the beginning
                    if(ptr->prev == NULL)
                    {
                        printf("Inserting at the beginning\n");
                        link->next = head;
                        head = link;
                        link->prev = NULL;
                    }
                    else
                    // Inserting in between
                    {
                        printf("Inserting in between\n");
                        link->prev = ptr->prev;
                        link->next = ptr;
                        ptr->prev->next = link;
                        ptr->prev = link;
                    }
                    break;
                }
                else
                {
                    // Inserting at the end
                    if(ptr->next == NULL)
                    {
                        printf("Inserting at the end\n");
                        temp = last;
                        temp->next = link;
                        link->prev = temp;
                        last = link;
                        link->next = NULL;
                        break;

                    }
                }
                ptr = ptr->next;
                ++counter;
            }
        }
        else
        {
            printf("Adding second node");
            if(Patients[ptr->patientID].patientAge < x.patientAge)
            {
                printf(" at the beginning");
                last = head;
                ptr->prev = link;
                link->prev = NULL;
                link->next = head;
                head = link;

            }
            else
            {
                printf(" at the end");
                ptr->next = link;
                link->prev = head;
                link->next = NULL;
                last = link;
            }
        }
    }
    else
    {
        printf("First node init");
        link->prev = head;
        link->next = last;
        head = link;
        last = link;
    }
    
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
        // printf("\e[1;1H\e[2J");
        system("cls");
        printf("Wipro Hospital Management System\n-------------------------------\nTime: %s", ctime(&t));
        printf("\n1) Patient Registration \n2) Out-Patient \n3) In-Patient \n4) Patient History \n5) Doctor Details \n6) Exit \nEnter your choice: ");
        scanf("%d", &choice);
        system("cls");
        // printf("\e[1;1H\e[2J");
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
                    strncpy(x.patientHistory, "NA", 100);
                    Patients[patientIDCounter] = x;
                    addPatient(Patients[patientIDCounter], ctime(&t));
                    printf("\n--------------------------\nNew Patient Registered\n");
                    printf("ID: %d \nName: %s \nAge: %d \n", Patients[patientIDCounter].patientID, Patients[patientIDCounter].patientName, Patients[patientIDCounter].patientAge);
                    ++patientIDCounter;
                    printf("\n\nPress any key to continue...");
                    getch();
                    break;
                }

            case 4:
                {
                    printf("Patient Details\n--------------------------\n");
                    printOutPatientInfo(head);
                    getch();
                    break;
                }

            default:
                break;
        }
    }
}