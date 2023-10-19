/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_READER_MODULE_H
#define FEDM_READER_MODULE_H

#include <vector>
#include <string>

#include "FedmBasic.h"
#include "FedmHide.h"
#include "IListenComDet.h"
#include "IListenConnect.h"
#include "GroupDiag.h"
#include "GroupHm.h"
#include "GroupBrm.h"
#include "GroupTagEvent.h"
#include "GroupConfig.h"
#include "GroupClock.h"
#include "GroupRf.h"
#include "GroupIO.h"
#include "GroupAsync.h"
#include "GroupLog.h"
#include "GroupSmartCard.h"
#include "GroupKeyMng.h"



/// @brief The main namespace
namespace FEDM {

/// @brief MAIN class for reader communication
class FEDM_CLASS_DEF ReaderModule
{
	friend class FedmFriend;
	friend class Internal::FunitWorker;  // for privateInterface() (see FedmHide.h)
	friend class Internal::ConfigWorker; // for privateInterface() (see FedmHide.h)

public:
/** @name Main
 */
///@{
	/// @brief Constructor for the ReaderModule
	/// @param[in] requestMode See RequestMode for details. 
	ReaderModule(RequestMode requestMode);

	/// @brief The standard constructor is not allowed
	ReaderModule() = delete;

	/// @brief To copy a ReaderModule is not allowed
	ReaderModule(ReaderModule & other) = delete;

	/// @brief To copy a ReaderModule is not allowed
	ReaderModule(const ReaderModule & other) = delete;

	/// @brief To copy a ReaderModule is not allowed
	ReaderModule & operator=(ReaderModule & other) = delete;

	/// @brief To copy a ReaderModule is not allowed
	ReaderModule & operator=(const ReaderModule & other) = delete;

	/// @brief Destructor for the reader module
	~ReaderModule();

	/// @brief The ReaderModule's RequestMode which was set by the constructor
	/// @return The request mode of the ReaderModule
	RequestMode requestMode(void) const;

	/// @brief Set the reader type manually
	/// @param[in] readerType (see #{DOC_LINK_TO_CLASS(FEDM::ReaderType)})
	///
	/// Usually there is no need to call this function. The reader type is automatically detected and set by the connect()-function.
	int setReaderType(uint32_t readerType);

	/// @brief Get the type of the current conected reader
	/// @return The reader type ID (see #{DOC_LINK_TO_CLASS(FEDM::ReaderType)})
	uint32_t readerType(void) const;
///@}


// ############################################################# Error Handling #############################################################
/** @name Error Handling
 */
///@{
	/// @brief Get last library error code
	/// @return The last library error code #{DOC_LINK_TO_CLASS(FEDM::ErrorCode)}
	///
	/// If the last library function call delivered a negative return code this function will return this value.<br>
	/// Otherwise 0 will be returned.
	int lastError(void) const;

	/// @brief Get status code of last reader response
	/// @return The last reader status #{DOC_LINK_TO_CLASS(FEDM::ReaderStatus)}
	///
	/// If the last library function call delivered a positive return code this function will return this value.<br>
	/// Otherwise 0 will be returned.
	int lastStatus(void) const;

	/// @brief Get last transponder ISO error code
	/// @return The last transponder ISO error (see reader manual or ISO documentation)
	///
	/// If the last library function call delivered a reader status response of ReaderStatus::IsoError or ReaderStatus::IsoError14443
	/// this function will return the transponders ISO error.<br>
	/// Otherwise 0 will be returned.
	int lastIsoError(void) const;

	/// @brief Get last error or status text
	/// @return The text of last library error, ISO error or reader status
	std::string lastErrorStatusText(void) const;

	/// @brief Get last library error text
	/// @return The text of last library error
	///
	/// This function is depreciated. Use lastErrorStatusText() instead.
	std::string lastErrorText(void) const;

	/// @brief Get status text of last reader response
	/// @return The text of last reader state
	///
	/// This function is depreciated. Use lastErrorStatusText() instead.
	std::string lastStatusText(void) const;
///@}


// ####################################################### Connection Control Functions #######################################################
/** @name Connection Control Functions
 */
///@{
	/// @brief Connect to the reader and set the current connector
	/// @param[in] connector Contains the parameter (see #{DOC_LINK_TO_CLASS(FEDM::Connector)})
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Example: connect( FEDM::Connector::createTcpConnector("192.168.3.33", 10005) );
	int connect(const Connector & connector);

