# Abstract Data Types in C

> Some basic ADT implementations in C that were created during the 2nd semester in the course<br> [Data Structures K08](https://www.di.uoa.gr/sites/default/files/undergraduate_courses_files/DIT_PPS_K08-DataStructures.pdf), DIT-UoA 2022,
Giorgos Sofronas (sdi2100180).<br>

## Project structure
   **All modules are implemented using as data-field the** [void pointer](https://www.geeksforgeeks.org/void-pointer-c-cpp/) **(void***),<br> 
   **thus making them generic, meaning that they are applicable to any data type**, i.e. int, char*, or even whole structs. <br>
    
   The user has to provide in each module's initialization appropriate functions that are used for:<br>
        - data comparison (CompareFunc)<br>
        - data destruction (DestroyFunc)<br>
        - data console-print (PrintFunc) (more details in the modules' .h files)<br>
      
   If a user doesn't want to assign a specific function type, for example a PrintFunc,<br> 
   NULL should be assigned in the corresponding function place. 

- `modules`

  **Contains the implementation (source code) of all provided ADTs of the project.** The following ADTs are included:
  - Binary Search Tree 
  - Circular List
  - Deque
  - Priority Queue
  - Queue
  - Red-Black Tree
  - Stack 
  <br>
  More details for each module and their implementation can be found in their individual folder.

- `lib`

  Contains the `libADT.a` library, which includes all mentioned modules and the `ADT.h` library-header file which should be included in user's program
  in order to compile and run using the library. Run `make lib` in this folder to compile the `libADT.a` library from scratch.
  
- `example`

   Contains an example of how to use the `libADT.a` library and how to complile it with a `main.c` source file.<br>
   Run `make run` in this folder to test the example program.

## Compilation and use
  The `example` folder contains a simple example of how the library is compiled with a C source file.<br>
  The specific compilation command for the executable file (which is included in the example folder's Makefile) is:<br>
  ```bash 
  gcc -o <executable-file-name> <C-source-file>.o -L. ../lib/libADT.a
  ```
  *next to -L. is the path to the `libADT.a` library, in this case in the `lib` folder.*
