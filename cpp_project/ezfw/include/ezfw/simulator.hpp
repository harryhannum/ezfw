#ifndef CPP_PROJECT_SIMULATOR_HPP
#define CPP_PROJECT_SIMULATOR_HPP

#include <cstdint>

namespace ezfw
{
    namespace simulator
    {
        void write_reg(uint64_t addr, uint64_t value);
        uint64_t read_reg(uint64_t addr);
    } // namespace fpga
} // namespace ezfw

#endif // CPP_PROJECT_SIMULATOR_HPP
