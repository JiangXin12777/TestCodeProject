// Copyright (C) RenZhai.2023.All Rights Reserved.

#pragma once
#include "SimpleProtocolsDefinition.h"

DEFINITION_SIMPLE_PROTOCOLS(StartGameServerRequests, 33)
DEFINITION_SIMPLE_PROTOCOLS(StartGameServerResponse, 34)
DEFINITION_SIMPLE_PROTOCOLS(DSServerIdentityRegistrationRequests, 35)
DEFINITION_SIMPLE_PROTOCOLS(DSServerIdentityRegistrationResponse, 36)
DEFINITION_SIMPLE_PROTOCOLS(GuardGatewayIdentityRegistrationRequests, 37)
DEFINITION_SIMPLE_PROTOCOLS(GuardGatewayIdentityRegistrationResponse, 38)
DEFINITION_SIMPLE_PROTOCOLS(GameServerInitializationRequests, 39)
DEFINITION_SIMPLE_PROTOCOLS(GameServerInitializationResponse, 40)
DEFINITION_SIMPLE_PROTOCOLS(AllPlayerCheckOutRequests, 41)//退房 游戏完结或者是选择角色的时候玩家没有选择
DEFINITION_SIMPLE_PROTOCOLS(AllPlayerCheckOutResponse, 42)//退房
