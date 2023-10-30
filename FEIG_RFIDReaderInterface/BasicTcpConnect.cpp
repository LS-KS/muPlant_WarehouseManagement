/*
 * Copyright (C) Lennart Schink, 2023
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include "BasicTcpConnect.h"


// Path to RFID Headerfiles must be set in project settings.
// EG: C:\Path\to\ProjectDir\FEIG_RFIDReaderInterface\x64.vc142\include\fedm

//includes
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include "ReaderModule.h"
#include "Utility/HexConvert.h"

//namespaces
using namespace FEDM;
using namespace FEDM::Utility;
using namespace TagHandler;
using namespace std;



class BasicTcpConnect {
/* This class is a workerclass to establish a TCP-Connection to an RFID Reader of FEIG GmbH.
 * It has a constructor which only needs ip, port and a waittime between rereads of the reader device.
 * For its purpose it uses the Windows Gen3 SDK provided by FEIG GmbH.
 * This class is used to expose itself and its run() method to C ABI to later bind it with ctypes.
 */
private:
    string& ip;
    uint16_t port;
    unique_ptr<ReaderModule> reader;
    int readTime;
    vector<string> tagReadIn;

    void read() {
        int state;
        // [0x33] Initialize Buffer
        cout << "from private read()-method:" << endl;
        state = this->reader->brm().initializeReaderBuffer();
        cout << "[0x33] Initialize Buffer " << reader->lastErrorStatusText() << endl;

        // Read Operation over set readtime
        cout << "Wait for " << readTime << "ms..." << endl;
        this_thread::sleep_for(chrono::milliseconds(readTime));

        // [0x31] Read Data Buffer Info, to get number of tags in buffer
        BufferInfo bufferInfo;
        state = reader->brm().readReaderBufferInfo(bufferInfo);
        cout << "[0x31] Read Data Buffer Info: " << reader->lastErrorStatusText() << endl;
        cout << "\t" << "No of Tags: " << bufferInfo.numTags() << endl;
        cout << "\t" << "Tab - Size: " << bufferInfo.maxTags() << endl;
        cout << "\t" << "Tab-Start: " << bufferInfo.firstTag() << endl;
        if (bufferInfo.numTags() > 0) {
            // [0x22] Read Buffer
            state = reader->brm().readReaderBuffer(bufferInfo.numTags());
            cout << "[0x22] Read Buffer (" << bufferInfo.numTags() << " tags): " << reader->lastErrorStatusText() << endl;
            cout << endl;
            cout << "queueMaxItemCount()" << reader->brm().queueMaxItemCount() << endl;
            // loop through all found tags
            while (reader->brm().queueItemCount() > 0) {
                // Get next transponder from buffer
                unique_ptr<const BrmItem> brmItemPtr = reader->brm().popItem();
                if (brmItemPtr.get() == nullptr) {
                    break;
                }
                tagReadIn.push_back(BrmItemToString(brmItemPtr.get()));
                cout << BrmItemToString(brmItemPtr.get()) << endl;
            }

            // "[0x32] Clear data buffer"
            state = reader->brm().clearReaderBuffer();
            cout << "[0x32] Clear Data Buffer: " << reader->lastErrorStatusText() << endl;
        }
        else {
            cout << "Buffer empty. No transponder in reader field." << endl;
        }
    }
    static string BrmItemToString(const BrmItem* brmItem) {
        ostringstream brmItemPrintStream;
        // **************
        // Date
        // **************
        if (brmItem->dateTime().isValidDate())
        {
            int day = brmItem->dateTime().day();
            int month = brmItem->dateTime().month();
            int year = brmItem->dateTime().year();

            brmItemPrintStream << "Date: " << year << "-" << month << "-" << day << endl;
        }
        else
        {
            brmItemPrintStream << "Date: " << "not valid" << endl;
        }

        // **************
        // Time
        // **************

        if (brmItem->dateTime().isValidTime())
        {
            int hour = brmItem->dateTime().hour();
            int minute = brmItem->dateTime().minute();
            int second = brmItem->dateTime().second();
            int milliSecond = brmItem->dateTime().milliSecond();

            brmItemPrintStream << "Time: " << hour << ":" << minute << ":" << second << "." << milliSecond << endl;
        }
        else
        {
            brmItemPrintStream << "Time: " << "not valid" << endl;
        }

        // **************
        // IDD
        // **************
        if (brmItem->tag().isValid())
        {
            brmItemPrintStream << "IDD: " << brmItem->tag().iddToHexString() << endl;

            // **************
            // RSSI
            // **************
            vector<RssiItem> list = brmItem->tag().rssiValues();
            for (const RssiItem& rssiItem : list) {
                if (rssiItem.isValid())
                {
                    brmItemPrintStream << "RSSI: " << rssiItem.rssi() << endl;
                }
                else
                {
                    brmItemPrintStream << "RSSI: " << "not valid" << endl;
                }

                brmItemPrintStream << "Phase Angle: " << rssiItem.phaseAngle() << "dec" << endl;

            }
        }
        else
        {
            brmItemPrintStream << "IDD: " << "not valid" << endl;
        }

        // **************
        // Data
        // **************
        if (brmItem->dataBlocks().isValid())
        {
            string resultString;
            HexConvert::vectorToString(brmItem->dataBlocks().blocks(), resultString, ' ');

            brmItemPrintStream << "Data: " << resultString << endl;
            brmItemPrintStream << "Data blockCount: " << brmItem->dataBlocks().blockCount() << endl;
            brmItemPrintStream << "Data blockSize: " << brmItem->dataBlocks().blockSize() << endl;
        }
        else
        {
            brmItemPrintStream << "Data: " << "not valid" << endl;
        }

        // **************
        // Antenna
        // **************
        if (brmItem->antennas().isValid())
        {
            brmItemPrintStream << "Antenna: " << brmItem->antennas().antennas() << endl;
        }
        else
        {
            brmItemPrintStream << "Antenna: " << "not valid" << endl;
        }

        // **************
        // MAC-Address
        // **************
        if (brmItem->mac().isValid())
        {
            string addrString;
            int i = 1;
            for (uint8_t addr : brmItem->mac().macAddress()) {
                addrString += std::to_string(addr);
                if (i < brmItem->mac().macAddress().size()) {
                    addrString += ':';
                }
                i++;
            }
            brmItemPrintStream << "MAC: " << addrString << endl;
        }
        else
        {
            brmItemPrintStream << "MAC: " << "not valid" << endl;
        }

        // **************
        // Input
        // **************

        if (brmItem->input().isValid())
        {
            brmItemPrintStream << "Input: " << brmItem->input().input() << endl;
            brmItemPrintStream << "State: " << brmItem->input().state() << endl;
        }
        else
        {
            brmItemPrintStream << "Input: " << "not valid" << endl;
        }

        // **************
        // Device/Scanner ID
        // **************
        if (brmItem->scannerId().isValid())
        {
            if (brmItem->scannerId().type() == BrmItem::SectorScannerId::TypeDeviceId)
            {
                brmItemPrintStream << "Device ID: " << brmItem->scannerId().scannerId() << endl;
            }
            if (brmItem->scannerId().type() == BrmItem::SectorScannerId::TypeScannerId)
            {
                brmItemPrintStream << "Scanner ID: " << brmItem->scannerId().scannerId() << endl;
            }

        }
        else
        {
            brmItemPrintStream << "Device/Scanner ID: " << "not valid" << endl;
        }

        // **************
        // Direction
        // **************

        if (brmItem->direction().isValid())
        {

            if (brmItem->direction().isDetectionDisabled())
            {
                brmItemPrintStream << "Sector Direction: " << "Detection Disabled" << endl;
            }
            if (brmItem->direction().isDirection1())
            {
                brmItemPrintStream << "Sector Direction: " << "Direction 1" << endl;
            }
            if (brmItem->direction().isDirection2())
            {
                brmItemPrintStream << "Sector Direction: " << "Direction 2" << endl;
            }

        }
        else
        {
            brmItemPrintStream << "Sector Direction: " << "not valid" << endl;
        }

        return brmItemPrintStream.str();
    }
