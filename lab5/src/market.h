#pragma once

#include <condition_variable>

#include "constants.h"
#include "log.h"
#include "seller.h"

class Market {
public:
    Market();
    void getInQueue(int productId, std::condition_variable* processedHandler);
    void initSellers();
    ~Market();

private:
    Seller** sellers_ = nullptr;
    bool stop_ = false;
};