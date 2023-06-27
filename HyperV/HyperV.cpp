#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Utils.h"
#include "HyperV.h"
#include "Skicript.hpp"

using PsLookupProcessByProcessId = NTSTATUS(__fastcall*)(ULONG64, PVOID*);
using PsGetProcessSectionBaseAddress = PVOID(__fastcall*)(ULONG64);
using PsGetProcessPeb = PVOID(__fastcall*)(ULONG64);
using ObfReferenceObject = LONG_PTR(*)(PVOID);

#pragma warning(push)
#pragma warning(disable: 4214)
#pragma pack(push,2)

typedef struct _FAR_JMP_16
{
	UCHAR  OpCode;  // = 0xe9
	USHORT Offset;
} FAR_JMP_16;

typedef struct _FAR_TARGET_32
{
	ULONG Offset;
	USHORT Selector;
} FAR_TARGET_32;

typedef struct _PSEUDO_DESCRIPTOR_32 {
	USHORT Limit;
	ULONG Base;
} PSEUDO_DESCRIPTOR_32;

#pragma pack(pop)
typedef union _KGDTENTRY64
{
	struct
	{
		USHORT  LimitLow;
		USHORT  BaseLow;
		union
		{
			struct
			{
				UCHAR   BaseMiddle;
				UCHAR   Flags1;
				UCHAR   Flags2;
				UCHAR   BaseHigh;
			} Bytes;

			struct
			{
				ULONG   BaseMiddle : 8;
				ULONG   Type : 5;
				ULONG   Dpl : 2;
				ULONG   Present : 1;
				ULONG   LimitHigh : 4;
				ULONG   System : 1;
				ULONG   LongMode : 1;
				ULONG   DefaultBig : 1;
				ULONG   Granularity : 1;
				ULONG   BaseHigh : 8;
			} Bits;
		};
		ULONG BaseUpper;
		ULONG MustBeZero;
	};
	ULONG64 Alignment;
} KGDTENTRY64, * PKGDTENTRY64;

typedef union _KIDTENTRY64
{
	struct
	{
		USHORT OffsetLow;
		USHORT Selector;
		USHORT IstIndex : 3;
		USHORT Reserved0 : 5;
		USHORT Type : 5;
		USHORT Dpl : 2;
		USHORT Present : 1;
		USHORT OffsetMiddle;
		ULONG OffsetHigh;
		ULONG Reserved1;
	};
	ULONG64 Alignment;
} KIDTENTRY64, * PKIDTENTRY64;

typedef union _KGDT_BASE
{
	struct
	{
		USHORT BaseLow;
		UCHAR BaseMiddle;
		UCHAR BaseHigh;
		ULONG BaseUpper;
	};
	ULONG64 Base;
} KGDT_BASE, * PKGDT_BASE;

typedef union _KGDT_LIMIT
{
	struct
	{
		USHORT LimitLow;
		USHORT LimitHigh : 4;
		USHORT MustBeZero : 12;
	};
	ULONG Limit;
} KGDT_LIMIT, * PKGDT_LIMIT;

#define PSB_GDT32_MAX       3

typedef struct _KDESCRIPTOR
{
	USHORT Pad[3];
	USHORT Limit;
	PVOID Base;
} KDESCRIPTOR, * PKDESCRIPTOR;

typedef struct _KDESCRIPTOR32
{
	USHORT Pad[3];
	USHORT Limit;
	ULONG Base;
} KDESCRIPTOR32, * PKDESCRIPTOR32;

typedef struct _KSPECIAL_REGISTERS
{
	ULONG64 Cr0;
	ULONG64 Cr2;
	ULONG64 Cr3;
	ULONG64 Cr4;
	ULONG64 KernelDr0;
	ULONG64 KernelDr1;
	ULONG64 KernelDr2;
	ULONG64 KernelDr3;
	ULONG64 KernelDr6;
	ULONG64 KernelDr7;
	KDESCRIPTOR Gdtr;
	KDESCRIPTOR Idtr;
	USHORT Tr;
	USHORT Ldtr;
	ULONG MxCsr;
	ULONG64 DebugControl;
	ULONG64 LastBranchToRip;
	ULONG64 LastBranchFromRip;
	ULONG64 LastExceptionToRip;
	ULONG64 LastExceptionFromRip;
	ULONG64 Cr8;
	ULONG64 MsrGsBase;
	ULONG64 MsrGsSwap;
	ULONG64 MsrStar;
	ULONG64 MsrLStar;
	ULONG64 MsrCStar;
	ULONG64 MsrSyscallMask;
} KSPECIAL_REGISTERS, * PKSPECIAL_REGISTERS;

