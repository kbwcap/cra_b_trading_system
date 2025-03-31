#include "StockTradingSystem.h"
#include "NemoStock.h"

void StockTradingSystem::selectStockBroker(bool isKiwer) {
    isKiwer = isKiwer;
}

// �׽�Ʈ���� Mock ��ü�� ���� ������ �� ���
void StockTradingSystem::setBrokerForTest(StockBrokerInterface* mock) {
    broker = mock; 
}

bool StockTradingSystem::login(const std::string& id, const std::string& pass) {
    return broker && broker->login(id, pass);
}
