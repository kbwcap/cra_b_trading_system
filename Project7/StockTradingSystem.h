#pragma once
#include "StockBrokerInterface.h"
#include <memory>

class StockTradingSystem {
private:
    bool isKiwer;
    StockBrokerInterface* broker = nullptr;

public:
    void selectStockBroker(bool isKiwer);
    void setBrokerForTest(StockBrokerInterface* mock); // 테스트용
    bool login(const std::string& id, const std::string& pass);
};
