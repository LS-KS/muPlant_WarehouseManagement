/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FWUPDATE_MODULE_H
#define FEDM_FWUPDATE_MODULE_H

#include <Fedm.h>
#include <FedmServiceBasic.h>
#include <FedmServiceHide.h>
#include <IFwUpdateListener.h>



namespace FEDM {

/// @brief MAIN class for reader firmware update
///
/// Supported reader:<br>
/// CPR40.xx-U, CPR40.xx<br>
/// CPR50.xx, MAX50.xx<br>
/// CPR30.xx, CPR30+.xx<br>
/// CPR30pro<br>
/// CPR46.xx<br>
/// CPR60.xx<br>
/// CPR70<br>
/// CPR74<br>
/// ISC.MU02<br>
/// ISC.PRH102<br>
/// ISC.PRHD102<br>
/// ISC.PRH200<br>
/// ISC.MR102<br>
/// ISC.MRU102<br>
/// ISC.LR1002<br>
/// ISC.LR2500-A<br>
/// ISC.LR2500-B<br>
/// ISC.LR5400<br>
/// ISC.LRU1002, MAX.U1002<br>
/// ISC.LRU3000<br>
/// LRU500i-BD, LRU500i-PoE, MAX.U500i<br>
/// HyWEAR compact, HyWEAR compact xT, HyWEAR compact sR<br>
/// ECCO Smart HF-BLE, ECCO Smart 2D-HF-BLE<br>
/// <br>
/// Firmware update files are available from FEIG ELECTRONIC.
class FEDM_SERVICE_CLASS_DEF FwUpdateModule
{
public:
	/// @brief Constructor for the firmware update module
	/// @param[in] reader A pointer to a ReaderModule
	///
	/// The update module does not take ownership of the reader module.<br>
	/// The update module must be destroyed before reader module's destructor is called!<br>
	/// The reader module can be already connected. Otherwise use startConnect() to establish a connection.
	FwUpdateModule(ReaderModule *reader);

	/// @brief The standard constructor is not allowed
	FwUpdateModule() = delete;

	/// @brief To copy a FwUpdateModule is not allowed
	FwUpdateModule(FwUpdateModule & other) = delete;

	/// @brief To copy a FwUpdateModule is not allowed
	FwUpdateModule(const FwUpdateModule & other) = delete;

	/// @brief To copy a FwUpdateModule is not allowed
	FwUpdateModule & operator=(FwUpdateModule & other) = delete;

	/// @brief To copy a FwUpdateModule is not allowed
	FwUpdateModule & operator=(const FwUpdateModule & other) = delete;

	~FwUpdateModule();

	/// @brief Query the version the fedm-service library
	static std::string libVersion(void);

	/// @brief Get the last error code
	int lastError(void) const;

	/// @brief Get the text of the last error
	std::string lastErrorText(void) const;


	/// @brief Set logging facility options
	/// @param[in] on Set logging on / off
	/// @param[in] path The path to store logfiles. If path is empty the current working directory is used.
	/// @return #{DOC_LIB_ERROR_VALUE}
	///
	/// The logfiles will contain communication protocols and messages in the order of appearance.<br>
	/// In case of a successful update the log filename will be 'FedmService-last.log'. This file will be removed before the next update starts.<br>
	/// In case of an update termination by error, this file will be renamed to 'FedmService-err-<date>--<time>.log'.
	void setLogOptions(bool on, const std::string & path = std::string());

	/// @brief Get the filename of the last log-file
	/// @returns The absolute path and filename of the last update log-file
	///
	/// See setLogOptions() for details.
	std::string lastLogFile(void) const;


	/// @brief Start message listener for compatibility check and firmware update
	/// @param[in] listener The listener for messages.
	///
	/// This will start the internal messenger thread.<br>
	/// Instead of using the messenger you can call popMessage() to obtain messages directly from the message queue.
	int startMessenger(IFwUpdateListener *listener);

	/// @brief Stop message listener
	///
	/// A running messenger will be stopped and all pending messages will be posted.<br>
	/// This function blocks until the message queue is empty, all messages are posted via IFwUpdateListener and the internal messenger thread is finished.
	void stopMessenger(void);


	/// @brief Clear the internal message queue
	void clearMessages(void);

	/// @brief Get the next message from the internal message queue
	/// @returns The next message object. If the message queue is empty, an invalid object is returned
	///
	/// Use this function to obtain update messages if you don't want to use an IFwUpdateListener.<br>
	/// The access to the message queue is thread save.
	FwUpdateMessage popMessage(void);


	/// @brief Get the result of the last verification
	/// @param[out] errorText The error text of the verification.
	/// @param[out] commentText An additinal comment to the error (optionally).
	/// @param[out] summaryText A summary of the reader (type, id) and the XML-file (filename, controller image versions).
	/// @returns The error code of the verification or 0.
	///
	/// This is a convenience function to obtain the verification information from the message queue.
	/// All messages up to the end of the verification are popped from the queue.
	int verifyResult(std::string & errorText, std::string & commentText, std::string & summaryText);


	/// @brief Start connecting to the reader
	/// @param[in] connector Contains the connection parameter
	/// @return #{DOC_LIB_ERROR_VALUE}
	///
	/// This function is non blocking. The operation is performed in an own thread.
	int startConnect(const Connector & connector);

	/// @brief Start detecting serial connection to the reader
	/// @param[in] detector Contains the detection parameter
	/// @return #{DOC_LIB_ERROR_VALUE}
	///
	/// This function is non blocking. The operation is performed in an own thread.<br>
	/// Each detection try will be posted to the message queue.
	int startDetectSerial(const DetectorSerial & detector);

	/// @brief Start the compatibility check of firmware file with the connected Reader
	/// @param[in] fwUpdateFilename The filename of the update file (.xml or .upd). This can be absolute or relative to the current working directory.
	/// @return #{DOC_LIB_ERROR_VALUE}
	///
	/// This function is non blocking. The operation is performed in an own thread.<br>
	/// Firmware XML-files are available from FEIG ELECTRONIC.
	int startVerify(const std::string & fwUpdateFilename);

	/// @brief Start the firmware update
	/// @param[in] fwUpdateFilename The filename of the update file (.xml or .upd). This can be absolute or relative to the current working directory.
	/// @return #{DOC_LIB_ERROR_VALUE}
	///
	/// This function is non blocking. The operation is performed in an own thread.<br>
	/// In case of an update via USB the FEDM::UsbManager MUST NOT in discover mode. Call stopDiscover() before!<br>
	/// Firmware XML-files or UPD-files are available from FEIG ELECTRONIC.
	int startUpdate(const std::string & fwUpdateFilename);

	/// @brief Wait for end of compatibility check update or firmware update
	/// @return #{DOC_LIB_ERROR_VALUE}
	///
	/// This function blocks until the function thread stops.<br>
	/// It returns error or state of the finished function.
	int waitOnThread(void);

	/// @brief Check if a verification or update thread is running
	///
	/// This function is non blocking
	bool isRunning(void) const;

private:
	Internal::FwUpdateThread *m_updThread;

}; // end of class FwUpdateModule

}; // end of namespace FEDM

#endif // FEDM_FWUPDATE_MODULE_H
