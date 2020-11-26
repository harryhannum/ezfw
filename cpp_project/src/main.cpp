#include "registers.hpp"
#include <cstdint>
#include <cstdio>

uint32_t multiply(uint32_t lhs, uint32_t rhs)
{
    fpga_registers::multiplier::LHS::write(lhs);
    fpga_registers::multiplier::RHS::write(rhs);

    while (fpga_registers::multiplier::Status::read() != fpga_registers::multiplier::READY_STATUS)
        ;

    return fpga_registers::multiplier::Result::read();
}

int main()
{
    uint32_t result = multiply(3, 5);
    printf("result = %u\r\n", result);

    return 0;
}
