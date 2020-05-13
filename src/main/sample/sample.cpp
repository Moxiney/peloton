#include <iostream>

#include "benchmark/benchmark_common.h"
#include "benchmark/sample/benchmark_sample.h"
#include "benchmark/sample/ycsb_configuration.h"
#include "common/logger.h"
#include "storage/data_table.h"

namespace peloton {
namespace benchmark {
namespace ycsb {

configuration state;

}
}  // namespace benchmark
}  // namespace peloton

int main(int argc, char **argv) {
  std::cout << "Hello World" << std::endl;
  Foo();
  Hoo();
  peloton::benchmark::FastRandom fastRand(0);
  std::cout << fastRand.next_u32() << std::endl;

  peloton::LOG_INFO("Hello World");
  peloton::LOG_WARN("Hello World");
  peloton::LOG_ERROR("Hello World");

  peloton::benchmark::ycsb::ParseArguments(argc, argv, peloton::benchmark::ycsb::state);

  std::cout << peloton::benchmark::ycsb::ycsb_database_oid << std::endl;

  return 0;
}