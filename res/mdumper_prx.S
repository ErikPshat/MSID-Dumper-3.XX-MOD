	.set noreorder

#include "pspstub.s"

	STUB_START "mdumper_prx",0x40090000,0x00010005
	STUB_FUNC  0x8B002469,pspMsReadAttrB
	STUB_END
