#pragma once
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

#include "constants.h"
#include "log.h"
#include "time.h"

class Seller {
public:
    explicit Seller(bool *stop);
    void queueAdd(std::condition_variable *processedHandler);
    const size_t queueSize();
    void emulate();

private:
    bool *stop_;
    std::mutex queue_mutex_;
    std::queue<std::condition_variable *> queue_;
    std::condition_variable cond_;
};

class Stop {
private:
    int sellers_stopped_ = 0;
    static Stop *stop_;
    Stop();

public:
    static Stop *getInstance();
    int sellersStopped();
    void inc();
};