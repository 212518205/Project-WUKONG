#pragma once
#include "GameplayTagContainer.h"

namespace Debug
{
	static void Print(const FString& Message, const FColor& Color = FColor::MakeRandomColor(), const float Time = 7.f, const int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, Time, Color, Message);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
	
	static void Print(const TMap<FString, float>& Values, const FColor& Color = FColor::MakeRandomColor(), const float Time = 7.f, const int32 InKey = -1)
	{
		FString Message;
		bool bFirst = true;
		for (const auto& Pair : Values)
		{
			if (!bFirst)
				Message += TEXT(", ");
			Message += FString::Printf(TEXT("%s: %f"), *Pair.Key, Pair.Value);
			bFirst = false;
		}
		Print(Message, Color, Time, InKey);
	}
	
	static void Print(const FGameplayTag& Tag, const FColor& Color = FColor::MakeRandomColor(), const float Time = 7.f, const int32 InKey = -1)
	{
		Print(Tag.ToString(), Color, Time, InKey);
	}
}
