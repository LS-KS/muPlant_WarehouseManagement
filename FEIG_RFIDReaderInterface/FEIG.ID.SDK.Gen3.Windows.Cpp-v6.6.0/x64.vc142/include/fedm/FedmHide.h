/*
 * Copyright (C) FEIG ELECTRONIC GmbH. All rights reserved. Do not disclose.
 *
 * This software is the confidential and proprietary information of
 * FEIG ELECTRONIC GmbH ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with FEIG ELECTRONIC GmbH.
 */

#ifndef FEDM_HIDE_H
#define FEDM_HIDE_H



namespace FEDM {

namespace Internal {
	class ReaderBase;
    class IReaderPrivate;
	class ThTag;
    class FunitWorker;
    class ConfigWorker;
}

namespace Payload {
	class PlBase;
	class PlBuf;
}

namespace Logger {
	class FedmLogger;
}

namespace SmartCardIso7816 {
    class SmartCardSlot;
}

namespace TagHandler {
	class ThIso14443_4_NXP_MifareDesfire_ImplBase;
	class ThIso14443_4_NXP_MifareDesfire_ImplC1;
	class ThIso14443_4_NXP_MifareDesfire_ImplC3;
}

} // end of namespace FEDM


#endif // FEDM_HIDE_H
