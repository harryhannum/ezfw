#include "detail/net.hpp"

#if defined(_WIN32)

std::atomic<size_t> WsaInitialiser::_counter;
WSADATA WsaInitialiser::_wsadata;

#endif
