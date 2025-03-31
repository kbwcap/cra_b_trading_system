#pragma once
#include "StockBrokerInterface.h"

class NemoStock : public StockBrokerInterface {
public:
    bool login(const std::string& id, const std::string& pass);
};
