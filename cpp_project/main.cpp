#include <cstdint>
#include "ezfw.hpp"

namespace cyder
{
    namespace fpga_registers
    {
        using Accessor = ACCESSOR(uint32_t);

        namespace multiplier
        {
            using Status = Accessor::Register<ezfw::policies::ReadOnly, 0>;
            using Lhs = Accessor::Register<ezfw::policies::WriteOnly, 4>;
            using Rhs = Accessor::Register<ezfw::policies::WriteOnly, 8>;
            using Result = Accessor::Register<ezfw::policies::ReadOnly, 12>;
        }
    }
}

int main()
{
    return 0;
}