typedef struct _KPROCESSOR_STATE
{
	KSPECIAL_REGISTERS SpecialRegisters;
	CONTEXT ContextFrame;
} KPROCESSOR_STATE, * PKPROCESSOR_STATE;

typedef struct _PROCESSOR_START_BLOCK* PPROCESSOR_START_BLOCK;

typedef struct _PROCESSOR_START_BLOCK
{
	FAR_JMP_16 Jmp;
	ULONG CompletionFlag;
	PSEUDO_DESCRIPTOR_32 Gdt32;
	PSEUDO_DESCRIPTOR_32 Idt32;
	KGDTENTRY64 Gdt[PSB_GDT32_MAX + 1];
	ULONG64 TiledCr3;
	FAR_TARGET_32 PmTarget;
	FAR_TARGET_32 LmIdentityTarget;
	PVOID LmTarget;
	PPROCESSOR_START_BLOCK SelfMap;
	ULONG64 MsrPat;
	ULONG64 MsrEFER;
	KPROCESSOR_STATE ProcessorState;
} PROCESSOR_START_BLOCK;
#pragma warning(pop)

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, * PRTL_PROCESS_MODULES;

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	WCHAR* Buffer;
} UNICODE_STRING;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	UCHAR Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB
{
	UCHAR InheritedAddressSpace;
	UCHAR ReadImageFileExecOptions;
	UCHAR BeingDebugged;
	UCHAR BitField;
	PVOID Mutant;
	PVOID ImageBaseAddress;
	PPEB_LDR_DATA Ldr;
} PEB, * PPEB;

typedef struct _SYSTEM_BIGPOOL_ENTRY
{
	union
	{
		PVOID VirtualAddress;
		ULONG_PTR NonPaged : 1;
	}
	;
	ULONG_PTR SizeInBytes;
	union 
	{
		UCHAR Tag[4];
		ULONG TagUlong;
	};
} SYSTEM_BIGPOOL_ENTRY, * PSYSTEM_BIGPOOL_ENTRY;

typedef struct _SYSTEM_BIGPOOL_INFORMATION
{
	ULONG Count;
	SYSTEM_BIGPOOL_ENTRY AllocatedInfo[ANYSIZE_ARRAY];
} SYSTEM_BIGPOOL_INFORMATION, * PSYSTEM_BIGPOOL_INFORMATION;


HyperV::HyperV()
{
	MemCopy = (ULONG64)GetKeExport(skCrypt("ntoskrnl.exe"), skCrypt("memcpy"));
	PsLookupPeproc = (ULONG64)GetKeExport(skCrypt("ntoskrnl.exe"), skCrypt("PsLookupProcessByProcessId"));
	ObDereferenceObject = (ULONG64)GetKeExport(skCrypt("ntoskrnl.exe"), skCrypt("ObfDereferenceObject"));
	NtShutdownSystemVa = (ULONG64)GetKeExport(skCrypt("ntoskrnl.exe"), skCrypt("NtShutdownSystem"));
	ProcBaseProt = (ULONG64)GetKeExport(skCrypt("ntoskrnl.exe"), skCrypt("PsGetProcessSectionBaseAddress"));
	ProcPebProt = (ULONG64)GetKeExport(skCrypt("ntoskrnl.exe"), skCrypt("PsGetProcessPeb"));

	

	RandomKey = (0 >= ULLONG_MAX ? 0 : 0 + (ULONG64)((ULLONG_MAX - 0) * ReadTimeStampCounter() * 2));



	CupArgs Args{ RandomKey };
	CupCallEx(0x12C11B554E4788C, 0x558402, &Args);
	///RandomKey = 0xBACFB55FDEAD180;// (0 >= ULLONG_MAX ? 0 : 0 + (ULONG64)((ULLONG_MAX - 0) * ReadTimeStampCounter() * 2));
	//VmCallEx(0x8582322657, 825, RandomKey, 0);
}

