#ifndef REGISTERS_H
#define REGISTERS_H

// #define USE_EZFW_SIMULATION

#include "ezfw.hpp"
#include <stdint.h>

namespace cyder_project
{
    namespace fpga_registers
    {
        using Accessor = ACCESSOR(uint32_t);

        namespace multiplier
        {
            enum RegAddress : size_t
            {
                EStatus = 0x00000000,
                ELHS = 0x00000004,
                ERHS = 0x00000008,
                EResult = 0x0000000c
            };

            static constexpr uint32_t READY_STATUS = 0xFACEB00C;

            using Status = Accessor::Register<ezfw::policies::ReadOnly, EStatus>;
            using LHS = Accessor::Register<ezfw::policies::WriteOnly, ELHS>;
            using RHS = Accessor::Register<ezfw::policies::WriteOnly, ERHS>;
            using Result = Accessor::Register<ezfw::policies::ReadOnly, EResult>;
        }
    }
}

#endif //REGISTERS_H
