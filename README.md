# Hospital Queue Management System

A console-based **Hospital Queue Management System** written in C. The program manages patients using a **priority queue implemented with a heap**, allowing hospital staff to register patients, process the highest-priority patient, update patient priorities, and display the current queue.

## Overview

This project was built as a data structures project to demonstrate how a priority queue can be used in a hospital environment. Each patient is assigned a priority level based on urgency. Patients with higher urgency are processed first, and when two patients have the same priority, the system uses their arrival time to decide who should be processed first.

## Features

- Register a new patient with personal information.
- Assign a priority level to each patient.
- Process the patient with the highest priority.
- Update a patient's priority using their SSN.
- Display the current list of patients in the queue.
- Use timestamps to handle patients with the same priority using FIFO logic.
- Implement heap operations using `upheap` and `downheap`.

## Priority Levels

| Priority | Meaning |
|---|---|
| 1 | Critical |
| 2 | High |
| 3 | Medium |
| 4 | Low |

A lower number means a higher priority. For example, a patient with priority `1` will be processed before a patient with priority `3`.

## Tasks Supported

The system allows the user to choose a task or medical service such as:

- Surgery
- Physical examination
- X-ray scan
- Blood test

## Data Structures Used

The project mainly uses the following structures:

- `Date`: stores the patient's date of birth.
- `Patient`: stores patient information such as name, gender, SSN, and date of birth.
- `QueueElement`: stores the patient, priority, task, and arrival timestamp.
- `PriorityQueue`: stores the heap array, current size, and capacity.

The priority queue is implemented using an array-based heap. The `upheap` function is used after inserting a new patient, while the `downheap` function is used after processing or updating a patient.

## How the Priority Queue Works

The system compares patients using two rules:

1. The patient with the smaller priority number is processed first.
2. If two patients have the same priority, the patient who arrived earlier is processed first.

This allows the system to combine priority-based processing with FIFO behavior when priorities are equal.

## File Structure

```text
hospital-queue-management-c/
│
├── hospital_queue_management.c
├── README.md
└── .gitignore
```

## Requirements

To compile and run this project, you need:

- A C compiler, such as GCC.
- A terminal or command prompt.

No external libraries are required. The program only uses standard C libraries:

- `stdio.h`
- `stdlib.h`
- `string.h`
- `time.h`

## Compilation

If the source file is named `hospital_queue_management.c`, compile it using:

```bash
gcc hospital_queue_management.c -o hospital_queue_management
```

If your file still has spaces in its name, compile it using:

```bash
gcc "hospital queue management.c" -o hospital_queue_management
```

## Running the Program

After compilation, run the program using:

```bash
./hospital_queue_management
```

On Windows, use:

```bash
hospital_queue_management.exe
```

## Menu Options

When the program starts, the user can choose from the following options:

```text
1: Register new patient
2: Process a patient
3: Update a patient's priority
4: Print list of patients
5: Exit
```

## Example Usage

```text
Choose an action:
1: Register new patient
2: Process a patient
3: Update a patient's priority
4: print list of patient
5: Exit
Enter your choice: 1
```

The user then enters the patient's name, gender, SSN, date of birth, priority, and required task.

## Main Functions

| Function | Description |
|---|---|
| `initializePriorityQueue` | Initializes the priority queue with a fixed capacity. |
| `newPatient` | Adds a new patient to the queue. |
| `processPatient` | Processes and removes the highest-priority patient. |
| `updatePatient` | Updates the priority of an existing patient using their SSN. |
| `upheap` | Restores heap order after insertion or priority increase. |
| `downheap` | Restores heap order after removal or priority decrease. |
| `swapElements` | Swaps two queue elements. |
| `printPatients` | Prints the current patient queue. |
| `comparePriority` | Compares two patients based on priority and arrival time. |
| `getCurrentTimestamp` | Gets the current arrival time. |
| `printReadableDate` | Displays a timestamp in readable format. |

## Limitations

- The queue capacity is fixed in the code.
- Patient data is not saved after the program exits.
- Input validation can be improved.
- The program does not free allocated memory before exiting.
- The system is for educational purposes only and is not intended for real hospital use.

## Future Improvements

- Add file storage to save and load patient records.
- Improve input validation for SSN, gender, date of birth, and priority.
- Allow dynamic resizing of the priority queue.
- Add a search feature for patients.
- Improve the printed table formatting.
- Add better memory management before program exit.

## License

This project is licensed under the MIT License.
