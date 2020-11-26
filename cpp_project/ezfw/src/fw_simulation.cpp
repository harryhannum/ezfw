#include "ezfw/fw_simulation.hpp"

#ifdef EZFW_SIMULATION

#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include "icd.hpp"

#ifndef EZFW_SERVER_PORT
#   define EZFW_SERVER_PORT 51337
#endif // !EZFW_SERVER_PORT

FwSimulation& FwSimulation::instance()
{
    static FwSimulation _instance;
    return _instance;
}

FwSimulation::FwSimulation() : _socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
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

    if (connect(_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
    {
        std::fprintf(stderr, "ERROR: failed to connect socket (%d)\n", errno);
        std::abort();
    }
}

uint64_t FwSimulation::read(size_t addr, size_t size)
{
    return 0;
}

void FwSimulation::write(size_t addr, size_t size, uint64_t value)
{
}

#endif /* EZFW_SIMULATION */