	/// @brief Detect serial communication parameter (baudrate, byte frame)
	/// @param[in] detector Contains the detection parameter (see #{DOC_LINK_TO_CLASS(FEDM::DetectorSerial)})
	/// @param[in] listener A pointer to a detecting listener or nullptr if a listener is not neccassary
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Example: detectSerial( FEDM::DetectorSerial::createDetector() );
	/// If successful the ReaderModul is connected and the current connector is set.
	int detectSerial(const DetectorSerial & detector, IComDetListener *listener = nullptr);

	/// @brief Reconnect to the reader using the current connector
	/// @return #{DOC_LIB_RETURN_VALUE}
	int reconnect(void);

	/// @brief Disconnect the current connection
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// The connector stays valid and can be reused for reconnect().<br>
	/// If there is no connection this function does nothing.
	int disconnect(void);

	/// @return True, if a connection to a reader is established, false otherwise
	bool isConnected(void) const;

	/// @brief Get the current / last used connector
	Connector currentConnector(void) const;



	/// @brief Start a listener thread for reader connection requests
	/// @param[in] param Contains the listener parameter (see #{DOC_LINK_TO_CLASS(FEDM::ListenerParam)})
	/// @param[in] listener A pointer to the reader connect listener. Can be nullptr.
	/// @return #{DOC_LIB_RETURN_VALUE}
	int startListenerThread(const ListenerParam & param, IConnectListener *listener = nullptr);
	
	/// @brief Stop the listener thread for reader connection requests
	///
	/// If there is no listener thread running this function does nothing.
	int stopListenerThread(void);



	/// @brief Overwrite the current receive timeout value
	/// @param[in] msec The maximum wait time between request and response in milliseconds
	///
	/// The initial receive timeout value is set by the connector.<br>
	/// This function does not overwrite the timeout value in the connector. To obtain the old value call<br>
	/// currentConnector().receiveTimeout();
	int setReceiveTimeout(int msec);

	/// @brief Get the current receive timeout value
	/// @return The maximum wait time between request and response in milliseconds
	int receiveTimeout(void);
///@}


// ####################################################### Basic Reader Functions #######################################################
/** @name Basic Reader Functions
 */
///@{
	/// @brief Read the reader identification (command [0x2D])
	/// @return #{DOC_LIB_RETURN_VALUE}
	int readReaderIdentification(void);

	/// @brief Get a copy of previously read reader identification
	///
	/// This function is thread save
	ReaderIdentification identification(void) const;


	/// @brief Read entire reader information data (command [0x66])
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// This is done automatically by the connect()-function when the connector's ReaderInfoPolicy property is set to 'All'.<br>
	/// If the connect was done with other ReaderInfoPolicy values, you can use this function to obtain the complete information later.<br>
	/// The ReaderInfo class can be obtained by the info()-function.
	int readReaderInfo(void);

	/// @brief Get a copy of previously read reader information data
	///
	/// This function is thread save
	ReaderInfo info(void) const;


	/// @brief Perform a reader system reset
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Dependend on the reader type it performs<br>
	/// command [0x64] mode [0x00]   or<br>
	/// command [0x64] mode [0x01]   or<br>
	/// command [0x63]
	int hardReset(void);

	/// @brief Perform a reader CPU reset
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// Performs a [0x63] command
	int softReset(void);


	/// @brief Perform a low level application request and wait for reader response
	/// @param[in] reqPayl A byte container with the request payload
	/// @param[out] rspPayl A byte container with the response payload
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// The payload starts with the command byte. This is valid for request and response alike.<br>
	/// Payloads are framed by the tranport library FEISP with a protocol header and CRC.<br>
	/// Example: The payload for 'read reader info all'<br>
	/// 66 FF<br>
	/// will be framed in case of an advanced protocol to<br>
	/// 02 00 08 FF 66 FF F0 1D
	int transceive(const std::vector<uint8_t> & reqPayl, std::vector<uint8_t> & rspPayl);

