#ifndef SELLER_H
#define SELLER_H

#include <chrono>

#include "client.h"
#include "mutex"
#include "queue"

class Seller {
public:
    Seller();
    void queueAdd(Client* client);
    const size_t queueSize();
    void emulate();

private:
    std::mutex queue_mutex_;
    std::queue<Client*> queue_;
    std::condition_variable cond_;
};

#endif