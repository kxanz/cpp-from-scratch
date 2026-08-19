#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdint>

struct ProccessRegion
{
    uint32_t pid;
    uint64_t base;
    uint64_t bounds;
};

class RegionChecker {
public:
    void add_process(uint32_t pid, uint64_t base, uint64_t bounds)
    {
        procceses_.push_back({pid, base, bounds});
    }

    std::vector<std::pair<uint32_t, uint32_t>> find_overlaps() const
    {
        std::vector<std::pair<uint32_t, uint32_t>> result;
        size_t size = procceses_.size();

        for (size_t currPid {0}; currPid < size; currPid++)
        {
            for (size_t nextPid {currPid + 1}; nextPid < size; nextPid++)
            {
                if (overlap(procceses_[currPid], procceses_[nextPid]))
                {
                    auto low = std::min(procceses_[currPid].pid, procceses_[nextPid].pid);
                    auto max = std::max(procceses_[currPid].pid, procceses_[nextPid].pid);
                    result.push_back({low, max});
                }
            }
        }
        return result;
    }
private:
    std::vector<ProccessRegion> procceses_;

    static bool overlap(const ProccessRegion& a, const ProccessRegion& b)
    {
        if (a.bounds == 0) { return false; }
        if (b.bounds == 0) { return false; }
        return a.base < b.base + b.bounds && b.base < a.base + a.bounds;
    }
};

int main()
{
    RegionChecker checker;

    checker.add_process(0, 0,   300);   // [0, 300)
    checker.add_process(1, 200, 300);   // [200, 500)
    checker.add_process(2, 400, 300);   // [400, 700)
    checker.add_process(3, 700, 100);   // [700, 800)

    auto overlaps = checker.find_overlaps();

    std::cout << "Overlapping pairs:\n";
    for (const auto& p : overlaps)
    {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }

    // Expected: (0, 1) and (1, 2)
    return 0;
}