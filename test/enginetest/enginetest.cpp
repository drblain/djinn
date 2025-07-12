#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "djinn/Engine.hpp"
#include "djinn/System.hpp"
#include "djinn/Time.hpp"

class TestSystem : public djinn::System
{
private:
    std::string name_;
    uint64_t num_inputs_;
    uint64_t num_updates_;
    uint64_t num_renders_;

public:
    TestSystem(djinn::EntityManager& manager, const std::string& name):
        System(manager),
        name_(name),
        num_inputs_(0),
        num_updates_(0),
        num_renders_(0)
    {}

    void input() override
    {
        ++num_inputs_;
    }

    void update(const djinn::TimeDuration&) override
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(8));

        ++num_updates_;
        std::cout << name_ << ": Processing update " << num_updates_ << " after " << num_inputs_ << " inputs and " << num_renders_ << " renders" << std::endl;
    }

    void render() override
    {
        ++num_renders_;
    }
};

int main(void)
{
    djinn::Engine ng(60, 5);
    ng.addSystem<TestSystem>(ng, "TestSystem1");
    ng.addSystem<TestSystem>(ng, "TestSystem2");
    ng.addSystem<TestSystem>(ng, "TestSystem3");

    std::thread ng_thread([&ng]() { ng.run(); });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    ng.stop();
    ng_thread.join();

    return 0;
}