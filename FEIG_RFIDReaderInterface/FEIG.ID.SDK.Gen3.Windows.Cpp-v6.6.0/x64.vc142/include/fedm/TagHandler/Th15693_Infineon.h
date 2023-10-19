/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO15693_INFINEON_H
#define FEDM_TH_ISO15693_INFINEON_H

#include "TagHandler/Th15693.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 15693 compliant Transponders from manufacturer Infineon Technologies AG
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// All methods are similiar to specific commands of Infineon Technologies AG. Thus, you must refer to the Technical Datasheets to get detailed information about the methods and the parameters.<br>
/// Secondly, all methods of this class are Custom specific commands, realized with the Reader command [0xB1], which are described in the Application Note <i>Infineon Custom and Proprietary Commands.pdf</i>
///
/// @note Programmers should be familiar with the ISO 15693 standard
class FEDM_CLASS_DEF ThIso15693_Infineon : public ThIso15693
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

    /// @brief Command [0xB1][0x10]: Read of Transponder data
	/// @param[in] firstDataBlock First data block address [0..255]
	/// @param[in] noOfDataBlocks Number of data blocks to be read
    /// @param[out] blockSize Number of bytes in each data block
   	/// @param[out] securityStatus Array with received status information, one byte for each data block. The array dimension becomes noOfDataBlocks
	/// @param[out] data Byte container for received data blocks
	/// @return #{DOC_LIB_RETURN_VALUE}
    int read(	size_t firstDataBlock,
                size_t noOfDataBlocks,
                size_t & blockSize,
                std::vector<uint8_t> & securityStatus,
                std::vector<uint8_t> & data);

    /// @brief Command [0xB1][0x30]: Write of Transponder data
	/// @param[in] firstDataBlock First data block address [0..255]
	/// @param[in] noOfDataBlocks Number of data blocks to be read
    /// @param[in] blockSize Number of bytes in each data block
	/// @param[in] data Data of the Data Block to be written to the Transponder
	/// @return #{DOC_LIB_RETURN_VALUE}
    int write(	size_t firstDataBlock,
                size_t noOfDataBlocks,
                size_t blockSize,
                const std::vector<uint8_t> & data);

    /// @brief Command [0xB1][0x90]: Write of Transponder data
	/// @param[in] firstDataBlock First data block address [0..255]
	/// @param[in] noOfDataBlocks Number of data blocks
	/// @return #{DOC_LIB_RETURN_VALUE}
    int writeByte(size_t firstDataBlock, size_t noOfDataBlocks);

	virtual ~ThIso15693_Infineon();

protected:
	ThIso15693_Infineon(Internal::ReaderBase *readerBase, const TagItem & tagItem = TagItem());

}; // end of class ThIso15693_Infineon

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO15693_INFINEON_H
