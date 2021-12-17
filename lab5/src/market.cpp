#include "market.h"

void Market::getInQueue(int productId, std::condition_variable* processedHandler) {
    int current_seller_index = productId / amount_of_products;
    PrintThread{} << "[DEBUG] thread #" << std::this_thread::get_id() << " (client): "
                  << "added self to queue #" << current_seller_index << '\n';
    Seller* current_seller = sellers_[current_seller_index];
    current_seller->queueAdd(processedHandler);
}

void Market::initSellers() {
    sellers_ = new Seller*[amount_of_sellers];
    for (int i = 0; i < amount_of_sellers; ++i) {
        auto seller = new Seller(&stop_);
        sellers_[i] = seller;
        std::thread ts(&Seller::emulate, seller);
        PrintThread{} << "[DEBUG] thread #" << std::this_thread::get_id() << " (main): "
                      << "detached new seller thread #" << ts.get_id() << '\n';
        ts.detach();
    }
}

Market::Market() {
    initSellers();
}

Market::~Market() {
    PrintThread{} << "[DEBUG] thread #" << std::this_thread::get_id() << " (main): "
                  << "deleting market...\n";
    stop_ = true;
    while (Stop::getInstance()->sellersStopped() != amount_of_sellers) {
        PrintThread{} << "[DEBUG] thread #" << std::this_thread::get_id() << " (main): "
                      << "not all sellers stopped yet...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    for (int i = 0; i < amount_of_sellers; ++i) {
        delete sellers_[i];
    }
    delete[] sellers_;
    PrintThread{} << "[DEBUG] thread #" << std::this_thread::get_id() << " (main): "
                  << "all sellers stopped!\n";
}