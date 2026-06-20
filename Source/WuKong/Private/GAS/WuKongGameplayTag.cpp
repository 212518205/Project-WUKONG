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
		UE_DEFINE_GAMEPLAY_TAG(Attackable, "Player.Ability.Attackable")
	}

	namespace Status
	{
		UE_DEFINE_GAMEPLAY_TAG(Jumping, "Player.Status.Jumping")
		UE_DEFINE_GAMEPLAY_TAG(Attacking, "Player.Status.Attacking")
		UE_DEFINE_GAMEPLAY_TAG(Dead, "Player.Status.Dead")
	}
}


namespace Shared
{
	namespace Event
	{
		UE_DEFINE_GAMEPLAY_TAG(MeleeHit, "Shared.Event.MeleeHit")
		UE_DEFINE_GAMEPLAY_TAG(TakeHit, "Shared.Event.TakeHit")
	}

	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG(BaseDamageMultiplier, "Shared.SetByCaller.BaseDamageMultiplier")
	}
}

namespace GameplayCue
{
	namespace Shared
	{
		UE_DEFINE_GAMEPLAY_TAG(TakeHit, "GameplayCue.Character.TakeHit")
	}
}
