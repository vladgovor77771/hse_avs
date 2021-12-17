#pragma once
#include <condition_variable>
#include <mutex>
#include <thread>

#include "constants.h"
#include "iostream"
#include "log.h"
#include "market.h"
#include "random"
#include "time.h"

class ShoppingList {
public:
    const int* products();
    const int size();
    static ShoppingList* random();
    ~ShoppingList();

private:
    int* products_;
    int size_;
    ShoppingList();
};

class Client {
public:
    Client(Market* market);
    ~Client();
    std::mutex mutex;
    std::condition_variable cv;
    void emulate();

private:
    ShoppingList* list_ = ShoppingList::random();
    int current_product_ = 0;
    Market* market_;
};