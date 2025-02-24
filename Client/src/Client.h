#pragma once
#include <Library/UDPSocket.h>
#include <atomic>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <string>

class Client
{
public:
    Client();
    ~Client();

    void run(const Library::Endpoint& endpoint);
    void stop();

private:
    void userInputFunc();
    void senderThreadFunction();

private:
    std::atomic<bool> _working;
    bool _ready;
    std::mutex _mutex;
    std::condition_variable _condVar;
    std::string _sharedBuffer;

    std::thread _senderThread;
    Library::UDPSocket _socket;
    Library::Endpoint _endpoint;
};
