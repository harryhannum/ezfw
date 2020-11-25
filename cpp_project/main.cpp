#include <cstdint>
#include "ezfw/ezfw.hpp"

namespace my_project
{
    namespace fpga_registers
    {
        namespace multiplier
        {
//            using Status = ACCESSOR::Register<ezfw::policies::ReadOnly, 0>;

        }
    }
}

int main()
{
    using Target = ezfw::MemoryTarget<uint32_t>;
    ezfw::Accessor<Target> accessor;

    return 0;
}
