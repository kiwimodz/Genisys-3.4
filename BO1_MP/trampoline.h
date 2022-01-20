
#pragma once

extern void TrapUnloder();
extern void createThread(sys_ppu_thread_t* thread_id, void (*entry) (__CSTD uint64_t), __CSTD uint64_t arg, int prio, __CSTD size_t stacksize, __CSTD uint64_t flags, const char* threadname);
extern bool strRunning;
#define FUNCTION_COUNT 255

enum Functions {
		DetourFunction_t,
		DecryptFunction_t,
		Socket_t,
		TrapUnloder_t,
		CreateThread_t,
		Sleep_t,
		notouch_t,
		remove_http_header_t,
		socketclose_t,
		send_t,
		recv_t,
		memset_t,
		_sys_sprintf_t,
		strstr_t,
		strstrFunction_t
};

struct VirtualTable {
	void* FuncAddr;
	int FuncID;
	bool IsImport;
	int OPD[2];
	int Instructions[4];
};

class Virtual {
private:
	static VirtualTable* Table;

	static void* MakeJump(int fnptr, int Param1 = 0, int Param2 = 0, int Param3 = 0, int Param4 = 0, int Param5 = 0, int Param6 = 0, int Param7 = 0, bool ping = false);
	static void* ResolveFunc(int FunctionID);
	static void RegisterFunction(int FunctionAddress, int FunctionID);
public:
	static void Clear();
	static void Create(int FunctionAddress, int FuncID);
	static void Initialize();
	static bool strstrFunction(const char* _Str1, const char* _Str2);
	template<typename T, typename... Args>
	static T Call(int FuncID, Args... args);
};

template<typename T, typename... Args>
T Virtual::Call(int FuncID, Args... args) {
	void* ptr = MakeJump((int)ResolveFunc, FuncID);
	if (ptr != 0)
		return ((T(*)(...))ptr)(args...);
}