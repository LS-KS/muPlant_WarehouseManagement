/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_FWUPDATE_MESSAGE_THREAD_H
#define FEDM_FWUPDATE_MESSAGE_THREAD_H

#include <string>
#include <FedmServiceBase.h>



namespace FEDM {

/// @brief DATA class for firmware update messages
class FwUpdateMessage
{
public:
	static const int TypeNone = 0;
	static const int TypeStatus = 1;
	static const int TypeController = 2;
	static const int TypeProgress = 3;
	static const int TypeMessage = 4;
	static const int TypeError = 5;

	static const int StatusNone = 0;
	static const int StatusUpdateStarted = 1;
	static const int StatusUpdateFinished = 2;
	static const int StatusVerifyStarted = 3;
	static const int StatusVerifyFinished = 4;
	static const int StatusSummaryBegin = 5;
	static const int StatusSummaryEnd = 6;
	static const int StatusConnectStarted = 7;
	static const int StatusConnectFinished = 8;
	static const int StatusDetectSerialStarted = 9;
	static const int StatusDetectSerialFinished = 10;
	static const int StatusBusy = 15;
	static const int StatusWaitingForReconnect = 16;
	static const int StatusStartFlashLoader = 20;
	static const int StatusActivateUpload = 21;
	static const int StatusDeleteFlash = 22;
	static const int StatusUploadImage = 23;
	static const int StatusUploadCanceled = 24;
	static const int StatusResetTarget = 25;
	static const int StatusUploadReady = 26;
	static const int StatusRebootReader = 27;
	static const int StatusFwActivationRequired = 30;
	static const int StatusAutoConfigReset = 31;
	static const int StatusPrhx102PressKey = 50;
	static const int StatusPrh200PressKey = 51;

	/// @brief TypeNone
	///
	/// This message type is created, if you pop from an empty message queue. In this case isValid() returns false.
	FwUpdateMessage() :
		m_type{TypeNone}, m_status{StatusNone}, m_progress{0}, m_progressMax{0}, m_error{0}, m_message{std::string()}
	{ }

	/// @brief TypeStatus
	///
	/// This message type will be posted to signal special states of the service working threads.<br>
	/// Call status() to obtain the status constant. See constants Status...<br>
	/// Call message() to obtain the status text.
	FwUpdateMessage(int status) :
		m_type{TypeStatus}, m_status{status}, m_progress{0}, m_progressMax{0}, m_error{0}
	{
		switch (m_status) {
			case StatusUpdateStarted:        m_message = "Update started"; break;
			case StatusUpdateFinished:       m_message = "Update finished"; break;
			case StatusVerifyStarted:        m_message = "Verify started"; break;
			case StatusVerifyFinished:       m_message = "Verify finished"; break;
			case StatusSummaryBegin:         m_message = "Summary begin"; break;
			case StatusSummaryEnd:           m_message = "Summary end"; break;
			case StatusConnectStarted:       m_message = "Connect started"; break;
			case StatusConnectFinished:      m_message = "Connect finished"; break;
			case StatusDetectSerialStarted:  m_message = "Detect serial started"; break;
			case StatusDetectSerialFinished: m_message = "Detect serial finished"; break;
			case StatusBusy:                 m_message = "Busy: Waiting..."; break;
			case StatusWaitingForReconnect:  m_message = "Waiting for reconnect..."; break;
			case StatusStartFlashLoader:     m_message = "Start the flash loader of the reader..."; break;
			case StatusActivateUpload:       m_message = "Activate file upload..."; break;
			case StatusDeleteFlash:          m_message = "Delete flash..."; break;
			case StatusUploadImage:          m_message = "Upload and flash image data..."; break;
			case StatusUploadCanceled:       m_message = "Update process must be cancelled.\n"
			                                             "The Reader may not work after power-up.\n"
			                                             "Please get in contact with identification-support@feig.de"; break;
			case StatusResetTarget:          m_message = "Reset target..."; break;
			case StatusUploadReady:          m_message = "Upload ready"; break;
			case StatusRebootReader:         m_message = "Reboot reader..."; break;
			case StatusFwActivationRequired: m_message = "Firmware activation required: Please contact your distributor"; break;
			case StatusAutoConfigReset:      m_message = "I M P O R T A N T   N O T E !\n"
														 "Due to the significant Firmware Version step,\n"
														 "all Configuration Parameters of the Reader are set\n"
														 "to factory default values.\n"
														 "The Reader was reset with command CPU-Reset."; break;
			case StatusPrhx102PressKey:      m_message = "Please press trigger button to continue..."; break;
			case StatusPrh200PressKey:       m_message = "Please press power on/off button to continue..."; break;
			default: m_status = StatusNone;  m_message.clear();  break;
		}
	}

