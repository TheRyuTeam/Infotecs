#pragma once
#include <Library/Endpoint.h>

namespace Library
{

class LIBRARY_API UDPSocket
{
public:
    UDPSocket();
    UDPSocket(const UDPSocket&) = delete;
    UDPSocket(UDPSocket&& other) noexcept;
    virtual ~UDPSocket();

    UDPSocket& operator=(const UDPSocket&) = delete;
    UDPSocket& operator=(UDPSocket&& other) noexcept;

    void bind(const Endpoint& endpoint);

    ssize_t sendTo(const Endpoint& endpoint, const char* data, size_t size);

    ssize_t recvFrom(char* data, size_t size);
    ssize_t recvFrom(char* data, size_t size, Endpoint& endpoint);

    void close();

private:
    void init(int af = AF_INET);

    friend void swap(UDPSocket& a, UDPSocket& b);

private:
    int _fd;
};

void swap(UDPSocket& a, UDPSocket& b);

} // namespace Library
