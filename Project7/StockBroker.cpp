#pragma once
#include "KiwerAPI.h"
#include "NemoAPI.h"
#include "gmock/gmock.h"
#include <string>
using std::string;

struct StockBroker{
public:
    virtual void login(string ID, string pass) = 0;
    virtual void buy(string stockCode, int count, int price) = 0;
    virtual void sell(string stockCode, int count, int price) = 0;
    virtual int currentPrice(string stockCode) = 0;
    virtual int getMarketPrice(string stockCode, int minute) = 0;
};

class MockKiwerStock : public StockBroker {
public:
    MockKiwerStock(KiwerAPI* kiwiApi) : _kiwiApi{ kiwiApi } {}
    void login(string ID, string pass) override {
        _kiwiApi->login(ID, pass);
    }
    void buy(string stockCode, int count, int price) override {
        _kiwiApi->buy(stockCode, count, price);
    }
    void sell(string stockCode, int count, int price) override {
        _kiwiApi->sell(stockCode, count, price);
    }
    int currentPrice(string stockCode) override {
        return _kiwiApi->currentPrice(stockCode);
    }
    int getMarketPrice(string stockCode, int minute) override {
        return  -1; // not support
    }
private:
    KiwerAPI* _kiwiApi;
};

class MockNemoStock : public StockBroker {
public:
    MockNemoStock(NemoAPI* nemoApi) : _nemoApi{ nemoApi } {}
    void login(string ID, string pass) override {
        _nemoApi->certification(ID, pass);
    }
    void buy(string stockCode, int count, int price) override {
        _nemoApi->purchasingStock(stockCode, price, count);
    }
    void sell(string stockCode, int count, int price) override {
        _nemoApi->sellingStock(stockCode, price, count);
    }
    int currentPrice(string stockCode) override {
        return  -1; // not support
    }
    int getMarketPrice(string stockCode, int minute) override {
        return _nemoApi->getMarketPrice(stockCode, minute);
    }
private:
    NemoAPI* _nemoApi;
};

class MockDriver : public StockBroker {
public:
    MOCK_METHOD(void, login, (string ID, string password), (override));
    MOCK_METHOD(void, buy, (string stockCode, int count, int price), (override));
    MOCK_METHOD(void, sell, (string stockCode, int count, int price), (override));
    MOCK_METHOD(int, currentPrice, (string stockCode), (override));
    MOCK_METHOD(int, getMarketPrice, (string stockCode, int minute), (override));
};
