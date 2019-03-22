#pragma once
#include <unordered_map>
#include <memory>

#include "f4se_common/f4se_version.h"
#include "f4se_common/Relocation.h"

#include "sscan/Pattern.h"

//=============================================================================================
//=======================================    RVA.h    =========================================
//=============================================================================================
//====      An RVA encapsulates a version-specific relative virtual address and a          ====
//====                 version-independent address signature pattern.                      ====
//=============================================================================================
//====      If addresses are explicitly specified for the current runtime version,         ====
//====      they will be used.                                                             ====
//====      If no addresses are available for the current runtime version,                 ====
//====      then a search will be performed against the provided signature in memory.      ====
//=============================================================================================
//====      Call RVAManager::UpdateAddresses(runtimeVersion) during plugin load            ====
//====      to resolve addresses for all declared RVAs.                                    ====
//=============================================================================================
//====      Author: registrator2000                                                        ====
//=============================================================================================

#define SHOW_ADDR 2
// 0 - Default - use addresses for the runtime version first, and sigscan if the addresses for the runtime version are not available. No logging.
// 1 - Always do sigscan and print address to log even if an address is present for the runtime version.
// 2 - Default + print addresses only if sigscan is performed

//------------------------
// Forward Declarations
//------------------------
namespace RVAUtils {
    inline bool ReadMemory(uintptr_t addr, void* data, size_t len);
}

//------------------------
// Data Structures
//------------------------
using indirection = std::vector<std::vector<int>>;
struct RVAData 
{
    std::unordered_map<UInt32, uintptr_t>			addr;   // Map of runtime version to RVA.
    const char*										sig					= NULL;     // Signature
    uintptr_t										effectiveAddress	= NULL;
    int												offset				= 0;
    int												indirectOffset		= 0;
    int												instructionLength	= 0;
	const char*										name				= "no name";
	indirection										indirections		 = indirection();
};

//------------------------
// Utility Classes
//------------------------

namespace RVAUtils {
    class Timer
    {
    public:
        void start() {
            QueryPerformanceCounter(&countStart);
            QueryPerformanceFrequency(&frequency);
        }
        long long int stop() {
            QueryPerformanceCounter(&countEnd);
            return (countEnd.QuadPart - countStart.QuadPart) / (frequency.QuadPart / 1000);
        }

    private:
        LARGE_INTEGER countStart, countEnd, frequency;
    };
}

//------------------------
// Address Manager
//------------------------

class RVAManager
{
public:
    static void UpdateAddresses(UInt32 runtimeVersion) {
        RVAUtils::Timer tmr; tmr.start();

        for (auto rvaData : m_rvaDataVec()) {
            if (rvaData->effectiveAddress) continue;
            UpdateSingle(rvaData, runtimeVersion);
        }

        if (SHOW_ADDR) _MESSAGE("Sigscan elapsed: %llu ms.", tmr.stop());
    }

    static void UpdateSingle(std::shared_ptr<RVAData> rvaData, UInt32 runtimeVersion = 0) {
        if (SHOW_ADDR != 1 && rvaData->addr.count(runtimeVersion) > 0) {
            rvaData->effectiveAddress = GetEffectiveAddress(rvaData->addr[runtimeVersion]);
        } else {
            // Sigscan
            if (rvaData->sig) {
                rvaData->effectiveAddress = (uintptr_t)Utility::pattern(rvaData->sig).count(1).get(0).get<void>(rvaData->offset);
                if (rvaData->indirectOffset != 0) {
                    SInt32 rel32 = 0;
                    RVAUtils::ReadMemory(rvaData->effectiveAddress + rvaData->indirectOffset, &rel32, sizeof(SInt32));
                    rvaData->effectiveAddress = rvaData->effectiveAddress + rvaData->instructionLength + rel32;
                }
				if (rvaData->indirections.size()>0)
				{
					SInt32 rel322 = 0;
					//_MESSAGE("initial rva: %p", rvaData->effectiveAddress - RelocationManager::s_baseAddr);
					for (int i = 0; i < rvaData->indirections.size(); i++)
					{
					//	_MESSAGE("%i %i %i", rvaData->indirections[i][0], rvaData->indirections[i][1], rvaData->indirections[i][2]);
						rvaData->effectiveAddress += rvaData->indirections[i][0];
						RVAUtils::ReadMemory(rvaData->effectiveAddress + rvaData->indirections[i][1], &rel322, sizeof(SInt32));
						rvaData->effectiveAddress = rvaData->effectiveAddress + rvaData->indirections[i][2] + rel322;
					//	_MESSAGE("mid rva: %p", rvaData->effectiveAddress - RelocationManager::s_baseAddr);
					}
				}

                #if SHOW_ADDR
                    _MESSAGE("---");
					_MESSAGE("name: %s", rvaData->name);
                    _MESSAGE("sig: %s", rvaData->sig);
                    _MESSAGE("effective address: %p", rvaData->effectiveAddress);
                    _MESSAGE("RVA: 0x%08X", rvaData->effectiveAddress - RelocationManager::s_baseAddr);
					_MESSAGE("			{ RUNTIME_VERSION_%d_%d_%d, 0x%08X },", GET_EXE_VERSION_MAJOR(CURRENT_RELEASE_RUNTIME),
						GET_EXE_VERSION_MINOR(CURRENT_RELEASE_RUNTIME),
						GET_EXE_VERSION_BUILD(CURRENT_RELEASE_RUNTIME), rvaData->effectiveAddress - RelocationManager::s_baseAddr);
                    _MESSAGE("---");
                #endif

            } else {
                _MESSAGE("Warning: No signature and no addresses for runtime.");
                for (auto addr : rvaData->addr) {
                    _MESSAGE("Runtime version: %08X \tAddress: %08X", addr.first, addr.second);
                }
            }
        }
    }

