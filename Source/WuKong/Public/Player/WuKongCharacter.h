#pragma once

#include "CoreMinimal.h"
#include "AbilityCharacter.h"
#include "WuKongCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class WUKONG_API AWuKongCharacter : public AAbilityCharacter
{
	GENERATED_BODY()

public:
	AWuKongCharacter();

	virtual void BeginPlay() override;
	
protected:

};
