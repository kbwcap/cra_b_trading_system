#pragma once
#include "StockBrokerInterface.h"
#include <gmock/gmock.h>

class MockNemoStock : public StockBrokerInterface {
public:
    MOCK_METHOD(bool, login, (const std::string& id, const std::string& pass), (override));
};
