#ifndef SELLER_CPP
#define SELLER_CPP

#include "seller.h"

#include "constants.h"
#include "iostream"
#include "random"
#include "shared_resources.h"
#include "time.h"

Seller::Seller() {
}

void Seller::queueAdd(Client* client) {
    std::unique_lock<std::mutex> lk(queue_mutex_);
    queue_.push(client);
    lk.unlock();         // unlock before notificiation to minimize mutex con
    cond_.notify_one();  // notify one waiting thread
}

const size_t Seller::queueSize() {
    std::unique_lock<std::mutex> lk(queue_mutex_);
    size_t size = queue_.size();
    lk.unlock();
    return size;
}

void Seller::emulate() {
    srand(time(NULL));
    while (!stop) {
        Client* current_client;
        {
            std::unique_lock<std::mutex> mlock(queue_mutex_);
            if (queue_.empty()) {
                cond_.wait_for(mlock, std::chrono::seconds(5));
            }
            if (queue_.empty()) {
                continue;
            }
            current_client = queue_.front();
            queue_.pop();
        }
        int sleep_time = sleep_from + std::rand() % (sleep_to - sleep_from);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        current_client->processed = true;
        current_client->cv.notify_one();
        std::cout << "Seller thread " << std::this_thread::get_id() << " processed client\n";
    }
}

#endif