	/// @brief Perform a low level application request and wait for reader response
	/// @param[in] reqPayl A hex coded string with the request payload
	/// @param[out] rspPayl A hex coded string with the response payload
	/// @return #{DOC_LIB_RETURN_VALUE}
	///
	/// The payload starts with the command byte. This is valid for request and response alike.<br>
	/// Payloads are framed by the tranport library FEISP with a protocol header and CRC.<br>
	/// Example: The payload for 'read reader info all'<br>
	/// 66 FF<br>
	/// will be framed in case of an advanced protocol to<br>
	/// 02 00 08 FF 66 FF F0 1D
	int transceive(const std::string & reqPayl, std::string & rspPayl);
///@}


// ####################################################### Reader Function Groups #######################################################
/** @name Reader Function Groups Non-Const
 */
///@{
	Async    & async   (void) { return m_async; }
	Brm      & brm     (void) { return m_brm; }
	TagEvent & tagEvent(void) { return m_tagEvent; }
	Hm       & hm      (void) { return m_hm; }
	Config   & config  (void) { return m_config; }
	Clock    & clock   (void) { return m_clock; }
	Rf       & rf      (void) { return m_rf; }
	IO       & io      (void) { return m_io; }
	Log      & log     (void) { return m_log; }
	Diagnostic    & diagnostic (void) { return m_diagnostic; }
	SmartCard     & smartCard  (void) { return m_smartCard; }
	KeyManagement & keyMng     (void) { return m_keyMgmt; }
///@}

/** @name Reader Function Groups Const
 */
///@{
	const Async    & async   (void) const { return m_async; }
	const Brm      & brm     (void) const { return m_brm; }
	const TagEvent & tagEvent(void) const { return m_tagEvent; }
	const Hm       & hm      (void) const { return m_hm; }
	const Config   & config  (void) const { return m_config; }
	const Clock    & clock   (void) const { return m_clock; }
	const Rf       & rf      (void) const { return m_rf; }
	const IO       & io      (void) const { return m_io; }
	const Log      & log     (void) const { return m_log; }
	const Diagnostic    & diagnostic (void) const { return m_diagnostic; }
	const SmartCard     & smartCard  (void) const { return m_smartCard; }
	const KeyManagement & keyMng     (void) const { return m_keyMgmt; }
///@}


// ####################################################### Miscellaneous Functions #######################################################
/** @name Miscellaneous Functions
 */
///@{		
	/// Causes all pending operations to terminate. Use this function to prepare a reader module's destructor call.<br>
	/// This function is nonblocking.<br>
	/// It may be any thread.<br>
	/// Use this function to speed up the shutdown of multiple reader applications.
	void terminate(void);
///@}


protected:
	Internal::ReaderBase *m_rdrBase;

private:
	Async    m_async;
	Brm      m_brm;
	TagEvent m_tagEvent;
	Hm       m_hm;
	Config   m_config;
	Clock    m_clock;
	Rf       m_rf;
	IO       m_io;
	Log      m_log;
	Diagnostic     m_diagnostic;
	SmartCard      m_smartCard;
	KeyManagement  m_keyMgmt;

	Internal::IReaderPrivate *privateInterface(void);

}; // end of class ReaderModule

}; // end of namespace FEDM

#endif // FEDM_READER_MODULE_H



/***** Include Hierachie ******
 *
 * --- Top Level --------------
 * LibInfo.h        API
 * UsbManager.h     API
 * UdpManager.h     API
 * ComManager.h     API
 * BleManager.h     API
 * ReaderModule.h	API
 * ReaderConfigPara.h API
 *
 * --- Group Level ------------
 * GroupInfo.h      API
 * GroupDiag.h      API
 * GroupBrm.h		API
 * GroupTagEvent.h	API
 * GroupHm.h		API
 * GroupConfig.h	API
 * GroupClock.h     API
 * GroupRf.h        API
 * GroupIO.h        API
 * GroupAsync.h		API
 * GroupLog.h       API
 * GroupSmartCard.h	API
 * GroupKeyMng.h    API
 *
 *
 * --- Listener (2nd Thread) --
 * IListenConnect.h	API
 * IListenRdr.h		API
 * IListenLog.h		API
 * IListenComDet.h	API
 *
 * --- Tag Handler ------------
 * Th.h				Conclusion
 * ThBase.h			API
 * ThEpcC1G2.h		API
 *
 * ############################
 *
 * --- Internal Reader Base ---
 * FedmHide.h		HighLevelBase
 * ReaderBase.h		--> FEISP
 * Payload.h		--> FEISP
 * ConfigMemory.h
 *
 * ############################
 *
 * --- Basics - Transporter ---
 * FedmBasic.h			Conclusion
 * FedmConnector.h		API
 * FedmPeerInfo.h		API
 * FedmRdrInfo.h		API
 * FedmRdrId.h			API
 * FedmRdrDiag.h		API
 * FedmDateTime.h		API
 * FedmTagItem.h		API
 * FedmTagEventItem.h   API
 * FedmBrmItem.h		API
 * FedmBufferInfo.h		API
 * FedmOutSett.h		API
 * FedmInvParam.h		API
 * FedmCardInfo14443.h	API
 * FedmCfgParInfo.h		API
 * FedmCfgId.h			API
 * FedmSmartCardItem.h	API
 * HexConvert.h			API
 *
 * --- Basics - Constants -----
 * FedmConst.h		API
 * FedmRdrType.h	API
 * FedmErrCode.h	API
 * FedmRdrStatus.h	API
 * FedmBase.h		API
 */
