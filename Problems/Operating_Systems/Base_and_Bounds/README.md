# Base and Bounds
 
**Topic:** Operating Systems (Virtualization)
 
## Background
 
In a base-and-bounds memory system, the OS assigns each process a contiguous region of physical memory described by two values:
 
- **Base** — the starting physical address of the process's region
- **Bounds** — the size of the region in bytes
A process with base `B` and bounds `N` occupies the half-open interval `[B, B + N)` in physical memory. The OS must ensure that no two live processes share any physical address; if their regions overlap, one process can corrupt the other's memory.
 
## Overlap Condition
 
Two regions `[baseA, baseA + boundsA)` and `[baseB, baseB + boundsB)` overlap if and only if:
 
```cpp
baseA < baseB + boundsB  &&  baseB < baseA + boundsA
```
 
- **Adjacent regions do not overlap.** If `baseA + boundsA == baseB`, the regions share a boundary point but no actual byte — this is valid placement and must not be reported as an overlap.
- **Zero-bounds processes occupy no memory.** A process with `bounds == 0` cannot overlap with any other region, regardless of its base address.
## Task
 
Implement `mem::RegionChecker`:
 
Register a process. `base` and `bounds` are in bytes. You may assume no duplicate PIDs are added.
 
```cpp
void add_process(uint32_t pid, uint64_t base, uint64_t bounds);
```
 
Return all overlapping pairs. Each pair `(pid_i, pid_j)` must satisfy `pid_i < pid_j`. Pairs may be returned in any order. If no overlaps exist, return an empty vector.
 
```cpp
std::vector<std::pair<int, int>> find_overlaps() const;
```
 
## Example
 
| PID | Base | Bounds | Region     |
|-----|------|--------|------------|
| 0   | 0    | 300    | `[0, 300)` |
| 1   | 200  | 300    | `[200, 500)` |
| 2   | 400  | 300    | `[400, 700)` |
| 3   | 700  | 100    | `[700, 800)` |
 
- PID 0 and PID 1 overlap at `[200, 300)` → report `(0, 1)`
- PID 1 and PID 2 overlap at `[400, 500)` → report `(1, 2)`
- PID 2 and PID 3 are adjacent at `700` → not reported
Result: `{(0, 1), (1, 2)}`
 
## Constraints
 
- Up to 10,000 processes added via `add_process`
- `0 ≤ base ≤ 2⁶⁴ − 1`, `0 ≤ bounds ≤ 2⁶⁴ − 1` (use `uint64_t` arithmetic to avoid overflow)
- PIDs are arbitrary `uint32_t` values
 
