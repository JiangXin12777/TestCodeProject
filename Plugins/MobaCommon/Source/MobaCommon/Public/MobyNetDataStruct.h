// Copyright (C) RenZhai.2023.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleNetChannelType.h"
#include "MobyNetDataStruct.generated.h"

struct MOBACOMMON_API FNetDSInfor
{
	FString IPString;//字符串类型的IP
	
	FGuid RoomID;
	FSimpleAddr Key;//主要作为中心服务器的验证 key 
	FSimpleAddr SimpleDSAddr;//简单的DS服务器地址
	FSimpleAddrInfo DSAddr;//DS服务器的真实地址 也是守护服务器链接DS服务器的地址

	bool bIsValid() { return RoomID.IsValid(); }

	void Reset() { RoomID = FGuid(); }
};

inline bool operator==(const FNetDSInfor& L, const FNetDSInfor& R)
{
	return L.RoomID == R.RoomID || L.DSAddr == R.DSAddr;
}

USTRUCT(BlueprintType)
struct MOBACOMMON_API FNetUserInfo
{
	GENERATED_USTRUCT_BODY()

	FNetUserInfo();

	UPROPERTY()
	FString Account;

	UPROPERTY()
	FString UserName;

	UPROPERTY()
	uint32 UserID;

	UPROPERTY()
	FString Avatar;//

	UPROPERTY()
	uint32 Gold;

	UPROPERTY()
	uint32 RenzhaiGold;
};

enum EMobaMatchingRules
{
	ONCE_VS_ONCE,//1vs1
	THREE_VS_THREE,//3vs3
	FIVE_VS_FIVE,//5vs5
};

enum EMobaServerType
{
	UNKNOWN_SERVER,//未知服务器
	DAEMON_SERVER,//守护服务器	
};

enum class EMatchCancellationType :uint8
{
	MC_INVALID,//无效
	MC_SERVER_FULL,//服务器满了
	MC_OTHER_PLAYERS_NOT_SURE,//其他玩家没有确定
	MC_TIME_OUT,//时间到了
	MC_PLAYER_EXIT,//有玩家退出游戏
	MC_ROOM_CREATION_FAILED,//房间创建失败
	MC_ALL_PLAYERS_EXIT,//所有玩家退场 一般是玩家已经在游戏中了 可能是选择角色的时候 有可能是游戏输了或者赢了
};
