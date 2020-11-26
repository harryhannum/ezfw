#ifndef FW_SIMULATION_HPP
#define FW_SIMULATION_HPP

#ifdef EZFW_SIMULATION

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <unordered_map>
#include <functional>
#include <future>
#include <mutex>
#include "detail/net.hpp"

namespace ezfw
{
    class FwSimulation
    {
    public:
        using IrqHandler = std::function<void(uint8_t)>;

        static FwSimulation& instance();

        uint64_t read(size_t addr, size_t size);
        void write(size_t addr, size_t size, uint64_t value);

        bool register_irq_handler(uint8_t irq_id, IrqHandler handler);
        void unregister_irq_handler(uint8_t irq_id);

    private:
        FwSimulation();
        ~FwSimulation();

        WsaInitialiser _socket_init;
        Socket _socket;
        std::mutex _irq_mutex;
        std::unordered_map<uint8_t, IrqHandler> _irq_handlers;
        std::unordered_map<uint8_t, std::future<uint64_t>> _pending_requests;
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
