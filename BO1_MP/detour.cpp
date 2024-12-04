#include<Includes.h>

#define STUB_ADDRESS_BLOCK 0x10D4954
void DetourFunction(int address, int hookFunc, int stubFunc);

unsigned int PRX_TOC_ADDRESS = 0;
unsigned char* Detour::HookSection = (unsigned char*)STUB_ADDRESS_BLOCK;
unsigned int Detour::HookCount = 0;

void Detour::Restore() {
	if (this->isHooked)
		WriteHenMem(this->Address, this->RestoreInstructions, 0x10);
	this->isHooked = false;
}

Detour::~Detour() {
	this->Restore();

	WriteHenMem((int)this, 0, sizeof(Detour));
}

Detour::Detour() {
	WriteHenMem((int)this, 0, sizeof(Detour));
}

unsigned int Detour::AllocateStub() {
	unsigned int stubInstructions = (unsigned int)((int)&this->HookSection[0] + (this->HookCount * 0x20));
	this->HookCount++;

	this->stubTOC[0] = stubInstructions;
	this->stubTOC[1] = TOC;

	return (unsigned int)&this->stubTOC[0];
}



void DetourFunction(int address, int hookFunc, int stubFunc) {
	int StubData[8], FuncData[4];

	int hook_address = hookFunc != NULL ? *(int*)hookFunc : 0;
	int stub_address = stubFunc != NULL ? *(int*)stubFunc : 0;

	if (stub_address) {
		int branchAddr = address + 0x10;
		StubData[0] = 0x3D600000 + ((branchAddr >> 16) & 0xFFFF) + (branchAddr & 0x8000 ? 1 : 0);
		StubData[1] = 0x396B0000 + (branchAddr & 0xFFFF);
		StubData[2] = 0x7D6903A6;
		StubData[7] = 0x4E800420;
		ReadHenMem(address, &StubData[3], 0x10);
		WriteHenMem(stub_address, StubData, 0x20);
	}

	if (hook_address) {
		FuncData[0] = 0x3D600000 + ((hook_address >> 16) & 0xFFFF) + (hook_address & 0x8000 ? 1 : 0);
		FuncData[1] = 0x396B0000 + (hook_address & 0xFFFF);
		FuncData[2] = 0x7D6903A6;
		FuncData[3] = 0x4E800420;
		WriteHenMem(address, FuncData, 0x10);
	}
}

void Detour::Hook(int address, void(*hookFunc)) {
	this->Address = address;
	this->hookFunction = (int)hookFunc;
	this->Stub = (int(*)(...))this->AllocateStub();

	ReadHenMem(this->Address, this->RestoreInstructions, 0x10);
	DetourFunction(this->Address, this->hookFunction, (int)this->Stub);

	this->isHooked = true;
}