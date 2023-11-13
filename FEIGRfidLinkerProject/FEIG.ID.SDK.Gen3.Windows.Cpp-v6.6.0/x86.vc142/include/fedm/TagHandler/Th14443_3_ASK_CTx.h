/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_TH_ISO14443_3_ASK_CTX_H
#define FEDM_TH_ISO14443_3_ASK_CTX_H

#include "TagHandler/Th14443_3.h"



namespace FEDM {
namespace TagHandler {

/// @brief Transponder class providing manufacturer specific commands for ISO 14443-3 compliant CTx Transponder of type CTx series from manufacturer ASK
///
/// High-level class for easy-to-use Transponder specific communication.<br>
/// See Reader System Manual for detailed information about the command and parameters.
///
/// @note Programmers should be familiar with the ISO 14443 standards
class FEDM_CLASS_DEF ThIso14443_3_ASK_CTx : public ThIso14443_3
{
	friend class Internal::ReaderBase;

public:

	virtual std::string transponderName() const override;

	/// @return Product Code
	///
	/// Method to query the Product Code
	/// The Product Code is part of the Inventory response.
	uint8_t productCode();

	/// @return Fab Code
	///
	/// Method to query the Fab Code
	/// The Fab Code is part of the Inventory response.
	uint8_t fabCode();

	/// @return App Code
	///
	/// Method to query the App Code
	/// The App Code is part of the Inventory response.
	uint8_t appCode();

	/// @return Embedder Code
	///
	/// Method to query the Embedder Code
	/// The Embedder Code is part of the Inventory response.
	uint8_t embedderCode();

	virtual ~ThIso14443_3_ASK_CTx();

protected:
	ThIso14443_3_ASK_CTx(Internal::ReaderBase* readerBase, const TagItem& tagItem = TagItem(), const CardInfo14443& cardInfo = CardInfo14443());

}; // end of class ThIso14443_3_ASK_CTx

}; // end of namespace TagHandler
}; // end of namespace FEDM

#endif // FEDM_TH_ISO14443_3_ASK_CTX_H
