#pragma once
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class IKiwerAPI {
public:
	virtual ~IKiwerAPI() = default;
	virtual void login(string ID, string password) = 0;
	virtual void buy(string stockCode, int count, int price) = 0;
	virtual void sell(string stockCode, int count, int price) = 0;
	virtual int currentPrice(string stockCode) = 0;
};

class KiwerAPI : public IKiwerAPI {
public:
	void login(string ID, string password) { cout << ID << " login success\n"; }

	void buy(string stockCode, int count, int price) {
		cout << stockCode << " : Buy stock ( " << price << " * " << count << ")\n";
	}

	void sell(string stockCode, int count, int price) {
		cout << stockCode << " : Sell stock ( " << price << " * " << count << ")\n";
	}

	int currentPrice(string stockCode) {
		srand(time(NULL));
		int ret = rand() % 10 * 100 + 5000;
		return ret;
	}
};