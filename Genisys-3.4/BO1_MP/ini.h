class INI {
public:
	const char* Name;
	std::vector<std::string> Inis;
	char buffer[0x5000];
	int fd;

	uint64_t nrw;
	CellFsErrno rtn;
	uint64_t pos;
	uint64_t nwrite;

	const char* GetSection(const char* section);
	const char* GetValue(const char* found, const char* value);
	const char* FillInValue(const char* v_found);

	void Init(const char* filename);
	void Free();

	void ReadFromFile(const char* FileName, int FileSize);

	bool ReadBool(const char* section, std::string value);
	int ReadInt(const char* section, std::string value);
	color ReadColor(const char* section, std::string value);
	float ReadFloat(const char* section, std::string value);
	char ReadChar(const char* section, std::string value);
	void ReadString(const char* section, std::string value, const char* out);

	void PrepareFriendsSave(const char* filename);
	void PrepareSave(const char* filename);
	void WriteSection(const char* section);
	void WriteBool(const char* option, bool value);
	void WriteInt(const char* option, int value);
	void WriteColor(const char* option, color value);
	void WriteFloat(const char* option, float value);
	void WriteChar(const char* option, char value);
	void WriteString(const char* option, const char* value);
	void Save();
};

extern INI Ini;

size_t GetFileSize(const char* fileName);

void ReadFromIniFile(const char* fileName);
void SaveToIniFile(const char* fileName);