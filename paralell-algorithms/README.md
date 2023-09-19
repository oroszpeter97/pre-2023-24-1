# Parallel Algorithms
Public repository for the Parallel Algorithms class 22/23/2. Documentation for each program can be found under &emsp; `/html/index.html`.

---

**Owner:** Orosz Péter  
**Neptun:** WO02D7

&nbsp;

# Semester Assignment &emsp; (*Accepted...*)

## Summary:
Write a C program using OpenMP, that will take as an argument a range, array size and number of threads to be used for each operation. Every operation should split the tasks into the given number of threads.  
 - Fill the array with random numbers from the given range.  
 - Sum the array.  
 - Prod the array. The elements of the array will be mapped to the range `[1.0, 1.1]`. While multipling the elements, if the current prod is over `1` the next element will be raised to the power or `-1` so we won't get a huge number.
 - Find min and max at the same time.  
 - Sort the array.  
 - Remove duplicates after sorting.  
 - Display how long each operation took with the given number of threads.  
 - Write into a file where at the beginning it displays the size of the array, its sum, its prod, its min, its max and time it took to calculate them, then show the sorted array itself in a readable way.  
 - The program shouldn't use any unnecesary global variables and should handle edge cases. Use a custom dynamic array. Using doxygen generate a documentation from the comments of the code.

## To compile the program you can use the Makefile:
 - The `make` commands must be ran under the `semester-assigment` folder.
 - `make` : Will compile the program.
 - `make run ARGS=""` : Will compile then run the program with given arguments.

## Valid arguments:
 - `-help` : Will display a small description of the program. Can be accessed easier using `make help`.
 - `array_size` &emsp; `element_lower_limit` &emsp; `element_upper_limit` &emsp; `number_of_threads`

## Example compiles and runs:
### Compiles the program.
```makefile
make
```

### Will compile, then run the program with the following arguments.
```makefile
make run ARGS="5000 0 75 4"
```

### Displays the programs summary.
```makefile
make help
```

### Recompiles and opens the documentation.
```makefile
make documentation
```

### Will compile, then run the program with the `-help` argument. Using `make help` is recommended.
```makefile
make run ARGS="-help"
```

### Cleans up the working directory of compiled files
```makefile
make clean
```