ULONG HyperV::InitHyperV()
{
	GROUP_AFFINITY OrigGroupAffinity{};
	GetThreadGroupAffinity(GetCurrentThread(), &OrigGroupAffinity);
	const WORD GroupCount = GetActiveProcessorGroupCount();
	for (UINT32 GroupNumber = 0u; GroupNumber < GroupCount; ++GroupNumber)
	{
		const DWORD ProcessorCount = GetActiveProcessorCount(GroupNumber);
		for (UINT32 ProcessorNumber = 0u; ProcessorNumber < ProcessorCount; ++ProcessorNumber)
		{
			GROUP_AFFINITY GroupAffinity{};
			GroupAffinity.Mask = (KAFFINITY)(1) << ProcessorNumber;
			GroupAffinity.Group = GroupNumber;
			SetThreadGroupAffinity(GetCurrentThread(), &GroupAffinity, NULL);
			ULONG Result = HyperCall(RandomKey, 5);
			if (Result != 0)
				return Result;
		}
	}
	SetThreadGroupAffinity(GetCurrentThread(), &OrigGroupAffinity, NULL);
	return 0;
}

bool HyperV::GetExtendProcCr3(ULONG pid)
{
	if (InitHyperV() != 0)
		return false;

	CurentCr3 = GetCurrentProcCr3();


	if(!InitPageTableBase())
		return false;

	NtShutdownSystemPa = Translate(KernelCr3, NtShutdownSystemVa);
	if(!NtShutdownSystemPa)
		return false;


	PVOID Process = NULL;
	Syscall<PsLookupProcessByProcessId>((PVOID)PsLookupPeproc, static_cast<ULONG64>(pid), &Process);
	if (!Process)
		return false;

	BaseAddress = (ULONG64)Syscall<PsGetProcessSectionBaseAddress>((PVOID)ProcBaseProt, (ULONG64)Process);
	ProcessPeb = (ULONG64)Syscall<PsGetProcessPeb>((PVOID)ProcPebProt, (ULONG64)Process);
	ReadMemKe(&ExtendCr3, (PVOID)((ULONG64)Process + 0x28), 8);
	Syscall<ObfReferenceObject>((PVOID)ObDereferenceObject, Process);

	if (CurentCr3 == 0)
	{
		Process = NULL;
		Syscall<PsLookupProcessByProcessId>((PVOID)PsLookupPeproc, static_cast<ULONG64>(GetCurrentProcessId()), &Process);
		if (!Process)
			return false;

		ReadMemKe(&CurentCr3, (PVOID)((ULONG64)Process + 0x28), 8);
		Syscall<ObfReferenceObject>((PVOID)ObDereferenceObject, Process);
	}
	return true;
}

bool HyperV::GetStatus()
{
	ULONG result = HyperCall(RandomKey, 11);
	if (result != 0)
		return false;

	return true;
}

ULONG64 HyperV::GetCurrentProcCr3()
{
	CupArgs Args{};
	if (CupCallEx(RandomKey, 9, &Args) != 0)
		return 0;

	return Args.Argd[0];
}

ULONG64 HyperV::Translate(ULONG64 Cr3, ULONG64 VirtAddr)
{
	CupArgs Args{ Cr3, VirtAddr };
	if (CupCallEx(RandomKey, 10, &Args) != 0)
		return 0;

	return Args.Argd[2];
}

ULONG HyperV::ReadPhys(ULONG64 PhysAddr, ULONG64 Buffer, ULONG64 Size)
{
	CupArgs Args{ PhysAddr, Buffer, Size };
	return CupCallEx(RandomKey, 6, &Args);
}

ULONG HyperV::WritePhys(ULONG64 PhysAddr, ULONG64 Buffer, ULONG64 Size)
{
	CupArgs Args{ PhysAddr, Buffer, Size };
	return CupCallEx(RandomKey, 7, &Args);
}

ULONG HyperV::ExCopyVirt(ULONG64 SrcCr3, ULONG64 VirtSrc, ULONG64 DestCr3, ULONG64 VirtDest, ULONG64 Size)
{
	CupArgs Args{ SrcCr3, VirtSrc, DestCr3, VirtDest, Size };
	return CupCallEx(RandomKey, 8, &Args);
}

bool HyperV::ReadMem(PVOID base, PVOID buffer, SIZE_T size)
{
	ULONG Value = ExCopyVirt(ExtendCr3, (ULONG64)(base), CurentCr3, (ULONG64)buffer, size);
	if (0 == Value)
		return true;

	return false;
}

bool HyperV::WriteMem(PVOID base, PVOID buffer, SIZE_T size)
{
	ULONG Value = ExCopyVirt(CurentCr3, (ULONG64)(buffer), ExtendCr3, (ULONG64)(base), size);
	if (0 == Value)
		return true;

	return false;
}