public:
    // Constructor to set IP address and port and read time.
    BasicTcpConnect(string& ipAddr, uint16_t ipPort, int readtime) : ip(ipAddr), port(ipPort), readTime(readtime){}

    // run method
    vector<string> run() {
        //create reader module with Request Mode UniDirectional = Advanced Protocol
        reader = unique_ptr<ReaderModule>(new ReaderModule(RequestMode::UniDirectional));

        int returnCode = ErrorCode::Ok;

        try
        {
            // Create TCP Connector Object
            Connector connTCP = Connector::createTcpConnector(this->ip, this->port);
            cout << "FEIG RFID Interface: BasicTCpConnectCode" << endl;
            cout << "Start connection with Reader: " << connTCP.tcpIpAddress() << endl;
            // connect reader with TCP Connector
            returnCode = reader->connect(connTCP);

            // check error code and throw exception with information.
            if (returnCode < ErrorCode::Ok) {
                throw std::runtime_error("Error from Library: Code = " + std::to_string(returnCode) + ": " + reader->lastErrorText());
            }
            else if (returnCode > ErrorCode::Ok) {
                throw std::runtime_error("Status from reader: Code = " + std::to_string(returnCode) + ": " + reader->lastStatusText());
            }
        }
        catch (const std::exception& e)
        {
            // Rethrow the exception with additional information
            throw std::runtime_error(e.what());
        }
        // Output Reader Type
        cout << "Reader " << reader->info().readerTypeToString() << "connected." << endl;

        this->read();

        // Disconnect Reader
        returnCode = reader->disconnect();
        if (returnCode == ErrorCode::Ok) {
            cout << "Reader: " << reader->info().readerTypeToString() << "disconnected." << endl;
            cout << endl;
        }
        if (tagReadIn.size() > 0) {
            return tagReadIn;
        }
        else {
            return vector<string>();
        }
    }
};
