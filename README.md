# djinn
A simple template-based Entity-Component-System game engine for a fun little side project

## TODO
- [ ] Implement GTest for testing
- [ ] Switch EntityComponentFn to a functor (I like them more than c++ lambda syntax)
- [x] Implement a working ThreadPool
- [ ] Implement System functions to deploy work to the ThreadPool with a class that keeps track of how many jobs are deployed and waits for all of them to be completed
- [x] Allow fixed tickrate and update throttling to be disabled with 0
- [x] Allow defining a dependsOn<typename... Systems> so that addSystem can put the new system after all the others that it depends on. Need to be able to find based on dependencies and find based on type
- [x] Implement a more generic "thread" class
- [ ] Define an input sampling rate separate from the tick_rate
- [ ] Implement (Linux) input polling
- [ ] Redefine EntityId, ComponentId, and SystemId using struct{ size_t } to enforce strong typing. (Also add std hash support)
- [ ] Add an assertion that a System is inserted before all Systems that depend on it
- [ ] Fix issue where ThreadPool hangs when shutting down even though all threads have stopped