	/// @brief TypeController
	///
	/// A firmware XML-file can contain update images for several controllers.<br>
	/// This message type will be posted at the begin of each controller image upload.<br>
	/// Call message() to obtain the name of the controller.<br>
	/// Call progress() to obtain the current controller number.<br>
	/// Call progressMax() to obtain the maximum count of controller images in the XML-file.<br>
	/// Call controllerToString() to obtain a summary text.
	FwUpdateMessage(const std::string & controller, int controllerNo, int controllerMax) :
		m_type{TypeController}, m_status{StatusNone}, m_progress{controllerNo}, m_progressMax{controllerMax}, m_error{0}, m_message{controller}
	{ }

	/// @brief TypeProgress
	///
	/// Each controller image is send in multiple packets to the reader. After each successful transfer a message of this type will be posted.<br>
	/// Call progress() to obtain the current packet number.<br>
	/// Call progressMax() to obtain the maximum count of packets.<br>
	/// Call progressToString() to obtain a summary text.<br>
	/// Before the first packet is send, a message with packetNo=0 and valid packetMax will be posted.
	/// You can use this message to reset and adjust a progress bar GUI object.
	FwUpdateMessage(int packetNo, int packetMax) :
		m_type{TypeProgress}, m_status{StatusNone}, m_progress{packetNo}, m_progressMax{packetMax}, m_error{0}, m_message{std::string()}
	{ }

	/// @brief TypeMessage
	///
	/// Call message() to obtain the message text.
	FwUpdateMessage(const std::string & message) :
		m_type{TypeMessage}, m_status{StatusNone}, m_progress{0}, m_progressMax{0}, m_error{0}, m_message{message}
	{ }

	/// @brief TypeError
	///
	/// In case of an error this message type will be posted. The update procedure is terminated.<br>
	/// Call error() to obtain the error code.<br>
	/// Call message() to obtain the error text.
	FwUpdateMessage(int error, const std::string & message) :
		m_type{TypeError}, m_status{StatusNone}, m_progress{0}, m_progressMax{0}, m_error{error}, m_message{message}
	{ }

	void clear(void) { *this = FwUpdateMessage(); }

	void setMessage(const std::string & message) { m_message = message; }


	// ##### READ ONLY #####

	/// @brief Query if message object is valid
	/// @return true if message object is valid, false otherwise. Invalid message object are created when popping from an empty message queue.
	bool isValid(void) const { return m_type != TypeNone; }

	/// @brief Query the message type
	/// @return The message type. See constants Type...
	int type(void) const { return m_type; }

	/// @brief Query the status if message type is TypeStatus
	/// @return The message status. See constants Status...
	int status(void) const { return m_status; }

	/// @brief Query the error code if message type is TypeError
	/// @return The error code.
	///
	/// Call message() to obtaim the error text.
	int error(void) const { return m_error; }

	/// @brief Get the text of the message object
	/// @return The text string. This can be:<br>
	/// TypeMessage: An arbitrary message<br>
	/// TypeStatus: A status message. See 'FedmFwUpdateMessage.h' for all possible status messages<br>
	/// TypeError: An error text<br>
	/// TypeController: A controller name
	const std::string & message(void) const { return m_message; }

	/// @brief Get the packet or controller number
	/// @return The progress number. This can be:<br>
	/// TypeController: The current controller number<br>
	/// TypeProgress: The current packet number
	int progress(void) const { return m_progress; }

	/// @brief Get the packet or controller maximum number
	/// @return The maximum progress number. This can be:<br>
	/// TypeController: The total number of controller images of a XML file<br>
	/// TypeProgress: The total number of packets of a controller image
	int progressMax(void) const { return m_progressMax; }

	/// @brief Get a standard packet progess text string
	/// @return A standard packet progress text string
	std::string progressToString(void) const
	{
		if (m_type != TypeProgress) {
			return std::string();

		} else if (m_progress <= 0) { // start image upload
			return "Start image upload: " + std::to_string(m_progressMax) + " packets";

		} else { // upload image progress
			return "Packet " + std::to_string(m_progress) + " of " + std::to_string(m_progressMax) + " done";
		}
	}

	/// @brief Get a standard controller progess text string
	/// @return A standard controller progress text string
	std::string controllerToString(void) const
	{
		if (m_type != TypeController) {
			return std::string();

		} else {
			return "Controller " + m_message + " (" + std::to_string(m_progress) + " of " + std::to_string(m_progressMax) + ")";
		}
	}

private:
	int	m_type;
	int	m_status;
	int	m_progress;
	int	m_progressMax;
	int	m_error;
	std::string m_message;
};

}; // end of namespace FEDM

#endif // FEDM_FWUPDATE_MESSAGE_THREAD_H
