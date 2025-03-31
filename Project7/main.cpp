#include <algorithm>
#include <stdexcept>
#include <vector>

#include "KiwerAPI.h"
#include "NemoAPI.h"
#include "StockTradingSystem.h"
#include "gmock/gmock.h"

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
| +sell(stockCode, quantity, price) : bool | +sell(stockCode, quantity, price) :
bool | | +getPrice(stockCode) : double | +getPrice(stockCode) : double |
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

#ifdef Release  // Kiwer 증권사 테스트 (Real)
class RealKiwerFixture : public StockTradingSystemTest {
 public:
  KiwerAPI Kiwer;
  stringstream buffer;
  streambuf* oldCout;
  RealKiwerFixture() {
    system.selectStockBroker(true);  // Kiwer 선택
    oldCout = cout.rdbuf(buffer.rdbuf());
  }
  ~RealKiwerFixture() { cout.rdbuf(oldCout); }
};

TEST_F(RealKiwerFixture, RealKiwerLogin) {
  string ID = "kjo7811";
  string PW = "1245";

  Kiwer.login(ID, PW);

  EXPECT_EQ(buffer.str(), ID + " login success\n");
}

TEST_F(RealKiwerFixture, RealKiwerBuy) {
  string stockCode = "NVIDIA";
  int count = 10;
  int price = 10000;

  Kiwer.buy(stockCode, count, price);

  EXPECT_EQ(buffer.str(), stockCode + " : Buy stock ( " + to_string(price) +
                              " * " + to_string(count) + ")\n");
}

TEST_F(RealKiwerFixture, RealKiwerSell) {
  string stockCode = "NVIDIA";
  int count = 10;
  int price = 10000;

  Kiwer.sell(stockCode, count, price);

  EXPECT_EQ(buffer.str(), stockCode + " : Sell stock ( " + to_string(price) +
                              " * " + to_string(count) + ")\n");
}
#endif  // Release

// Kiwer 증권사 테스트 (Mock)
class MockKiwerStock : public IKiwerAPI {
 public:
  MOCK_METHOD(void, login, (string ID, string password), (override));
  MOCK_METHOD(void, buy, (string stockCode, int count, int price), (override));
  MOCK_METHOD(void, sell, (string stockCode, int count, int price), (override));
  MOCK_METHOD(int, currentPrice, (string stockCode), (override));
};

class MockKiwerFixture : public StockTradingSystemTest {
 public:
  MockKiwerStock mockKiwer;
  std::stringstream buffer;
  std::streambuf* oldCout;
  MockKiwerFixture() {
    system.selectStockBroker(true);  // Kiwer 선택
    oldCout = std::cout.rdbuf(buffer.rdbuf());
  }
  ~MockKiwerFixture() { std::cout.rdbuf(oldCout); }
};

TEST_F(MockKiwerFixture, MockKiwerLogin) {
  string ID = "kjo7811";
  string PW = "1245";

  ON_CALL(mockKiwer, login(_, _)).WillByDefault([](string ID, string password) {
    cout << ID << " login success\n";
  });

  EXPECT_CALL(mockKiwer, login(ID, PW)).Times(1);

  mockKiwer.login(ID, PW);

  EXPECT_EQ(buffer.str(), ID + " login success\n");
}

TEST_F(MockKiwerFixture, MockKiwerBuy) {
  string stockCode = "NVIDIA";
  int count = 10;
  int price = 10000;

  ON_CALL(mockKiwer, buy(_, _, _))
      .WillByDefault([](string stockCode, int count, int price) {
        cout << stockCode << " : Buy stock ( " << price << " * " << count
             << ")\n";
      });

  EXPECT_CALL(mockKiwer, buy(stockCode, count, price)).Times(1);

  mockKiwer.buy(stockCode, count, price);

  EXPECT_EQ(buffer.str(), stockCode + " : Buy stock ( " + to_string(price) +
                              " * " + to_string(count) + ")\n");
}

TEST_F(MockKiwerFixture, MockKiwerSell) {
  string stockCode = "NVIDIA";
  int count = 10;
  int price = 10000;

  ON_CALL(mockKiwer, sell(_, _, _))
      .WillByDefault([](string stockCode, int count, int price) {
        cout << stockCode << " : Sell stock ( " << price << " * " << count
             << ")\n";
      });

  EXPECT_CALL(mockKiwer, sell(stockCode, count, price)).Times(1);

  mockKiwer.sell(stockCode, count, price);

  EXPECT_EQ(buffer.str(), stockCode + " : Sell stock ( " + to_string(price) +
                              " * " + to_string(count) + ")\n");
}

TEST_F(MockKiwerFixture, MockKiwerCurrentPrice) {
  string stockCode = "NVIDIA";
  int expected = 50000;
  EXPECT_CALL(mockKiwer, currentPrice(stockCode))
      .Times(1)
      .WillRepeatedly(Return(expected));

  EXPECT_EQ(mockKiwer.currentPrice(stockCode), expected);
}

// Nemo 증권사 테스트
TEST_F(StockTradingSystemTest, TestNemoLogin) {
  // MockNemoStock mockNemo;
  system.selectStockBroker(false);  // Nemo 선택

  // EXPECT_CALL(mockNemo, login("박화영", "1234"))
  //     .WillOnce(::testing::Return(true));

  // EXPECT_TRUE(system.login("박화영", "1245"));
}

int main() {
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}
