/*
 * PROJECT:     ReactOS KDBG Kernel Debugger Terminal Driver
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Serial driver
 * COPYRIGHT:   Copyright 2004 Art Yerkes <ayerkes@speakeasy.net>
 *              Copyright 2005 Gregor Anich <blight@blight.eu.org>
 */

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>

/* FUNCTIONS *****************************************************************/

CHAR
KdbpTryGetCharSerial(ULONG Retry)
{
    CHAR Result = -1;

    if (Retry == 0)
        while (!KdPortGetByteEx(&SerialPortInfo, (PUCHAR)&Result));
    else
        while (!KdPortGetByteEx(&SerialPortInfo, (PUCHAR)&Result) && Retry-- > 0);

    return Result;
}