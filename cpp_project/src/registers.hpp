#ifndef REGISTERS_H
#define REGISTERS_H

#include "ezfw.hpp"
#include <stdint.h>

namespace fpga_registers
{
    using Accessor = ACCESSOR(uint32_t);

    namespace multiplier
    {
        static constexpr uint32_t READY_STATUS = 1;

        using Status = Accessor::Register<ezfw::policies::ReadOnly, 0x00000000>;
        using LHS = Accessor::Register<ezfw::policies::WriteOnly, 0x00000004>;
        using RHS = Accessor::Register<ezfw::policies::WriteOnly, 0x00000008>;
        using Result = Accessor::Register<ezfw::policies::ReadOnly, 0x0000000c>;
    } // namespace multiplier
} // namespace fpga_registers

#endif //REGISTERS_H
