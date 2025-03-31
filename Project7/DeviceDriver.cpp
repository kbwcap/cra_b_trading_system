
#include "DeviceDriver.h"
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    const int num_readings = 5;
    const int sleep_duration_ms = 200;
    std::vector<int> readings;

    for (int i = 0; i < num_readings; ++i) {
        int value = (int)(m_hardware->read(address));
        readings.push_back(value);

        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration_ms));
    }

    // check if all same
    if (std::all_of(readings.begin(), readings.end(), [&](int val) { return val == readings[0]; })) {
        return readings[0];
    }
    else {
        throw ReadFailException("Read values are inconsistent!");
    }
}

void DeviceDriver::write(long address, int data)
{
    if ((int)(m_hardware->read(address)) != 0xFF) {
        throw WriteFailException("Value is already written!");
    }

    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::ReadAndPrint(long startAddr, long endAddr)
{
    for (long addr = startAddr; addr <= endAddr; ++addr) {
        try {
            int value = read(addr);
            cout << "Address: 0x" << hex << addr << " Value: 0x" << hex << value << endl;
        }
        catch (const ReadFailException& e) {
            cout << "Read failed for address 0x" << hex << addr << ": " << e.what() << endl;
        }
    }
}

void DeviceDriver::WriteAll(int value)
{
    for (long addr = 0x00; addr <= 0x04; ++addr) {
        try {
            write(addr, value);
            cout << "Written value 0x" << hex << value << " to address 0x" << hex << addr << endl;
        }
        catch (const WriteFailException& e) {
            cout << "Write failed for address 0x" << hex << addr << ": " << e.what() << endl;
        }
    }
}