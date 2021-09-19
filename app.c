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
#include<string.h>
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
} Visitors[10];

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

struct outPatientPriorityList *head = NULL;
struct outPatientPriorityList *last = NULL;
struct outPatientPriorityList *current = NULL;

// In-Patient Linked List
struct inPatientPriorityList
{
    /* data */
    int patientID;
    int roomID;
    int doctorID;
    char timeOfEntry[50];
    struct inPatientPriorityList* next;
};

struct inPatientPriorityList *first = NULL;

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

// Display details of the patient in the Out-Patient queue
void printPatientInfo(struct outPatientPriorityList *n)
{
    if(n == NULL)
    {
        printf("No patient details found. Press any key to continue...");
        getch();
    }
    else
    {
        printf("\nPatient ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor: %s\nPatient History: %s\nTime of Visit: %s", n->patientID, Patients[n->patientID].patientName, Patients[n->patientID].patientAge, Doctors[n->doctorID].doctorName, Patients[n->patientID].patientHistory, n->timeOfVisit);
    }
}

// Display details of admitted patients
void printAdmittedPatientInfo(struct inPatientPriorityList *n)
{
    if(n == NULL)
    {
        printf("No patient details found. Press any key to continue...");
        getch();
    }
    int counter = 1;
    while(n!= NULL) 
    {
        printf("#%d\nRoom: %d\nPatient ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor: %s\nPatient History: %s\nTime of Visit: %s", counter, n->roomID, n->patientID, Patients[n->patientID].patientName, Patients[n->patientID].patientAge, Doctors[n->doctorID].doctorName, Patients[n->patientID].patientHistory, n->timeOfEntry);
        printf("-------------------------------\n");
        n = n->next;
        ++counter;
    }
}

