#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char name[100];
    char gender;
    char ssn[12];
    Date dob;
} Patient;

typedef struct {
    Patient patient;
    int priority;
    char task[50];
    long current_time;
} QueueElement;

typedef struct {
    QueueElement* elements;
    int size;
    int capacity;
} PriorityQueue;

// Utility functions to be implemented
void initializePriorityQueue(PriorityQueue* pq, int capacity);
void newPatient(PriorityQueue* pq, Patient patient, int priority, char* task, long timestamp);
void processPatient(PriorityQueue* pq);
void updatePatient(PriorityQueue* pq, char* ssn, int newPriority);
void upheap(PriorityQueue* pq, int index);
void downheap(PriorityQueue* pq, int index);
void swapElements(QueueElement* e1, QueueElement* e2);
void printPatients(PriorityQueue* pq);
int comparePriority(int p1, int p2, long t1, long t2);
long getCurrentTimestamp();
void printReadableDate(long timestamp);

int main() {
    PriorityQueue pq;
    initializePriorityQueue(&pq, 10); // Example capacity
    int choice;
    char task[50];
    int priority;
    char name[100];
    char gender;
    char ssn[12];
    Date dob;
    long timestamp;

    do{
        printf("Choose an action:\n");
        printf("1: Register new patient\n");
        printf("2: Process a patient\n");
        printf("3: Update a patient's priority\n");
        printf("4: print list of patient\n");
        printf("5: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter patient's name: ");
                scanf(" %[^\n]%*c", name);  // Read string with spaces
                printf("Enter gender (M/F): ");
                scanf(" %c", &gender);
                printf("Enter SSN (format XXX-XX-XXXX): ");
                scanf("%s", ssn);
                printf("Enter date of birth (dd mm yyyy): ");
                scanf("%d %d %d", &dob.day, &dob.month, &dob.year);
                getchar();
                printf("Enter assigned priority (1-Critical, 2-High, 3-Medium, 4-Low): ");
                scanf("%d", &priority);
                getchar();
                
                printf("please Enter the task that you want it to be performed: \n");

                printf("1:surgery\n");
                printf("2:physical examination\n");
                printf("3:X-ray scan\n");
                printf("4:blood test\n");
                scanf(" %[^\n]%*c", task);
                
                timestamp =  getCurrentTimestamp();  // Generate current timestamp
                
                Patient patientData;  // Corrected variable name
                strcpy(patientData.name, name);
                patientData.gender = gender;
                strcpy(patientData.ssn, ssn);
                patientData.dob = dob;  // Direct assignment of struct
                newPatient(&pq, patientData, priority, task, timestamp);
                
                
                break;

            case 2:
                processPatient(&pq);
                break;

            case 3:
                printf("Enter SSN of patient to update: ");
                scanf("%s", ssn);
                printf("Enter new priority (1-Critical, 2-High, 3-Medium, 4-Low): ");
                scanf("%d", &priority);
                updatePatient(&pq, ssn, priority);
                break;
           case 4:
                printPatients(&pq);
                break;

            case 5:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    
}while(choice != 5);
    return 0;
}

void initializePriorityQueue(PriorityQueue* pq, int capacity) {
    pq->elements = (QueueElement*) malloc(sizeof(QueueElement) * capacity);
    if (pq->elements == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    pq->size = 0;
    pq->capacity = capacity;
}


void newPatient(PriorityQueue* pq, Patient patient, int priority, char* task, long timestamp) {
    if (pq->size == pq->capacity) {
        fprintf(stderr, "Priority Queue is full!\n");
        return;
    }
    QueueElement newElement = {patient, priority, "", timestamp};
    strcpy(newElement.task, task); // Copy the task string into the new element
    pq->elements[pq->size] = newElement; // Add the new element to the array
    upheap(pq, pq->size); // Ensure the heap property is maintained after insertion
    pq->size++; // Increase the size of the priority queue
}



void processPatient(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("No patients in the queue.\n");
        return;
    }
    QueueElement highestPriorityPatient = pq->elements[0];
    printf("Processing patient: %s\n", highestPriorityPatient.patient.name);
    pq->elements[0] = pq->elements[pq->size - 1];
    pq->size--;
    downheap(pq, 0);
}


