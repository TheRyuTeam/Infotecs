#include <Library/Endpoint.h>
#include <stdexcept>
#include <cstring>
#include <netinet/ip.h>
#include <arpa/inet.h>

namespace Library
{

Endpoint::Endpoint()
    : Endpoint{ "0.0.0.0", 0 }
{
}

Endpoint::Endpoint(const void* saddr, uint32_t saddrlen)
    : _address{}
{
    if (saddrlen != sizeof(sockaddr_in) && saddrlen != sizeof(sockaddr_in6)) {
        throw std::runtime_error("Invalid saddr length");
    }
    memcpy(&_address, saddr, saddrlen);
    if (_address.family != AF_INET && _address.family != AF_INET6) {
        throw std::runtime_error("Invalid address family");
    }
}

Endpoint::Endpoint(const char* address, uint16_t port)
    : _address{}
{
    int rc = inet_pton(AF_INET, address, &_address.v4.sin_addr);
    if (rc != 0) {
        _address.v4.sin_family = AF_INET;
        _address.v4.sin_port = htons(port);
        return;
    }

    rc = inet_pton(AF_INET6, address, &_address.v6.sin6_addr);
    if (rc != 0) {
        _address.v6.sin6_family = AF_INET6;
        _address.v6.sin6_port = htons(port);
        return;
    }

    throw std::runtime_error("Invalid ip address");
}

std::string Endpoint::toString() const
{
    char buffer[INET6_ADDRSTRLEN]{};
    if (af() == AF_INET) {
        inet_ntop(AF_INET, &_address.v4.sin_addr, buffer, INET6_ADDRSTRLEN);
    } else {
        inet_ntop(AF_INET6, &_address.v6.sin6_addr, buffer, INET6_ADDRSTRLEN);
    }
    return std::string(buffer) + ":" + std::to_string(port());
}

uint16_t Endpoint::af() const noexcept
{
    return _address.family;
}

uint16_t Endpoint::port() const noexcept
{
    return af() == AF_INET ? htons(_address.v4.sin_port) : htons(_address.v6.sin6_port);
}

const void* Endpoint::saddr() const noexcept
{
    return reinterpret_cast<const sockaddr*>(&_address);
}

uint32_t Endpoint::saddrlen() const noexcept
{
    return af() == AF_INET ? sizeof(sockaddr_in) : sizeof(sockaddr_in6);
}

} // namespace Library