    static uintptr_t GetEffectiveAddress(uintptr_t rva) {
        return RelocationManager::s_baseAddr + rva;
    }

    static void Add(std::shared_ptr<RVAData> data) {
        m_rvaDataVec().push_back(data);
    }

private:
    using RVADataVec = std::vector<std::shared_ptr<RVAData>>;
    static RVADataVec& m_rvaDataVec() { static RVADataVec v; return v; }
};

//------------------------
// Address Type
//------------------------

template <typename T = void>
class RVA
{
public:
    using AddressMap = std::unordered_map<UInt32, uintptr_t>;

    RVA(AddressMap addr, const char* sig, int offset = 0, int indirectOffset = 0, int instructionLength = 0) {
        init(addr, sig, offset, indirectOffset, instructionLength);
    }

	RVA(const char* name, AddressMap addr, const char* sig, int offset = 0, int indirectOffset = 0, int instructionLength = 0) {
		init(addr, sig, offset, indirectOffset, instructionLength, name);
	}

	RVA(const char* name, const char* sig, int offset = 0, int indirectOffset = 0, int instructionLength = 0) {
		init({}, sig, offset, indirectOffset, instructionLength, name);
	}

	RVA(const char* name, AddressMap addr, const char* sig, indirection indirections) {
		init(addr, sig, 0, 0, 0, name,indirections);
	}

	RVA(const char* name, const char* sig, indirection indirections) {
		init({}, sig, 0, 0, 0, name, indirections);
	}

    RVA(const char* sig, int offset, AddressMap addr) {
        init(addr, sig, offset);
    }

    RVA(const char* sig, AddressMap addr) {
        init(addr, sig, 0);
    }

    // Address map only
    RVA(AddressMap addr) {
        init(addr, NULL, 0);
    }

    // Address only
    RVA(uintptr_t rva) {
        AddressMap addr = {{ CURRENT_RELEASE_RUNTIME, rva }};
        init(addr, NULL, 0);
    }

    // Address + sig
    RVA(uintptr_t rva, const char* sig, int offset = 0, int indirectOffset = 0, int instructionLength = 0) {
        AddressMap addr = {{ CURRENT_RELEASE_RUNTIME, rva }};
        init(addr, sig, offset, indirectOffset, instructionLength);
    }

    // Signature only
    RVA(const char* sig, int offset = 0, int indirectOffset = 0, int instructionLength = 0) {
        AddressMap addr;
        init(addr, sig, offset, indirectOffset, instructionLength);
    }

    // Default constructor (empty)
    RVA() {
        // do nothing
    }

    // type conversion operator
    // implicit conversion between an instance of the class and the specified type
    /*operator T*() const
    {
        return GetPtr();
    }*/

    T& operator* ()
    {
        return *GetPtr();
    }

    operator T()
    {
        return reinterpret_cast<T>(data->effectiveAddress);
    }

    T* operator->() const
    {
        return GetPtr();
    }

    T* GetPtr() const
    {
        return reinterpret_cast<T*>(data->effectiveAddress);
    }

    const T * GetConst() const
    {
        return reinterpret_cast<T*>(data->effectiveAddress);
    }

    uintptr_t GetUIntPtr() const
    {
        return data->effectiveAddress;
    }

    bool IsResolved() const {
        return (data->effectiveAddress != NULL);
    }

    void Resolve(UInt32 runtimeVersion) {
        if (!IsResolved()) RVAManager::UpdateSingle(data, runtimeVersion);
    }

    void Set(uintptr_t rva) {
        data->effectiveAddress = RVAManager::GetEffectiveAddress(rva);
    }

    void SetEffective(uintptr_t ea) {
        data->effectiveAddress = ea;
    }

    //void operator=(RVA const&) = delete;    

private:
    std::shared_ptr<RVAData> data;

	void init(AddressMap addr, const char* sig, int offset, int indirectOffset = 0, int instructionLength = 0, const char* name = "no name", indirection indirections = indirection()) {
        data = std::make_shared<RVAData>();
        data->addr = addr;
        data->sig = sig;
        data->offset = offset;
        data->indirectOffset = indirectOffset;
        data->instructionLength = instructionLength;
		data->name = name;
		data->indirections = indirections;
        RVAManager::Add(data);
    }
};

//--------------------
// Utility Functions
//--------------------

namespace RVAUtils {
    inline bool ReadMemory(uintptr_t addr, void* data, size_t len) {
        UInt32 oldProtect;
        if (VirtualProtect((void *)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(data, (void*)addr, len);
            if (VirtualProtect((void *)addr, len, oldProtect, &oldProtect))
                return true;
        }
        return false;
    }
}