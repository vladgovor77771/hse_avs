#include "seller.h"

Stop::Stop() {
}

Stop* Stop::getInstance() {
    if (!stop_) {
        stop_ = new Stop();
    }
    return stop_;
}

int Stop::sellersStopped() {
    return sellers_stopped_;
}

void Stop::inc() {
    ++sellers_stopped_;
}

Stop* Stop::stop_ = 0;

Seller::Seller(bool* stop) {
    stop_ = stop;
}

void Seller::queueAdd(std::condition_variable* clientProcessed) {
    std::unique_lock<std::mutex> lk(queue_mutex_);
    queue_.push(clientProcessed);
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
    PrintThread{} << " (seller): started emulation\n";

    srand(time(NULL));
    while (!queue_.empty() || !*stop_) {
        std::condition_variable* current_client_cv;
        {
            std::unique_lock<std::mutex> mlock(queue_mutex_);
            if (queue_.empty()) {
                PrintThread{} << " (seller): queue empty, waiting for clients\n";
                cond_.wait_for(mlock, std::chrono::seconds(5));
            }
            if (queue_.empty()) {
                continue;
            }
            current_client_cv = queue_.front();
            queue_.pop();
        }
        int sleep_time = sleep_from + std::rand() % (sleep_to - sleep_from);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        current_client_cv->notify_one();

        PrintThread{} << " (seller): processed client\n";
    }
    PrintThread{} << " (seller): stopped emulation\n";
    Stop::getInstance()->inc();
}
