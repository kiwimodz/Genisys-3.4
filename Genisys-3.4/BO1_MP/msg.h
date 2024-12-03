
class msg_t {
public:
    int overflowed;
    int readOnly;
    const char* data;
    const char* splitData;
    int maxsize;
    int cursize;
    int splitSize;
    int readcount;
    int bit;
    int lastEntityRef;
    int flush;
    netsrc_t targetLocalNetID;

    msg_t() {}
    msg_t(const char* data, int length);

    void write_long(int c);
    void write_string(const char* s);
    void write_short(short c);
    void write_bool(bool b);
    void write_byte(int c);
    void write_data(const void* data, int length);
    void write_int32(int i);
    void write_int64(unsigned __int64 c);

    void read_beginread();
    void read_data(void* data, int len);
    int read_int();
    long read_long();
    short read_short();
    bool read_bool();
    char read_byte();
    const char* read_string(const char* string, unsigned int maxChars);
    float read_float();
};

#pragma region MSG_ Functions
//Write
extern void(*MSG_Init)(msg_t* buf, const char* data, int length);
extern void(*MSG_WriteLong)(msg_t* msg, int c);
extern void(*MSG_WriteString)(msg_t* msg, const char* s);
extern void(*MSG_WriteShort)(msg_t* msg, short c);
extern void(*MSG_WriteByte)(msg_t* msg, int c);
extern void(*MSG_WriteData)(msg_t* buf, const void* data, int length);
extern void(*MSG_WriteInt64)(msg_t* buf, unsigned __int64 c);

//Read
extern void(*MSG_BeginReading)(msg_t* buf);
extern int(*MSG_ReadLong)(msg_t* buf);
extern int(*MSG_ReadShort)(msg_t* buf);
extern int(*MSG_ReadByte)(msg_t* buf);
extern unsigned __int64 (*MSG_ReadInt64)(msg_t* msg);
#pragma endregion