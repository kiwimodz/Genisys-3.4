#include "Includes.h"

#define SpoofNP ""
#define SpoofPSN ""

//DetourC sceNpManagerGetNpIdDetour, sceNpManagerGetOnlineIdDetour, sceNpManagerGetStatusDetour, sceNpManagerRequestTicket2Detour, sceNpManagerRequestTicket2Detour;


SceNpCommunicationId communication_id = {
		{'N','P','X','S','0','0','0','0','5'},
		'\0',
		0,
		0
};

SceNpCommunicationId communication_id_BO2 = {
	{ 'N', 'P', 'W', 'R', '0', '2', '0', '5', '9' },
	'\0',
	0,
	0
};

SceNpCommunicationPassphrase CommPassphrase = {
	{
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
		0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa
	}
};


SceNpCommunicationId* GetNpCommId() {
	return &communication_id;
}


SceNpCommunicationId* GetNpCommId_BO2() {
	return &communication_id_BO2;
}


SceNpCommunicationPassphrase* GetNpPass() {
	return &CommPassphrase;
}

NPClient_Info npclient;
#define LOOKUP_THREAD_PRIO            1500
static int __doLookupNpId(SceNpId& npId, SceNpOnlineId onlineId) {
	int ret, lookupTransId;
	SceNpId selfNpId;
	int32_t lookupTitleCtxId = -1;

	ret = sceNpManagerGetNpId(&selfNpId);
	if (ret < 0) {
		printf("[BO2] sceNpManagerGetNpId() failed. ret = 0x%x\n", ret);
	}

	ret = sceNpLookupCreateTitleCtx(GetNpCommId_BO2(), &selfNpId);
	if (ret < 0) {
		printf("[BO2] sceNpLookupCreateTitleCtx() failed. ret = 0x%x\n", ret);
	}
	lookupTitleCtxId = ret;

	ret = sceNpLookupCreateTransactionCtx(ret);
	if (ret < 0) {
		printf("[BO2] sceNpLookupCreateTransactionCtx() failed. ret = 0x%x\n", ret);
	}
	lookupTransId = ret;

	ret = sceNpLookupNpIdAsync(ret, &onlineId, &npId, NULL, NULL);
	if (ret < 0) {
		printf("[BO2] sceNpLookupNpIdAsync() failed. ret = 0x%x\n", ret);
	}
	int32_t result;
	ret = 1;
	while (ret == 1) {
		ret = sceNpLookupPollAsync(lookupTransId, &result);
		cellSysutilCheckCallback();
	}

error:
	if (lookupTransId >= 0) {
		ret = sceNpLookupDestroyTransactionCtx(lookupTransId);
		if (ret < 0) {
			printf("[BO2] sceNpLookupDestroyTransactionCtx() failed. ret = 0x%x\n", ret);
		}
		lookupTransId = 0;
	}

	if (lookupTitleCtxId >= 0) {
		ret = sceNpLookupDestroyTitleCtx(lookupTitleCtxId);
		if (ret < 0) {
			printf("[BO2] sceNpLookupDestroyTitleCtx() failed. ret = 0x%x\n", ret);
		}
	}

	return ret;
}

std::pair<SceNpId, int> doLookupNpId(const char* onlineIdString) {
	int32_t ret, tmp;
	int32_t lookupTitleCtxId;
	SceNpId npId;

	SceNpOnlineId onlineId;
	memset(&onlineId, 0, sizeof(onlineId));
	strncpy(onlineId.data, onlineIdString, SCE_NET_NP_ONLINEID_MAX_LENGTH);

	int32_t transId = sceNpLookupCreateTransactionCtx(*(int*)0x2670640);

	ret = sceNpLookupNpIdAsync(transId, &onlineId, &npId, NULL, NULL);
	int32_t result;
	ret = 1;
	while (ret == 1) {
		ret = sceNpLookupPollAsync(transId, &result);
		cellSysutilCheckCallback();
	}
	sceNpLookupDestroyTransactionCtx(transId);

	return std::make_pair(npId, ret);
}