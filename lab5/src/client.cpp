#include "client.h"

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

Client::Client(Market* market) {
    market_ = market;
}

Client::~Client() {
    delete list_;
    // market must be removed outside
}

void Client::emulate() {
    PrintThread{} << "[DEBUG] thread #" << std::this_thread::get_id()
                  << " (client): started emulation, need to buy " << list_->size() << " products\n";
    while (current_product_ < list_->size()) {
        market_->getInQueue(list_->products()[current_product_], &cv);

        // Wait until seller notify client's cv
        {
            std::unique_lock<std::mutex> lk(mutex);
            cv.wait(lk);
        }
        ++current_product_;
    }
    PrintThread{} << "[DEBUG] thread #" << std::this_thread::get_id()
                  << " (client): stopped emulation\n";
}
