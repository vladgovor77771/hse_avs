#include <chrono>
#include <iostream>
#include <thread>

#include "client.h"
#include "log.h"
#include "market.h"

Client** initClients(Market* market) {
    Client** res = new Client*[amount_of_clients];
    for (int i = 0; i < amount_of_clients; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        auto client = new Client(market);
        res[i] = client;
        std::thread tc(&Client::emulate, client);
        tc.detach();
    }
    return res;
}

void deleteClients(Client** clients) {
    for (int i = 0; i < amount_of_clients; ++i) {
        delete clients[i];
    }
    delete[] clients;
}

int main() {
    Market* market = new Market();
    PrintThread{} << "[DEBUG] thread #" << std::this_thread::get_id() << " (main): "
                  << "created market\n";

    auto clients = initClients(market);

    std::this_thread::sleep_for(std::chrono::seconds(main_sleep_seconds));

    delete market;
    deleteClients(clients);

    return 0;
}