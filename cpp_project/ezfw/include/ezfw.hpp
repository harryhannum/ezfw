#ifndef EZFW_HPP
#define EZFW_HPP

#include <cstddef>
#include <climits>
#include <limits>
#include <type_traits>

#ifdef EZFW_SIMULATION
#   include "ezfw/fw_simulation.hpp"
#   define ACCESSOR(type)   ::ezfw::Accessor< ::ezfw::SimulatedTarget<type>>
#else // if !EZFW_SIMULATION
#   define ACCESSOR(type)   ::ezfw::Accessor< ::ezfw::MemoryTarget<type>>
#endif // !EZFW_SIMULATION

namespace ezfw
{
    template<class Target>
    struct Accessor
    {
        template<
            template<class T, size_t, T, size_t> class MutabilityPolicy,
            size_t Addr,
            typename Target::ValueType Mask = std::numeric_limits<typename Target::ValueType>::max(),
            size_t Offset = 0>
        struct Register : public MutabilityPolicy<typename Target::ValueType, Addr, Mask, Offset>
        {
            static_assert(
                Offset < (CHAR_BIT * sizeof(typename Target::ValueType)), "Offset must not exceed the target value type");
            static_assert(
                (((Mask << Offset) & std::numeric_limits<typename Target::ValueType>::max()) >> Offset) == Mask,
                "Mask must not exceed the target value type when offset");
        };
    };

    template<class T>
    struct MemoryTarget
    {
        using ValueType = std::remove_volatile_t<std::remove_const_t<T>>;

        static_assert(
            std::is_unsigned<ValueType>::value,
            "Only unsigned types are supported as a memory target");

        static inline ValueType read(size_t addr, ValueType mask, size_t offset)
        {
            return (*reinterpret_cast<const volatile ValueType *>(addr) >> offset) & mask;
        }

        static inline void write(size_t addr, ValueType mask, size_t offset, ValueType value)
        {
            *reinterpret_cast<const volatile ValueType *>(addr) = (value & mask) << offset;
        }
    };

    namespace policies
    {
        template<class Target, size_t Addr, Target Mask, size_t Offset>
        struct ReadOnly
        {
            static inline typename Target::ValueType read()
            {
                return Target::read(Addr, Mask, Offset);
            }
        };

        template<class Target, size_t Addr, Target Mask, size_t Offset>
        struct WriteOnly
        {
            static inline void write(typename Target::ValueType value)
            {
                Target::write(Addr, Mask, Offset, value);
            }
        };

        template<class Target, size_t Addr, Target Mask, size_t Offset>
        struct ReadWrite :
            public ReadOnly<Target, Addr, Mask, Offset>,
            public WriteOnly<Target, Addr, Mask, Offset>
        {
        };
    }
} // namespace ezfw

#endif /* !EZFW_HPP */