std::string HyperV::ReadString(ULONG64 address)
{
	std::string buffer;

	do
	{
		buffer.push_back(ReadValue64<char>(address++));
	}
	while (ReadValue64<char>(address) != '\0');
	return buffer;
}

std::wstring HyperV::ReadWideString(ULONG64 address)
{

	std::wstring buffer;
	do
	{
		buffer.push_back(ReadValue64<wchar_t>(address++));
	} while (ReadValue64<wchar_t>(address) != '\0');
	return buffer;

}

bool HyperV::InitPageTableBase()
{
	BOOL bRet = false;
	PUCHAR Data = (PUCHAR)malloc(0x1000);
	if (Data == NULL)
		return false;

	ULONG Cr3Offset = ULONG(FIELD_OFFSET(PROCESSOR_START_BLOCK, ProcessorState) + FIELD_OFFSET(KSPECIAL_REGISTERS, Cr3));
	for (DWORD_PTR Addr = 0; Addr < 0x100000; Addr += 0x1000)
	{
		if (ReadPhys((ULONG64)Addr, (ULONG64)(void*)Data, 0x1000) == 0)
		{
			if (0x00000001000600E9 != (0xFFFFFFFFFFFF00FF & *(UINT64*)(Data)))
				continue;

			if (0xFFFFF80000000000 != (0xFFFFF80000000003 & *(UINT64*)(Data + FIELD_OFFSET(PROCESSOR_START_BLOCK, LmTarget))))
				continue;

			if (0xFFFFFF0000000FFF & *(UINT64*)(Data + Cr3Offset))
				continue;

			KernelCr3 = *(UINT64*)(Data + Cr3Offset);
			bRet = true;
			break;
		}
	}
	if (Data)
		free(Data);

	return bRet;
}

template <class T, class ... Ts>
__forceinline std::invoke_result_t<T, Ts...> HyperV::Syscall(void* addr, Ts ... args)
{
	static const auto proc = GetProcAddress(GetModuleHandleA(skCrypt("ntdll.dll")), skCrypt("NtShutdownSystem"));
	std::uint8_t jmp_code[] =
	{
		0xff, 0x25, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00
	};

	std::uint8_t orig_bytes[sizeof jmp_code];
	*reinterpret_cast<void**>(jmp_code + 6) = addr;
	ReadPhys(NtShutdownSystemPa, (ULONG64)orig_bytes, sizeof orig_bytes);
	WritePhys(NtShutdownSystemPa, (ULONG64)jmp_code, sizeof jmp_code);
	auto result = reinterpret_cast<T>(proc)(args ...);
	WritePhys(NtShutdownSystemPa, (ULONG64)orig_bytes, sizeof orig_bytes);
	return result;
}

