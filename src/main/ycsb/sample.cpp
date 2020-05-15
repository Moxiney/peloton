#include <iostream>
#include <fstream>
#include <iomanip>

#include "benchmark/benchmark_common.h"
#include "benchmark/ycsb/benchmark_sample.h"
#include "benchmark/ycsb/ycsb_configuration.h"
#include "benchmark/ycsb/ycsb_loader.h"
#include "benchmark/ycsb/ycsb_workload.h"
#include "common/logger.h"
#include "storage/data_table.h"

#include "gc/gc_manager_factory.h"
#include "concurrency/epoch_manager_factory.h"

namespace peloton {
namespace benchmark {
namespace ycsb {

configuration state;

void RunBenchmark() {
  // LOG_INFO("Start YCSB benchmark");

  // CreateYCSBDatabase();
  // LOG_INFO("DB and Table created");

  // DropYCSBDatabase();
  // LOG_INFO("DB dropped");

  if (state.gc_mode == false) {
    gc::GCManagerFactory::Configure(0);
  } else {
    gc::GCManagerFactory::Configure(state.gc_backend_count);
  }

  concurrency::EpochManagerFactory::Configure(state.epoch);

  std::unique_ptr<std::thread> epoch_thread;
  std::vector<std::unique_ptr<std::thread>> gc_threads;

  concurrency::EpochManager &epoch_manager =
      concurrency::EpochManagerFactory::GetInstance();

  if (concurrency::EpochManagerFactory::GetEpochType() ==
      EpochType::DECENTRALIZED_EPOCH) {
    for (size_t i = 0; i < (size_t)state.backend_count; ++i) {
      // register thread to epoch manager
      epoch_manager.RegisterThread(i);
    }
  }

  // start epoch.
  epoch_manager.StartEpoch(epoch_thread);

  gc::GCManager &gc_manager = gc::GCManagerFactory::GetInstance();

  // start GC.
  gc_manager.StartGC(gc_threads);

  // Create the database
  CreateYCSBDatabase();

  // Load the databases
  LoadYCSBDatabase();

  // Run the workload
  RunWorkload();

  // stop GC.
  gc_manager.StopGC();

  // stop epoch.
  epoch_manager.StopEpoch();

  // join all gc threads
  for (auto &gc_thread : gc_threads) {
    PELOTON_ASSERT(gc_thread != nullptr);
    gc_thread->join();
  }

  // join epoch thread
  PELOTON_ASSERT(epoch_thread != nullptr);
  epoch_thread->join();

  // Emit throughput
  WriteOutput();
  return;
}

}  // namespace ycsb
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

  peloton::benchmark::ycsb::ParseArguments(argc, argv,
                                           peloton::benchmark::ycsb::state);

  peloton::benchmark::ycsb::RunBenchmark();

  return 0;
}