// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/WuKongGameplayTag.h"

namespace Player
{
	namespace Ability
	{
		namespace Input
		{
			UE_DEFINE_GAMEPLAY_TAG(LMB, "Player.Ability.Input.LMB");
			UE_DEFINE_GAMEPLAY_TAG(RMB, "Player.Ability.Input.RMB");
			UE_DEFINE_GAMEPLAY_TAG(Q, "Player.Ability.Input.Q");
			UE_DEFINE_GAMEPLAY_TAG(Space, "Player.Ability.Input.Space");
		}
		UE_DEFINE_GAMEPLAY_TAG(Light, "Player.Ability.Light")
		UE_DEFINE_GAMEPLAY_TAG(Heavy, "Player.Ability.Heavy")
		UE_DEFINE_GAMEPLAY_TAG(Ability1, "Player.Ability.Ability1")
		UE_DEFINE_GAMEPLAY_TAG(Jump, "Player.Ability.Jump")
	}

	namespace Status
	{
		UE_DEFINE_GAMEPLAY_TAG(Jumping, "Player.Status.Jumping")
	}
}