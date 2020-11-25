#include "ezfw/fw_simulation.hpp"

#ifdef EZFW_SIMULATION

FwSimulation& FwSimulation::instance()
{
    static FwSimulation _instance;
    return _instance;
}

FwSimulation::FwSimulation() {}

uint64_t FwSimulation::read(size_t addr, size_t size)
{
    return 0;
}

void FwSimulation::write(size_t addr, size_t size, uint64_t value)
{
}

#endif /* EZFW_SIMULATION */
