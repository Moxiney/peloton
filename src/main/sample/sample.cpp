#include<iostream>


#include "benchmark/benchmark_sample.h"
#include "benchmark/benchmark_common.h"

#include "storage/data_table.h"
#include "common/logger.h"

int main() {
    std::cout<<"Hello World"<<std::endl;
    Foo();
    Hoo();
    peloton::benchmark::FastRandom fastRand(0);
    std::cout<<fastRand.next_u32()<<std::endl;
    
    peloton::LOG_INFO("Hello World");
    return 0;
}