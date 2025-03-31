#pragma once
#include <string>

class StockBrokerInterface {
public:
    virtual ~StockBrokerInterface() = default;

    virtual bool login(const std::string& id, const std::string& pass) = 0;
};
