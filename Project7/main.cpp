#include "gmock/gmock.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "NemoAPI.h"
#include "KiwerAPI.h"
#include "StockTradingSystem.h"

using namespace testing;
using namespace std;




/**
* stockTradingSystem : 핵심 클래스 
* - selectStockBroker(): 어떤 증권사를 사용할지 선택
*        void selectStockBroker(bool isKiwer) 
*             true -> kiwer 선택
*             false : meno 선택
* - login(id, pass): 로그인
* - buy(stockCode, quantity, price): 주식을 매수
* - sell(stockCode, quantity, price): 주식을 매도
* - getPrice(stockCode): 주식의 현재가를 확인
*/

/**
* StockBrokerInterface : KiwerStock 과 NemoStock 인터페이스 
* - login(id, pass): 로그인
* - buy(stockCode, quantity, price): 주식을 매수
* - sell(stockCode, quantity, price): 주식을 매도
* - getPrice(stockCode): 주식의 현재가를 확인
*/

/*

+-------------------------------------------------- +
| StockTradingSystem                                |
+-------------------------------------------------- +
| +selectStockBroker(isKiwer : bool)                |
| +login(id : string, pass : string) : bool         |
| +buy(stockCode : string, quantity : int, price : double) : bool |
| +sell(stockCode : string, quantity : int, price : double) : bool |
| +getPrice(stockCode : string) : double            |
+-------------------------------------------------- +
             |                          |
             |                          |
             v                          v
+ ---------------------------+    +-------------------------- - +
| StockBrokerInterface      |     |      StockBrokerInterface |
+---------------------------+     +-------------------------- - +
| +login(id, pass)          |    | +login(id, pass) : bool    |
| +buy(stockCode, quantity, price)| +buy(stockCode, quantity, price) : bool |
| +sell(stockCode, quantity, price) : bool | +sell(stockCode, quantity, price) : bool |
| +getPrice(stockCode) : double | +getPrice(stockCode) : double |
+---------------------------++-------------------------- - +
^                                 ^
|                                 |
+--------------------+       +--------------------+
| KiwerStock         |       |     NemoStock      |
+--------------------+       +--------------------+
| +login(id, pass)   |       | +login(id, pass)   |
| +buy(...)          |       | +buy(...)          |
| +sell(...)         |       | +sell(...)         |
| +getPrice(...)     |       | +getPrice(...)     |
+--------------------+       +--------------------+
        ^                                 ^
        |                                 |
+---------------------------+      +-------------------------- - +
| MockKiwerStock            |      |   MockNemoStock |
+---------------------------+      +-------------------------- - +
| +login(id, pass) : bool    |     | +login(id, pass) : bool    |
| +buy(...) : bool           |     | +buy(...) : bool           |
| +sell(...) : bool          |     | +sell(...) : bool          |
| +getPrice(...) : double    |     | +getPrice(...) : double |
+---------------------------+      +-------------------------- - +

*/

class StockTradingSystemTest : public ::testing::Test {
protected:
    StockTradingSystem system;
    
};




// Kiwer 증권사 테스트
TEST_F(StockTradingSystemTest, TestKiwerLogin) {
    //MockKiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    //EXPECT_CALL(mockKiwer, login("김윤제", "1245"))
    //    .WillOnce(::testing::Return(true));  // 성공적으로 로그인

    //EXPECT_TRUE(system.login("김윤제", "1245"));
}

TEST_F(StockTradingSystemTest, TestKiwerBuy) {
    //MockKiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    //EXPECT_CALL(mockKiwer, buy("삼성전자", 10, 58000.0))
    //    .WillOnce(::testing::Return(true));  // 매수 성공

    //EXPECT_TRUE(system.buy("삼성전자", 10, 58000.0));
}

TEST_F(StockTradingSystemTest, TestKiwerGetPrice) {
    //MockKiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    //EXPECT_CALL(mockKiwer, getPrice("삼성전자"))
    //    .WillOnce(::testing::Return(58200.0));  // 현재가 반환

    //EXPECT_EQ(system.getPrice("AAPL"), 58200.0);
}



// Nemo 증권사 테스트
TEST_F(StockTradingSystemTest, TestNemoLogin) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    //EXPECT_CALL(mockNemo, login("박화영", "1234"))
    //    .WillOnce(::testing::Return(true));

    //EXPECT_TRUE(system.login("박화영", "1245"));
}

TEST_F(StockTradingSystemTest, TestNemoBuy) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    //EXPECT_CALL(mockNemo, buy("삼성전자", 10, 58000.0))
    //    .WillOnce(::testing::Return(true));  // 매수 성공

    //EXPECT_TRUE(system.buy("삼성전자", 10, 58000.0));
}

TEST_F(StockTradingSystemTest, TestNemoGetPrice) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    //EXPECT_CALL(mockNemo, getPrice("삼성전자"))
    //    .WillOnce(::testing::Return(58200.0));  // 현재가 반환

    //EXPECT_EQ(system.getPrice("AAPL"), 58200.0);
}

// 로그인 로직이 실패한 경우 예외 던짐
// 로그인 정보가 유효하지 않은 경우.
TEST_F(StockTradingSystemTest, TestKiwerLogin_Failure) {
    //KiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    //EXPECT_THROW(mockKiwer.login("", ""), LoginException);
}

