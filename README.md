# C++ From Scratch
 
Implementations of STL components, smart pointers, and coding problems — built in modern C++ to understand how things work under the hood.
 
Each folder contains its own README with design notes, complexity analysis, and things I learned along the way.
 
---
 
## STL & Core Components
 
| Implementation |
|---|
| |
 
## Problems
 
### Operating Systems
 
| Problem |
|---|
| [Base and Bounds](./Problems/Operating_Systems/Base_and_Bounds) |
 
---
 
## Building
 
All implementations use C++17 (or later) and are built with CMake:
 
```bash
mkdir build && cd build
cmake ..
make
```
 
## Structure
 
```
cpp-from-scratch/
├── stl/         # STL container & smart pointer implementations
├── problems/    # Coding problems
└── CMakeLists.txt
```
 
## Goals
 
- Understand the internals of the standard library, not just its API
- Practice manual memory management, RAII, and move semantics
- Write tested, readable modern C++
## Notes
 
These are educational implementations. They prioritize clarity over completeness and are not drop-in replacements for the standard library.
 
