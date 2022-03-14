#include "Includes.h"

VirtualTable* Virtual::Table;

void* Virtual::MakeJump(int fnptr, int Param1, int Param2, int Param3, int Param4, int Param5, int Param6, int Param7, bool ping) {
	if (ping) {
		return ((void* (*)(...))fnptr)(Param1, Param2, Param3, Param4, Param5, Param6, Param7);
	} else {
		return MakeJump(fnptr, Param1, Param2, Param3, Param4, Param5, Param6, Param7, true);
	}
}

void* Virtual::ResolveFunc(int FunctionID) {
	for (int i = 0; i < FUNCTION_COUNT; i++) {
		if (Table[i].FuncID == FunctionID) {
			uint64_t OPDAddress = (uint64_t)Table[i].FuncAddr;
			uint64_t Instructions = *(uint32_t*)OPDAddress;

			// Restore OPD
			WriteHenMem((int)OPDAddress, Table[i].OPD, 0x8);

			// Restore Instructions
			WriteHenMem((int)Instructions, Table[i].Instructions, 0x10);

			return Table[i].FuncAddr;
		}
	}
	return 0;
}

void Virtual::RegisterFunction(int FunctionAddress, int FunctionID) {
	if (FunctionAddress) {
		for (int i = 0; i < FUNCTION_COUNT; i++) {
			if (Table[i].FuncAddr != 0)
				continue;

			Table[i].FuncAddr = (void*)FunctionAddress;
			Table[i].FuncID = FunctionID;

			uint64_t OPDAddress = (uint64_t)Table[i].FuncAddr;
			uint64_t Instructions = *(uint32_t*)OPDAddress;

			//Save OPD
			ReadHenMem(OPDAddress, Table[i].OPD, 0x8);

			//Save Instructions
			ReadHenMem(Instructions, Table[i].Instructions, 0x10);
			break;
		}
	}
}

void Virtual::Clear() {
	if (Table != 0) {
		Virtual::Call<int>(memset_t, Table, 0, sizeof(VirtualTable) * FUNCTION_COUNT);
		MakeJump((int)memset, (int)Table, 0, sizeof(VirtualTable) * FUNCTION_COUNT);
		delete[] Table;
		Table = 0;
	}
}

void Virtual::Create(int FunctionAddress, int FunctionID) {
	MakeJump((int)RegisterFunction, FunctionAddress, FunctionID);
}

bool strRunning = false;
bool Virtual::strstrFunction(const char* _Str1, const char* _Str2) {
	strRunning = true;

	return strstr(_Str1, _Str2);
}

void Virtual::Initialize() {
	if (!Table) {
		Table = new VirtualTable[sizeof(VirtualTable) * FUNCTION_COUNT];
		Virtual::Call<int>(memset_t, Table, 0, sizeof(VirtualTable) * FUNCTION_COUNT);
		MakeJump((int)memset, (int)Table, 0, sizeof(VirtualTable) * FUNCTION_COUNT);
	}
}


