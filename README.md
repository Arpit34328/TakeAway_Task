# Data Structures Implementation

This repository contains implementations of two important data structures:
1. Sparse Matrix using linked lists
2. Priority Queue for patient management

## Project Structure

```
.
├── README.md
├── link_list              # Sparse Matrix Implementation
│   ├── Makefile
│   └── source
│       ├── Main
│       │   ├── asking_for_continue.c
│       │   ├── main.c
│       │   └── sparse_matrix.c
│       ├── include
│       │   └── S_Matrix.h
│       └── library
│           └── S_Matrix.c
└── queue                  # Priority Queue Implementation
    ├── Makefile
    └── source
        ├── Main
        │   ├── asking_for_continue.c
        │   ├── main.c
        │   └── patient_management_system.c
        ├── include
        │   └── priority_q.h
        └── library
            └── priority_q.c
```

## Sparse Matrix Implementation

The sparse matrix implementation efficiently stores only non-zero values using a linked list approach. This saves memory when dealing with matrices that contain many zero values.

### Features

- Create a sparse matrix with specified dimensions
- Insert values at specific positions
- Check for the existence of duplicate values
- Resize the matrix by doubling its dimensions
- Transpose the matrix
- Display the matrix in a formatted manner
- Memory-efficient storage of non-zero values

### Usage

To compile and run the sparse matrix implementation:

```bash
cd link_list
make
make run
```

### Interface

The sparse matrix provides a menu-driven interface with the following options:

- **C**: Create a new matrix
- **I**: Insert a value at a specific position
- **D**: Check if a value exists in the matrix
- **R**: Resize the matrix by doubling its dimensions
- **T**: Transpose the matrix
- **Q**: Quit and free allocated memory

## Priority Queue Implementation

The priority queue implementation is designed for a patient management system. Patients are processed based on their priority levels (lower values indicate higher priority).

### Features

- Add new patients with name and priority
- View the patient at the front of the queue
- Upgrade a patient's priority
- Process the patient at the front of the queue
- Clear the queue
- Display the current queue state

### Usage

To compile and run the priority queue implementation:

```bash
cd queue
make
make run
```

### Interface

The patient management system provides a menu-driven interface with the following options:

- **N**: Add a new patient
- **F**: View the patient at the front of the queue
- **U**: Upgrade a patient's priority
- **P**: Process the patient at the front of the queue
- **B**: Bulk processing (not implemented in the current version)
- **C**: Clear the queue
- **Q**: Quit and free allocated memory

## Technical Details

### Sparse Matrix

The sparse matrix uses a doubly linked list structure to store non-zero elements efficiently. Each matrix node contains:
- Row and column indices
- The value at that position
- Pointers to the next nodes in the same row and column

### Priority Queue

The priority queue is implemented as a singly linked list sorted by priority. Each queue node contains:
- Patient name
- Priority value
- Pointer to the next node

Lower priority values represent higher priority patients who will be processed first.

## Building and Cleaning

Both implementations include a Makefile with the following targets:

- `make`: Build the project
- `make run`: Build and run the project
- `make clean`: Remove all compiled files
- `make rebuild`: Clean and rebuild the project

## Authors

- Arpit Patel
- Dharma KaPatel

## Date

March 2025
