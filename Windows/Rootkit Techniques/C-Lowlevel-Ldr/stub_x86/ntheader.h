#pragma once

#include <winnt.h>
#include <ntsecapi.h>

#define STATUS_ACCESS_DENIED 0xC0000022
typedef LPVOID *PPVOID;

typedef LONG KPRIORITY;

typedef struct _CLIENT_ID {
	DWORD                   ClientID0;
	DWORD                   ClientID1; // thread id
} CLIENT_ID, *PCLIENT_ID;

typedef struct _LDR_MODULE {
	LIST_ENTRY              InLoadOrderModuleList;
	LIST_ENTRY              InMemoryOrderModuleList;
	LIST_ENTRY              InInitializationOrderModuleList;
	PVOID                   BaseAddress;
	PVOID                   EntryPoint;
	ULONG                   SizeOfImage;
	UNICODE_STRING          FullDllName;
	UNICODE_STRING          BaseDllName;
	ULONG                   Flags;
	SHORT                   LoadCount;
	SHORT                   TlsIndex;
	LIST_ENTRY              HashTableEntry;
	ULONG                   TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

typedef struct _PEB_LDR_DATA {
	ULONG                   Length;
	BOOL                    Initialized;
	PVOID                   SsHandle;
	LIST_ENTRY              InLoadOrderModuleList;
	LIST_ENTRY              InMemoryOrderModuleList;
	LIST_ENTRY              InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _RTL_DRIVE_LETTER_CURDIR {
	USHORT                  Flags;
	USHORT                  Length;
	ULONG                   TimeStamp;
	UNICODE_STRING          DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
	ULONG                   MaximumLength;
	ULONG                   Length;
	ULONG                   Flags;
	ULONG                   DebugFlags;
	PVOID                   ConsoleHandle;
	ULONG                   ConsoleFlags;
	HANDLE                  StdInputHandle;
	HANDLE                  StdOutputHandle;
	HANDLE                  StdErrorHandle;
	UNICODE_STRING          CurrentDirectoryPath;
	HANDLE                  CurrentDirectoryHandle;
	UNICODE_STRING          DllPath;
	UNICODE_STRING          ImagePathName;
	UNICODE_STRING          CommandLine;
	PVOID                   Environment;
	ULONG                   StartingPositionLeft;
	ULONG                   StartingPositionTop;
	ULONG                   Width;
	ULONG                   Height;
	ULONG                   CharWidth;
	ULONG                   CharHeight;
	ULONG                   ConsoleTextAttributes;
	ULONG                   WindowFlags;
	ULONG                   ShowWindowFlags;
	UNICODE_STRING          WindowTitle;
	UNICODE_STRING          DesktopName;
	UNICODE_STRING          ShellInfo;
	UNICODE_STRING          RuntimeData;
	RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _SECTION_IMAGE_INFORMATION {
	PVOID                   EntryPoint;
	ULONG                   StackZeroBits;
	ULONG                   StackReserved;
	ULONG                   StackCommit;
	ULONG                   ImageSubsystem;
	WORD                    SubsystemVersionLow;
	WORD                    SubsystemVersionHigh;
	ULONG                   Unknown1;
	ULONG                   ImageCharacteristics;
	ULONG                   ImageMachineType;
	ULONG                   Unknown2[3];
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _RTL_USER_PROCESS_INFORMATION {
	ULONG                   Size;
	HANDLE                  ProcessHandle;
	HANDLE                  ThreadHandle;
	CLIENT_ID               ClientId;
	SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

typedef void(*PPEBLOCKROUTINE)(PVOID PebLock);

typedef struct _PEB_FREE_BLOCK {
	struct _PEB_FREE_BLOCK  *Next;
	ULONG                   Size;
} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

typedef struct _PEB {
	BOOLEAN                 InheritedAddressSpace;
	BOOLEAN                 ReadImageFileExecOptions;
	BOOLEAN                 BeingDebugged;
	BOOLEAN                 Spare;
	HANDLE                  Mutant;
	PVOID                   ImageBaseAddress;
	PPEB_LDR_DATA           LoaderData;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID                   SubSystemData;
	PVOID                   ProcessHeap;
	PVOID                   FastPebLock;
	PPEBLOCKROUTINE         FastPebLockRoutine;
	PPEBLOCKROUTINE         FastPebUnlockRoutine;
	ULONG                   EnvironmentUpdateCount;
	PPVOID                  KernelCallbackTable;
	PVOID                   EventLogSection;
	PVOID                   EventLog;
	PPEB_FREE_BLOCK         FreeList;
	ULONG                   TlsExpansionCounter;
	PVOID                   TlsBitmap;
	ULONG                   TlsBitmapBits[0x2];
	PVOID                   ReadOnlySharedMemoryBase;
	PVOID                   ReadOnlySharedMemoryHeap;
	PPVOID                  ReadOnlyStaticServerData;
	PVOID                   AnsiCodePageData;
	PVOID                   OemCodePageData;
	PVOID                   UnicodeCaseTableData;
	ULONG                   NumberOfProcessors;
	ULONG                   NtGlobalFlag;
	BYTE                    Spare2[0x4];
	LARGE_INTEGER           CriticalSectionTimeout;
	ULONG                   HeapSegmentReserve;
	ULONG                   HeapSegmentCommit;
	ULONG                   HeapDeCommitTotalFreeThreshold;
	ULONG                   HeapDeCommitFreeBlockThreshold;
	ULONG                   NumberOfHeaps;
	ULONG                   MaximumNumberOfHeaps;
	PPVOID                  *ProcessHeaps;
	PVOID                   GdiSharedHandleTable;
	PVOID                   ProcessStarterHelper;
	PVOID                   GdiDCAttributeList;
	PVOID                   LoaderLock;
	ULONG                   OSMajorVersion;
	ULONG                   OSMinorVersion;
	ULONG                   OSBuildNumber;
	ULONG                   OSPlatformId;
	ULONG                   ImageSubSystem;
	ULONG                   ImageSubSystemMajorVersion;
	ULONG                   ImageSubSystemMinorVersion;
	ULONG                   GdiHandleBuffer[0x22];
	ULONG                   PostProcessInitRoutine;
	ULONG                   TlsExpansionBitmap;
	BYTE                    TlsExpansionBitmapBits[0x80];
	ULONG                   SessionId;
} PEB, *PPEB;

typedef struct _INITIAL_TEB {
	PVOID                   StackBase;
	PVOID                   StackLimit;
	PVOID                   StackCommit;
	PVOID                   StackCommitMax;
	PVOID                   StackReserved;
} INITIAL_TEB, *PINITIAL_TEB;

typedef struct _THREAD_BASIC_INFORMATION {
	NTSTATUS                ExitStatus;
	PVOID                   TebBaseAddress;
	CLIENT_ID               ClientId;
	KAFFINITY               AffinityMask;
	KPRIORITY               Priority;
	KPRIORITY               BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef struct _THREAD_TIMES_INFORMATION {
	LARGE_INTEGER           CreationTime;
	LARGE_INTEGER           ExitTime;
	LARGE_INTEGER           KernelTime;
	LARGE_INTEGER           UserTime;
} THREAD_TIMES_INFORMATION, *PTHREAD_TIMES_INFORMATION;

typedef struct _TEB {
	NT_TIB                  Tib;
	PVOID                   EnvironmentPointer;
	CLIENT_ID               Cid;
	PVOID                   ActiveRpcInfo;
	PVOID                   ThreadLocalStoragePointer;
	PPEB                    Peb;
	ULONG                   LastErrorValue;
	ULONG                   CountOfOwnedCriticalSections;
	PVOID                   CsrClientThread;
	PVOID                   Win32ThreadInfo;
	ULONG                   Win32ClientInfo[0x1F];
	PVOID                   WOW32Reserved;
	ULONG                   CurrentLocale;
	ULONG                   FpSoftwareStatusRegister;
	PVOID                   SystemReserved1[0x36];
	PVOID                   Spare1;
	ULONG                   ExceptionCode;
	ULONG                   SpareBytes1[0x28];
	PVOID                   SystemReserved2[0xA];
	ULONG                   GdiRgn;
	ULONG                   GdiPen;
	ULONG                   GdiBrush;
	CLIENT_ID               RealClientId;
	PVOID                   GdiCachedProcessHandle;
	ULONG                   GdiClientPID;
	ULONG                   GdiClientTID;
	PVOID                   GdiThreadLocaleInfo;
	PVOID                   UserReserved[5];
	PVOID                   GlDispatchTable[0x118];
	ULONG                   GlReserved1[0x1A];
	PVOID                   GlReserved2;
	PVOID                   GlSectionInfo;
	PVOID                   GlSection;
	PVOID                   GlTable;
	PVOID                   GlCurrentRC;
	PVOID                   GlContext;
	NTSTATUS                LastStatusValue;
	UNICODE_STRING          StaticUnicodeString;
	WCHAR                   StaticUnicodeBuffer[0x105];
	PVOID                   DeallocationStack;
	PVOID                   TlsSlots[0x40];
	LIST_ENTRY              TlsLinks;
	PVOID                   Vdm;
	PVOID                   ReservedForNtRpc;
	PVOID                   DbgSsReserved[0x2];
	ULONG                   HardErrorDisabled;
	PVOID                   Instrumentation[0x10];
	PVOID                   WinSockData;
	ULONG                   GdiBatchCount;
	ULONG                   Spare2;
	ULONG                   Spare3;
	ULONG                   Spare4;
	PVOID                   ReservedForOle;
	ULONG                   WaitingOnLoaderLock;
	PVOID                   StackCommit;
	PVOID                   StackCommitMax;
	PVOID                   StackReserved;
} TEB, *PTEB;

struct ModuleInfoNode
{
	LIST_ENTRY LoadOrder;
	LIST_ENTRY InitOrder;
	LIST_ENTRY MemoryOrder;
	HMODULE BaseAddress;		// base address AKA module handle
	unsigned long EntryPoint;
	unsigned int Size;			// size of the modules image
	UNICODE_STRING FullPath;
	UNICODE_STRING Name;
	unsigned long Flags;
	unsigned short LoadCount;
	unsigned short TlsIndex;
	LIST_ENTRY HashTable;		// linked list of any other modules that have the same first letter
	unsigned long Timestamp;
};

typedef struct
{
	WORD	Offset : 12;
	WORD	Type : 4;
} IMAGE_FIXUP_ENTRY, *PIMAGE_FIXUP_ENTRY;

typedef enum _SECTION_INHERIT {

	ViewShare = 1, ViewUnmap = 2

} SECTION_INHERIT, *PSECTION_INHERIT;

typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID    Pointer;
	};
	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct
{
	NTSTATUS ExitStatus;
	void *PebBaseAddress;
	ULONG_PTR AffinityMask;
	KPRIORITY BasePriority;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR InheritedFromUniqueProcessId;
}PROCESS_BASIC_INFORMATION, *PPROCESS_BASIC_INFORMATION;

typedef enum
{
	ProcessBasicInformation,
	ProcessQuotaLimits,
	ProcessIoCounters,
	ProcessVmCounters,
	ProcessTimes,
	ProcessBasePriority,
	ProcessRaisePriority,
	ProcessDebugPort,
	ProcessExceptionPort,
	ProcessAccessToken,
	ProcessLdtInformation,
	ProcessLdtSize,
	ProcessDefaultHardErrorMode,
	ProcessIoPortHandlers,          // Note: this is kernel mode only
	ProcessPooledUsageAndLimits,
	ProcessWorkingSetWatch,
	ProcessUserModeIOPL,
	ProcessEnableAlignmentFaultFixup,
	ProcessPriorityClass,
	ProcessWx86Information,
	ProcessHandleCount,
	ProcessAffinityMask,
	ProcessPriorityBoost,
	ProcessDeviceMap,
	ProcessSessionInformation,
	ProcessForegroundInformation,
	ProcessWow64Information,
	ProcessImageFileName,
	ProcessLUIDDeviceMapsEnabled,
	ProcessBreakOnTermination,
	ProcessDebugObjectHandle,
	ProcessDebugFlags,
	ProcessHandleTracing,
	ProcessIoPriority,
	ProcessExecuteFlags,
	ProcessTlsInformation,
	ProcessCookie,
	ProcessImageInformation,
	ProcessCycleTime,
	ProcessPagePriority,
	ProcessInstrumentationCallback,
	ProcessThreadStackAllocation,
	ProcessWorkingSetWatchEx,
	ProcessImageFileNameWin32,
	ProcessImageFileMapping,
	MaxProcessInfoClass             // MaxProcessInfoClass should always be the last enum
}PROCESSINFOCLASS;



typedef VOID(NTAPI *PIO_APC_ROUTINE)(__in PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG Reserved);