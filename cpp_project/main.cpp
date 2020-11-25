#include "ezfw/ezfw.hpp"

namespace cyder
{
    namespace fpga_registers
    {
        namespace multiplier
        {
            using Status = ACCESSOR::Register<ezfw::policies::ReadOnly, 0>;
            using Lhs = ACCESSOR::Register<ezfw::policies::WriteOnly, 4>;
            using Rhs = ACCESSOR::Register<ezfw::policies::WriteOnly, 8>;
            using Result = ACCESSOR::Register<ezfw::policies::ReadOnly, 12>;
        }
    }
}

int main()
{
    return 0;
}
