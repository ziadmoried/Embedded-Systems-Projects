# 1 · Student Management System

A console application written in C that manages student records using a **singly linked list**. It exercises conditions, loops, strings, structs, pointers and dynamic memory allocation.

## Features

| Menu option | Behavior |
|-------------|----------|
| Add a student | Rejects duplicate IDs; allocates a node and appends it to the list |
| Display students | Traverses the list and prints every record |
| Search by ID | Prints the matching student or a "not found" message |
| Update student | Edits name, age or GPA of an existing student |
| Delete a student | Unlinks and frees the node with the given ID |
| Average GPA | Sums GPAs over the list and prints the mean |
| Highest GPA | Finds and prints the top student |
| Exit | Frees the entire list and quits |

## Data model

```c
struct student { int id; char name[50]; int age; float gpa; };
struct node    { struct student data; struct node *next; };
```

## Build and run

```bash
gcc src/student_management.c -o student_management
./student_management
```

## Files

| Path | Description |
|------|-------------|
| [`docs/EDGES_C_Project_Standard_Final.pdf`](docs/EDGES_C_Project_Standard_Final.pdf) | Project specification |
| [`src/student_management.c`](src/student_management.c) | Source code |

## Demo

https://youtu.be/SlGfWfT15eI
