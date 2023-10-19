/**
*
* Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
*
* This software is the confidential and proprietary information of
* FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
* disclose such Confidential Information and shall use it only in
* accordance with the terms of the license agreement you entered
* into with FEIG ELECTRONIC GmbH.
*
* Version: 05.06.05 / 01.03.2023
*
* This file is auto-generated
*/


#ifndef FEDM_READER_CONFIG_PARA_H
#define FEDM_READER_CONFIG_PARA_H

#include <string>
#include "FedmBase.h"

using namespace std;

namespace FEDM
{
	/// Namespace %ReaderConfig collects all configuration parameters
	namespace ReaderConfig
	{		/// General device parameters
		namespace Device
		{
			FEDM_CLASS_DEF extern const std::string ConfigLayoutID;
			FEDM_CLASS_DEF extern const std::string ConfigCustomLayoutID;
			FEDM_CLASS_DEF extern const std::string ConfigVersion;

			/// Parameters for device identification
			namespace Identifier
			{
				FEDM_CLASS_DEF extern const std::string ScannerID;
				FEDM_CLASS_DEF extern const std::string ReaderID;
				FEDM_CLASS_DEF extern const std::string CustomerParameter;
			}
		}

		/// Configuration parameters for security and access protection
		namespace AccessProtection
		{
			FEDM_CLASS_DEF extern const std::string Password;
			FEDM_CLASS_DEF extern const std::string Lock_CFG0;
			FEDM_CLASS_DEF extern const std::string Lock_CFG1;
			FEDM_CLASS_DEF extern const std::string Lock_CFG2;
			FEDM_CLASS_DEF extern const std::string Lock_CFG3;
			FEDM_CLASS_DEF extern const std::string Lock_CFG4;
			FEDM_CLASS_DEF extern const std::string Lock_CFG5;
			FEDM_CLASS_DEF extern const std::string Lock_CFG6;
			FEDM_CLASS_DEF extern const std::string Lock_CFG7;
			FEDM_CLASS_DEF extern const std::string Lock_CFG8;
			FEDM_CLASS_DEF extern const std::string Lock_CFG9;
			FEDM_CLASS_DEF extern const std::string Lock_CFG10;
			FEDM_CLASS_DEF extern const std::string Lock_CFG11;
			FEDM_CLASS_DEF extern const std::string Lock_CFG12;
			FEDM_CLASS_DEF extern const std::string Lock_CFG13;
			FEDM_CLASS_DEF extern const std::string Lock_CFG14;
			FEDM_CLASS_DEF extern const std::string Lock_CFG15;
			FEDM_CLASS_DEF extern const std::string Lock_CFG16;
			FEDM_CLASS_DEF extern const std::string Lock_CFG17;
			FEDM_CLASS_DEF extern const std::string Lock_CFG18;
			FEDM_CLASS_DEF extern const std::string Lock_CFG19;
			FEDM_CLASS_DEF extern const std::string Lock_CFG20;
			FEDM_CLASS_DEF extern const std::string Lock_CFG21;
			FEDM_CLASS_DEF extern const std::string Lock_CFG36;
			FEDM_CLASS_DEF extern const std::string Lock_CFG37;
			FEDM_CLASS_DEF extern const std::string Lock_CFG38;
			FEDM_CLASS_DEF extern const std::string Lock_CFG39;
			FEDM_CLASS_DEF extern const std::string Lock_CFG48;
			FEDM_CLASS_DEF extern const std::string Lock_CFG63;
			FEDM_CLASS_DEF extern const std::string Lock_CFG22_29;
			FEDM_CLASS_DEF extern const std::string Lock_CFG30_35;
			FEDM_CLASS_DEF extern const std::string Lock_CFG30_39;
			FEDM_CLASS_DEF extern const std::string Lock_CFG40_49;
			FEDM_CLASS_DEF extern const std::string Lock_CFG50_59;
			FEDM_CLASS_DEF extern const std::string Lock_CFG60_62;
			FEDM_CLASS_DEF extern const std::string Lock_CFG64_86;
			FEDM_CLASS_DEF extern const std::string CryptoMode;
			FEDM_CLASS_DEF extern const std::string Categories;
		}

		/// Configuration parameters for communication interfaces
		namespace HostInterface
		{
			FEDM_CLASS_DEF extern const std::string Interfaces;
			FEDM_CLASS_DEF extern const std::string Enable_RS232;
			FEDM_CLASS_DEF extern const std::string Enable_RS4xx;
			FEDM_CLASS_DEF extern const std::string Enable_LAN;
			FEDM_CLASS_DEF extern const std::string Enable_WLAN;
			FEDM_CLASS_DEF extern const std::string Enable_USB;
			FEDM_CLASS_DEF extern const std::string Enable_Discovery;
			FEDM_CLASS_DEF extern const std::string Enable_Hostname;
			FEDM_CLASS_DEF extern const std::string Hostname;
			FEDM_CLASS_DEF extern const std::string Enable_SSH;

			/// %Serial Port specific parameters
			namespace Serial
			{
				FEDM_CLASS_DEF extern const std::string BusAddress;
				FEDM_CLASS_DEF extern const std::string Baudrate;
				FEDM_CLASS_DEF extern const std::string Frame;
				FEDM_CLASS_DEF extern const std::string Parity;
				FEDM_CLASS_DEF extern const std::string Databits;
				FEDM_CLASS_DEF extern const std::string Stopbits;
				FEDM_CLASS_DEF extern const std::string ProtocolStartSynchronizationTime;
				FEDM_CLASS_DEF extern const std::string FlashloaderBaudrate;

				/// RS485 or RS422 specific parameters
				namespace RS4xx
				{
					FEDM_CLASS_DEF extern const std::string Enable_TerminationResistors;
				}
			}

			/// %USB specific parameters
			namespace USB
			{
				FEDM_CLASS_DEF extern const std::string Enable_UniformDeviceID;

				/// USB %HID specific parameters
				namespace HID
				{
					FEDM_CLASS_DEF extern const std::string KeyStroke_Delay;
				}
			}

			/// %LAN specific parameters
			namespace LAN
			{
				FEDM_CLASS_DEF extern const std::string PortNumber;

				/// Parameter group for LAN hostname
				namespace Hostname
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Length;
					FEDM_CLASS_DEF extern const std::string Name;
				}

				/// Keep-Alive specific parameters (important when network gets broken)
				namespace Keepalive
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string RetransmissionCount;
					FEDM_CLASS_DEF extern const std::string IdleTime;
					FEDM_CLASS_DEF extern const std::string IntervalTime;
				}

				/// 
				namespace Discovery
				{
					FEDM_CLASS_DEF extern const std::string Enable_FEUDP;
				}

				/// Connection parameters for Localhost (embedded Application)
				namespace LocalHost
				{
					FEDM_CLASS_DEF extern const std::string PortNumber;
				}

				/// %IPv4 specific connection parameters
				namespace IPv4
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Enable_DHCP;
					FEDM_CLASS_DEF extern const std::string IPAddress;
					FEDM_CLASS_DEF extern const std::string PortNumber;
					FEDM_CLASS_DEF extern const std::string SubnetMask;
					FEDM_CLASS_DEF extern const std::string GatewayAddress;
					FEDM_CLASS_DEF extern const std::string Speed;
					FEDM_CLASS_DEF extern const std::string TCP_UserTimeout;
				}

