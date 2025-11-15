# Maximum Element — C++ implementation

This folder contains a reference C++ implementation of the "maximum element" algorithm from the provided slide.

File:

-   `max_element.cpp` — C++ implementation with a small demo/test harness.

Compile and run with a C++17-capable compiler (example using g++):

```powershell
g++ -O2 -std=c++17 .\max_element.cpp -o max_element.exe
.\max_element.exe
```

Usage (interactive):

Provide n followed by n integers on stdin. Example:

```powershell
echo "6 3 1 4 1 5 9" | .\max_element.exe
```

The program also runs a small set of demo tests and prints results when run with no stdin input.

Algorithm (as on slide): initialize max := a1, loop i from 2 to n, if max <= a_i then max := a_i.
