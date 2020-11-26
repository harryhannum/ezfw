#ifndef FW_SIMULATION_HPP
#define FW_SIMULATION_HPP

#ifdef EZFW_SIMULATION

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include "detail/net.hpp"

namespace ezfw
{
    class FwSimulation
    {
    public:
        static FwSimulation& instance();

        uint64_t read(size_t addr, size_t size);
        void write(size_t addr, size_t size, uint64_t value);

    private:
        FwSimulation();

        Socket _socket;
    };

    template<class T>
    struct SimulatedTarget
    {
        using ValueType = std::remove_volatile_t<std::remove_const_t<T>>;

        static_assert(
            std::is_unsigned<ValueType>::value, "Only unsigned types are supported as a simulated target");
        static_assert(sizeof(uint64_t) >= sizeof(ValueType), "Only up to 64-bit value types are supported");

        static inline ValueType read(size_t addr, ValueType mask, size_t offset)
        {
            return static_cast<ValueType>(FwSimulation::instance().read(addr, sizeof(ValueType)) >> offset) & mask;
        }

        static inline void write(size_t addr, ValueType mask, size_t offset, ValueType value)
        {
            FwSimulation::instance().write(addr, sizeof(ValueType), static_cast<uint64_t>((value & mask) << offset));
        }
    };
} // namespace ezfw

#endif /* EZFW_SIMULATION */

#endif /* !FW_SIMULATION_HPP */
