#include "ezfw/simulator.hpp"
#include "ezfw/icd.hpp"
#include <cstdlib>
#include <cstdio>

// TODO: Add communication include
#include <cstddef>
bool write(const uint8_t* data, size_t size) {return true;}
bool read(uint8_t* o_data, size_t size) {return true;}

namespace ezfw
{
    namespace simulator
    {
        void write_reg(uint64_t addr, uint64_t value)
        {
            icd::Header request_header = {icd::request::WriteRequest::OPCODE};
            icd::request::WriteRequest request = {addr, value};

            write(reinterpret_cast<uint8_t*>(&request_header), sizeof(request_header));
            write(reinterpret_cast<uint8_t*>(&request), sizeof(request));

            // Wait for ack
            icd::Header response_header;
            read(reinterpret_cast<uint8_t*>(&response_header), sizeof(response_header));

            switch (response_header.opcode)
            {
            case icd::response::WriteAck::OPCODE:
                return;

            case icd::response::Nack::OPCODE:
                icd::response::Nack nack;
                read(reinterpret_cast<uint8_t*>(&nack), sizeof(nack));

                printf("Got nack with value %d\r\n", uint32_t(nack.error_code));
                /* FALLTHRU */

            case icd::request::WriteRequest::OPCODE:
            case icd::request::ReadRequest::OPCODE:
            case icd::response::ReadResponse::OPCODE:
            default:
                printf("Got a response with an unauthorized opcode %d\r\n", response_header.opcode);
                break;
            }

            abort();
        }

        uint64_t read_reg(uint64_t addr)
        {
            icd::Header request_header = {icd::request::ReadRequest::OPCODE};
            icd::request::ReadRequest request = {addr};

            write(reinterpret_cast<uint8_t*>(&request_header), sizeof(request_header));
            write(reinterpret_cast<uint8_t*>(&request), sizeof(request));

            // Wait for response
            icd::Header response_header;
            read(reinterpret_cast<uint8_t*>(&response_header), sizeof(response_header));

            switch (response_header.opcode)
            {
            case icd::response::ReadResponse::OPCODE:
                icd::response::ReadResponse response;
                read(reinterpret_cast<uint8_t*>(&response), sizeof(response));

                return response.value;

            case icd::response::Nack::OPCODE:
                icd::response::Nack nack;
                read(reinterpret_cast<uint8_t*>(&nack), sizeof(nack));

                printf("Got nack with value %d\r\n", uint32_t(nack.error_code));
                /* FALLTHRU */

            case icd::request::WriteRequest::OPCODE:
            case icd::request::ReadRequest::OPCODE:
            case icd::response::WriteAck::OPCODE:
            default:
                printf("Got a response with an unauthorized opcode %d\r\n", response_header.opcode);
                break;
            }

            abort();
        }
    } // namespace fpga
} // namespace ezfw
