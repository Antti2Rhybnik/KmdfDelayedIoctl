/*++

Copyright (c) 1997  Microsoft Corporation

Module Name:

    nonpnp.h

Abstract:

    Contains function prototypes and includes other neccessary header files.

Environment:

    Kernel mode only.

--*/

#include <ntddk.h>
#include <wdf.h>

#define NTSTRSAFE_LIB
#include <ntstrsafe.h>
#include <wdmsec.h> // for SDDLs
#include "public.h" // contains IOCTL definitions
#include "Trace.h" // contains macros for WPP tracing

#define NTDEVICE_NAME_STRING      L"\\Device\\NONPNP"
#define SYMBOLIC_NAME_STRING     L"\\DosDevices\\NONPNP"
#define POOL_TAG                   'ELIF'

typedef struct _CONTROL_DEVICE_EXTENSION {

    //HANDLE   FileHandle; // Store your control data here
	WDFTIMER Timer;

} CONTROL_DEVICE_EXTENSION, *PCONTROL_DEVICE_EXTENSION;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(CONTROL_DEVICE_EXTENSION,
                                        ControlGetData)


//
// Device driver routine declarations.
//

typedef struct _MY_TIMER_CTX {

	WDFREQUEST Request;
	size_t InputBufferLength;
	size_t OutputBufferLength;
	ULONG IoControlCode;
	WDFQUEUE Queue;

} MY_TIMER_CTX, *PMY_TIMER_CTX;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(MY_TIMER_CTX, getMyTimerCtx)


DRIVER_INITIALIZE DriverEntry;

//
// Don't use EVT_WDF_DRIVER_DEVICE_ADD for NonPnpDeviceAdd even though 
// the signature is same because this is not an event called by the 
// framework.
//
NTSTATUS
NonPnpDeviceAdd(
	IN WDFDRIVER Driver,
	IN PWDFDEVICE_INIT DeviceInit
);

EVT_WDF_DRIVER_UNLOAD NonPnpEvtDriverUnload;

EVT_WDF_DEVICE_CONTEXT_CLEANUP NonPnpEvtDriverContextCleanup;
EVT_WDF_DEVICE_SHUTDOWN_NOTIFICATION NonPnpShutdown;

EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL FileEvtIoDeviceControl;
EVT_WDF_TIMER TimerCallback;

EVT_WDF_IO_IN_CALLER_CONTEXT NonPnpEvtDeviceIoInCallerContext;

VOID
PrintChars(
	_In_reads_(CountChars) PCHAR BufferAddress,
	_In_ size_t CountChars
);

#pragma warning(disable:4127)

