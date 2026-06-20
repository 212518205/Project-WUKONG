// 


#include "Component/UI/UWukongWidgetComponent.h"

#include "CommonTextBlock.h"
#include "Components/ProgressBar.h"
#include "GAS/WuKongAttributeSet.h"
#include "GAS/ASC/PlayerAbilitySystemComponent.h"
#include "Player/WuKongCharacter.h"
#include "UI/PlayerHealthBarWidget.h"

void UWukongWidgetComponent::InitWidget()
{
	Super::InitWidget();
	
	UPlayerAbilitySystemComponent* PlayerASC = Cast<AWuKongCharacter>(GetOwner())->GetAbilitySystemComponent();
	
	CachedHealthWidget = Cast<UPlayerHealthBarWidget>(GetUserWidgetObject());
	check(CachedHealthWidget);
	
	BindCharacterInfoToUI(PlayerASC);
}

void UWukongWidgetComponent::BindCharacterInfoToUI(UPlayerAbilitySystemComponent* PlayerASC)
{
	CachedHealthWidget = Cast<UPlayerHealthBarWidget>(GetUserWidgetObject());
	
	if (!PlayerASC || !CachedHealthWidget)return;
	
	MaxHealth = PlayerASC->GetNumericAttribute(UWuKongAttributeSet::GetMaxHealthAttribute());
	Health = PlayerASC->GetNumericAttribute(UWuKongAttributeSet::GetHealthAttribute());
	const float Percent = MaxHealth > 0.f ? Health / MaxHealth : 0.f;
	CachedHealthWidget->HealthBar->SetPercent(Percent);
	
	PlayerASC->GetGameplayAttributeValueChangeDelegate(UWuKongAttributeSet::GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			float OldHealth = Data.OldValue;
			Health = Data.NewValue;
			const float HealthPercent = MaxHealth > 0.f ? Health / MaxHealth : 0.f;
			CachedHealthWidget->HealthBar->SetPercent(HealthPercent);
		});	
	
	PlayerASC->GetGameplayAttributeValueChangeDelegate(UWuKongAttributeSet::GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			MaxHealth = Data.NewValue;
			const float HealthPercent = MaxHealth > 0.f ? Health / MaxHealth : 0.f;
			CachedHealthWidget->HealthBar->SetPercent(HealthPercent);
		});
}

void UWukongWidgetComponent::ShowDamage(const float DamageTaken) const
{
	CachedHealthWidget->TextBlock_DamageTaken->SetText(FText::AsNumber(DamageTaken));
	CachedHealthWidget->PlayAnimation(CachedHealthWidget->DamageFloatAnimation);
}
