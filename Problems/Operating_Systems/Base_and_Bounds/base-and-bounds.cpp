#include <cstdint>     // uint32_t, uint64_t, UINT64_MAX
#include <vector>      // std::vector
#include <algorithm>   // std::sort, std::erase_if, std::min, std::max
#include <utility>     // std::pair
#include <iostream>

/*
Trying the interval algo 
*/

    class RegionChecker {
        private:
            struct Process
            {
                uint32_t pid;
                uint64_t base;
                uint64_t bounds;
            };
            std::vector<Process> processes_;
    public:
        void add_process(uint32_t pid, uint64_t base, uint64_t bounds) 
        {
            processes_.push_back({pid, base, bounds});
        }
    
        std::vector<std::pair<uint32_t, uint32_t>> find_overlaps() const 
        {
            std::vector<std::pair<uint32_t, uint32_t>> result;
            result.reserve(processes_.size()); 
        
            auto sorted { processes_ }; //copy since there is a const
            std::sort(sorted.begin(), sorted.end(), [](const Process& x, const Process& y) { return x.base < y.base; }); //lambda 
    
            std::vector<Process> active;
    
            for (const auto& current : sorted) 
            {
                if (current.bounds == 0) continue;
    
                uint64_t curr_end;
                if (current.bounds > UINT64_MAX - current.base) curr_end = UINT64_MAX;
                else curr_end = current.base + current.bounds;
                
                std::erase_if(active, [&](const Process& p)
                {
                    uint64_t p_end;
                    if (p.bounds > UINT64_MAX - p.base) p_end = UINT64_MAX;
                    else p_end = p.base + p.bounds;
                    return p_end <= current.base;
                });
    
                for (const auto& a : active)
                {
                    result.push_back({std::min(a.pid, current.pid),
                                      std::max(a.pid, current.pid)});
                }
                active.push_back(current);
            }
            return result;
        }
    };

    int main() {
        RegionChecker checker;
        checker.add_process(0, 0, 300);
        checker.add_process(1, 200, 300);
        checker.add_process(2, 400, 300);
        checker.add_process(3, 700, 100);
    
        auto result = checker.find_overlaps();
    
        for (const auto& [a, b] : result) {
            std::cout << "(" << a << ", " << b << ")\n";
        }
        // expected:
        // (0, 1)
        // (1, 2)
        return 0;
    }