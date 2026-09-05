#include "UniquePtr/uniqueptr.h"
#include <cassert>
#include <iostream>
#include <utility>

struct Test
{
    static inline int alive{ 0 };
    static inline int destroyed { 0 };
    int id{};

    explicit Test(int i = 0) : id{ i } { ++alive; }
    ~Test() { --alive; ++destroyed; }
};

int main()
{
    {
        kxanz::unique_ptr<Test> p{ new Test{1} };
        assert(Test::alive == 1);
    }
    assert(Test::alive == 0);
    assert(Test::destroyed == 1);
}
