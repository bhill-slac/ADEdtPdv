//////////////////////////////////////////////////////////////////////////////
// This file is part of 'ADEdtPdv'.
// It is subject to the license terms in the LICENSE.txt file found in the 
// top-level directory of this distribution and at: 
//    https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html. 
// No part of 'ADEdtPdv', including this file, 
// may be copied, modified, propagated, or distributed except according to 
// the terms contained in the LICENSE.txt file.
//////////////////////////////////////////////////////////////////////////////
//
//	asynEdtPdvSerial.h
//
//	Header file for asynEdtPdvSerial class.
//	It inherits from asynPortDriver and implements
//	serial I/O to EDT framegrabber based camlink cameras
//	via the EDT PDV serial API
//
#ifndef	asynEdtPdvSerial_H
#define	asynEdtPdvSerial_H

#include "asynPortDriver.h"

#include "edtinc.h"

///	asynEdtPdvSerial class
class asynEdtPdvSerial : public asynPortDriver
{
public:		//	Public member functions

	///	Constructor
	asynEdtPdvSerial(	const char			*	portName,
						int						priority	= 0,	// 0 = default 50, high is 90
						int						autoConnect	= 0,	// 0 = no auto-connect
						int						maxBuffers	= 0,	// 0 = unlimited
						size_t					maxMemory	= 0,	// 0 = unlimited
						int						stackSize	= 0		// 0 = default 1MB
						);

	/// Destructor
	virtual ~asynEdtPdvSerial();

	//
	//	asynPortDriver function overrides
	//
    virtual asynStatus	connect(	asynUser	* pasynUser	);

    virtual asynStatus	disconnect(	asynUser	* pasynUser	);

	virtual asynStatus	readOctet(
		asynUser		*	pasynUser,
		char			*	value,
		size_t				maxChars,
		size_t			*	nActual,
		int				*	eomReason	);

	virtual asynStatus	writeOctet(
		asynUser		*	pasynUser,
		const char		*	value,
		size_t				maxChars,
		size_t			*	nActual	);

    void	report(	FILE	*	fp,	int	details	);

	asynStatus	pdvDevConnected(
		PdvDev			*	pPdvDev	);

	asynStatus	pdvDevDisconnected(
		PdvDev			*	pPdvDev	);

	//	Private member variables
	PdvDev			*	m_pPdvDev;
	asynUser		*	m_pasynUser;
	char			*	m_inputEosOctet;
	int					m_inputEosLenOctet;
	char			*	m_outputEosOctet;
	int					m_outputEosLenOctet;
	bool				m_fConnected;
	epicsMutexId		m_serialLock;
};

#endif	//	asynEdtPdvSerial_H
