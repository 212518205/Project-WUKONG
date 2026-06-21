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
		UE_DEFINE_GAMEPLAY_TAG(Dead, "GameplayCue.Character.Dead")
	}
}

namespace UI
{
	namespace Layer
	{
		UE_DEFINE_GAMEPLAY_TAG(GameHUD, "UI.Layer.GameHUD")
		UE_DEFINE_GAMEPLAY_TAG(MainMenu, "UI.Layer.MainMenu")
		UE_DEFINE_GAMEPLAY_TAG(PauseMenu, "UI.Layer.PauseMenu")
		UE_DEFINE_GAMEPLAY_TAG(Inventory, "UI.Layer.Inventory")
		UE_DEFINE_GAMEPLAY_TAG(Dialog, "UI.Layer.Dialog")
		UE_DEFINE_GAMEPLAY_TAG(LoadingScreen, "UI.Layer.LoadingScreen")
	}
}

namespace Session
{
	namespace Status
	{
		UE_DEFINE_GAMEPLAY_TAG(Hosting, "Session.Status.Hosting")
		UE_DEFINE_GAMEPLAY_TAG(Searching, "Session.Status.Searching")
		UE_DEFINE_GAMEPLAY_TAG(InSession, "Session.Status.InSession")
	}
}
