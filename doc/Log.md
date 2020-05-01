# Log

## 1. Build

1. VB，course，桥接，有线网
2. VB，vagrant，NAT，设置代理, 
    不行，好像是我的代理不接受局域网的请求
3. vagrant 桥接
    不能直接在virtualbox里面修改
    如果在vagrantfile里面修改的话，vagrant ssh连不上
4. 直接下载对应的whl然后安装
 tensorflow-1.5.0-cp36-cp36m-manylinux1_x86_64.whl
 numpy-1.18.3-cp36-cp36m-manylinux1_x86_64.whl
 不行，即使装完轮子之后再调用packages.sh的时候还是显示没有安装

5. pip 的时候加上 -i https://pypi.tuna.tsinghua.edu.cn/simple
    不行，下载tensorflow的时候要递归调用pip，这时候无法在packages.sh里面指定url

6. 在~/.pip/pip-config里面指定阿里云作为源
   可以，build通过

## 2. Test

1. script/oltpbenchmark
> git clone https://github.com/oltpbenchmark/oltpbench.git ，用这个来测试，没有参考价值

2. insert 
```
void InsertTuple(storage::DataTable *table, type::AbstractPool *pool,
                 oid_t tilegroup_count_per_loader,
                 UNUSED_ATTRIBUTE uint64_t thread_itr) {
  
  auto &txn_manager = concurrency::TransactionManagerFactory::GetInstance();

  oid_t tuple_count = tilegroup_count_per_loader * TEST_TUPLES_PER_TILEGROUP;

  // Start a txn for each insert
  
  auto txn = txn_manager.BeginTransaction();
  
  std::unique_ptr<storage::Tuple> tuple(
      TestingExecutorUtil::GetTuple(table, ++loader_tuple_id, pool));

  std::unique_ptr<executor::ExecutorContext> context(
      new executor::ExecutorContext(txn));

  planner::InsertPlan node(table, std::move(tuple));

  // Insert the desired # of tuples
  for (oid_t tuple_itr = 0; tuple_itr < tuple_count; tuple_itr++) {
    
    executor::InsertExecutor executor(&node, context.get());
    
    executor.Execute();
  
  }

  txn_manager.CommitTransaction(txn);

}
```