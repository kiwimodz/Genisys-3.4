#pragma once

#define FRIENDS_DIR "/dev_hdd0/tmp/Genisys/Fake Friends/"
#define FRIENDS_SUB_DIR "/dev_hdd0/tmp/Genisys/"

class friend_list
{
public:
    char _fpad[4];
    char name[16];
    char _pad[4];
    char npid[8];
    char pad[0xEC];
};

class friends
{
public:
    static int sceNpBasicGetFriendPresenceByIndexC(uint32_t index, SceNpUserInfo* user, SceNpBasicPresenceDetails2* pres, uint32_t options);

    static void write_friend(std::string user, std::string npid);
    static void read_friends();
    static void delete_friend(std::string user);
    static void import_friends(const std::string& user_file);

    static void start();

    static unsigned int true_count;
    static int friend_count;
    static int friend_increment;
};