#ifndef CLIENT_CPP
#define CLIENT_CPP

#include "client.h"

#include "constants.h"
#include "iostream"
#include "random"
#include "seller.h"
#include "shared_resources.h"
#include "time.h"

ShoppingList::ShoppingList() {
    srand(time(NULL));
    size_ = 1 + std::rand() % (amount_of_sellers * amount_of_products);
    products_ = new int[size_];
    for (int i = 0; i < size_; ++i) {
        products_[i] = std::rand() % (amount_of_sellers * amount_of_products);
    }
}

ShoppingList::~ShoppingList() {
    delete[] products_;
}

const int* ShoppingList::products() {
    return products_;
}

const int ShoppingList::size() {
    return size_;
}

ShoppingList* ShoppingList::random() {
    return new ShoppingList();
}

Client::Client() {
}

Client::~Client() {
    delete list_;
}

void Client::emulate() {
    if (!sellers) {
        std::cout << "Sellers not initialized\n";
        return;
    }
    while (current_product_ < list_->size()) {
        int current_seller_index = list_->products()[current_product_] / amount_of_products;
        Seller* current_seller = sellers[current_seller_index];
        current_seller->queueAdd(this);
        std::cout << "Client thread " << std::this_thread::get_id() << " added self to queue "
                  << current_seller_index << '\n';
        // Wait until seller change processed on self
        {
            std::unique_lock<std::mutex> lk(mutex);
            cv.wait(lk, [this] { return !processed; });
        }
        ++current_product_;
    }
}

#endif