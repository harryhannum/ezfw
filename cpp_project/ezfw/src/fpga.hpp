#ifndef CPP_PROJECT_FPGA_HPP
#define CPP_PROJECT_FPGA_HPP

#include <cstdint>

namespace ezfw
{
    namespace fpga
    {
        /**
         *
         * @param addr
         * @param value
         */
        void write_reg(uint32_t addr, uint32_t value);

        /**
         *
         * @param addr
         * @return
         */
        uint32_t read_reg(uint32_t addr);
    } // namespace fpga
} // namespace ezfw

#endif //CPP_PROJECT_FPGA_HPP
