# Binary Search Tree Student Management System

**Course:** Data Structures and Algorithmic Problem Solving  
**Assignment:** 2 – Binary Search Tree  

## Project Overview  
This project implements a console-based student record management system in C++ using a binary search tree (BST) to store, search, and traverse student records efficiently. It includes functions to:

- Read records from a file into a BST.  
- Find and display the deepest nodes.  
- Traverse and display the BST in ascending or descending order, printing to screen or file.  
- Clone a subtree rooted at a specified node.  
- Print nodes at each level.  
- Print all external paths (root-to-leaf paths).  
- Provide an interactive menu interface.

## Input Files  
- **`student.txt`**  
  - One student record per line, with fields:  
    ```
    id name address DOB phone_no course cgpa
    ```  
  - Example:  
    ```
    12345 John_Doe 123_Main_St 01/01/2000 012-3456789 CS 3.75
    ```  

## Technical Details  
- **Language & Environment:** C++ (Visual Studio 2022)  
- **Dependencies:** Standard C++ libraries (`<iostream>`, `<fstream>`, `<string>`, `<iomanip>`, etc.)  
- **Error Handling:**  
  - Functions return `false` on errors (e.g., file-not-found, empty tree, item not found) and print clear error messages.  
  - Validates tree operations and handles edge cases (empty tree, no matching node).

## Project Structure  
- **`main.cpp`**  
  - Contains `main()` and `menu()` for user interaction and option handling.  
- **`BST.h` / `BST.cpp`**  
  - `BST` class and `Node` struct definitions.  
  - Implements member functions: `readFile`, `deepestNodes`, `display`, `CloneSubtree`, `printLevelNodes`, `printPath`, and internal traversal helpers.  
- **`Student.h` / `Student.cpp`**  
  - `Student` struct encapsulating a student's data and a `print()` method for formatted output.  
- **`utils.h` / `utils.cpp`** (optional)  
  - Helper functions for parsing, date handling, and file I/O utilities.

## Core Functions  
1. **`bool readFile(const char *filename, BST *t1)`**  
   Reads student records from `filename` and inserts them into `t1`.  
2. **`bool BST::deepestNodes()`**  
   Finds and prints all nodes at the deepest level (prints IDs).  
3. **`bool BST::display(int order, int source)`**  
   Traverses and prints the tree:  
   - `order = 1` (ascending), `order = 2` (descending)  
   - `source = 1` (console), `source = 2` (to `student-info.txt`)  
4. **`bool BST::CloneSubtree(BST t1, type item)`**  
   Clones the subtree rooted at `item` from `t1` into the current tree.  
5. **`bool BST::printLevelNodes()`**  
   Prints node IDs grouped by tree level.  
6. **`bool BST::printPath()`**  
   Prints all external paths from root to leaves (IDs only).  
7. **`int menu()`**  
   Displays an interactive menu to invoke the above functions.

## Usage  
1. **Build:** Open in Visual Studio 2022 and build all projects.  
2. **Run:** Ensure `student.txt` is in the working directory.  
3. **Interact:** Select options 1–7 from the menu to test each feature.