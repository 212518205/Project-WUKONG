// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ExecCalc/ExecCalc_DamageTaken.h"

#include "WuKongDebugHelper.h"
#include "FunctionLibrary/WuKongGameFunctionLibrary.h"
#include "GAS/WuKongAttributeSet.h"
#include "GAS/WuKongGameplayTag.h"

struct FWuKongAttributeCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamage)
	
	FWuKongAttributeCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWuKongAttributeSet, DamageTaken, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWuKongAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWuKongAttributeSet, Attack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWuKongAttributeSet, CriticalChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWuKongAttributeSet, CriticalDamage, Source, false);
	}
};

namespace
{
	const FWuKongAttributeCapture& AttributeCapture()
	{
		static FWuKongAttributeCapture Capture;
		return Capture;
	}
	
	#define ATTRIBUTE_GETTER_SAFE(Name, T) \
		float T##Name = 0.f; \
		if (!ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttributeCapture().Name##Def, EvaluateParameters, T##Name)) \
		{ \
			UE_LOG(LogTemp, Warning, TEXT("Failed to capture " #T #Name " in ExecCalcDamageTaken")); \
			return; \
		}
	
}

UExecCalc_DamageTaken::UExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(AttributeCapture().DamageTakenDef);
	RelevantAttributesToCapture.Add(AttributeCapture().AttackDef);
	RelevantAttributesToCapture.Add(AttributeCapture().ArmorDef);
	RelevantAttributesToCapture.Add(AttributeCapture().CriticalChanceDef);
	RelevantAttributesToCapture.Add(AttributeCapture().CriticalDamageDef);
}

void UExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec EffectSpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	ATTRIBUTE_GETTER_SAFE(DamageTaken, Target);
	ATTRIBUTE_GETTER_SAFE(Armor, Target);
	ATTRIBUTE_GETTER_SAFE(Attack, Source)
	ATTRIBUTE_GETTER_SAFE(CriticalChance, Source);
	ATTRIBUTE_GETTER_SAFE(CriticalDamage, Source);

	const float BaseDamageMultiplier = EffectSpec.GetSetByCallerMagnitude(Shared::SetByCaller::BaseDamageMultiplier);
	SourceAttack *= BaseDamageMultiplier;
	if (UWuKongGameFunctionLibrary::CheckProbability(SourceCriticalChance))SourceAttack = SourceAttack * 2 * (1.f + SourceCriticalDamage);
	SourceAttack -= TargetArmor;
	
	if (SourceAttack >= 0)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				AttributeCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				SourceAttack
			)	
		);
	}
	
}
