#include <Library/UDPSocket.h>
#include <stdexcept>
#include <utility>
#include <unistd.h>
#include <cstring>

namespace Library
{

UDPSocket::UDPSocket()
    : _fd{ -1 }
{
}

UDPSocket::UDPSocket(UDPSocket&& other) noexcept
    : _fd{ -1 }
{
    swap(*this, other);
}

UDPSocket::~UDPSocket()
{
    close();
}

UDPSocket& UDPSocket::operator=(UDPSocket&& other) noexcept
{
    swap(*this, other);
    return *this;
}

void UDPSocket::bind(const Endpoint& endpoint)
{
    init(endpoint.af());
    if (::bind(_fd, reinterpret_cast<const sockaddr*>(endpoint.saddr()), endpoint.saddrlen()) != 0) {
        throw std::runtime_error("Can not bind udp socket to address " + endpoint.toString() + '\t' + strerror(errno));
    }
}

ssize_t UDPSocket::sendTo(const Endpoint& endpoint, const char* data, size_t size)
{
    init();
    return ::sendto(_fd, data, size, 0, reinterpret_cast<const sockaddr*>(endpoint.saddr()), endpoint.saddrlen());
}

ssize_t UDPSocket::recvFrom(char* data, size_t size)
{
    return ::recvfrom(_fd, data, size, 0, nullptr, nullptr);
}

ssize_t UDPSocket::recvFrom(char* data, size_t size, Endpoint& endpoint)
{
    sockaddr saddr;
    uint32_t saddrlen = sizeof(saddr);
    ssize_t rc = ::recvfrom(_fd, data, size, 0, &saddr, &saddrlen);
    if (rc > 0) {
        endpoint = Endpoint(reinterpret_cast<const void*>(&saddr), saddrlen);
    }
    return rc;
}

void UDPSocket::close()
{
    if (_fd != -1) {
        ::close(_fd);
        _fd = -1;
    }
}

void UDPSocket::init(int af)
{
    if (_fd == -1) {
        _fd = ::socket(af, SOCK_DGRAM, 0);
        if (_fd == -1) {
            throw std::runtime_error("Can not create socket");
        }
    }
}

void swap(UDPSocket& a, UDPSocket& b)
{
    std::swap(a._fd, b._fd);
}

} // namespace Library
