// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace Player
{
	namespace Ability
	{
		namespace Input
		{
			WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(LMB);
			WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(RMB);
			WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Q);
			WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Space);
		}
		WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Light);
		WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Heavy);
		WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability1);
		WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Jump);
	}

	namespace Status
	{
		WUKONG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Jumping);
	}
}
