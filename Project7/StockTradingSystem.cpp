#include "StockTradingSystem.h"
#include "NemoStock.h"

void StockTradingSystem::selectStockBroker(bool isKiwer) {
    isKiwer = isKiwer;
}

// 테스트에서 Mock 객체를 직접 주입할 때 사용
void StockTradingSystem::setBrokerForTest(StockBrokerInterface* mock) {
    broker = mock; 
}

bool StockTradingSystem::login(const std::string& id, const std::string& pass) {
    return broker && broker->login(id, pass);
}
