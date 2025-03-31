#include "gmock/gmock.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "NemoAPI.h"
#include "KiwerAPI.h"
#include "StockTradingSystem.h"
#include "MockNemoStock.h"

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

class StockTradingSystemTest : public Test {
protected:
    StockTradingSystem system;
};

// Nemo 증권사 테스트
TEST_F(StockTradingSystemTest, TestNemoLogin) {
    MockNemoStock mockNemo;
    StockTradingSystem system;

    system.setBrokerForTest(&mockNemo);  // 테스트용 mock 직접 설정

    EXPECT_CALL(mockNemo, login("박화영", "1234"))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_TRUE(system.login("박화영", "1234"));  // 인자 일치해야 함
}


int main() {
	InitGoogleMock();
	return RUN_ALL_TESTS();
}