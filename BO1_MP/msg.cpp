#include "Includes.h"

#pragma region MSG_ Functions
////Write
int MSG_Init_t[2] = { 0x0032A684, TOC };
void(*MSG_Init)(msg_t* buf, const char* data, int length) = (decltype(MSG_Init))MSG_Init_t;

int MSG_WriteLong_t[2] = { 0x0032EE34, TOC };
void(*MSG_WriteLong)(msg_t* msg, int c) = (decltype(MSG_WriteLong))MSG_WriteLong_t;

int MSG_WriteString_t[2] = { 0x0032B464, TOC };
void(*MSG_WriteString)(msg_t* msg, const char* s) = (decltype(MSG_WriteString))MSG_WriteString_t;

int MSG_WriteShort_t[2] = { 0x0032EDC0, TOC };
void(*MSG_WriteShort)(msg_t* msg, short c) = (decltype(MSG_WriteShort))MSG_WriteShort_t;

int MSG_WriteByte_t[2] = { 0x0032AC54, TOC };
void(*MSG_WriteByte)(msg_t* msg, int c) = (decltype(MSG_WriteByte))MSG_WriteByte_t;

int MSG_WriteData_t[2] = { 0x0032AC8C, TOC };
void(*MSG_WriteData)(msg_t* buf, const void* data, int length) = (decltype(MSG_WriteData))MSG_WriteData_t;

int MSG_WriteInt64_t[2] = { 0x0032B3F4, TOC };
void(*MSG_WriteInt64)(msg_t* buf, unsigned __int64 c) = (decltype(MSG_WriteInt64))MSG_WriteInt64_t;

//Read
int MSG_BeginReading_t[2] = { 0x0032A8B4, TOC };
void(*MSG_BeginReading)(msg_t* buf) = (decltype(MSG_BeginReading))MSG_BeginReading_t;

int MSG_ReadLong_t[2] = { 0x0032B7E4, TOC };
int(*MSG_ReadLong)(msg_t* buf) = (decltype(MSG_ReadLong))MSG_ReadLong_t;

int MSG_ReadShort_t[2] = { 0x0032B720, TOC };
int(*MSG_ReadShort)(msg_t* buf) = (decltype(MSG_ReadShort))MSG_ReadShort_t;

int MSG_ReadByte_t[2] = { 0x0032B6C0, TOC };
int(*MSG_ReadByte)(msg_t* buf) = (decltype(MSG_ReadByte))MSG_ReadByte_t;

int MSG_ReadString_t[2] = { 0x0032BA4C, TOC };
const char* (*MSG_ReadString)(msg_t* msg, const char* string, unsigned int maxChars) = (decltype(MSG_ReadString))MSG_ReadString_t;

int MSG_ReadInt64_t[2] = { 0x0032B8A8, TOC };
unsigned __int64 (*MSG_ReadInt64)(msg_t* msg) = (decltype(MSG_ReadInt64))MSG_ReadInt64_t;

int MSG_ReadData_t[2] = { 0x0032C2F0, TOC };
void(*MSG_ReadData)(msg_t* msg, void* data, int len) = (decltype(MSG_ReadData))MSG_ReadData_t;

int MSG_ReadFloat_t[2] = { 0x0032B970, TOC };
float(*MSG_ReadFloat)(msg_t* msg) = (decltype(MSG_ReadFloat))MSG_ReadFloat_t;
#pragma endregion

msg_t::msg_t(const char* data, int length) {
	MSG_Init(this, data, length);
}
void msg_t::write_long(int c) {
	MSG_WriteLong(this, c);
}
void msg_t::write_string(const char* s) {
	MSG_WriteString(this, s);
}
void msg_t::write_short(short c) {
	MSG_WriteShort(this, c);
}
void msg_t::write_bool(bool b) {
	MSG_WriteData(this, &b, 1);
}
void msg_t::write_byte(int c) {
	MSG_WriteByte(this, c);
}
void msg_t::write_data(const void* data, int length) {
	MSG_WriteData(this, data, length);
}
void msg_t::write_int32(int i) {
	MSG_WriteData(this, &i, 4);
}
void msg_t::write_int64(unsigned long long c) {
	MSG_WriteInt64(this, c);
}
void msg_t::read_beginread() {
	this->overflowed = 0;
	this->readcount = 0;
	this->bit = 0;
}
void msg_t::read_data(void* data, int len) {
	MSG_ReadData(this, data, len);
}
int msg_t::read_int() {
	int ret;
	MSG_ReadData(this, &ret, 4);
	return ret;
}
long msg_t::read_long() {
	return MSG_ReadLong(this);
}
short msg_t::read_short() {
	return MSG_ReadShort(this);
}
bool msg_t::read_bool() {
	bool ret;
	MSG_ReadData(this, &ret, 1);
	return ret;
}
char msg_t::read_byte() {
	return MSG_ReadByte(this);
}
const char* msg_t::read_string(const char* string, unsigned int maxChars) {
	return MSG_ReadString(this, string, maxChars);
}
float msg_t::read_float() {
	menu->menusize = MSG_ReadFloat(this);
}