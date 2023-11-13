//
// Created by Lennart Schink on 23.10.23.
//

#ifndef FEIG_RFIDREADERINTERFACE_BASICTCPCONNECT_H
#define FEIG_RFIDREADERINTERFACE_BASICTCPCONNECT_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

// Forward declaration of ReaderModule
class ReaderModule;
class BrmItem;

class BasicTcpConnect {
public:
    BasicTcpConnect(string& ipAddr, uint16_t ipPort, int waitTime);
    ~BasicTcpConnect();
    vector<string> run();

private:
    string& ip;
    uint16_t port;
    unique_ptr<ReaderModule> reader;
    int waitTime;
    vector<string> tagReadIn;
    void read();
    static string BrmItemToString(const BrmItem brmItem);
};

#endif //FEIG_RFIDREADERINTERFACE_BASICTCPCONNECT_H


