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

	char* GetSection(const char* section);
	char* GetValue(char* found, const char* value);
	char* FillInValue(char* v_found);

	void Init(const char* filename);
	void Free();

	void ReadFromFile(const char* FileName, int FileSize);

	bool ReadBool(const char* section, std::string value);
	int ReadInt(const char* section, std::string value);
	color ReadColor(const char* section, std::string value);
	float ReadFloat(const char* section, std::string value);
	char ReadChar(const char* section, std::string value);
	void ReadString(const char* section, std::string value, char* out);

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

class FriendList {
public:
	std::string name, npid;
};

class Friends {
public:
	uint64_t nrw;
	uint64_t pos;

	int fd;

	char buffer[3000];
	const char* FileName;

	std::vector<std::string> vFriends;
	std::vector<std::string> vList;
	std::vector<std::string> vNpids;
	std::vector<std::string> vNames;

	void Init();
	void PrepareSave();
	void Free();

	char* GetSection(const char* section);
	char* GetValue(char* found, const char* value);
	char* FillInValue(char* v_found);

	bool DeleteFriend(std::string name);

	void ReadFromFile(int FileSize);
	const char* ReadChar(const char* section, std::string value);
	bool ReadFriends();

	void WriteSection(const char* section);
	bool WriteFriends(std::string name, std::string npid);
};

extern INI Ini;
extern Friends Fr;

size_t GetFileSize(const char* fileName);

void ReadFromIniFile(const char* fileName);
void SaveToIniFile(const char* fileName);