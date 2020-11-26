#ifndef REGISTERS_H
#define REGISTERS_H

#define USE_EZFW_SIMULATION

#include "ezfw.hpp"

namespace cyder_project
{
    namespace fpga_registers
    {
        namespace multiplier
        {
            enum class ERegAdress
            {
                Status = 0x00000001,
                LHS = 0x00000004,
                RHS = 0x00000008,
                Result = 0x0000000c
            };

            static constexpr uint32_t READY_STATUS = 0xFACEBOOC;

           using Status = ACCESSOR::Register<ezfw::policies::ReadOnly, ERegAdress::Status>;
           using LHS = ACCESSOR::Register<ezfw::policies::WriteOnly, ERegAdress::LHS>;
           using RHS = ACCESSOR::Register<ezfw::policies::WriteOnly, ERegAdress::RHS>;
           using Result = ACCESSOR::Register<ezfw::policies::ReadOnly, ERegAdress::Result>;
        }
    }
}

#endif //REGISTERS_H
