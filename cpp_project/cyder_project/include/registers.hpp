#ifndef REGISTERS_H
#define REGISTERS_H

// #define USE_EZFW_SIMULATION

#include "ezfw.hpp"

namespace cyder_project
{
    namespace fpga_registers
    {
        namespace multiplier
        {
            enum RegAdress : size_t
            {
                EStatus = 0x00000001,
                ELHS = 0x00000004,
                ERHS = 0x00000008,
                EResult = 0x0000000c
            };

            static constexpr uint32_t READY_STATUS = 0xFACEB00C;

            using Status = ACCESSOR::Register<ezfw::policies::ReadOnly, EStatus>;
            using LHS = ACCESSOR::Register<ezfw::policies::WriteOnly, ELHS>;
            using RHS = ACCESSOR::Register<ezfw::policies::WriteOnly, ERHS>;
            using Result = ACCESSOR::Register<ezfw::policies::ReadOnly, EResult>;
        }
    }
}

#endif //REGISTERS_H
