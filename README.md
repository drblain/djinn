# djinn
A simple template-based Entity-Component-System game engine for a fun little side project

## TODO
- [ ] Implement GTest for testing
- [ ] Switch EntityComponentFn to a functor (I like them more than c++ lambda syntax)
- [x] Implement a working ThreadPool
- [ ] Implement System functions to deploy work to the ThreadPool with a class that keeps track of how many jobs are deployed and waits for all of them to be completed
