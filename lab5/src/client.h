#ifndef CLIENT_H
#define CLIENT_H

#include <condition_variable>
#include <mutex>
#include <thread>

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
    Client();
    ~Client();
    std::mutex mutex;
    std::condition_variable cv;
    bool processed = false;
    void emulate();

private:
    ShoppingList* list_ = ShoppingList::random();
    int current_product_ = 0;
};

#endif