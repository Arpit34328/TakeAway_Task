# Sparse Matrix Implementation

This repository contains an implementation of a sparse matrix data structure using linked lists. The implementation is designed to efficiently store and manipulate matrices with a large number of zero values.

## Introduction to Sparse Matrices

A sparse matrix is a matrix in which most of the elements are zero. Using a standard two-dimensional array to represent such matrices would waste a lot of memory storing these zeros. Instead, we can use more efficient representations that only store the non-zero elements.

In this implementation, we use a linked list structure where each node contains information about a non-zero element (its row, column, and value) along with pointers to traverse the matrix both row-wise and column-wise.

## Data Structure

The data structure consists of two main components:

### Node Structure

```c
typedef struct node { 
    int row, column;
    double value; 
    struct node* rowPtr; 
    struct node* colPtr; 
} node;
```

Each node contains:
- `row` and `column`: The position of the element in the matrix
- `value`: The value of the element (non-zero)
- `rowPtr`: Pointer to the next node in the same row
- `colPtr`: Pointer to the next node in the same column

### Matrix Structure

```c
typedef struct matrix { 
    node** rowList;    // rowList is a pointer to the array of rows 
    node** columnList; // column list is a pointer to the array of columns
    int rows, columns; // store the number of rows and columns of the matrix 
} matrix;
```

The matrix structure contains:
- `rowList`: An array of pointers, where each pointer points to the first non-zero element in a row
- `columnList`: An array of pointers, where each pointer points to the first non-zero element in a column
- `rows` and `columns`: The dimensions of the matrix

## Implemented Functions

The following functions have been implemented to manipulate the sparse matrix:

### 1. Matrix Initialization

Allocates memory for a new matrix of size n × m.

```c
matrix* initMatrix(int n, int m);
```

### 2. Node Insertion

Inserts a node at the beginning of its respective row and column lists.

```c
void insertNode(matrix* M, node* ptr);
```

### 3. Value Existence Check

Checks if a specific value exists in the matrix.

```c
int duplicateValue(matrix* M, double value);
```

### 4. Matrix Resizing

Doubles the number of rows and columns in the matrix.

```c
int resize(matrix** M);
```

### 5. Matrix Transposition

Creates the transpose of the matrix where rows become columns and columns become rows.

```c
int transpose(matrix** M);
```

## Implementation Details

### Matrix Initialization
The initialization function allocates memory for the matrix structure and its row and column lists. Each list initially points to NULL.

### Node Insertion
When inserting a node, we link it into both the row list and the column list:
- Add it to the beginning of the list for its row
- Add it to the beginning of the list for its column

### Value Existence Check
To check if a value exists, we traverse all nodes in the matrix and compare their values with the target value.

### Matrix Resizing
Resizing involves:
1. Creating a new matrix with twice the dimensions
2. Copying all nodes from the old matrix to the new one
3. Freeing the old matrix

### Matrix Transposition
For transposition:
1. Create a new matrix with swapped dimensions
2. For each node in the original matrix, create a new node with swapped row and column indices
3. Insert the new node into the transposed matrix
4. Free the original matrix

## Usage Example

```c
// Initialize a 3x3 matrix
matrix* M = initMatrix(3, 3);

// Create and insert nodes
node* n1 = createNode(0, 1, 5.0);
node* n2 = createNode(1, 2, 3.5);
node* n3 = createNode(2, 0, 2.0);

insertNode(M, n1);
insertNode(M, n2);
insertNode(M, n3);

// Check if value exists
if (duplicateValue(M, 3.5)) {
    printf("Value 3.5 exists in the matrix\n");
}

// Resize the matrix
if (resize(&M) == 0) {
    printf("Matrix resized successfully\n");
}

// Transpose the matrix
if (transpose(&M) == 0) {
    printf("Matrix transposed successfully\n");
}
```

## Testing

Unit tests have been implemented to verify the correctness of each function:
- Test matrix initialization
- Test node insertion
- Test duplicate value checking
- Test matrix resizing
- Test matrix transposition

## Coding Standards

The implementation follows these coding standards:
- Consistent indentation and formatting
- Descriptive variable and function names
- Proper error handling with meaningful return values
- Memory management with appropriate allocation and deallocation
- Documentation for functions and complex logic

## References

For more information about sparse matrices, you can refer to:
- [GeeksforGeeks - Sparse Matrix Representation](https://www.geeksforgeeks.org/sparse-matrix-representation/)
- [Wikipedia - Sparse Matrix](https://en.wikipedia.org/wiki/Sparse_matrix)

## Contributing

Contributions to improve the implementation are welcome. Please feel free to submit a pull request or open an issue.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
