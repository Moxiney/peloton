#include<iostream>

#include "storage/data_table.h"
#include "benchmark/benchmark_sample.h"
#include "benchmark/benchmark_common.h"

int main() {
    std::cout<<"Hello World"<<std::endl;
    Foo();
    Hoo();
    peloton::benchmark::FastRandom fastRand(0);
    std::cout<<fastRand.next_u32()<<std::endl;
    return 0;
}