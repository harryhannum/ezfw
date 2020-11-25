#ifndef EZLIB_HPP
#define EZLIB_HPP

#include <cstddef>
#include <numeric>
#include <type_traits>

namespace ezlib {
    template<class Target>
    struct Accessor
    {
        template<
            template<class T, size_t, T, size_t> class MutabilityPolicy,
            size_t Addr,
            Target Mask = std::numeric_limits<Target::value_type>::max(),
            size_t Offset = 0>
        struct Register : public MutabilityPolicy<Target, Addr, Mask, Offset>
        {
            static_assert(Offset < (CHAR_BIT * sizeof(Target::value_type)), "");
            static_assert(
                (((Mask << Offset) & std::numeric_limits<Target::value_type>::max()) >> Offset) == Mask,
                "");
        };
    };

    template<class T>
    struct MemoryTarget
    {
        using value_type = std::remove_volatile_t<std::remove_const_t<T>>;

        static_assert(
            std::is_unsigned<value_type>::value,
            "Only unsigned types are suppported as a memory target");

        static inline value_type read(size_t addr, value_type mask, size_t offset) {
            return (*reinterpret_cast<const volatile value_type *>(addr) >> offset) & mask;
        }

        static inline void write(size_t addr, value_type mask, size_t offse, value_type value) {
            *reinterpret_cast<const volatile value_type *>(addr) = (value & mask) << offset;
        }
    }

    namespace policies {
        template<class Target, size_t Addr, Target Mask, size_t Offset>
        struct ReadOnly
        {
            static inline typename Target::value_type read() {
                return Target::read(Addr, Mask, Offset);
            }
        };

        template<class Target, size_t Addr, Target Mask, size_t Offset>
        struct WriteOnly
        {
            static inline void write(typename Target::value_type value) {
                Target::write(Addr, Mask, Offset, value)
            }
        };

        template<class Target, size_t Addr, Target Mask, size_t Offset>
        struct ReadWrite :
            public ReadOnlyPolicy<Target, Addr, Mask, Offset>,
            public WriteOnlyPolicy<Target, Addr, Mask, Offset>
        {
        };
    }
}

#endif
