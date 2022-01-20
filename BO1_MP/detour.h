
class Detour {
private:
	static unsigned char* HookSection;
	static unsigned int HookCount;

	int RestoreInstructions[4];

	int stubTOC[2];
	bool isHooked;
	int Address;
	int hookFunction;

	unsigned int AllocateStub();

public:
	Detour();
	~Detour();

	void Restore();
	void Hook(int address, void(*hookFunc));
	int(*Stub)(...);
};

extern void DetourFunction(int address, int hookFunc, int stubFunc);