void printAdmittedShortInfo()
{
    struct inPatientPriorityList *n = first;
    if(n == NULL)
    {
        printf("No admitted patient details found. Press any key to continue...");
        getch();
    }
    else
    {
        printf("\nPatients:");
        while(n != NULL)
        {
            printf("\n%d: %s (Room: %d, Doctor: %s)\n", n->patientID, Patients[n->patientID].patientName, n->roomID, Doctors[n->doctorID].doctorName);
            printf("-------------------------------");
            n = n->next;
        }
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
    // printf("Current Queue Length: %d\n", queueLength + 1);
    // Adding node
    if(queueLength != 0) 
    {
        int counter = 0;
        // If there are more than 1 nodes
        if(queueLength > 1)
        {
            // Iterating through the list
            while(ptr!=NULL)
            {
                // If current node's age is less than that of the given age
                if(Patients[ptr->patientID].patientAge < x.patientAge)
                {
                    temp = ptr->prev;
                    // Inserting at the beginning
                    if(ptr->prev == NULL)
                    {
                        link->next = head;
                        head = link;
                        link->prev = NULL;
                        ptr->prev = link;
                    }
                    else
                    // Inserting in between
                    {
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
        // Inserting the second node
        else
        {
            if(Patients[ptr->patientID].patientAge < x.patientAge)
            {
                last = head;
                ptr->prev = link;
                link->prev = NULL;
                link->next = head;
                head = link;

            }
            else
            {
                ptr->next = link;
                link->prev = head;
                link->next = NULL;
                last = link;
            }
        }
    }
    // First node init
    else
    {
        link->prev = head;
        link->next = last;
        head = link;
        last = link;
    }
}

void popOutPatient(struct outPatientPriorityList *n)
{
    int len = length();
    if(len == 1)
    {
        n->prev = NULL;
        n->next = NULL;
        head = NULL;
    }
    else
    {
        struct outPatientPriorityList *temp = n->next;
        temp->prev = NULL;
        head = head->next;
    }
    
    // printf("%d %s preserved", temp->patientID, Patients[temp->patientID].patientName);
}

void admitPatient(struct outPatientPriorityList *n)
{
    time_t t;
    time(&t);
    struct inPatientPriorityList *link = (struct inPatientPriorityList*) malloc(sizeof(struct inPatientPriorityList));
    struct inPatientPriorityList *last = first;
    link->patientID = n->patientID;
    link->doctorID = n->doctorID;
    strncpy(link->timeOfEntry, ctime(&t), 50);
    link->next = NULL;
    if(first == NULL)
    {
        first = link;
        link->roomID = 0;
    }
    else
    {
        int roomCounter = 1;
        while(last->next != NULL)
        {
            ++roomCounter;
            last = last->next;
        }
        link->roomID = roomCounter;
        last->next = link;
    }
    
    printf("\n%d: %s has been admitted to room %d under the supervision of %s.", link->patientID, Patients[link->patientID].patientName, link->roomID, Doctors[link->doctorID].doctorName);
}

int main() 
{    
    // Initializing patient ID counter
    int patientIDCounter = 0;

    int visitorCounter = 0;

    // User choice variable
    int choice = 0;

    // Initializing time's object
    time_t t;
    time(&t);

    // Initializing doctors
    initDoctors();

    // Starting menu loop
    while(choice != 8) 
    {
        // Clearing console
        printf("\e[1;1H\e[2J");
        // system("cls");
        printf("Wipro Hospital Management System\n-------------------------------\nTime: %s", ctime(&t));
        printf("\n1) Patient Registration \n2) Out-Patient \n3) In-Patient \n4) Patient History \n5) Visitor Check-In \n6) Day Report \n7) Doctor's Report \n8) Exit \nEnter your choice: ");
        scanf("%d", &choice);
        // system("cls");
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
                    strncpy(x.patientHistory, "NA", 100);
                    Patients[patientIDCounter] = x;
                    time(&t);
                    addPatient(Patients[patientIDCounter], ctime(&t));
                    printf("\n--------------------------\nNew Patient Registered\n");
                    printf("ID: %d \nName: %s \nAge: %d \n", Patients[patientIDCounter].patientID, Patients[patientIDCounter].patientName, Patients[patientIDCounter].patientAge);
                    ++patientIDCounter;
                    printf("\n\nPress any key to continue...");
                    getch();
                    break;
                }

            case 2: 
                {
                    printf("Out-Patient\n--------------------------\nPatient Details: \n");
                    printPatientInfo(head);
                    if(head != NULL)
                    {
                        if(Doctors[head->doctorID].doctorID == 0)
                        {
                            printf("\nAssign a Doctor:\n");
                            for(int i=1; i<4; i++)
                            {
                                printf("%d: %s\n", Doctors[i].doctorID, Doctors[i].doctorName);
                            }
                            int id;
                            printf("Enter Doctor ID: ");
                            scanf("%d", &id);
                            if(id<4 && id>=0)
                            {
                                head->doctorID = id;
                            }
                            else
                            {
                                printf("Invalid Response. Press any key to return to the main menu...");
                                getch();
                            }
                        }
                        else
                        {
                            int choice;
                            printf("\n1. Admit Patient\n2. Release\n3. Exit\nEnter your choice: ");
                            scanf("%d", &choice);
                            switch(choice)
                            {
                                case 1: 
                                    {
                                        admitPatient(head);
                                        popOutPatient(head);
                                        getch();
                                        break;
                                    }

                                case 2: 
                                    {
                                        printf("%d: %s released. Press any key to continue...", head->patientID, Patients[head->patientID].patientName);
                                        popOutPatient(head);
                                        getch();
                                        break;
                                    }

                                case 3:
                                    {
                                        break;
                                    }

                                default:
                                    {
                                        printf("Invalid Response. Press any key to continue...");
                                        getch();
                                    }
                            }
                        }
                    }
                    break;
                }
            case 3:
                {
                    int choice;
                    printf("In-Patient\n--------------------------\n");
                    if(first != NULL)
                    {
                        printf("1) Admitted Patient Details\n2) Update Patient History\n3) Reassign Room\n4) Reassign Doctor\n5) Discharge Patient\n6) Exit\nEnter your choice: ");
                        scanf("%d", &choice);
                        printf("\n--------------------------\n");
                        switch (choice)
                        {
                            case 1:
                                {
                                    printAdmittedPatientInfo(first);
                                    printf("\nPress any key to continue...");
                                    getch();
                                    break;
                                }

                            case 2:
                                {
                                    int id;
                                    printAdmittedShortInfo();
                                    printf("\nEnter Patient ID: ");
                                    scanf("%d", &id);
                                    struct inPatientPriorityList *n = first;
                                    printf("\nDetails:");
                                    while(n != NULL)
                                    {
                                        if(id == n->patientID)
                                        {
                                            printf("\nPatient ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor: %s\nPatient History: %s\nTime of Visit: %s", n->patientID, Patients[n->patientID].patientName, Patients[n->patientID].patientAge, Doctors[n->doctorID].doctorName, Patients[n->patientID].patientHistory, n->timeOfEntry);
                                            printf("-------------------------------");
                                            break;
                                        }
                                        n = n->next;
                                    }
                                    char story[100];
                                    getchar();
                                    printf("\nEnter Updated Patient History: ");
                                    // Using fgets instead of gets due to security reasons
                                    fgets(story, sizeof(story), stdin);
                                    // Removing trailing new line from input
                                    story[strcspn(story, "\n")] = 0;
                                    strncpy(Patients[n->patientID].patientHistory, story, 100);          
                                    printf("\nPatient History updated. Press any key to continue...");
                                    getch();
                                    break;
                                }
                            
                            case 3:
                                {
                                    int id;
                                    printAdmittedShortInfo();
                                    printf("\nEnter Patient ID: ");
                                    scanf("%d", &id);
                                    struct inPatientPriorityList *n = first;
                                    printf("\nDetails:");
                                    while(n != NULL)
                                    {
                                        if(id == n->patientID)
                                        {
                                            printf("\nPatient ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor: %s\nPatient History: %s\nTime of Visit: %s", n->patientID, Patients[n->patientID].patientName, Patients[n->patientID].patientAge, Doctors[n->doctorID].doctorName, Patients[n->patientID].patientHistory, n->timeOfEntry);
                                            printf("-------------------------------");
                                            break;
                                        }
                                        n = n->next;
                                    }
                                    int roomID;
                                    printf("\nEnter New Room ID: ");
                                    scanf("%d", &roomID);
                                    n->roomID = roomID;
                                    printf("\nPatient Room Updated. Press any key to continue...");
                                    getch();
                                    break;
                                }

                            case 4:
                                {
                                    int id;
                                    printAdmittedShortInfo();
                                    printf("\nEnter Patient ID: ");
                                    scanf("%d", &id);
                                    struct inPatientPriorityList *n = first;
                                    printf("\nPatient Details:");
                                    while(n != NULL)
                                    {
                                        if(id == n->patientID)
                                        {
                                            printf("\nPatient ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor: %s\nPatient History: %s\nTime of Visit: %s", n->patientID, Patients[n->patientID].patientName, Patients[n->patientID].patientAge, Doctors[n->doctorID].doctorName, Patients[n->patientID].patientHistory, n->timeOfEntry);
                                            printf("-------------------------------\n");
                                            break;
                                        }
                                        n = n->next;
                                    }
                                    for(int i=1; i<4; i++)
                                    {
                                        printf("%d: %s\n", Doctors[i].doctorID, Doctors[i].doctorName);
                                    }
                                    int doctorID;
                                    printf("Enter Doctor ID: ");
                                    scanf("%d", &doctorID);
                                    if(doctorID<4 && doctorID>=0)
                                    {
                                        n->doctorID = doctorID;
                                    }
                                    else
                                    {
                                        printf("Invalid Response. Press any key to return to the main menu...");
                                        getch();
                                    }
                                    break;
                                }

                            case 5:
                                {
                                    int id;
                                    printAdmittedShortInfo();
                                    printf("\nEnter Patient ID: ");
                                    scanf("%d", &id);
                                    struct inPatientPriorityList *n = first;
                                    printf("\nDetails:");
                                    while(n != NULL)
                                    {
                                        if(id == n->patientID)
                                        {
                                            printf("\nPatient ID: %d\nPatient Name: %s\nPatient Age: %d\nDoctor: %s\nPatient History: %s\nTime of Visit: %s", n->patientID, Patients[n->patientID].patientName, Patients[n->patientID].patientAge, Doctors[n->doctorID].doctorName, Patients[n->patientID].patientHistory, n->timeOfEntry);
                                            printf("-------------------------------");
                                            break;
                                        }
                                        n = n->next;
                                    }
                                    printf("\nDischarge Patient? \n1) Yes\n2) No\nEnter your choice: ");
                                    int dischargeChoice;
                                    scanf("%d", &dischargeChoice);
                                    if(dischargeChoice == 1)
                                    {
                                        struct inPatientPriorityList *t = first;
                                        struct inPatientPriorityList *temporary;
                                        while(t != NULL)
                                        {
                                            if(t->next == NULL)
                                            {
                                                first = NULL;
                                                break;
                                            }
                                            temporary = t->next;
                                            if(temporary->patientID == id)
                                            {
                                                t->next = n->next;
                                                break;
                                            }
                                            t = t->next;
                                        }
                                        printf("\nPatient Discharged. Press any key to continue...");
                                        getch();
                                    }
                                    break;
                                }

                            default:
                                break;
                        }
                    }
                    else
                    {
                        printf("\nNo admitted patient details found. Press any key to continue...");
                        getch();
                    }
                    break;
                }

            case 4:
                {
                    printf("\e[1;1H\e[2J");
                    printf("Patient Details\n--------------------------\n1) Out-Patient\n2) In-Patient\nEnter your choice: ");
                    int infoChoice;
                    scanf("%d", &infoChoice);
                    switch (infoChoice)
                    {
                        case 1:
                            {
                                printOutPatientInfo(head);
                                break;
                            }
                        
                        case 2:
                            {
                                printAdmittedPatientInfo(first);
                                break;
                            }

                        default:
                            {
                                printf("Invalid Response. Press any key to continue...");
                                break;
                            }
                    }
                    getch();
                    break;
                }

            case 5:
                {
                    int visitorChoice;
                    printf("Visitor Check-In\n--------------------------\n");
                    if(first != NULL)
                    {
                        printf("1) Add Visitor \n2) Check Current Patient Visitor Count \n3) Exit \nEnter your choice: ");
                        scanf("%d", &visitorChoice);
                        switch (visitorChoice)
                        {
                        case 1:
                            {
                                if(visitorCounter < 10)
                                {
                                    printAdmittedShortInfo();
                                    Visitors[visitorCounter].visitorID = visitorCounter;
                                    printf("\nEnter Patient ID: ");
                                    int tempID;
                                    char nameVisitor[50];
                                    scanf("%d", &tempID);
                                    Visitors[visitorCounter].visitingPatientID = tempID;
                                    printf("Enter Visitor Name: ");
                                    getchar();
                                    // Using fgets instead of gets due to security reasons
                                    fgets(nameVisitor, sizeof(nameVisitor), stdin);
                                    // Removing trailing new line from input
                                    nameVisitor[strcspn(nameVisitor, "\n")] = 0;
                                    strncpy(Visitors[visitorCounter].visitorName, nameVisitor, 50);
                                    ++visitorCounter;
                                }
                                else
                                {
                                    printf("Visitor Capacity Reached. Please try again later! Press any key to continue...");
                                    getch();
                                }
                                break;
                            }
                        
                        case 2:
                            {
                                int flag, visitorCheckID, count = 0;
                                printAdmittedShortInfo();
                                printf("\nEnter Patient ID: ");
                                scanf("%d", &visitorCheckID);
                                for(int i=0; i<10; i++)
                                {
                                    if(visitorCheckID == Visitors[i].visitingPatientID)
                                    {
                                        ++count;
                                        flag = 1;
                                    }
                                }
                                if(!flag)
                                {
                                    printf("No matches. Press any key to continue...");
                                    getch();
                                }
                                else
                                {
                                    printf("\nThere are %d visitors for patient %s.\nPress any key to continue...", count, Patients[visitorCheckID].patientName);
                                    getch();
                                }
                                break;
                            }
                        
                        default:
                            break;
                        }
                    }
                    else
                    {
                        printf("\nNo admitted patient details found. Press any key to continue...");
                        getch();
                    }
                    break;
                }

            case 6:
                {
                    int reportChoice;
                    printf("Day Report\n--------------------------\n1) Out-Patient \n2) In-Patient \n3) Exit \nEnter your choice: ");
                    scanf("%d", &reportChoice);
                    switch (reportChoice)
                    {
                    case 1:
                        {
                            if(head != NULL)
                            {
                                int counter = 0;
                                for(struct outPatientPriorityList *i = head; i != NULL; i = i->next) 
                                {
                                    printf("\n%s------------------------------\n%d: %s - %s\n", i->timeOfVisit, Patients[i->patientID].patientID, Patients[i->patientID].patientName, Doctors[i->doctorID].doctorName);
                                }
                            }
                            else
                            {
                                printf("\nNo patient data found. Press any key to continue...");
                            }
                            getch();
                            break;    
                        }

                    case 2:
                        {
                            if(head != NULL)
                            {
                                int counter = 0;
                                for(struct inPatientPriorityList *i = first; i != NULL; i = i->next) 
                                {
                                    printf("\n%s------------------------------\n%d: %s - %s, Room: %d\n", i->timeOfEntry, Patients[i->patientID].patientID, Patients[i->patientID].patientName, Doctors[i->doctorID].doctorName, i->roomID);
                                }
                            }
                            else
                            {
                                printf("\nNo patient data found. Press any key to continue...");
                            }
                            getch();
                            break;    
                        }
                    
                    
                    default:
                        break;
                    }
                    break;
                }

            case 7:
                {
                    int doctorChoice;
                    printf("Doctor Report\n--------------------------\nDoctors:\n");
                    for(int i=1; i<4; i++)
                    {
                        printf("%d: %s\n", Doctors[i].doctorID, Doctors[i].doctorName);
                    }
                    printf("Enter Doctor ID: ");
                    scanf("%d", &doctorChoice);
                    if(doctorChoice<4 && doctorChoice>=0)
                    {
                        struct outPatientPriorityList *x = head;
                        struct inPatientPriorityList *t = first;
                        int iflag = 0, oflag = 0;
                        printf("\nOut-Patients:\n");
                        while(x != NULL)
                        {
                            if(x->doctorID == doctorChoice)
                            {
                                printf("\n%d: %s", x->patientID, Patients[x->patientID].patientName);
                                oflag = 1;
                            }
                            x = x->next;
                        }
                        if(oflag == 0)
                        {
                            printf("\n%s does not have any Out-Patients right now.", Doctors[doctorChoice].doctorName);
                        }
                        printf("\n-------------\n\nIn-Patients:\n");
                        while(t != NULL)
                        {
                            if(t->doctorID == doctorChoice)
                            {
                                printf("\n%d: %s (Room: %d)", t->patientID, Patients[t->patientID].patientName, t->roomID);
                                iflag = 1;
                            }
                            t = t->next;
                        }
                        if(iflag == 0)
                        {
                            printf("\n%s does not have any In-Patients right now.", Doctors[doctorChoice].doctorName);
                        }

                    }
                    else
                    {
                        printf("\nInvalid Response. Press any key to return to the main menu...");
                    }
                    getch();
                    break;
                }
            default:
                break;
        }
    }
}