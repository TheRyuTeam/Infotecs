#include "Client.h"
#include <Library/Library.h>
#include <algorithm>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>

Client::Client()
    : _working{ false }
    , _ready{ false }
    , _mutex{}
    , _condVar{}
    , _sharedBuffer{}
    , _senderThread{}
    , _socket{}
    , _endpoint{}
{
}

Client::~Client()
{
    stop();
}

void Client::run(const Library::Endpoint& endpoint)
{
    _endpoint = endpoint;
    _working = true;
    std::cout << "Client started. Server address: " << endpoint << '\n';

    _senderThread = std::thread(&Client::senderThreadFunction, this);
    userInputFunc();
}

void Client::stop()
{
    _working = false;
    if (_senderThread.joinable()) {
        _senderThread.join();
    }
}

void Client::userInputFunc()
{
    while (_working) {
        std::string input;
        std::getline(std::cin, input);
        if (input.empty() || input.size() > 64 || !std::all_of(input.begin(), input.end(), isdigit)) {
            std::cout << "Invalid input\n";
            continue;
        }

        auto sortedKbString = Library::sortNumStrAndInsertKB(input);

        std::lock_guard<std::mutex> ld(_mutex);
        _sharedBuffer = std::move(sortedKbString);
        _ready = true;
        _condVar.notify_one();
    }
}

void Client::senderThreadFunction()
{
    while (_working) {
        std::unique_lock<std::mutex> ul(_mutex);
        _condVar.wait(ul, [this] { return _ready; });

        _ready = false;
        std::string localBuffer = std::move(_sharedBuffer);
        std::cout << localBuffer << '\n';

        ul.unlock();

        auto digitSum = Library::digitsSum(localBuffer);
        _socket.sendTo(_endpoint, reinterpret_cast<const char*>(&digitSum), sizeof(digitSum));
    }
}
