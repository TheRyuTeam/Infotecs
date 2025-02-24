#include "Client.h"

int main()
{
    const Library::Endpoint endpoint("127.0.0.1", 46789);

    Client client;
    client.run(endpoint);
}
