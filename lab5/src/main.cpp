#include <chrono>
#include <iostream>
#include <thread>

#include "client.h"
#include "constants.h"
#include "seller.h"
#include "shared_resources.h"

void initSellers() {
    sellers = new Seller*[amount_of_sellers];
    for (int i = 0; i < amount_of_sellers; ++i) {
        auto seller = new Seller();
        sellers[i] = seller;
        std::thread ts(&Seller::emulate, seller);
    }
}

void clearSellers() {
    while (sellers_stopped != amount_of_sellers) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    for (int i = 0; i < amount_of_sellers; ++i) {
        delete sellers[i];
    }
    delete[] sellers;
}

int main() {
    initSellers();
    auto client = new Client();
    std::thread tc(&Client::emulate, client);
    tc.join();
    stop = true;
    clearSellers();
    delete client;
    return 0;
}