#ifndef EZFW_ICD_H
#define EZFW_ICD_H

#include <cstdint>

namespace icd
{
    struct Header
    {
        uint8_t opcode;
    };

    namespace request
    {
        struct WriteRequest
        {
            static constexpr uint8_t OPCODE = 0x37;

            uint32_t addr;
            uint32_t value;
        };

        struct ReadRequest
        {
            static constexpr uint8_t OPCODE = 0x77;

            uint32_t addr;
        };
    } // namespace request

    namespace response
    {
        struct WriteAck
        {
            static constexpr uint8_t OPCODE = 0x3A;
        };

        struct ReadResponse
        {
            static constexpr uint8_t OPCODE = 0x7A;

            uint32_t value;
        };
    } // namespace response
} // namespace icd

#endif //EZFW_ICD_H
