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



int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}