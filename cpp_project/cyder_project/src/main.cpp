#include "registers.hpp"

using namespace cyder_project;
using namespace fpga_registers;

uint32_t multiply(uint32_t lhs, uint32_t rhs)
{
    multiplier::LHS::write(lhs);
    multiplier::RHS::write(rhs);

    while (true)
    {
        if (multiplier::Status::read() == READY_STATUS)
        {
            break;
        }
    }

    return multiplier::Result::read();
}

int main()
{
    uint32_t result = multiply(3, 5);
    printf("result = %u", result);

    return 0;
}