				/// %IPv6 specific connection parameters
				namespace IPv6
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Enable_DHCP;
					FEDM_CLASS_DEF extern const std::string IPAddress;
					FEDM_CLASS_DEF extern const std::string SubnetMask;
					FEDM_CLASS_DEF extern const std::string GatewayAddress;
				}

				/// LAN specific connection parameters
				namespace Autonegotiation
				{
					FEDM_CLASS_DEF extern const std::string Disable;
					FEDM_CLASS_DEF extern const std::string Duplex;
					FEDM_CLASS_DEF extern const std::string Speed;
				}

				/// 
				namespace Remote
				{

					/// 
					namespace Channel1
					{
						FEDM_CLASS_DEF extern const std::string AddressUsage;
						FEDM_CLASS_DEF extern const std::string IPv4Address;
						FEDM_CLASS_DEF extern const std::string IPv6Address;
						FEDM_CLASS_DEF extern const std::string Hostname;
						FEDM_CLASS_DEF extern const std::string PortNumber;
						FEDM_CLASS_DEF extern const std::string ConnectionHoldTime;
						FEDM_CLASS_DEF extern const std::string ResponseTimeout;

						/// 
						namespace Heartbeat
						{
							FEDM_CLASS_DEF extern const std::string Enable;
							FEDM_CLASS_DEF extern const std::string IntervalTime;
						}

						/// 
						namespace DiagEvent
						{
							FEDM_CLASS_DEF extern const std::string Enable;
						}
					}

					/// 
					namespace Channel2
					{
						FEDM_CLASS_DEF extern const std::string AddressUsage;
						FEDM_CLASS_DEF extern const std::string IPv4Address;
						FEDM_CLASS_DEF extern const std::string IPv6Address;
						FEDM_CLASS_DEF extern const std::string Hostname;
						FEDM_CLASS_DEF extern const std::string PortNumber;
						FEDM_CLASS_DEF extern const std::string ConnectionHoldTime;
						FEDM_CLASS_DEF extern const std::string ResponseTimeout;

						/// 
						namespace Heartbeat
						{
							FEDM_CLASS_DEF extern const std::string Enable;
							FEDM_CLASS_DEF extern const std::string IntervalTime;
						}
					}
				}
			}

			/// %WLAN specific parameters
			namespace WLAN
			{
				FEDM_CLASS_DEF extern const std::string PortNumber;
				FEDM_CLASS_DEF extern const std::string NetworkType;
				FEDM_CLASS_DEF extern const std::string AdHocChannel;
				FEDM_CLASS_DEF extern const std::string FrequencyBand;
				FEDM_CLASS_DEF extern const std::string Region;

				/// Parameter group for WLAN hostname
				namespace Hostname
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Length;
					FEDM_CLASS_DEF extern const std::string Name;
				}

				/// Keep-Alive specific parameters (important when network gets broken)
				namespace Keepalive
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string RetransmissionCount;
					FEDM_CLASS_DEF extern const std::string IdleTime;
					FEDM_CLASS_DEF extern const std::string IntervalTime;
				}

				/// 
				namespace AccessPoint
				{
					FEDM_CLASS_DEF extern const std::string Channel;
					FEDM_CLASS_DEF extern const std::string SecurityMode;
					FEDM_CLASS_DEF extern const std::string Enable_HTTPServer;
				}

				/// Connection parameters for secured transmission
				namespace Security
				{
					FEDM_CLASS_DEF extern const std::string AuthenticationType;
					FEDM_CLASS_DEF extern const std::string EncryptionType;

					/// SSID parameters
					namespace ServiceSetIdentifier
					{
						FEDM_CLASS_DEF extern const std::string Enable;
						FEDM_CLASS_DEF extern const std::string Length;
						FEDM_CLASS_DEF extern const std::string SSID;
					}

					/// %WEP Key
					namespace WEP
					{
						FEDM_CLASS_DEF extern const std::string KeyLength;
						FEDM_CLASS_DEF extern const std::string Key;
					}

					/// %WPA Key
					namespace WPA
					{
						FEDM_CLASS_DEF extern const std::string KeyLength;
						FEDM_CLASS_DEF extern const std::string Key;
					}

					/// %WPA2 Key
					namespace WPA2
					{
						FEDM_CLASS_DEF extern const std::string KeyLength;
						FEDM_CLASS_DEF extern const std::string Key;
					}

					/// 
					namespace EAP
					{
						FEDM_CLASS_DEF extern const std::string Method;
						FEDM_CLASS_DEF extern const std::string InnerMethod;
						FEDM_CLASS_DEF extern const std::string UserID;
						FEDM_CLASS_DEF extern const std::string UserPassword;
						FEDM_CLASS_DEF extern const std::string Enable_OKC;
					}
				}

				/// %IPv4 specific connection parameters
				namespace IPv4
				{
					FEDM_CLASS_DEF extern const std::string Enable_IPv4;
					FEDM_CLASS_DEF extern const std::string IPAddress;
					FEDM_CLASS_DEF extern const std::string PortNumber;
					FEDM_CLASS_DEF extern const std::string SubnetMask;
					FEDM_CLASS_DEF extern const std::string GatewayAddress;
					FEDM_CLASS_DEF extern const std::string DNS1;
					FEDM_CLASS_DEF extern const std::string DNS2;
					FEDM_CLASS_DEF extern const std::string Enable_DHCP;
					FEDM_CLASS_DEF extern const std::string TCP_UserTimeout;

					/// Parameters for IPv4 remote connection
					namespace Remote
					{
						FEDM_CLASS_DEF extern const std::string IPAddress;
						FEDM_CLASS_DEF extern const std::string PortNumber;
						FEDM_CLASS_DEF extern const std::string ConnectionHoldTime;
						FEDM_CLASS_DEF extern const std::string Hostname;
					}
				}

				/// %IPv6 specific connection parameters
				namespace IPv6
				{
				}
			}

			/// 
			namespace DNS
			{
				FEDM_CLASS_DEF extern const std::string Static;

				/// 
				namespace Server1
				{
					FEDM_CLASS_DEF extern const std::string AddressUsage;
					FEDM_CLASS_DEF extern const std::string IPv4Address;
					FEDM_CLASS_DEF extern const std::string IPv6Address;
				}

				/// 
				namespace Server2
				{
					FEDM_CLASS_DEF extern const std::string AddressUsage;
					FEDM_CLASS_DEF extern const std::string IPv4Address;
					FEDM_CLASS_DEF extern const std::string IPv6Address;
				}
			}

			/// 
			namespace NTP
			{
				FEDM_CLASS_DEF extern const std::string Enable;
				FEDM_CLASS_DEF extern const std::string Static;

				/// 
				namespace Server1
				{
					FEDM_CLASS_DEF extern const std::string AddressUsage;
					FEDM_CLASS_DEF extern const std::string IPv4Address;
					FEDM_CLASS_DEF extern const std::string IPv6Address;
					FEDM_CLASS_DEF extern const std::string Hostname;
				}

				/// 
				namespace Server2
				{
					FEDM_CLASS_DEF extern const std::string AddressUsage;
					FEDM_CLASS_DEF extern const std::string IPv4Address;
					FEDM_CLASS_DEF extern const std::string IPv6Address;
					FEDM_CLASS_DEF extern const std::string Hostname;
				}
			}

			/// %Bluetooth specific parameters
			namespace Bluetooth
			{
				FEDM_CLASS_DEF extern const std::string DestinationAddress;
				FEDM_CLASS_DEF extern const std::string DeviceName;
				FEDM_CLASS_DEF extern const std::string NameSuffix;
				FEDM_CLASS_DEF extern const std::string Key;
				FEDM_CLASS_DEF extern const std::string PIN;
				FEDM_CLASS_DEF extern const std::string PowerOnTime;

				/// Bluetooth %HID specific parameters
				namespace HID
				{
					FEDM_CLASS_DEF extern const std::string KeyStrokeDelay;
					FEDM_CLASS_DEF extern const std::string AutoReconnect;
				}

				/// Bluetooth classic specific parameters
				namespace Classic
				{
					FEDM_CLASS_DEF extern const std::string MasterMode;
					FEDM_CLASS_DEF extern const std::string PairingMode;
					FEDM_CLASS_DEF extern const std::string PIN;
					FEDM_CLASS_DEF extern const std::string DeviceName;

					/// 
					namespace HID
					{
						FEDM_CLASS_DEF extern const std::string KeyStrokeDelay;
						FEDM_CLASS_DEF extern const std::string AutoReconnect;
					}
				}

				/// BLE specific parameters
				namespace LowEnergy
				{
					FEDM_CLASS_DEF extern const std::string Services;
					FEDM_CLASS_DEF extern const std::string Security;
					FEDM_CLASS_DEF extern const std::string TxPower;
					FEDM_CLASS_DEF extern const std::string KeyStrokeDelay;
					FEDM_CLASS_DEF extern const std::string LocalShortName;
				}
			}

			/// Data-Clock Port specific parameters
			namespace DataClock
			{
				FEDM_CLASS_DEF extern const std::string Format;

				/// %Wiegand specific parameters
				namespace Wiegand
				{
					FEDM_CLASS_DEF extern const std::string Delay;
					FEDM_CLASS_DEF extern const std::string PulseWidth;
					FEDM_CLASS_DEF extern const std::string PulseInterval;
				}
			}

			/// 
			namespace MultiDropBus
			{
				FEDM_CLASS_DEF extern const std::string DeviceAddress;
				FEDM_CLASS_DEF extern const std::string TerminalID;
			}

			/// 
			namespace IrDA
			{

				/// 
				namespace AccessPassword
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Password;
				}
			}

			/// %Miscellaneous communication interface parameters
			namespace Miscellaneous
			{
				FEDM_CLASS_DEF extern const std::string ProtocolSelection;
			}
		}

		/// Configuration parameters for configuring the different working modes
		namespace OperatingMode
		{
			FEDM_CLASS_DEF extern const std::string Mode;
			FEDM_CLASS_DEF extern const std::string EMVco;
			FEDM_CLASS_DEF extern const std::string EMV;
			FEDM_CLASS_DEF extern const std::string PowerOnMode;

			/// Configuration parameters for adjusting the Host-Mode (polling mode)
			namespace HostMode
			{
				FEDM_CLASS_DEF extern const std::string InventoryAbortCondition;

				/// %Filter parameters
				namespace Filter
				{
					FEDM_CLASS_DEF extern const std::string ResponseMode;
				}
			}

			/// Common configuration parameters for adjusting any Auto Read Mode
			namespace AutoReadModes
			{

				/// Parameters for defining event layout
				namespace DataSelector
				{
					FEDM_CLASS_DEF extern const std::string Selector;
					FEDM_CLASS_DEF extern const std::string Date;
					FEDM_CLASS_DEF extern const std::string Time;
					FEDM_CLASS_DEF extern const std::string IDD;
					FEDM_CLASS_DEF extern const std::string DataTidMem;
					FEDM_CLASS_DEF extern const std::string DataEpcMem;
					FEDM_CLASS_DEF extern const std::string DataUserMem;
					FEDM_CLASS_DEF extern const std::string AFI;
					FEDM_CLASS_DEF extern const std::string Antenna;
					FEDM_CLASS_DEF extern const std::string InputEvents;
					FEDM_CLASS_DEF extern const std::string Direction;
					FEDM_CLASS_DEF extern const std::string Signals;
					FEDM_CLASS_DEF extern const std::string ReaderID;

					/// Parameters for defining event data
					namespace Mode
					{
						FEDM_CLASS_DEF extern const std::string ReadCompleteTidBank;
						FEDM_CLASS_DEF extern const std::string ReadCompleteEpcBank;
						FEDM_CLASS_DEF extern const std::string ReadCompleteUserBank;
						FEDM_CLASS_DEF extern const std::string ByteOrderUserBank;
						FEDM_CLASS_DEF extern const std::string EAS_Alarm;
					}
				}

				/// Parameters for defining event data
				namespace DataSource
				{
					FEDM_CLASS_DEF extern const std::string Engine;

					/// Parameters for defining event data from TID bank
					namespace TidBank
					{
						FEDM_CLASS_DEF extern const std::string FirstDataBlock;
						FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
					}

					/// Parameters for defining event data from EPC bank
					namespace EpcBank
					{
						FEDM_CLASS_DEF extern const std::string FirstDataBlock;
						FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
					}

					/// Parameters for defining event data from User bank
					namespace UserBank
					{
						FEDM_CLASS_DEF extern const std::string FirstDataBlock;
						FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
					}
				}

				/// Parameters for defining event buffer behaviour
				namespace DataBuffer
				{
					FEDM_CLASS_DEF extern const std::string BatchMode;
				}

				/// Parameters for filtering event data
				namespace Filter
				{
					FEDM_CLASS_DEF extern const std::string TransponderValidTime;
					FEDM_CLASS_DEF extern const std::string Enable_Input1Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input2Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input3Event;
					FEDM_CLASS_DEF extern const std::string Enable_TriggerEvent;
					FEDM_CLASS_DEF extern const std::string Enable_TimeoutEvent;
				}

				/// %Trigger Parameters
				namespace Trigger
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Mode;
					FEDM_CLASS_DEF extern const std::string Condition;

					/// 
					namespace Source
					{

						/// 
						namespace Input
						{

							/// 
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}
						}
					}
				}
			}

			/// Configuration parameters for adjusting the Buffered-Read-Mode (auto-read mode)
			namespace BufferedReadMode
			{

				/// Parameters for selecting data items
				namespace DataSelector
				{
					FEDM_CLASS_DEF extern const std::string Selector;
					FEDM_CLASS_DEF extern const std::string UID;
					FEDM_CLASS_DEF extern const std::string Data;
					FEDM_CLASS_DEF extern const std::string EAS;
					FEDM_CLASS_DEF extern const std::string AntennaNo;
					FEDM_CLASS_DEF extern const std::string Time;
					FEDM_CLASS_DEF extern const std::string Date;
					FEDM_CLASS_DEF extern const std::string InputEvents;
					FEDM_CLASS_DEF extern const std::string AFI;
					FEDM_CLASS_DEF extern const std::string Direction;
					FEDM_CLASS_DEF extern const std::string TagStatistic;
					FEDM_CLASS_DEF extern const std::string RSSI;
					FEDM_CLASS_DEF extern const std::string ExtensionFlag1;
					FEDM_CLASS_DEF extern const std::string ExtensionFlag2;

					/// Parameters for adjusting the selected data items
					namespace Mode
					{
						FEDM_CLASS_DEF extern const std::string Enable_AntennaPool;
						FEDM_CLASS_DEF extern const std::string ReadCompleteBank;
						FEDM_CLASS_DEF extern const std::string SeekFunction;
						FEDM_CLASS_DEF extern const std::string ChangeAFI;
						FEDM_CLASS_DEF extern const std::string ActionOnEPC;
						FEDM_CLASS_DEF extern const std::string ChangeEAS;
					}
				}

				/// Parameters for defining the sources of Transponder data
				namespace DataSource
				{
					FEDM_CLASS_DEF extern const std::string BankNo;
					FEDM_CLASS_DEF extern const std::string FirstDataBlock;
					FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
					FEDM_CLASS_DEF extern const std::string ByteOrderOfData;
				}

				/// Parameters for filtering event data
				namespace Filter
				{
					FEDM_CLASS_DEF extern const std::string TransponderValidTime;
					FEDM_CLASS_DEF extern const std::string Enable_Input1Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input2Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input3Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input4Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input5Event;
					FEDM_CLASS_DEF extern const std::string Enable_TriggerEvent;
					FEDM_CLASS_DEF extern const std::string Enable_TimeoutEvent;
				}

				/// Parameters for defining trigger conditions
				namespace Trigger
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Condition;
					FEDM_CLASS_DEF extern const std::string Enable_UnlimitTransponderValidTime;
					FEDM_CLASS_DEF extern const std::string RFOffAfterRead;
					FEDM_CLASS_DEF extern const std::string NoReadSignalization;

					/// Parameters for defining the trigger source
					namespace Source
					{

						/// Parameters for trigger source of type %Input
						namespace Input
						{

							/// 1st Input
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 2nd Input
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 3rd Input
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 4th Input
							namespace No4
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 5th Input
							namespace No5
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}
						}
					}
				}

				/// Parameters for %EAS (Electronic Article Surveillance)
				namespace EAS
				{
					FEDM_CLASS_DEF extern const std::string AlarmMode;
					FEDM_CLASS_DEF extern const std::string TagType;
				}

				/// 
				namespace SeekFunction
				{
					FEDM_CLASS_DEF extern const std::string MaskStartAddress;
					FEDM_CLASS_DEF extern const std::string MaskLength;
					FEDM_CLASS_DEF extern const std::string NewAFI;
					FEDM_CLASS_DEF extern const std::string NewEAS;
					FEDM_CLASS_DEF extern const std::string Enable_Password;
					FEDM_CLASS_DEF extern const std::string Password;

					/// 
					namespace Mask
					{
					}
				}

				/// %Miscellaneous configuration parameters
				namespace Miscellaneous
				{
					FEDM_CLASS_DEF extern const std::string NoRfReset;
					FEDM_CLASS_DEF extern const std::string Blacklist;
					FEDM_CLASS_DEF extern const std::string DetectionSensitivity;
				}

				/// 
				namespace Alarm
				{
					FEDM_CLASS_DEF extern const std::string Method;
					FEDM_CLASS_DEF extern const std::string TagBank;
					FEDM_CLASS_DEF extern const std::string TagAddress;
					FEDM_CLASS_DEF extern const std::string TagValue;

					/// 
					namespace LED
					{
						FEDM_CLASS_DEF extern const std::string SettlingMode;
						FEDM_CLASS_DEF extern const std::string SettlingTime;
					}

					/// 
					namespace Buzzer
					{
						FEDM_CLASS_DEF extern const std::string SettlingMode;
						FEDM_CLASS_DEF extern const std::string SettlingTime;
					}
				}
			}

			/// Configuration parameters for adjusting the Notification-Mode (auto-read mode)
			namespace NotificationMode
			{
				FEDM_CLASS_DEF extern const std::string InputMessage;
				FEDM_CLASS_DEF extern const std::string Interface;

				/// Parameters for selecting data items
				namespace DataSelector
				{
					FEDM_CLASS_DEF extern const std::string Selector;
					FEDM_CLASS_DEF extern const std::string UID;
					FEDM_CLASS_DEF extern const std::string Data;
					FEDM_CLASS_DEF extern const std::string EAS;
					FEDM_CLASS_DEF extern const std::string AntennaNo;
					FEDM_CLASS_DEF extern const std::string Time;
					FEDM_CLASS_DEF extern const std::string Date;
					FEDM_CLASS_DEF extern const std::string InputEvents;
					FEDM_CLASS_DEF extern const std::string MacAddress;
					FEDM_CLASS_DEF extern const std::string AFI;
					FEDM_CLASS_DEF extern const std::string Direction;
					FEDM_CLASS_DEF extern const std::string RSSI;
					FEDM_CLASS_DEF extern const std::string ExtensionFlag1;
					FEDM_CLASS_DEF extern const std::string ExtensionFlag2;

					/// Parameters for adjusting the selected data items
					namespace Mode
					{
						FEDM_CLASS_DEF extern const std::string Enable_AntennaPool;
						FEDM_CLASS_DEF extern const std::string ReadCompleteBank;
						FEDM_CLASS_DEF extern const std::string ReadCompleteTidBank;
						FEDM_CLASS_DEF extern const std::string ReadCompleteEpcBank;
						FEDM_CLASS_DEF extern const std::string ReadCompleteUserBank;
						FEDM_CLASS_DEF extern const std::string SeekFunction;
						FEDM_CLASS_DEF extern const std::string ChangeAFI;
						FEDM_CLASS_DEF extern const std::string ActionOnEPC;
						FEDM_CLASS_DEF extern const std::string ChangeEAS;
					}
				}

				/// Parameters for defining the sources of Transponder data
				namespace DataSource
				{
					FEDM_CLASS_DEF extern const std::string BankNo;
					FEDM_CLASS_DEF extern const std::string FirstDataBlock;
					FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
					FEDM_CLASS_DEF extern const std::string ByteOrderOfData;
					FEDM_CLASS_DEF extern const std::string FirstByte;
					FEDM_CLASS_DEF extern const std::string NoOfBytes;

					/// %Miscellaneous configuration parameters
					namespace Miscellaneous
					{

						/// 
						namespace ISO_14443
						{

							/// 
							namespace Part4
							{
								FEDM_CLASS_DEF extern const std::string ByteOrderOfData;
							}
						}
					}

					/// Access parameters for %Mifare Transponders
					namespace Mifare
					{

						/// Access parameters for Mifare %Classic Transponders
						namespace Classic
						{
							FEDM_CLASS_DEF extern const std::string AppID;
							FEDM_CLASS_DEF extern const std::string KeyAddress;
							FEDM_CLASS_DEF extern const std::string KeyType;
						}

						/// Access parameters for Mifare %Ultralight Transponders
						namespace Ultralight
						{
							FEDM_CLASS_DEF extern const std::string Enable_Authentication;
							FEDM_CLASS_DEF extern const std::string KeyAddress;
						}

						/// Access parameters for Mifare %DESFire Transponders
						namespace DESFire
						{
							FEDM_CLASS_DEF extern const std::string Enable_Authentication;
							FEDM_CLASS_DEF extern const std::string AppID;
							FEDM_CLASS_DEF extern const std::string KeyNumber;
							FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
							FEDM_CLASS_DEF extern const std::string FileType;
							FEDM_CLASS_DEF extern const std::string FileNumber;
							FEDM_CLASS_DEF extern const std::string FileCommSettings;
							FEDM_CLASS_DEF extern const std::string FileOffset;
							FEDM_CLASS_DEF extern const std::string FileLength;
						}

						/// 
						namespace Plus
						{

							/// 
							namespace SecurityLevel1
							{
								FEDM_CLASS_DEF extern const std::string Enable_Authentication;
								FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
							}

							/// 
							namespace SecurityLevel3
							{
								FEDM_CLASS_DEF extern const std::string Enable_Authentication;
								FEDM_CLASS_DEF extern const std::string KeyType;
								FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
								FEDM_CLASS_DEF extern const std::string ReadCommand;
								FEDM_CLASS_DEF extern const std::string BlockNumber;
								FEDM_CLASS_DEF extern const std::string Ext;
								FEDM_CLASS_DEF extern const std::string AppID;
								FEDM_CLASS_DEF extern const std::string FirstByte;
								FEDM_CLASS_DEF extern const std::string NoOfBytes;
							}
						}
					}
				}

				/// 
				namespace AutoWrite
				{
					FEDM_CLASS_DEF extern const std::string AFI1;
					FEDM_CLASS_DEF extern const std::string AFI2;
				}

				/// Parameters for filtering event data
				namespace Filter
				{
					FEDM_CLASS_DEF extern const std::string TransponderValidTime;
					FEDM_CLASS_DEF extern const std::string Enable_Input1Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input2Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input3Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input4Event;
					FEDM_CLASS_DEF extern const std::string Enable_Input5Event;
					FEDM_CLASS_DEF extern const std::string Enable_TriggerEvent;
					FEDM_CLASS_DEF extern const std::string Enable_TimeoutEvent;
				}

				/// Parameters for defining trigger conditions
				namespace Trigger
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Condition;
					FEDM_CLASS_DEF extern const std::string Enable_UnlimitTransponderValidTime;
					FEDM_CLASS_DEF extern const std::string RFOffAfterRead;
					FEDM_CLASS_DEF extern const std::string NoReadSignalization;

					/// Parameters for defining the trigger source
					namespace Source
					{

						/// Parameters for trigger source of type %Input
						namespace Input
						{

							/// 1st Input
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 2nd Input
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 3rd Input
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 4th Input
							namespace No4
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 5th Input
							namespace No5
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}
						}
					}
				}

				/// Parameters for %EAS (Electronic Article Surveillance)
				namespace EAS
				{
					FEDM_CLASS_DEF extern const std::string AlarmMode;
					FEDM_CLASS_DEF extern const std::string TagType;
				}

				/// Parameters for defining transmission parameters
				namespace Transmission
				{
					FEDM_CLASS_DEF extern const std::string ResponseTimeout;
					FEDM_CLASS_DEF extern const std::string NotifyTrigger;
					FEDM_CLASS_DEF extern const std::string TimeTriggeredTime;
					FEDM_CLASS_DEF extern const std::string DataSetsLimit;
					FEDM_CLASS_DEF extern const std::string Enable_Acknowledge;

					/// Parameters for defining the transmission destination
					namespace Destination
					{
						FEDM_CLASS_DEF extern const std::string PortNumber;
						FEDM_CLASS_DEF extern const std::string ConnectionHoldTime;

						/// %IPv4 specific connection parameters
						namespace IPv4
						{
							FEDM_CLASS_DEF extern const std::string IPAddress;
							FEDM_CLASS_DEF extern const std::string TCP_UserTimeout;
						}

						/// %IPv6 specific connection parameters
						namespace IPv6
						{
						}
					}

					/// Keep-Alive specific parameters (important when network gets broken)
					namespace KeepAlive
					{
						FEDM_CLASS_DEF extern const std::string Enable;
						FEDM_CLASS_DEF extern const std::string IntervalTime;
					}
				}

				/// 
				namespace SeekFunction
				{
					FEDM_CLASS_DEF extern const std::string MaskStartAddress;
					FEDM_CLASS_DEF extern const std::string MaskLength;
					FEDM_CLASS_DEF extern const std::string NewAFI;
					FEDM_CLASS_DEF extern const std::string NewEAS;
					FEDM_CLASS_DEF extern const std::string Enable_Password;
					FEDM_CLASS_DEF extern const std::string Password;

					/// 
					namespace Mask
					{
					}
				}

				/// Parameters for defining event parameters of Gate-People-Counter
				namespace GatePeopleCounter
				{

					/// Parameters for defining transmission parameters
					namespace Transmission
					{

						/// Parameters for defining the transmission destination
						namespace Destination
						{
							FEDM_CLASS_DEF extern const std::string PortNumber;

							/// %IPv4 specific connection parameters
							namespace IPv4
							{
								FEDM_CLASS_DEF extern const std::string IPAddress;
							}
						}
					}
				}

				/// %Miscellaneous configuration parameters
				namespace Miscellaneous
				{
					FEDM_CLASS_DEF extern const std::string Blacklist;
					FEDM_CLASS_DEF extern const std::string DetectionSensitivity;
				}

				/// 
				namespace Alarm
				{
					FEDM_CLASS_DEF extern const std::string Method;
					FEDM_CLASS_DEF extern const std::string TagBank;
					FEDM_CLASS_DEF extern const std::string TagAddress;
					FEDM_CLASS_DEF extern const std::string TagValue;

					/// 
					namespace LED
					{
						FEDM_CLASS_DEF extern const std::string SettlingMode;
						FEDM_CLASS_DEF extern const std::string SettlingTime;
					}

					/// 
					namespace Buzzer
					{
						FEDM_CLASS_DEF extern const std::string SettlingMode;
						FEDM_CLASS_DEF extern const std::string SettlingTime;
					}
				}
			}

			/// Configuration parameters for adjusting the Scan-Mode (auto-read mode)
			namespace ScanMode
			{
				FEDM_CLASS_DEF extern const std::string Interface;
				FEDM_CLASS_DEF extern const std::string Framing;
				FEDM_CLASS_DEF extern const std::string Mode;

				/// Parameters for selecting data items
				namespace DataSelector
				{
					FEDM_CLASS_DEF extern const std::string Selector;
					FEDM_CLASS_DEF extern const std::string IDD;
					FEDM_CLASS_DEF extern const std::string UID;
					FEDM_CLASS_DEF extern const std::string Data;
					FEDM_CLASS_DEF extern const std::string EAS;
					FEDM_CLASS_DEF extern const std::string AntennaNo;
					FEDM_CLASS_DEF extern const std::string Time;
					FEDM_CLASS_DEF extern const std::string Date;
					FEDM_CLASS_DEF extern const std::string InputEvents;
					FEDM_CLASS_DEF extern const std::string ScannerID;
					FEDM_CLASS_DEF extern const std::string MifareAppID;
					FEDM_CLASS_DEF extern const std::string Direction;
					FEDM_CLASS_DEF extern const std::string RSSI;
					FEDM_CLASS_DEF extern const std::string ExtensionFlag1;
					FEDM_CLASS_DEF extern const std::string ExtensionFlag2;

					/// Parameters for adjusting the selected data items
					namespace Mode
					{
						FEDM_CLASS_DEF extern const std::string Enable_AntennaPool;
						FEDM_CLASS_DEF extern const std::string Enable_IndependentTransmission;
						FEDM_CLASS_DEF extern const std::string ReadCompleteBank;
					}
				}

				/// Parameters for defining the sources of Transponder data
				namespace DataSource
				{
					FEDM_CLASS_DEF extern const std::string Engine;
					FEDM_CLASS_DEF extern const std::string BankNo;
					FEDM_CLASS_DEF extern const std::string FirstDataBlock;
					FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
					FEDM_CLASS_DEF extern const std::string ByteOrderOfData;
					FEDM_CLASS_DEF extern const std::string ByteOrderOfData_ProcessorCards;
					FEDM_CLASS_DEF extern const std::string FirstByte;
					FEDM_CLASS_DEF extern const std::string NoOfBytes;

					/// 
					namespace IDD
					{
						FEDM_CLASS_DEF extern const std::string Format;
					}

					/// Parameters for defining event data from TID bank
					namespace TidBank
					{
						FEDM_CLASS_DEF extern const std::string FirstByte;
						FEDM_CLASS_DEF extern const std::string NoOfBytes;
					}

					/// Parameters for defining event data from EPC bank
					namespace EpcBank
					{
						FEDM_CLASS_DEF extern const std::string FirstByte;
						FEDM_CLASS_DEF extern const std::string NoOfBytes;
						FEDM_CLASS_DEF extern const std::string Format;
					}

					/// Parameters for defining event data from User bank
					namespace UserBank
					{
						FEDM_CLASS_DEF extern const std::string FirstByte;
						FEDM_CLASS_DEF extern const std::string NoOfBytes;
						FEDM_CLASS_DEF extern const std::string Format;
					}

					/// Access parameters for %Mifare Transponders
					namespace Mifare
					{

						/// Access parameters for Mifare %Classic Transponders
						namespace Classic
						{
							FEDM_CLASS_DEF extern const std::string AppID;
							FEDM_CLASS_DEF extern const std::string KeyAddress;
							FEDM_CLASS_DEF extern const std::string KeyType;
						}

						/// Access parameters for Mifare %DESFire Transponders
						namespace DESFire
						{
							FEDM_CLASS_DEF extern const std::string AppID;
							FEDM_CLASS_DEF extern const std::string KeyNumber;
							FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
							FEDM_CLASS_DEF extern const std::string FileType;
							FEDM_CLASS_DEF extern const std::string FileNumber;
							FEDM_CLASS_DEF extern const std::string FileCommSettings;
							FEDM_CLASS_DEF extern const std::string FileOffset;
							FEDM_CLASS_DEF extern const std::string FileLength;
							FEDM_CLASS_DEF extern const std::string EnableAuthentication;
						}

						/// 
						namespace PLUS
						{

							/// 
							namespace SecurityLevel1
							{
								FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
								FEDM_CLASS_DEF extern const std::string EnableAuthentication;
							}

							/// 
							namespace SecurityLevel3
							{
								FEDM_CLASS_DEF extern const std::string KeyType;
								FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
								FEDM_CLASS_DEF extern const std::string ReadCommand;
								FEDM_CLASS_DEF extern const std::string FirstDataBlock;
								FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
								FEDM_CLASS_DEF extern const std::string AppID;
								FEDM_CLASS_DEF extern const std::string EnableAuthentication;
							}
						}

						/// 
						namespace UltralightC
						{
							FEDM_CLASS_DEF extern const std::string KeyAddress;
							FEDM_CLASS_DEF extern const std::string EnableAuthentication;
						}
					}

					/// 
					namespace ISO_14443_3
					{
						FEDM_CLASS_DEF extern const std::string FirstDataBlock;
						FEDM_CLASS_DEF extern const std::string FirstByte;
						FEDM_CLASS_DEF extern const std::string NoOfBytes;
					}

					/// 
					namespace ISO_15693_18000
					{
						FEDM_CLASS_DEF extern const std::string FirstDataBlock;
						FEDM_CLASS_DEF extern const std::string FirstByte;
						FEDM_CLASS_DEF extern const std::string NoOfBytes;
					}

					/// 
					namespace ISO_18000_3M3
					{
						FEDM_CLASS_DEF extern const std::string BankNo;
					}
				}

				/// Parameters for formatting the data output
				namespace DataFormat
				{
					FEDM_CLASS_DEF extern const std::string BusAddressPrefix;
					FEDM_CLASS_DEF extern const std::string Format;
					FEDM_CLASS_DEF extern const std::string DoNoTransmitPCofEPC;
					FEDM_CLASS_DEF extern const std::string NoOfUserHeaderChars;
					FEDM_CLASS_DEF extern const std::string UserHeaderChar1;
					FEDM_CLASS_DEF extern const std::string UserHeaderChar2;
					FEDM_CLASS_DEF extern const std::string UserHeaderChar3;
					FEDM_CLASS_DEF extern const std::string UserHeaderChar4;
					FEDM_CLASS_DEF extern const std::string SeparationChar;
					FEDM_CLASS_DEF extern const std::string UserSeparationChar;
					FEDM_CLASS_DEF extern const std::string EndChar;
					FEDM_CLASS_DEF extern const std::string NoOfUserEndChars;
					FEDM_CLASS_DEF extern const std::string UserEndChar;
					FEDM_CLASS_DEF extern const std::string UserEndChar1;
					FEDM_CLASS_DEF extern const std::string UserEndChar2;
					FEDM_CLASS_DEF extern const std::string UserEndChar3;
					FEDM_CLASS_DEF extern const std::string UidInBcd;
					FEDM_CLASS_DEF extern const std::string PrefixLength;
					FEDM_CLASS_DEF extern const std::string Prefix;
					FEDM_CLASS_DEF extern const std::string SuffixLength;
					FEDM_CLASS_DEF extern const std::string Suffix;
				}

				/// Parameters for filtering event data
				namespace Filter
				{
					FEDM_CLASS_DEF extern const std::string ResponseMode;
					FEDM_CLASS_DEF extern const std::string TransponderValidTime;
				}

				/// Parameters for defining trigger conditions
				namespace Trigger
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Mode;
					FEDM_CLASS_DEF extern const std::string Condition;
					FEDM_CLASS_DEF extern const std::string Enable_UnlimitTransponderValidTime;
					FEDM_CLASS_DEF extern const std::string RFOffAfterRead;
					FEDM_CLASS_DEF extern const std::string NoReadSignalization;

					/// Parameters for defining the trigger source
					namespace Source
					{

						/// Parameters for trigger source of type %Input
						namespace Input
						{

							/// 1st Input
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 2nd Input
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 3rd Input
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 4th Input
							namespace No4
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 5th Input
							namespace No5
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}
						}
					}
				}

				/// Parameters for %EAS (Electronic Article Surveillance)
				namespace EAS
				{
					FEDM_CLASS_DEF extern const std::string AlarmMode;
					FEDM_CLASS_DEF extern const std::string TagType;
				}

				/// 
				namespace Transmission
				{
					FEDM_CLASS_DEF extern const std::string Timeout;

					/// 
					namespace Destination
					{
						FEDM_CLASS_DEF extern const std::string Mode;
						FEDM_CLASS_DEF extern const std::string PortNumber;

						/// 
						namespace IPv4
						{
							FEDM_CLASS_DEF extern const std::string IPAddress;
							FEDM_CLASS_DEF extern const std::string Hostname;
						}
					}
				}
			}

			/// Configuration parameters for adjusting the Access-Mode (auto-read mode)
			namespace AccessMode
			{
				FEDM_CLASS_DEF extern const std::string Mode;
				FEDM_CLASS_DEF extern const std::string Disable_TeachIn;

				/// 
				namespace Antipassback
				{
					FEDM_CLASS_DEF extern const std::string Mode;
					FEDM_CLASS_DEF extern const std::string TimeOfDayForLockClearing;
				}

				/// 
				namespace AccessControl
				{
					FEDM_CLASS_DEF extern const std::string OnlineRequest;
					FEDM_CLASS_DEF extern const std::string RequestTimeout;
				}

				/// Parameters for selecting data items
				namespace DataSelector
				{
					FEDM_CLASS_DEF extern const std::string UID;
					FEDM_CLASS_DEF extern const std::string Data;
				}

				/// Parameters for defining the sources of Transponder data
				namespace DataSource
				{
					FEDM_CLASS_DEF extern const std::string BankNo;
					FEDM_CLASS_DEF extern const std::string FirstDataBlock;
					FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
					FEDM_CLASS_DEF extern const std::string ByteOrderOfData;
					FEDM_CLASS_DEF extern const std::string FirstByte;
					FEDM_CLASS_DEF extern const std::string NoOfBytes;

					/// 
					namespace Miscellaneous
					{

						/// 
						namespace ISO_14443
						{

							/// 
							namespace Part4
							{
								FEDM_CLASS_DEF extern const std::string ByteOrderOfData;
							}
						}
					}

					/// 
					namespace Mifare
					{

						/// 
						namespace Classic
						{
							FEDM_CLASS_DEF extern const std::string AppID;
							FEDM_CLASS_DEF extern const std::string KeyAddress;
							FEDM_CLASS_DEF extern const std::string KeyType;
						}

						/// 
						namespace Ultralight
						{
							FEDM_CLASS_DEF extern const std::string Enable_Authentication;
							FEDM_CLASS_DEF extern const std::string KeyAddress;
						}

						/// Access parameters for Mifare %DESFire Transponders
						namespace DESFire
						{
							FEDM_CLASS_DEF extern const std::string Enable_Authentication;
							FEDM_CLASS_DEF extern const std::string AppID;
							FEDM_CLASS_DEF extern const std::string KeyNumber;
							FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
							FEDM_CLASS_DEF extern const std::string FileType;
							FEDM_CLASS_DEF extern const std::string FileNumber;
							FEDM_CLASS_DEF extern const std::string FileCommSettings;
							FEDM_CLASS_DEF extern const std::string FileOffset;
							FEDM_CLASS_DEF extern const std::string FileLength;
						}

						/// 
						namespace Plus
						{

							/// 
							namespace SecurityLevel1
							{
								FEDM_CLASS_DEF extern const std::string Enable_Authentication;
								FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
							}

							/// 
							namespace SecurityLevel3
							{
								FEDM_CLASS_DEF extern const std::string Enable_Authentication;
								FEDM_CLASS_DEF extern const std::string KeyType;
								FEDM_CLASS_DEF extern const std::string ReaderKeyIndex;
								FEDM_CLASS_DEF extern const std::string ReadCommand;
								FEDM_CLASS_DEF extern const std::string BlockNumber;
								FEDM_CLASS_DEF extern const std::string Ext;
								FEDM_CLASS_DEF extern const std::string AppID;
								FEDM_CLASS_DEF extern const std::string FirstByte;
								FEDM_CLASS_DEF extern const std::string NoOfBytes;
							}
						}
					}
				}

				/// Parameters for filtering event data
				namespace Filter
				{
					FEDM_CLASS_DEF extern const std::string TransponderValidTime;
					FEDM_CLASS_DEF extern const std::string Enable_EventNotification;
					FEDM_CLASS_DEF extern const std::string Enable_AccessEvent;
					FEDM_CLASS_DEF extern const std::string Enable_InputEvent;
					FEDM_CLASS_DEF extern const std::string Enable_AlarmEvent;
				}

				/// Parameters for defining trigger conditions
				namespace Trigger
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Condition;
					FEDM_CLASS_DEF extern const std::string Enable_UnlimitTransponderValidTime;

					/// Parameters for defining the trigger source
					namespace Source
					{

						/// 
						namespace Input
						{
							FEDM_CLASS_DEF extern const std::string AntennaAssignment;

							/// 
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}

							/// 
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string TriggerUse;
								FEDM_CLASS_DEF extern const std::string HoldTime;
							}
						}
					}
				}

				/// Parameters for defining transmission parameters
				namespace Transmission
				{

					/// Parameters for defining the transmission destination
					namespace Destination
					{
						FEDM_CLASS_DEF extern const std::string PortNumber;
						FEDM_CLASS_DEF extern const std::string ConnectionHoldTime;

						/// %IPv4 specific connection parameters
						namespace IPv4
						{
							FEDM_CLASS_DEF extern const std::string IPAddress;
						}
					}

					/// Keep-Alive specific parameters (important when network gets broken)
					namespace KeepAlive
					{
						FEDM_CLASS_DEF extern const std::string Enable;
						FEDM_CLASS_DEF extern const std::string IntervalTime;
					}

					/// Parameters for formatting the data output
					namespace DataLayout
					{
						FEDM_CLASS_DEF extern const std::string IDD;
						FEDM_CLASS_DEF extern const std::string TimeStamp;
						FEDM_CLASS_DEF extern const std::string Status;
						FEDM_CLASS_DEF extern const std::string Input;
						FEDM_CLASS_DEF extern const std::string AntennaNo;
					}
				}
			}

			/// %Miscellaneous configuration parameters
			namespace Miscellaneous
			{

				/// %HF specific parameters
				namespace HF
				{

					/// 
					namespace ReaderSynchronization
					{
						FEDM_CLASS_DEF extern const std::string Enable_Synchronization;
						FEDM_CLASS_DEF extern const std::string Is_Master;
						FEDM_CLASS_DEF extern const std::string SwitchCondition;
						FEDM_CLASS_DEF extern const std::string RfOffCondition;
						FEDM_CLASS_DEF extern const std::string SynchronizationTimeout;
					}
				}

				/// 
				namespace TransponderIdentification
				{
					FEDM_CLASS_DEF extern const std::string Source;
					FEDM_CLASS_DEF extern const std::string DataBlockNo;
					FEDM_CLASS_DEF extern const std::string NoOfDataBlocks;
				}

				/// 
				namespace Logging
				{
					FEDM_CLASS_DEF extern const std::string Enable;
				}
			}

			/// 
			namespace Payment
			{
				FEDM_CLASS_DEF extern const std::string Interface;

				/// 
				namespace girogo
				{
					FEDM_CLASS_DEF extern const std::string Functions;
					FEDM_CLASS_DEF extern const std::string CreditDisplay;
					FEDM_CLASS_DEF extern const std::string PaymentAck;
					FEDM_CLASS_DEF extern const std::string ConfirmPayment;
					FEDM_CLASS_DEF extern const std::string MerchantReferenceNo;

					/// 
					namespace AutomaticAccountReconciliation
					{
						FEDM_CLASS_DEF extern const std::string TransactionLimit;
					}

					/// 
					namespace SmartCard
					{
						FEDM_CLASS_DEF extern const std::string Enable;
					}
				}
			}
		}

		/// Configuration parameters for adjusting the RF-Interface
		namespace AirInterface
		{
			FEDM_CLASS_DEF extern const std::string TimeLimit;
			FEDM_CLASS_DEF extern const std::string RFPower;
			FEDM_CLASS_DEF extern const std::string RFProfile;
			FEDM_CLASS_DEF extern const std::string ScanTime;

			/// Configuration parameters for adjusting the %Antennas
			namespace Antenna
			{

				/// %HF specific parameters
				namespace HF
				{

					/// Antenna output 1
					namespace No1
					{
						FEDM_CLASS_DEF extern const std::string OutputPower;
						FEDM_CLASS_DEF extern const std::string PowerOnTime;
						FEDM_CLASS_DEF extern const std::string Enable_DCPower;

						/// 
						namespace Filter
						{
							FEDM_CLASS_DEF extern const std::string SensitivityLevel;
						}
					}

					/// Antenna output 2
					namespace No2
					{
						FEDM_CLASS_DEF extern const std::string Enable_DCPower;
					}

					/// Antenna output 3
					namespace No3
					{
						FEDM_CLASS_DEF extern const std::string Enable_DCPower;
					}

					/// Antenna output 4
					namespace No4
					{
						FEDM_CLASS_DEF extern const std::string Enable_DCPower;
					}

					/// %Miscellaneous configuration parameters
					namespace Miscellaneous
					{
						FEDM_CLASS_DEF extern const std::string Enable_PowerUpTuning;
						FEDM_CLASS_DEF extern const std::string Enable_DCPower;
						FEDM_CLASS_DEF extern const std::string MinimumLevelMode;
						FEDM_CLASS_DEF extern const std::string MinimumLevel;
						FEDM_CLASS_DEF extern const std::string Enable_TagDetect;
					}
				}

				/// %UHF specific parameters
				namespace UHF
				{

					/// Antenna output 1
					namespace No1
					{
						FEDM_CLASS_DEF extern const std::string OutputPower;
						FEDM_CLASS_DEF extern const std::string RSSIFilter;
					}

					/// Antenna output 2
					namespace No2
					{
						FEDM_CLASS_DEF extern const std::string OutputPower;
						FEDM_CLASS_DEF extern const std::string RSSIFilter;
					}

					/// Antenna output 3
					namespace No3
					{
						FEDM_CLASS_DEF extern const std::string OutputPower;
						FEDM_CLASS_DEF extern const std::string RSSIFilter;
					}

					/// Antenna output 4
					namespace No4
					{
						FEDM_CLASS_DEF extern const std::string OutputPower;
						FEDM_CLASS_DEF extern const std::string RSSIFilter;
					}

					/// %Miscellaneous configuration parameters
					namespace Miscellaneous
					{
						FEDM_CLASS_DEF extern const std::string Gain;
						FEDM_CLASS_DEF extern const std::string Type;
						FEDM_CLASS_DEF extern const std::string Enable_DCPower;
						FEDM_CLASS_DEF extern const std::string RSSIStartLevel;
					}

					/// 
					namespace Int
					{
						FEDM_CLASS_DEF extern const std::string OutputPower;
						FEDM_CLASS_DEF extern const std::string RSSIFilter;
					}
				}
			}

			/// %Regional settings
			namespace Region
			{

				/// %UHF specific parameters
				namespace UHF
				{
					FEDM_CLASS_DEF extern const std::string Regulation;

					/// Settings for European Union regulation
					namespace EU
					{

						/// %Channel parameters
						namespace Channel
						{

							/// Settings for EN302208 with LBT
							namespace EN302208_with_LBT
							{
								FEDM_CLASS_DEF extern const std::string Enable_865MHz1;
								FEDM_CLASS_DEF extern const std::string Enable_865MHz3;
								FEDM_CLASS_DEF extern const std::string Enable_865MHz5;
								FEDM_CLASS_DEF extern const std::string Enable_865MHz7;
								FEDM_CLASS_DEF extern const std::string Enable_865MHz9;
								FEDM_CLASS_DEF extern const std::string Enable_866MHz1;
								FEDM_CLASS_DEF extern const std::string Enable_866MHz3;
								FEDM_CLASS_DEF extern const std::string Enable_866MHz5;
								FEDM_CLASS_DEF extern const std::string Enable_866MHz7;
								FEDM_CLASS_DEF extern const std::string Enable_866MHz9;
								FEDM_CLASS_DEF extern const std::string Enable_867MHz1;
								FEDM_CLASS_DEF extern const std::string Enable_867MHz3;
								FEDM_CLASS_DEF extern const std::string Enable_867MHz5;
								FEDM_CLASS_DEF extern const std::string Enable_867MHz7;
								FEDM_CLASS_DEF extern const std::string Enable_867MHz9;
							}

							/// Settings for EN302208 4-Channel-Plan
							namespace EN302208_4_ChannelPlan
							{

								/// Preferred channels for EN302208 4-Channel-Plan
								namespace PreferredChannels
								{
									FEDM_CLASS_DEF extern const std::string NoOfChannels;
									FEDM_CLASS_DEF extern const std::string ChannelNo1;
									FEDM_CLASS_DEF extern const std::string ChannelNo2;
									FEDM_CLASS_DEF extern const std::string ChannelNo3;
									FEDM_CLASS_DEF extern const std::string ChannelNo4;
								}
							}

							/// Settings for %EN300220
							namespace EN300220
							{
								FEDM_CLASS_DEF extern const std::string Disable_869MHz_FallbackChannel;
							}

							/// 
							namespace Morocco
							{
								FEDM_CLASS_DEF extern const std::string ChannelNo1;
							}
						}
					}

					/// Settings for %FCC regulation
					namespace FCC
					{

						/// %Channel parameters
						namespace Channel
						{
							FEDM_CLASS_DEF extern const std::string ChannelAllocationMode;
							FEDM_CLASS_DEF extern const std::string UpperChannel;
							FEDM_CLASS_DEF extern const std::string LowerChannel;

							/// 
							namespace Japan
							{
								FEDM_CLASS_DEF extern const std::string LowerChannel;
								FEDM_CLASS_DEF extern const std::string UpperChannel;
							}
						}
					}

					/// Settings for %Korea regulation
					namespace Korea
					{

						/// %Channel parameters
						namespace Channel
						{
							FEDM_CLASS_DEF extern const std::string LowerChannel;
							FEDM_CLASS_DEF extern const std::string UpperChannel;
							FEDM_CLASS_DEF extern const std::string ChannelAllocationMode;
						}
					}
				}
			}

			/// Configuration parameters for internal or external %Multiplexer
			namespace Multiplexer
			{
				FEDM_CLASS_DEF extern const std::string Enable;
				FEDM_CLASS_DEF extern const std::string EnableAntennas;
				FEDM_CLASS_DEF extern const std::string SelectedDefaultAntenna;

				/// %HF specific settings
				namespace HF
				{

					/// 
					namespace Internal
					{
						FEDM_CLASS_DEF extern const std::string AntennaSelectionMode;
						FEDM_CLASS_DEF extern const std::string NoOfAntennas;
						FEDM_CLASS_DEF extern const std::string SelectedAntennas;

						/// 
						namespace Antenna
						{

							/// 
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// 
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// 
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// 
							namespace No4
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// 
							namespace No5
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// 
							namespace No6
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// 
							namespace No7
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// 
							namespace No8
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}
						}
					}

					/// %External Multiplexer
					namespace External
					{
						FEDM_CLASS_DEF extern const std::string SwitchCondition;
						FEDM_CLASS_DEF extern const std::string InputChannelMode;
						FEDM_CLASS_DEF extern const std::string NoOfOutputChannels;

						/// Settings for %Antenna Outputs
						namespace Antenna
						{

							/// Output 1
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 2
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 3
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 4
							namespace No4
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 5
							namespace No5
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 6
							namespace No6
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 7
							namespace No7
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 8
							namespace No8
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}
						}

						/// 
						namespace Output
						{

							/// 
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string SelectedAntennas;
							}

							/// 
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string SelectedAntennas;
							}

							/// 
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string SelectedAntennas;
							}

							/// 
							namespace No4
							{
								FEDM_CLASS_DEF extern const std::string SelectedAntennas;
							}
						}
					}
				}

				/// %UHF specific settings
				namespace UHF
				{

					/// %Internal Multiplexer
					namespace Internal
					{
						FEDM_CLASS_DEF extern const std::string SwitchCondition;
						FEDM_CLASS_DEF extern const std::string AntennaSelectionMode;
						FEDM_CLASS_DEF extern const std::string NoOfAntennas;
						FEDM_CLASS_DEF extern const std::string SelectedAntennas;

						/// Settings for %Antenna Outputs
						namespace Antenna
						{

							/// Output 1
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 2
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 3
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}

							/// Output 4
							namespace No4
							{
								FEDM_CLASS_DEF extern const std::string ActiveTime;
							}
						}
					}

					/// %External Multiplexer
					namespace External
					{

						/// Settings for Antenna %Outputs
						namespace Output
						{

							/// Output 1
							namespace No1
							{
								FEDM_CLASS_DEF extern const std::string SelectedAntennas;
							}

							/// Output 2
							namespace No2
							{
								FEDM_CLASS_DEF extern const std::string SelectedAntennas;
							}

							/// Output 3
							namespace No3
							{
								FEDM_CLASS_DEF extern const std::string SelectedAntennas;
							}

							/// Output 4
							namespace No4
							{
								FEDM_CLASS_DEF extern const std::string SelectedAntennas;
							}
						}
					}
				}
			}

			/// %Miscellaneous configuration parameters
			namespace Miscellaneous
			{

				/// %HF specific parameters
				namespace HF
				{
					FEDM_CLASS_DEF extern const std::string Modulation;
					FEDM_CLASS_DEF extern const std::string ReceiverChannel;
					FEDM_CLASS_DEF extern const std::string ReceiverSensitivity;

					/// Settings for ISO 15693 and/or ICode1
					namespace ISO_15693_ICode1
					{

						/// Settings for error handling
						namespace ErrorHandling
						{
							FEDM_CLASS_DEF extern const std::string WeakCollision;
						}
					}

					/// Settings for ICode UID and ICode EPC
					namespace ICodeUID_ICodeEPC
					{

						/// Settings for error handling
						namespace ErrorHandling
						{
							FEDM_CLASS_DEF extern const std::string WeakCollision;
						}
					}

					/// Settings for ISO 15693
					namespace ISO_15693
					{
						FEDM_CLASS_DEF extern const std::string Modulation;
						FEDM_CLASS_DEF extern const std::string SubCarrier;
					}

					/// Settings for error handling
					namespace ISO_18000_3M3
					{

						/// Settings for ISO 18000-3M3
						namespace ErrorHandling
						{
							FEDM_CLASS_DEF extern const std::string WeakCollision;
						}
					}

					/// 
					namespace ASK_Modulation
					{

						/// Settings for error handling
						namespace ErrorHandling
						{
							FEDM_CLASS_DEF extern const std::string WeakCollision;
						}
					}

					/// 
					namespace NoiseLevel
					{
					}
				}
			}
		}

		/// Configuration parameters for %Transponder drivers
		namespace Transponder
		{

			/// Transponder %Driver
			namespace Driver
			{
				FEDM_CLASS_DEF extern const std::string Enable_HF;
				FEDM_CLASS_DEF extern const std::string Enable_UHF;

				/// %HF Drivers (in fixed execution order)
				namespace HF
				{
					FEDM_CLASS_DEF extern const std::string Selector;
					FEDM_CLASS_DEF extern const std::string Drivers;
					FEDM_CLASS_DEF extern const std::string ICode1;
					FEDM_CLASS_DEF extern const std::string Tagit_HF;
					FEDM_CLASS_DEF extern const std::string ISO_15693;
					FEDM_CLASS_DEF extern const std::string ISO_14443_TypeA;
					FEDM_CLASS_DEF extern const std::string ISO_14443_TypeB;
					FEDM_CLASS_DEF extern const std::string ICodeEPC;
					FEDM_CLASS_DEF extern const std::string ICodeUID;
					FEDM_CLASS_DEF extern const std::string EPC_Class1Gen2;
					FEDM_CLASS_DEF extern const std::string Jewel;
					FEDM_CLASS_DEF extern const std::string SR176;
					FEDM_CLASS_DEF extern const std::string SRIxx;
					FEDM_CLASS_DEF extern const std::string Microchip_MCRF45x;
					FEDM_CLASS_DEF extern const std::string Keyboard;
					FEDM_CLASS_DEF extern const std::string ISO_18000_3M3;
					FEDM_CLASS_DEF extern const std::string FeliCa;

					/// Drivers, in execution order defined by user
					namespace UserSequenced
					{
						FEDM_CLASS_DEF extern const std::string No1;
						FEDM_CLASS_DEF extern const std::string No2;
						FEDM_CLASS_DEF extern const std::string No3;
						FEDM_CLASS_DEF extern const std::string No4;
						FEDM_CLASS_DEF extern const std::string No5;
						FEDM_CLASS_DEF extern const std::string No6;
						FEDM_CLASS_DEF extern const std::string No7;
						FEDM_CLASS_DEF extern const std::string No8;
						FEDM_CLASS_DEF extern const std::string No9;
						FEDM_CLASS_DEF extern const std::string No10;
						FEDM_CLASS_DEF extern const std::string No11;
						FEDM_CLASS_DEF extern const std::string No12;
						FEDM_CLASS_DEF extern const std::string No13;
						FEDM_CLASS_DEF extern const std::string No14;
					}

					/// Sub-Drivers for ISO 14443
					namespace ISO_14443
					{
						FEDM_CLASS_DEF extern const std::string Drivers;

						/// Sub-Drivers for ISO 14443, Part A
						namespace TypeA
						{
							FEDM_CLASS_DEF extern const std::string MifareStandard;
							FEDM_CLASS_DEF extern const std::string my_d_Proximity_SLE55Rxx;
							FEDM_CLASS_DEF extern const std::string MifareUltraLight;
							FEDM_CLASS_DEF extern const std::string Part4;
						}
					}
				}

				/// %UHF Driver
				namespace UHF
				{
					FEDM_CLASS_DEF extern const std::string Drivers;
					FEDM_CLASS_DEF extern const std::string ISO_18000_6_B;
					FEDM_CLASS_DEF extern const std::string EM4222_EM4444;
					FEDM_CLASS_DEF extern const std::string EPC_Class1Gen1;
					FEDM_CLASS_DEF extern const std::string EPC_Class1Gen2;
				}
			}

			/// Anticollission settings
			namespace Anticollision
			{
				FEDM_CLASS_DEF extern const std::string Enable;
			}

			/// Persistence Reset settings
			namespace PersistenceReset
			{
				FEDM_CLASS_DEF extern const std::string Mode;
				FEDM_CLASS_DEF extern const std::string Time;

				/// Settings for %Antenna outputs
				namespace Antenna
				{

					/// Output 1
					namespace No1
					{
						FEDM_CLASS_DEF extern const std::string PersistenceResetTime;
					}

					/// Output 2
					namespace No2
					{
						FEDM_CLASS_DEF extern const std::string PersistenceResetTime;
					}

					/// Output 3
					namespace No3
					{
						FEDM_CLASS_DEF extern const std::string PersistenceResetTime;
					}

					/// Output 4
					namespace No4
					{
						FEDM_CLASS_DEF extern const std::string PersistenceResetTime;
					}
				}
			}

			/// Configuration parameters for %HF Transponders
			namespace HF
			{

				/// I-Code1 specific settings
				namespace ICode1
				{

					/// %Anticollision settings
					namespace Anticollision
					{
						FEDM_CLASS_DEF extern const std::string MaximalTimeslots;
						FEDM_CLASS_DEF extern const std::string MinimalTimeslots;
						FEDM_CLASS_DEF extern const std::string Timeslots;
					}

					/// Link settings
					namespace LinkRate
					{
						FEDM_CLASS_DEF extern const std::string FastMode;
					}

					/// Mask settings
					namespace SelectionMask
					{
						FEDM_CLASS_DEF extern const std::string FamilyCode;
						FEDM_CLASS_DEF extern const std::string ApplicationIdentifier;
					}

					/// %Miscellaneous configuration parameters
					namespace Miscellaneous
					{
						FEDM_CLASS_DEF extern const std::string MemoryMapping;
						FEDM_CLASS_DEF extern const std::string EASLevel;
					}
				}

				/// ISO 15693 specific settings
				namespace ISO_15693
				{

					/// %Anticollision settings
					namespace Anticollision
					{
						FEDM_CLASS_DEF extern const std::string NoOfTimeslots;
					}

					/// Link settings
					namespace LinkRate
					{
						FEDM_CLASS_DEF extern const std::string DataCoding;
						FEDM_CLASS_DEF extern const std::string DataRate;
					}

					/// Mask settings
					namespace SelectionMask
					{
						FEDM_CLASS_DEF extern const std::string Enable_AFI;
						FEDM_CLASS_DEF extern const std::string AFI1;
						FEDM_CLASS_DEF extern const std::string AFI2;
						FEDM_CLASS_DEF extern const std::string AFI3;
						FEDM_CLASS_DEF extern const std::string AFI4;
					}

					/// %Miscellaneous configuration parameters
					namespace Miscellaneous
					{
						FEDM_CLASS_DEF extern const std::string WriteOption;
						FEDM_CLASS_DEF extern const std::string CommandBreak;
						FEDM_CLASS_DEF extern const std::string Modulation;

						/// Settings for reading Transponder data
						namespace ReadOption
						{
							FEDM_CLASS_DEF extern const std::string ReadMode;
							FEDM_CLASS_DEF extern const std::string BlockSizeSelection;
							FEDM_CLASS_DEF extern const std::string BlockSize;
						}
					}
				}

				/// ICode UID and ICode EPC specific settings
				namespace ICodeUID_ICodeEPC
				{

					/// %Anticollision settings
					namespace Anticollision
					{
						FEDM_CLASS_DEF extern const std::string MinimalTimeslots;
						FEDM_CLASS_DEF extern const std::string MaximalTimeslots;
					}

					/// Mask settings
					namespace SelectionMask
					{
						FEDM_CLASS_DEF extern const std::string MaskLength;
						FEDM_CLASS_DEF extern const std::string Mask;
					}
				}

				/// EPC Class1 Gen2 specific settings
				namespace EPC_Class1Gen2
				{

					/// %Anticollision settings
					namespace Anticollision
					{
						FEDM_CLASS_DEF extern const std::string Session;
					}
				}

				/// ISO 14443 specific settings
				namespace ISO_14443
				{

					/// Link settings
					namespace Bitrate
					{
						FEDM_CLASS_DEF extern const std::string Transmit;
						FEDM_CLASS_DEF extern const std::string Receive;
					}

					/// ISO 14443, Part 4 specific settings
					namespace Part4
					{

						/// %Miscellaneous configuration parameters
						namespace Miscellaneous
						{
							FEDM_CLASS_DEF extern const std::string PowerLevelCheck;
							FEDM_CLASS_DEF extern const std::string ErrorRetry;
						}
					}

					/// ISO 14443, Type A specific settings
					namespace TypeA
					{
						FEDM_CLASS_DEF extern const std::string OptionalInventoryInfo;
						FEDM_CLASS_DEF extern const std::string UID_Order;
					}

					/// ISO 14443, Type B specific settings
					namespace TypeB
					{

						/// Mask settings
						namespace SelectionMask
						{
							FEDM_CLASS_DEF extern const std::string AFI;
						}

						/// %Miscellaneous configuration parameters
						namespace Miscellaneous
						{
							FEDM_CLASS_DEF extern const std::string BitrateSelect;
						}
					}

					/// %Miscellaneous configuration parameters
					namespace Miscellaneous
					{
						FEDM_CLASS_DEF extern const std::string StartupTime;
					}
				}

				/// ISO 18000-3M3 specific settings
				namespace ISO_18000_3M3
				{

					/// Mask settings
					namespace SelectionMask
					{

						/// 1st Mask
						namespace No1
						{
							FEDM_CLASS_DEF extern const std::string Bank;
							FEDM_CLASS_DEF extern const std::string MaskLength;
							FEDM_CLASS_DEF extern const std::string FirstBit;
							FEDM_CLASS_DEF extern const std::string Mask;
							FEDM_CLASS_DEF extern const std::string Operation;
						}
					}

					/// 
					namespace Anticollision
					{
						FEDM_CLASS_DEF extern const std::string Session;
					}
				}

				/// Configuration parameters for Transponder-specific Custom-Commands
				namespace CustomerCommandOptions
				{

					/// EM Microelectronic-Marin SA
					namespace EM_Microelectronic
					{
						FEDM_CLASS_DEF extern const std::string StorageQuiet;
					}

					/// %Fujitsu Limited
					namespace Fujitsu
					{
						FEDM_CLASS_DEF extern const std::string FastInventory;
						FEDM_CLASS_DEF extern const std::string FastCommands;
						FEDM_CLASS_DEF extern const std::string MB89R117_Inventory;
						FEDM_CLASS_DEF extern const std::string MB89R117_Commands;
					}

					/// %Infineon Technologies AG
					namespace Infineon
					{
						FEDM_CLASS_DEF extern const std::string ReadWrite_Commands;
					}

					/// %NXP Semiconductors
					namespace NXP
					{
						FEDM_CLASS_DEF extern const std::string Disable;
						FEDM_CLASS_DEF extern const std::string FastReturnLink;
						FEDM_CLASS_DEF extern const std::string Inventory;
						FEDM_CLASS_DEF extern const std::string InventoryReadPage;
						FEDM_CLASS_DEF extern const std::string InventoryReadBlock;
						FEDM_CLASS_DEF extern const std::string LongRangeCommand;
					}

					/// %STMicroelectronics SA
					namespace STMicroelectronics
					{
						FEDM_CLASS_DEF extern const std::string InitiateInventory;
						FEDM_CLASS_DEF extern const std::string FastCommands;
					}

					/// Texas Instruments
					namespace Texas_Instruments
					{
						FEDM_CLASS_DEF extern const std::string InventoryReadBlock;
						FEDM_CLASS_DEF extern const std::string FastSID;
					}
				}
			}

			/// Configuration parameters for %UHF Transponders
			namespace UHF
			{

				/// ISO 18000-6B specific settings
				namespace ISO_18000_6_B
				{

					/// Link settings
					namespace LinkRate
					{
						FEDM_CLASS_DEF extern const std::string ReturnLinkBitrate;
						FEDM_CLASS_DEF extern const std::string ForwardLinkModulation;
						FEDM_CLASS_DEF extern const std::string ForwardLinkBitrate;
					}

					/// Mask settings
					namespace SelectionMask
					{
						FEDM_CLASS_DEF extern const std::string MaskLength;
						FEDM_CLASS_DEF extern const std::string FirstByte;
						FEDM_CLASS_DEF extern const std::string Operation;
						FEDM_CLASS_DEF extern const std::string Mask;
					}
				}

				/// EPC Class1 Gen1 specific settings
				namespace EPC_Class1Gen1
				{

					/// Link settings
					namespace LinkRate
					{
						FEDM_CLASS_DEF extern const std::string ReturnLinkBitrate;
						FEDM_CLASS_DEF extern const std::string UidLength;
					}

					/// Mask settings
					namespace SelectionMask
					{
						FEDM_CLASS_DEF extern const std::string MaskLength;
						FEDM_CLASS_DEF extern const std::string FirstBit;
						FEDM_CLASS_DEF extern const std::string Mask;
					}
				}

				/// EPC Class1 Gen2 specific settings
				namespace EPC_Class1Gen2
				{

					/// %Anticollision settings
					namespace Anticollision
					{
						FEDM_CLASS_DEF extern const std::string AnticollisionStartValue;
						FEDM_CLASS_DEF extern const std::string Session;
					}

					/// Link settings
					namespace LinkRate
					{
					}

					/// Mask settings
					namespace SelectionMask
					{

						/// 1st Mask
						namespace No1
						{
							FEDM_CLASS_DEF extern const std::string BankNo;
							FEDM_CLASS_DEF extern const std::string MaskLength;
							FEDM_CLASS_DEF extern const std::string FirstBit;
							FEDM_CLASS_DEF extern const std::string Mask;
							FEDM_CLASS_DEF extern const std::string Negation;
							FEDM_CLASS_DEF extern const std::string Enable_EPCTruncation;
						}

						/// 2nd Mask
						namespace No2
						{
							FEDM_CLASS_DEF extern const std::string BankNo;
							FEDM_CLASS_DEF extern const std::string MaskLength;
							FEDM_CLASS_DEF extern const std::string FirstBit;
							FEDM_CLASS_DEF extern const std::string Mask;
							FEDM_CLASS_DEF extern const std::string Negation;
							FEDM_CLASS_DEF extern const std::string Logic;
							FEDM_CLASS_DEF extern const std::string Enable_EPCTruncation;
						}

						/// 3rd Mask
						namespace No3
						{
							FEDM_CLASS_DEF extern const std::string BankNo;
							FEDM_CLASS_DEF extern const std::string MaskLength;
							FEDM_CLASS_DEF extern const std::string FirstBit;
							FEDM_CLASS_DEF extern const std::string Mask;
							FEDM_CLASS_DEF extern const std::string Negation;
							FEDM_CLASS_DEF extern const std::string Logic;
							FEDM_CLASS_DEF extern const std::string Enable_EPCTruncation;
						}
					}

					/// %Miscellaneous configuration parameters
					namespace Miscellaneous
					{
						FEDM_CLASS_DEF extern const std::string WriteOption;
						FEDM_CLASS_DEF extern const std::string TagAuthent;
					}
				}
			}

			/// 
			namespace Blacklist
			{
				FEDM_CLASS_DEF extern const std::string Size;
				FEDM_CLASS_DEF extern const std::string Item1;
				FEDM_CLASS_DEF extern const std::string Item2;
				FEDM_CLASS_DEF extern const std::string Item3;
				FEDM_CLASS_DEF extern const std::string Item4;
			}

			/// %Miscellaneous configuration parameters
			namespace Miscellaneous
			{
				FEDM_CLASS_DEF extern const std::string IdentifierInterpretationMode;
				FEDM_CLASS_DEF extern const std::string TIDLength;
			}
		}

		/// Configuration parameters for %Barcodes
		namespace Barcode
		{
			FEDM_CLASS_DEF extern const std::string Aiming;
			FEDM_CLASS_DEF extern const std::string Light;
			FEDM_CLASS_DEF extern const std::string VideoReverse;
			FEDM_CLASS_DEF extern const std::string ScanTime;
			FEDM_CLASS_DEF extern const std::string DisplayMode;
			FEDM_CLASS_DEF extern const std::string MirroredImage;
			FEDM_CLASS_DEF extern const std::string PicklistMode;
			FEDM_CLASS_DEF extern const std::string TransmitCodeIDCharacter;

			/// Configuration parameters for read sensitivity
			namespace Sensitivity
			{
				FEDM_CLASS_DEF extern const std::string Threshold;
			}

			/// Configuration parameters for 1D-Barcodes
			namespace Type1D
			{
				FEDM_CLASS_DEF extern const std::string Inverse;

				/// AIM 128 parameters
				namespace AIM_128
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
				}

				/// %Codabar parameters
				namespace Codabar
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string Letter;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
					FEDM_CLASS_DEF extern const std::string TransmitStartStopCharacters;
					FEDM_CLASS_DEF extern const std::string StartStopCharacters;
				}

				/// Code 11 parameters
				namespace Code_11
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
					FEDM_CLASS_DEF extern const std::string CheckDigitVerification;
				}

				/// Code 39 parameters
				namespace Code_39
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string Length1;
					FEDM_CLASS_DEF extern const std::string Length2;
					FEDM_CLASS_DEF extern const std::string ASCIIDecode;
					FEDM_CLASS_DEF extern const std::string CheckDigitVerification;
					FEDM_CLASS_DEF extern const std::string ConvertCode39ToCode32;
					FEDM_CLASS_DEF extern const std::string ReducedQuietZone;
					FEDM_CLASS_DEF extern const std::string TransmitCode32Prefix;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
					FEDM_CLASS_DEF extern const std::string TransmitStartStopCharacters;
				}

				/// Code 93 parameters
				namespace Code_93
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string Length1;
					FEDM_CLASS_DEF extern const std::string Length2;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
				}

				/// Code 128 parameters
				namespace Code_128
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string Length1;
					FEDM_CLASS_DEF extern const std::string Length2;
					FEDM_CLASS_DEF extern const std::string ReducedQuietZone;
				}

				/// EAN-8 parameters
				namespace EAN_8
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string ExpandToEAN_13;
					FEDM_CLASS_DEF extern const std::string AddOnCodeRequired;
					FEDM_CLASS_DEF extern const std::string Enable2BitsExpandCharacters;
					FEDM_CLASS_DEF extern const std::string Enable5BitsExpandCharacters;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
				}

				/// EAN-13 parameters
				namespace EAN_13
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string AddOnCodeRequired;
					FEDM_CLASS_DEF extern const std::string Enable2BitsAddendaCode;
					FEDM_CLASS_DEF extern const std::string Enable5BitsAddendaCode;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
				}

				/// GS1-128 parameters
				namespace GS1_128
				{
					FEDM_CLASS_DEF extern const std::string Enable;
				}

				/// GS1-Databar parameters
				namespace GS1_DataBar
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string TransmitApplicationID;
				}

				/// Industrial-25 parameters
				namespace Industrial_25
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
				}

				/// ITF 2-of-5 parameters
				namespace Interleaved_2of5
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string Length1;
					FEDM_CLASS_DEF extern const std::string Length2;
					FEDM_CLASS_DEF extern const std::string CheckDigitVerification;
					FEDM_CLASS_DEF extern const std::string ReducedQuietZone;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit_ITF_6;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit_ITF_14;
				}

				/// %ISBN parameters
				namespace ISBN
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string AddOnCodeRequired;
					FEDM_CLASS_DEF extern const std::string Enable2BitsAddendaCode;
					FEDM_CLASS_DEF extern const std::string Enable5BitsAddendaCode;
					FEDM_CLASS_DEF extern const std::string Format;
				}

				/// ISBT-128 parameters
				namespace ISBT_128
				{
					FEDM_CLASS_DEF extern const std::string Enable;
				}

				/// %ISSN parameters
				namespace ISSN
				{
					FEDM_CLASS_DEF extern const std::string Enable;
				}

				/// ITF-6 parameters
				namespace ITF_6
				{
					FEDM_CLASS_DEF extern const std::string Enable;
				}

				/// ITF-14 parameters
				namespace ITF_14
				{
					FEDM_CLASS_DEF extern const std::string Enable;
				}

				/// Matrix-25 parameters
				namespace Matrix_25
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
				}

				/// MSI-Plessey parameters
				namespace MSI_Plessey
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
					FEDM_CLASS_DEF extern const std::string CheckDigitVerification;
				}

				/// %Plessey parameters
				namespace Plessey
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
				}

				/// Standard-25 parameters
				namespace Standard_25
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
				}

				/// %UPC parameters
				namespace UPC
				{
					FEDM_CLASS_DEF extern const std::string ReducedQuietZone;
				}

				/// UPC-A parameters
				namespace UPC_A
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string AddOnCodeRequired;
					FEDM_CLASS_DEF extern const std::string Enable2BitsAddendaCode;
					FEDM_CLASS_DEF extern const std::string Enable5BitsAddendaCode;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
					FEDM_CLASS_DEF extern const std::string TransmitPrecursor;
				}

				/// UPC-E parameters
				namespace UPC_E
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string ExpandToUPC_A;
					FEDM_CLASS_DEF extern const std::string AddOnCodeRequired;
					FEDM_CLASS_DEF extern const std::string Enable2BitsAddendaCode;
					FEDM_CLASS_DEF extern const std::string Enable5BitsAddendaCode;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
					FEDM_CLASS_DEF extern const std::string TransmitPrecursor;
				}

				/// UPC-E1 parameters
				namespace UPC_E1
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string TransmitCheckDigit;
				}

				/// UCC EAN-128 parameters
				namespace UCC_EAN_128
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
				}
			}

			/// Configuration parameters for 2D-Barcodes
			namespace Type2D
			{

				/// %Aztec parameters
				namespace Aztec
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Inverse;
				}

				/// Datamatrix parameters
				namespace DataMatrix
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string Inverse;
					FEDM_CLASS_DEF extern const std::string DisableRectangularSymbols;
					FEDM_CLASS_DEF extern const std::string MirrorImages;
					FEDM_CLASS_DEF extern const std::string SingleTwin;
					FEDM_CLASS_DEF extern const std::string ForwardBackward;
					FEDM_CLASS_DEF extern const std::string EnableECIOutput;
					FEDM_CLASS_DEF extern const std::string CharacterEncoding;
				}

				/// PDF 417 parameters
				namespace PDF417
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string SingleTwin;
					FEDM_CLASS_DEF extern const std::string ForwardBackward;
					FEDM_CLASS_DEF extern const std::string EnableECIOutput;
					FEDM_CLASS_DEF extern const std::string CharacterEncoding;
				}

				/// QR-Code parameters
				namespace QR_Code
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string SingleTwin;
					FEDM_CLASS_DEF extern const std::string ForwardBackward;
					FEDM_CLASS_DEF extern const std::string EnableECIOutput;
					FEDM_CLASS_DEF extern const std::string CharacterEncoding;
				}

				/// %DotCode parameters
				namespace DotCode
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string Inverse;
					FEDM_CLASS_DEF extern const std::string Mirrored;
					FEDM_CLASS_DEF extern const std::string Prioritize;
				}

				/// Chinese Sensible Code parameters
				namespace Chinese_Sensible_Code
				{
					FEDM_CLASS_DEF extern const std::string Enable;
					FEDM_CLASS_DEF extern const std::string MinMessageLength;
					FEDM_CLASS_DEF extern const std::string MaxMessageLength;
					FEDM_CLASS_DEF extern const std::string SingleTwin;
					FEDM_CLASS_DEF extern const std::string ForwardBackward;
				}
			}
		}

		/// Configuration parameters for digital inputs and outputs, Relays and LEDs
		namespace DigitalIO
		{

			/// Settings for digital buttons
			namespace Button
			{

				/// Settings for trigger button
				namespace Trigger
				{
					FEDM_CLASS_DEF extern const std::string Enable_UnlockTrigger;
					FEDM_CLASS_DEF extern const std::string Function;
					FEDM_CLASS_DEF extern const std::string TransferStringLength;
					FEDM_CLASS_DEF extern const std::string TransferString;
				}

				/// Settings for left button
				namespace Left
				{
					FEDM_CLASS_DEF extern const std::string Enable_PowerOff;
					FEDM_CLASS_DEF extern const std::string Function;
					FEDM_CLASS_DEF extern const std::string TransferStringLength;
					FEDM_CLASS_DEF extern const std::string TransferString;
				}

				/// Settings for right button
				namespace Right
				{
					FEDM_CLASS_DEF extern const std::string Enable_PowerOff;
					FEDM_CLASS_DEF extern const std::string Function;
					FEDM_CLASS_DEF extern const std::string TransferStringLength;
					FEDM_CLASS_DEF extern const std::string TransferString;
				}

				/// 
				namespace Key1
				{
					FEDM_CLASS_DEF extern const std::string Function;
				}

				/// 
				namespace Key2
				{
					FEDM_CLASS_DEF extern const std::string Function;
				}

				/// 
				namespace Key3
				{
					FEDM_CLASS_DEF extern const std::string Function;
				}
			}

			/// Settings for digital inputs
			namespace Input
			{

				/// No 1
				namespace No1
				{
					FEDM_CLASS_DEF extern const std::string Mode;
				}

				/// No 2
				namespace No2
				{
					FEDM_CLASS_DEF extern const std::string Mode;
				}

				/// No 3
				namespace No3
				{
					FEDM_CLASS_DEF extern const std::string Mode;
				}

				/// No 4
				namespace No4
				{
					FEDM_CLASS_DEF extern const std::string Mode;
				}

				/// No 5
				namespace No5
				{
					FEDM_CLASS_DEF extern const std::string Mode;
				}
			}

			/// Settings for digital outputs
			namespace Output
			{
				FEDM_CLASS_DEF extern const std::string OfflineDelay;
				FEDM_CLASS_DEF extern const std::string TagDetectActiveTime;

				/// No 1
				namespace No1
				{
					FEDM_CLASS_DEF extern const std::string IdleMode;
					FEDM_CLASS_DEF extern const std::string IdleFlashMode;
					FEDM_CLASS_DEF extern const std::string SettlingTime;
					FEDM_CLASS_DEF extern const std::string OnlineState;
					FEDM_CLASS_DEF extern const std::string OfflineState;
					FEDM_CLASS_DEF extern const std::string TagDetectState;
					FEDM_CLASS_DEF extern const std::string ActiveState;

					/// Event link
					namespace ReadEventActivation
					{
						FEDM_CLASS_DEF extern const std::string AntennaNo;
					}

					/// Settings for Access-Mode
					namespace AccessMode
					{
						FEDM_CLASS_DEF extern const std::string AccessActiveTime;
					}
				}

				/// No 2
				namespace No2
				{
					FEDM_CLASS_DEF extern const std::string IdleMode;
					FEDM_CLASS_DEF extern const std::string IdleFlashMode;
					FEDM_CLASS_DEF extern const std::string SettlingTime;
					FEDM_CLASS_DEF extern const std::string OnlineState;
					FEDM_CLASS_DEF extern const std::string OfflineState;
					FEDM_CLASS_DEF extern const std::string TagDetectState;
					FEDM_CLASS_DEF extern const std::string ActiveState;

					/// Event link
					namespace ReadEventActivation
					{
						FEDM_CLASS_DEF extern const std::string AntennaNo;
					}

					/// 
					namespace AccessMode
					{
						FEDM_CLASS_DEF extern const std::string AccessActiveTime;
					}
				}

				/// No 3
				namespace No3
				{
					FEDM_CLASS_DEF extern const std::string OnlineState;
					FEDM_CLASS_DEF extern const std::string OfflineState;
					FEDM_CLASS_DEF extern const std::string TagDetectState;
				}
			}

			/// Settings for %Relays
			namespace Relay
			{

				/// No 1
				namespace No1
				{
					FEDM_CLASS_DEF extern const std::string IdleMode;
					FEDM_CLASS_DEF extern const std::string OfflineState;
					FEDM_CLASS_DEF extern const std::string OnlineState;
					FEDM_CLASS_DEF extern const std::string TagDetectState;
					FEDM_CLASS_DEF extern const std::string IdleFlashMode;
					FEDM_CLASS_DEF extern const std::string SettlingTime;
					FEDM_CLASS_DEF extern const std::string ActiveState;

					/// Event link
					namespace ReadEventActivation
					{
						FEDM_CLASS_DEF extern const std::string AntennaNo;
					}

					/// Settings for Access-Mode
					namespace AccessMode
					{
						FEDM_CLASS_DEF extern const std::string AccessActiveTime;
					}
				}

				/// No 2
				namespace No2
				{
					FEDM_CLASS_DEF extern const std::string IdleMode;
					FEDM_CLASS_DEF extern const std::string IdleFlashMode;
					FEDM_CLASS_DEF extern const std::string SettlingTime;
					FEDM_CLASS_DEF extern const std::string ActiveState;

					/// Event link
					namespace ReadEventActivation
					{
						FEDM_CLASS_DEF extern const std::string AntennaNo;
					}
				}

				/// No 3
				namespace No3
				{
					FEDM_CLASS_DEF extern const std::string IdleMode;
					FEDM_CLASS_DEF extern const std::string IdleFlashMode;
					FEDM_CLASS_DEF extern const std::string SettlingTime;
					FEDM_CLASS_DEF extern const std::string ActiveState;

					/// Event link
					namespace ReadEventActivation
					{
						FEDM_CLASS_DEF extern const std::string AntennaNo;
					}
				}

				/// No 4
				namespace No4
				{
					FEDM_CLASS_DEF extern const std::string IdleMode;
					FEDM_CLASS_DEF extern const std::string IdleFlashMode;
					FEDM_CLASS_DEF extern const std::string SettlingTime;

					/// Event link
					namespace ReadEventActivation
					{
						FEDM_CLASS_DEF extern const std::string AntennaNo;
					}
				}
			}

			/// Settings for %Signalers/Buzzers
			namespace Signaler
			{
				FEDM_CLASS_DEF extern const std::string OfflineDelay;
				FEDM_CLASS_DEF extern const std::string Enable_StartupSignal;
				FEDM_CLASS_DEF extern const std::string TagDetectActiveTime;
				FEDM_CLASS_DEF extern const std::string AlarmTimeout;

				/// Automatic activation by sources
				namespace EventSource
				{
					FEDM_CLASS_DEF extern const std::string OfflineDetect;
					FEDM_CLASS_DEF extern const std::string TagDetect;
					FEDM_CLASS_DEF extern const std::string StartupSignal;
					FEDM_CLASS_DEF extern const std::string Input1;
					FEDM_CLASS_DEF extern const std::string Input2;
					FEDM_CLASS_DEF extern const std::string Input3;
				}

				/// Settings for %Buzzers
				namespace Buzzer
				{
					FEDM_CLASS_DEF extern const std::string IdleState;
					FEDM_CLASS_DEF extern const std::string ActiveState;
					FEDM_CLASS_DEF extern const std::string OfflineState;
					FEDM_CLASS_DEF extern const std::string OnlineState;
					FEDM_CLASS_DEF extern const std::string TagDetectState;
					FEDM_CLASS_DEF extern const std::string IdleFlashFrequency;
					FEDM_CLASS_DEF extern const std::string ActiveFlashFrequency;
					FEDM_CLASS_DEF extern const std::string InputFlashFrequency;
					FEDM_CLASS_DEF extern const std::string OfflineFlashFrequency;
					FEDM_CLASS_DEF extern const std::string ActivationTime;
					FEDM_CLASS_DEF extern const std::string ActivationSources;
					FEDM_CLASS_DEF extern const std::string Volume;

					/// Settings for Access-Mode
					namespace AccessMode
					{
						FEDM_CLASS_DEF extern const std::string AccessState;
						FEDM_CLASS_DEF extern const std::string AccessDeniedState;
						FEDM_CLASS_DEF extern const std::string AccessActiveTime;
						FEDM_CLASS_DEF extern const std::string AccessDeniedActiveTime;
						FEDM_CLASS_DEF extern const std::string AlarmState;
					}
				}

				/// Settings for %Vibrators
				namespace Vibrator
				{
					FEDM_CLASS_DEF extern const std::string ActiveState;
					FEDM_CLASS_DEF extern const std::string ActiveFlashFrequency;
					FEDM_CLASS_DEF extern const std::string ActivationTime;
					FEDM_CLASS_DEF extern const std::string ActivationSources;
				}

				/// Settings for %LEDs
				namespace LED
				{
					FEDM_CLASS_DEF extern const std::string Mode;

					/// %Blue LED
					namespace Blue
					{
						FEDM_CLASS_DEF extern const std::string IdleState;
						FEDM_CLASS_DEF extern const std::string ActiveState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
						FEDM_CLASS_DEF extern const std::string IdleFlashFrequency;
						FEDM_CLASS_DEF extern const std::string ActivationTime;
						FEDM_CLASS_DEF extern const std::string ActiveFlashFrequency;

						/// Settings for Access-Mode
						namespace AccessMode
						{
							FEDM_CLASS_DEF extern const std::string AccessState;
							FEDM_CLASS_DEF extern const std::string AccessDeniedState;
							FEDM_CLASS_DEF extern const std::string AccessActiveTime;
							FEDM_CLASS_DEF extern const std::string AccessDeniedActiveTime;
							FEDM_CLASS_DEF extern const std::string AlarmState;
						}
					}

					/// %Green LED
					namespace Green
					{
						FEDM_CLASS_DEF extern const std::string IdleState;
						FEDM_CLASS_DEF extern const std::string ActiveState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
						FEDM_CLASS_DEF extern const std::string IdleFlashFrequency;
						FEDM_CLASS_DEF extern const std::string ActiveFlashFrequency;
						FEDM_CLASS_DEF extern const std::string InputFlashFrequency;
						FEDM_CLASS_DEF extern const std::string OfflineFlashFrequency;
						FEDM_CLASS_DEF extern const std::string ActivationTime;

						/// Settings for Access-Mode
						namespace AccessMode
						{
							FEDM_CLASS_DEF extern const std::string AccessState;
							FEDM_CLASS_DEF extern const std::string AccessDeniedState;
							FEDM_CLASS_DEF extern const std::string AccessActiveTime;
							FEDM_CLASS_DEF extern const std::string AccessDeniedActiveTime;
							FEDM_CLASS_DEF extern const std::string AlarmState;
						}
					}

					/// %Yellow LED
					namespace Yellow
					{
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
						FEDM_CLASS_DEF extern const std::string InputEventActivation;
						FEDM_CLASS_DEF extern const std::string OutputEventActivation;
						FEDM_CLASS_DEF extern const std::string Time;
					}

					/// %Red LED
					namespace Red
					{
						FEDM_CLASS_DEF extern const std::string IdleState;
						FEDM_CLASS_DEF extern const std::string ActiveState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
						FEDM_CLASS_DEF extern const std::string IdleFlashFrequency;
						FEDM_CLASS_DEF extern const std::string ActiveFlashFrequency;
						FEDM_CLASS_DEF extern const std::string InputFlashFrequency;
						FEDM_CLASS_DEF extern const std::string OfflineFlashFrequency;
						FEDM_CLASS_DEF extern const std::string ActivationTime;

						/// Settings for Access-Mode
						namespace AccessMode
						{
							FEDM_CLASS_DEF extern const std::string AccessState;
							FEDM_CLASS_DEF extern const std::string AccessDeniedState;
							FEDM_CLASS_DEF extern const std::string AccessActiveTime;
							FEDM_CLASS_DEF extern const std::string AccessDeniedActiveTime;
							FEDM_CLASS_DEF extern const std::string AlarmState;
						}
					}

					/// LED No 1
					namespace No1
					{
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
					}

					/// LED No 2
					namespace No2
					{
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
					}

					/// LED No 3
					namespace No3
					{
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
					}

					/// LED No 4
					namespace No4
					{
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
					}

					/// LED No 5
					namespace No5
					{
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
					}

					/// LED No 6
					namespace No6
					{
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
					}

					/// LED No 7
					namespace No7
					{
						FEDM_CLASS_DEF extern const std::string OnlineState;
						FEDM_CLASS_DEF extern const std::string OfflineState;
						FEDM_CLASS_DEF extern const std::string TagDetectState;
					}
				}

				/// Settings for traffic lights
				namespace TrafficLight
				{
					FEDM_CLASS_DEF extern const std::string Mode;
					FEDM_CLASS_DEF extern const std::string IdleState;
					FEDM_CLASS_DEF extern const std::string TagDetectState;
					FEDM_CLASS_DEF extern const std::string ActiveFlash;
					FEDM_CLASS_DEF extern const std::string AccessState;
					FEDM_CLASS_DEF extern const std::string AccessDeniedState;
					FEDM_CLASS_DEF extern const std::string AccessFlash;
					FEDM_CLASS_DEF extern const std::string AccessDeniedFlash;
					FEDM_CLASS_DEF extern const std::string ActivationTime;

					/// 
					namespace ReadEventActivation
					{
						FEDM_CLASS_DEF extern const std::string AntennaNo;
					}
				}
			}

			/// %Miscellaneous configuration parameters
			namespace Miscellaneous
			{
				FEDM_CLASS_DEF extern const std::string AFIAssignment;
				FEDM_CLASS_DEF extern const std::string Enable_CPRIO;
				FEDM_CLASS_DEF extern const std::string Enable_CPRMUX;
			}
		}

		/// Configuration parameters for adjusting the power consumption
		namespace PowerManagement
		{
			FEDM_CLASS_DEF extern const std::string Mode;
			FEDM_CLASS_DEF extern const std::string WakeUpPulse;
			FEDM_CLASS_DEF extern const std::string PowerOnTime;
			FEDM_CLASS_DEF extern const std::string AutoPowerOff;
			FEDM_CLASS_DEF extern const std::string RFOnMode;
			FEDM_CLASS_DEF extern const std::string RFOnTime_Min;
			FEDM_CLASS_DEF extern const std::string RFOnTime_Max;
			FEDM_CLASS_DEF extern const std::string RfOffTime;
		}

		/// Configuration parameters for internal clock or timer
		namespace Clock
		{

			/// Settings for Network Time Protocol
			namespace NetworkTimeProtocol
			{
				FEDM_CLASS_DEF extern const std::string Mode;
				FEDM_CLASS_DEF extern const std::string TriggerTime;

				/// %IPv4 specific settings
				namespace IPv4
				{
					FEDM_CLASS_DEF extern const std::string IPAddress;
				}

				/// %IPv6 specific settings
				namespace IPv6
				{
				}
			}
		}

		/// Configuration parameters for Peripheral Devices, like People-Counter
		namespace PeripheralDevice
		{

			/// 
			namespace GatePeopleCounter
			{
				FEDM_CLASS_DEF extern const std::string DirectionMode;
				FEDM_CLASS_DEF extern const std::string DetectionMode;
				FEDM_CLASS_DEF extern const std::string AntennaType;
				FEDM_CLASS_DEF extern const std::string NotifyChannel;

				/// 
				namespace TriggerFilter
				{
					FEDM_CLASS_DEF extern const std::string TimeLimit_TagDetectionBeforeTrigger;
					FEDM_CLASS_DEF extern const std::string TimeLimit_TagDetectionAfterTrigger;
				}

				/// 
				namespace Mode
				{
					FEDM_CLASS_DEF extern const std::string EnableGPC;
					FEDM_CLASS_DEF extern const std::string EnableIO;
					FEDM_CLASS_DEF extern const std::string EnableNotifyCounter;
				}

				/// 
				namespace BusAddr1
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}

						/// 
						namespace No2
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}

						/// 
						namespace No3
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}

				/// 
				namespace BusAddr2
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}

						/// 
						namespace No2
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}

						/// 
						namespace No3
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}

				/// 
				namespace BusAddr3
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}

						/// 
						namespace No2
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}

						/// 
						namespace No3
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}
			}

			/// 
			namespace LedController
			{
				FEDM_CLASS_DEF extern const std::string AlarmColor;

				/// 
				namespace BusAddr11
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}

				/// 
				namespace BusAddr12
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}

				/// 
				namespace BusAddr13
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}

				/// 
				namespace BusAddr14
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}

				/// 
				namespace BusAddr15
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}

				/// 
				namespace BusAddr16
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}

				/// 
				namespace BusAddr17
				{

					/// 
					namespace Output
					{

						/// 
						namespace No1
						{

							/// 
							namespace ReadEventActivation
							{
								FEDM_CLASS_DEF extern const std::string AntennaNo;
							}
						}
					}
				}
			}

			/// 
			namespace Output
			{
				FEDM_CLASS_DEF extern const std::string SettlingMode;
				FEDM_CLASS_DEF extern const std::string SettlingTime;
			}
		}

		/// Additional tools
		namespace SystemTools
		{

			/// %Linux specific tools
			namespace Linux
			{
				FEDM_CLASS_DEF extern const std::string Telnet;
				FEDM_CLASS_DEF extern const std::string ssh;
				FEDM_CLASS_DEF extern const std::string WebServer;
				FEDM_CLASS_DEF extern const std::string FTPServer;
			}
		}

	}
}

#endif // FEDM_READER_CONFIG_PARA_H
