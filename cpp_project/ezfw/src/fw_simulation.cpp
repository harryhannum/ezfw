#include "fw_simulation.hpp"

#ifdef EZFW_SIMULATION

#include "icd.hpp"

#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <cstring>

#ifndef EZFW_SERVER_PORT
#   define EZFW_SERVER_PORT 65432
#endif // !EZFW_SERVER_PORT

namespace ezfw
{
    FwSimulation& FwSimulation::instance()
    {
        static FwSimulation _instance;
        return _instance;
    }

    FwSimulation::FwSimulation() : _socket_init{}, _socket{::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)}
    {
        if (_socket == INVALID_SOCKET)
        {
            std::fprintf(stderr, "ERROR: failed to open socket (%d)\n", errno);
            std::abort();
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(0x7f000001); // 127.0.0.1
        server_addr.sin_port = htons(EZFW_SERVER_PORT);

        if (::connect(_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
        {
            std::fprintf(stderr, "ERROR: failed to connect socket (%d)\n", errno);
            std::abort();
        }
    }

    FwSimulation::~FwSimulation()
    {
        if (_socket != INVALID_SOCKET)
        {
            closesocket(_socket);
        }
    }

    uint64_t FwSimulation::read(size_t addr, size_t size)
    {
        icd::Header header{};
        header.opcode = icd::request::ReadRequest::OPCODE;

        icd::request::ReadRequest request{};
        request.addr = addr;

        char buffer[sizeof(header) + sizeof(request)];
        memcpy(buffer, &header, sizeof(header));
        memcpy(buffer + sizeof(header), &request, sizeof(request));

        if (::send(_socket, buffer, sizeof(buffer), 0) != sizeof(buffer))
        {
            std::fprintf(stderr, "ERROR: failed to send read request\n");
            std::abort();
        }

        if (::recv(_socket, reinterpret_cast<char *>(&header), sizeof(header), 0) != sizeof(header))
        {
            std::fprintf(stderr, "ERROR: failed to recv read response header\n");
            std::abort();
        }

        switch (header.opcode)
        {
        case icd::response::ReadResponse::OPCODE:
            {
                icd::response::ReadResponse response{};

                if (::recv(_socket, reinterpret_cast<char *>(&response), sizeof(response), 0) != sizeof(response))
                {
                    std::fprintf(stderr, "ERROR: failed to recv read response body\n");
                    std::abort();
                }

                return response.value;
            }

        case icd::response::Nack::OPCODE:
            {
                icd::response::Nack nack{};

                if (::recv(_socket, reinterpret_cast<char *>(&nack), sizeof(nack), 0) != sizeof(nack))
                {
                    std::fprintf(stderr, "ERROR: failed to recv read response NACK body\n");
                }
                else
                {
                    std::fprintf(stderr, "ERROR: read response NACK (%d)\n", static_cast<int>(nack.error_code));
                }

                break;
            }

        case icd::request::WriteRequest::OPCODE:
        case icd::request::ReadRequest::OPCODE:
        case icd::response::WriteAck::OPCODE:
        default:
            std::fprintf(stderr, "ERROR: invalid write response opcode (%d)\n", header.opcode);
            break;
        }

        std::abort();
    }

    void FwSimulation::write(size_t addr, size_t size, uint64_t value)
    {
        icd::Header header{};
        header.opcode = icd::request::WriteRequest::OPCODE;

        icd::request::WriteRequest request{};
        request.addr = addr;
        request.value = value;

        char buffer[sizeof(header) + sizeof(request)];
        memcpy(buffer, &header, sizeof(header));
        memcpy(buffer + sizeof(header), &request, sizeof(request));

        if (::send(_socket, buffer, sizeof(buffer), 0) != sizeof(buffer))
        {
            std::fprintf(stderr, "ERROR: failed to send write request\n");
            std::abort();
        }

        if (::recv(_socket, reinterpret_cast<char *>(&header), sizeof(header), 0) != sizeof(header))
        {
            std::fprintf(stderr, "ERROR: failed to recv write response header\n");
            std::abort();
        }

        switch (header.opcode)
        {
        case icd::response::WriteAck::OPCODE:
            return;

        case icd::response::Nack::OPCODE:
            {
                icd::response::Nack nack{};

                if (::recv(_socket, reinterpret_cast<char *>(&nack), sizeof(nack), 0) != sizeof(nack))
                {
                    std::fprintf(stderr, "ERROR: failed to recv write response NACK body\n");
                }
                else
                {
                    std::fprintf(stderr, "ERROR: write response NACK (%d)\n", static_cast<int>(nack.error_code));
                }

                break;
            }

        case icd::request::WriteRequest::OPCODE:
        case icd::request::ReadRequest::OPCODE:
        case icd::response::ReadResponse::OPCODE:
        default:
            std::fprintf(stderr, "ERROR: invalid write response opcode (%d)\n", header.opcode);
            break;
        }

        std::abort();
    }
} // namespace ezfw

#endif /* EZFW_SIMULATION */
