#include <Library/UDPSocket.h>
#include <Library/Library.h>
#include <iostream>

int main()
{
    const Library::Endpoint endpoint("127.0.0.1", 46789);

    Library::UDPSocket socket;
    socket.bind(endpoint);

    std::cout << "Server started at " << endpoint << '\n';

    while (true) {
        Library::digits_sum_t digitSum = 0;
        auto rc = socket.recvFrom(reinterpret_cast<char*>(&digitSum), sizeof(digitSum));
        if (rc == sizeof(digitSum)) {
            if (Library::analize(digitSum)) {
                std::cout << "Valid data received\n";
            } else {
                std::cout << "Error: invalid data received\n";
            }
        }
    }

    return 0;
}
