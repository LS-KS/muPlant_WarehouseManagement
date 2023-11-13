#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

using namespace std;

class BasicTcpConnection
{
private:
	std::string& ip;
	int port;

public:
	BasicTcpConnection(std::string& ipAddr, int ipPort);
	vector<string&> run();
};
