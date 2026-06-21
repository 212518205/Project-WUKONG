#include "UI/WuKongHUD.h"
#include "UI/CommonActiveStack.h"
#include "Components/CanvasPanelSlot.h"

void UWuKongHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (ActiveStack)
	{
		if (UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(ActiveStack->Slot))
		{
			PanelSlot->SetAnchors(FAnchors(0, 0, 1, 1));
			PanelSlot->SetOffsets(FMargin(0, 0, 0, 0));
		}
	}
}
