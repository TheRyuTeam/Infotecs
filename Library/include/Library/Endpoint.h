#pragma once
#include <Library/LibraryExports.h>
#include <string>
#include <cstdint>
#include <netinet/in.h>
#include <ostream>

namespace Library
{

class LIBRARY_API Endpoint
{
public:
    Endpoint();
    Endpoint(const void* saddr, uint32_t saddrlen);
    Endpoint(const char* address, uint16_t port);
    Endpoint(const Endpoint& other) = default;
    Endpoint(Endpoint&& other) noexcept = default;
    ~Endpoint() = default;

    Endpoint& operator=(const Endpoint& other) = default;
    Endpoint& operator=(Endpoint&& other) noexcept = default;

    std::string toString() const;

    uint16_t af() const noexcept;
    uint16_t port() const noexcept;

    const void* saddr() const noexcept;
    uint32_t saddrlen() const noexcept;

private:
    union {
        unsigned short family;
        sockaddr_in v4;
        sockaddr_in6 v6;
    } _address;
};

inline std::ostream& operator<<(std::ostream& os, const Endpoint& endpoint)
{
    return os << endpoint.toString();
}

} // namespace Library