PVOID HyperV::GetKeExport(const char* module_name, const char* export_name, bool rva)
{
	void* buffer = nullptr;
	DWORD buffer_size = NULL;

	NTSTATUS status = NtQuerySystemInformationEx(11, buffer, buffer_size, &buffer_size);
	while (status == 0xC0000004L)
	{
		VirtualFree(buffer, 0, MEM_RELEASE);
		buffer = VirtualAlloc(nullptr, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		status = NtQuerySystemInformationEx(11, buffer, buffer_size, &buffer_size);
	}

	if (!NT_SUCCESS(status))
	{
		VirtualFree(buffer, 0, MEM_RELEASE);
		return nullptr;
	}

	const auto modules = static_cast<PRTL_PROCESS_MODULES>(buffer);
	for (auto idx = 0u; idx < modules->NumberOfModules; ++idx)
	{
		const std::string current_module_name = std::string(reinterpret_cast<char*>(modules->Modules[idx].FullPathName) + modules->Modules[idx].OffsetToFileName);
		if (!_stricmp(current_module_name.c_str(), module_name))
		{
			std::string full_path = reinterpret_cast<char*>(modules->Modules[idx].FullPathName);
			full_path.replace(full_path.find("\\SystemRoot\\"), sizeof("\\SystemRoot\\") - 1, std::string(getenv("SYSTEMROOT")).append("\\"));
			const auto module_base = LoadLibraryExA(full_path.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);

			PIMAGE_DOS_HEADER p_idh;
			PIMAGE_NT_HEADERS p_inh;
			PIMAGE_EXPORT_DIRECTORY p_ied;

			PDWORD addr, name;
			PWORD ordinal;

			p_idh = (PIMAGE_DOS_HEADER)module_base;
			if (p_idh->e_magic != IMAGE_DOS_SIGNATURE)
				return NULL;

			p_inh = (PIMAGE_NT_HEADERS)((LPBYTE)module_base + p_idh->e_lfanew);
			if (p_inh->Signature != IMAGE_NT_SIGNATURE)
				return NULL;

			if (p_inh->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0)
				return NULL;

			p_ied = (PIMAGE_EXPORT_DIRECTORY)((LPBYTE)module_base + p_inh->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
			addr = (PDWORD)((LPBYTE)module_base + p_ied->AddressOfFunctions);
			name = (PDWORD)((LPBYTE)module_base + p_ied->AddressOfNames);
			ordinal = (PWORD)((LPBYTE)module_base + p_ied->AddressOfNameOrdinals);

			for (DWORD i = 0; i < p_ied->AddressOfFunctions; i++)
			{
				if (!strcmp(export_name, (char*)module_base + name[i]))
				{
					if (!rva)
					{
						auto result = (void*)((std::uintptr_t)modules->Modules[idx].ImageBase + addr[ordinal[i]]);
						VirtualFree(buffer, NULL, MEM_RELEASE);
						FreeLibrary(module_base);
						return result;
					}
					else
					{
						auto result = (ULONG64)(addr[ordinal[i]]);
						VirtualFree(buffer, NULL, MEM_RELEASE);
						FreeLibrary(module_base);
						return (PVOID)result;
					}
				}
			}
		}
	}
	VirtualFree(buffer, NULL, MEM_RELEASE);
	return nullptr;
}

ULONG64 HyperV::GetProcessModule(const wchar_t* Name)
{
	PEB PebEx{};
	if (!ReadMem((PVOID)ProcessPeb, &PebEx, sizeof(PEB)))
		return 0;

	PEB_LDR_DATA LdrList{};
	if (!ReadMem((PVOID)(PebEx.Ldr), &LdrList, sizeof(PEB_LDR_DATA)))
		return 0;

	ULONG64 first_link = ULONG64(LdrList.InLoadOrderModuleList.Flink);
	ULONG64 forward_link = first_link;

	do
	{
		LDR_DATA_TABLE_ENTRY entry{};
		if (!ReadMem((PVOID)forward_link, &entry, sizeof(LDR_DATA_TABLE_ENTRY)))
			continue;

		std::wstring Buffer(entry.BaseDllName.Length, 0);
		if (!ReadMem((PVOID)entry.BaseDllName.Buffer, (PVOID)Buffer.data(), entry.BaseDllName.Length))
			continue;

		forward_link = ULONG64(entry.InLoadOrderLinks.Flink);
		if (!entry.DllBase)
			continue;

		if (wcsstr(Buffer.c_str(), Name))
			return (ULONG64)entry.DllBase;

	} while (forward_link && forward_link != first_link);
	return 0;
}

ULONG64 HyperV::GetValGuardRegion()
{
	void* buffer = nullptr;
	DWORD buffer_size = NULL;

	NTSTATUS status = NtQuerySystemInformationEx(0x42, buffer, buffer_size, &buffer_size);
	while (status == 0xC0000004L)
	{
		VirtualFree(buffer, 0, MEM_RELEASE);
		buffer = VirtualAlloc(nullptr, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		status = NtQuerySystemInformationEx(0x42, buffer, buffer_size, &buffer_size);
	}

	if (!NT_SUCCESS(status))
	{
		if (buffer)
			VirtualFree(buffer, 0, MEM_RELEASE);

		return 0;
	}

	ULONG64 TempAddress = 0;
	const PSYSTEM_BIGPOOL_INFORMATION BigPoolData = static_cast<PSYSTEM_BIGPOOL_INFORMATION>(buffer);
	if (BigPoolData != NULL)
	{
		for (ULONG i = 0; i < BigPoolData->Count; i++)
		{
			PSYSTEM_BIGPOOL_ENTRY AllocationEntry = &BigPoolData->AllocatedInfo[i];
			ULONG64 VirtualAddress = (ULONG64)AllocationEntry->VirtualAddress & ~1ull;
			if (AllocationEntry->NonPaged && AllocationEntry->SizeInBytes == 0x200000)
			{
				if (TempAddress == 0 && AllocationEntry->TagUlong == 'TnoC')
					TempAddress = VirtualAddress;
			}
		}
		VirtualFree(BigPoolData, 0, MEM_RELEASE);
	}
	return TempAddress;
}