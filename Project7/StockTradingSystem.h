#pragma once
#include "StockBroker.cpp"

class StockTradingSystem {
public:
	void selectStockBroker(bool isKiwer) {
		if (isKiwer) {
			stockBrocker = new MockKiwerStock(&kiwerApi);
		}
		else {
			stockBrocker = new MockNemoStock(&nemoApi);
		}
	}

	void setStockBroker(StockBroker* broker) {
		stockBrocker = broker;
	}

	StockBroker* getStockBroker() const {
		return stockBrocker;
	}
private:
	StockBroker* stockBrocker;
	KiwerAPI kiwerApi;
	NemoAPI nemoApi;
};

