#ifndef NET_HPP
#define NET_HPP

#if (defined(__unix__) || defined(unix)) && !defined(USG)
#   include <sys/param.h>
#endif /* (defined(__unix__) || defined(unix)) && !defined(USG) */

#if defined(_WIN32)
#   if defined(_MSC_VER)
#       pragma comment(lib, "ws2_32.lib")
#       pragma warning(disable : 4996)
#   endif /* defined(_MSC_VER) */

#   include <cstdlib>
#   include <atomic>

#   define WIN32_LEAN_AND_MEAN
#   include <WinSock2.h>
#   include <WS2tcpip.h>
#   include <Windows.h>

typedef SOCKET Socket;

struct WsaInitialiser
{
    WsaInitialiser()
    {
        if ((_counter++ == 0) && (WSAStartup(0x101, &_wsadata) != 0))
        {
            std::abort();
        }
    }

    ~WsaInitialiser()
    {
        if (--_counter)
        {
            WSACleanup();
        }
    }

private:
    static std::atomic<size_t> _counter;
    static WSADATA _wsadata;
};
#else /* if !defined(_WIN32) */
#   include <errno.h>
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <netdb.h>
#   include <fcntl.h>
#   include <poll.h>
#   include <arpa/inet.h>
#   include <unistd.h>

#   define closesocket     close
#   define INVALID_SOCKET  (-1)

typedef int Socket;
typedef uint32_t socklen_t;

struct WsaInitialiser {};
#endif /* !defined(_WIN32) */

#endif /* !NET_HPP */