void updatePatient(PriorityQueue* pq, char* ssn, int newPriority) {
    int index = -1;
    for (int i = 0; i < pq->size; i++) {
        if (strcmp(pq->elements[i].patient.ssn, ssn) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Patient with SSN %s not found.\n", ssn);
        return;
    }
    int oldPriority = pq->elements[index].priority;
    pq->elements[index].priority = newPriority;
    if (newPriority < oldPriority)
        upheap(pq, index);
    else
        downheap(pq, index);
}


void upheap(PriorityQueue* pq, int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (comparePriority(pq->elements[parentIndex].priority, pq->elements[index].priority, pq->elements[parentIndex].current_time, pq->elements[index].current_time) <= 0)
            break;
        swapElements(&pq->elements[parentIndex], &pq->elements[index]);
        index = parentIndex;
    }
}



void downheap(PriorityQueue* pq, int index) {
    int childIndex;
    while ((childIndex = 2 * index + 1) < pq->size) {
        int rightChild = childIndex + 1;
        // Check if right child exists and if it has a higher priority using timestamps as well
        if (rightChild < pq->size && comparePriority(pq->elements[rightChild].priority, pq->elements[childIndex].priority, pq->elements[rightChild].current_time, pq->elements[childIndex].current_time) < 0) {
            childIndex = rightChild;
        }
        // Include timestamps in the comparison for the current node and the child
        if (comparePriority(pq->elements[index].priority, pq->elements[childIndex].priority, pq->elements[index].current_time, pq->elements[childIndex].current_time) <= 0)
            break;
        swapElements(&pq->elements[index], &pq->elements[childIndex]);
        index = childIndex;
    }
}

void swapElements(QueueElement* e1, QueueElement* e2) {
    QueueElement temp = *e1;
    *e1 = *e2;
    *e2 = temp;
}

void printPatients(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("No patients in the queue.\n");
        return;
    }
    printf("Current list of patients in the queue:\n");
    printf("-------------------------------------------------------------\n");
    printf("Name\tGender\tSSN\t\tDOB\t\tPriority\tTask\t\tdate and time\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < pq->size; i++) {
        QueueElement elem = pq->elements[i];
        printf("%s\t%c\t%s\t%02d/%02d/%04d\t%d\t\t%s\t",
               elem.patient.name,
               elem.patient.gender,
               elem.patient.ssn,
               elem.patient.dob.day,
               elem.patient.dob.month,
               elem.patient.dob.year,
               elem.priority,
               elem.task);
               printReadableDate(elem.current_time);
    }
    printf("-------------------------------------------------------------\n");
}

long getCurrentTimestamp() {
    time_t current_time = time(NULL);  // Get the current time as a Unix timestamp
    if (current_time == (time_t)-1) {
        fprintf(stderr, "Failed to obtain the current time.\n");
        return -1;  // Return an error code or handle the error as needed
    }

    // Convert time_t to local time as a tm structure
    struct tm *local_time = localtime(&current_time);
    if (local_time == NULL) {
        fprintf(stderr, "Failed to convert the current time to local time.\n");
        return -1;
    }

    // Print the current time in "Hours:Minutes"
    

    return (long)current_time;  // Return the Unix timestamp
}
void printReadableDate(long current_time) {
    struct tm *tm = localtime((time_t*)&current_time);
    if (tm) {
        printf(" %04d-%02d-%02d %02d:%02d:%02d\n",
               tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
               tm->tm_hour, tm->tm_min, tm->tm_sec);
    } else {
        printf("Failed to convert the timestamp.\n");
    }
}

int comparePriority(int p1, int p2, long t1, long t2) {
    if (p1 < p2) {
        return -1;
    } else if (p1 > p2) {
        return 1;
    } else {
        // If priorities are the same, compare the timestamps
        // The one with the earlier timestamp has a higher priority
        if (t1 < t2) {
            return -1;
        } else if (t1 > t2) {
            return 1;
        } else {
            return 0;
        }
    }
}