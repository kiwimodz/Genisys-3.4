#pragma once

extern SceNpCommunicationId communication_id;
extern SceNpCommunicationPassphrase CommPassphrase;

extern SceNpCommunicationId* GetNpCommId();
extern SceNpCommunicationPassphrase* GetNpPass();

struct NPClient_Info {
	SceNpId npId;
	sys_ppu_thread_t cmd_tid;
	struct Friendlist* friendlist;
	int32_t titleCtxId;
	int32_t	lookupTitleCtxId;
	int32_t tusTitleCtxId;
};

extern NPClient_Info npclient;
extern std::pair<SceNpId, int> doLookupNpId(const char* onlineIdString);