// 매수수량 및 단가가 음수인 경우 예외처리
// 종목 code가 비어 있는 경우 예외처리
TEST_F(StockTradingSystemTest, TestKiwerBuy_Failure) {
    //KiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    //EXPECT_THROW(mockKiwer.buy("삼성전자", -10, 58000.0), BuyException);
}

// 매도수량 및 단가가 음수인 경우 예외처리
// 종목 code가 비어 있는 경우 예외처리
TEST_F(StockTradingSystemTest, TestKiwerSell_Failure) {
    //KiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    //EXPECT_THROW(mockKiwer.sell("삼성전자", 58000.0, -100), SellException);
}


// 종목 code가 비어 있는 경우 예외 처리 
TEST_F(StockTradingSystemTest, TestKiwerGetPrice_Failure) {
    //KiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    //EXPECT_THROW(mockKiwer.getPrice(""), PriceException);
}



// 로그인 로직이 실패한 경우 예외 던짐
// 로그인 정보가 유효하지 않은 경우.
TEST_F(StockTradingSystemTest, TestNemoLogin_Failure) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    //EXPECT_THROW(mockNemo.login("", ""), LoginException);
}

// 매수수량 및 단가가 음수인 경우 예외처리
// 종목 code가 비어 있는 경우 예외처리
TEST_F(StockTradingSystemTest, TestNemoBuy_Failure) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    //EXPECT_THROW(mockNemo.buy("삼성전자", -10, 58000.0), BuyException);
}

// 매도수량 및 단가가 음수인 경우 예외처리
// 종목 code가 비어 있는 경우 예외처리
TEST_F(StockTradingSystemTest, TestNemoSell_Failure) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    //EXPECT_THROW(mockNemo.sell("삼성전자", 58000.0, -100), SellException);
}


// 종목 code가 비어 있는 경우 예외 처리 
TEST_F(StockTradingSystemTest, TestNemoGetPrice_Failure) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    //EXPECT_THROW(mockNemo.getPrice(""), PriceException);
}

// 가격이 3연속계속 상승하는 것을 확인하면 매수 진행한다. 
TEST_F(StockTradingSystemTest, TestKiwerBuyNiceTiming_Success) {
    //KiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    // 가격이 58000, 58100, 58200 으로 계속 상승한다는 가정
    //EXPECT_CALL(mockKiwer, getPrice("삼성전자"))
    //    .WillOnce(::testing::Return(58000.0))
    //    .WillOnce(::testing::Return(58100.0))
    //    .WillOnce(::testing::Return(58200.0));

    //EXPECT_CALL(mockKiwer, buy("삼성전자", 10, 58200.0))
    //    .WillOnce(::testing::Return(true));

    //EXPECT_TRUE(system.buyNiceTiming("삼성전자", 582000));
}

// 가격이 3연속 하락하는 것을 확인하면 매도 진행한다. 
TEST_F(StockTradingSystemTest, TestKiwerSellNiceTiming_Success) {
    //KiwerStock mockKiwer;
    system.selectStockBroker(true);  // Kiwer 선택

    // 가격이 58200, 58100, 58000 으로 하락
    //EXPECT_CALL(mockKiwer, getPrice("삼성전자"))
    //    .WillOnce(::testing::Return(58200.0))
    //    .WillOnce(::testing::Return(58100.0))
    //    .WillOnce(::testing::Return(58000.0));

    //EXPECT_CALL(mockKiwer, sell("삼성전자", 10, 58000.0))
    //    .WillOnce(::testing::Return(true));

    //EXPECT_TRUE(system.sellNiceTiming("삼성전자", 10));
}


// 가격이 3연속계속 상승하는 것을 확인하면 매수 진행한다. 
TEST_F(StockTradingSystemTest, TestNemoBuyNiceTiming_Success) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    // 가격이 58000, 58100, 58200 으로 계속 상승한다는 가정
    //EXPECT_CALL(mockNemo, getPrice("삼성전자"))
    //    .WillOnce(::testing::Return(58000.0))
    //    .WillOnce(::testing::Return(58100.0))
    //    .WillOnce(::testing::Return(58200.0));

    //EXPECT_CALL(mockNemo, buy("삼성전자", 10, 58200.0))
    //    .WillOnce(::testing::Return(true));

    //EXPECT_TRUE(system.buyNiceTiming("삼성전자", 582000));
}

// 가격이 3연속 하락하는 것을 확인하면 매도 진행한다. 
TEST_F(StockTradingSystemTest, TestNemoSellNiceTiming_Success) {
    //MockNemoStock mockNemo;
    system.selectStockBroker(false);  // Nemo 선택

    // 가격이 58200, 58100, 58000 으로 하락
    //EXPECT_CALL(mockNemo, getPrice("삼성전자"))
    //    .WillOnce(::testing::Return(58200.0))
    //    .WillOnce(::testing::Return(58100.0))
    //    .WillOnce(::testing::Return(58000.0));

    //EXPECT_CALL(mockNemo, sell("삼성전자", 10, 58000.0))
    //    .WillOnce(::testing::Return(true));

    //EXPECT_TRUE(system.sellNiceTiming("삼성전자", 10));
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}