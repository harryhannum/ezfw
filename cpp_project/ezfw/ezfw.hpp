#ifndef CPP_PROJECT_EZFW_HPP
#define CPP_PROJECT_EZFW_HPP

#ifndef USE_EZFW
#   define FPGA_READ_REG(addr) *((volatile uint32_t*) addr)
#   define FPGA_WRITE_REG(addr, value) *((volatile uint32_t*) addr) = value
#else // ifdef USE_EZFW
#   include "fpga.hpp"
#   define FPGA_READ_REG(addr) ::ezfw::fpga::read_reg(addr)
#   define FPGA_WRITE_REG(addr, value) ::ezfw::fpga::write_reg(addr, value)
#endif // !USE_EZFW

#endif //CPP_PROJECT_EZFW_HPP
