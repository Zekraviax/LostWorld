#include "BaseClass_WidgetComponent_Stats.h"

#include "BaseClass_EntityInBattle.h"


void UBaseClass_WidgetComponent_Stats::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseClass_WidgetComponent_Stats::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (LinkedEntity) {
		float HealthValue = float(LinkedEntity->EntityBaseData.HealthValues.X_Value) / float(LinkedEntity->EntityBaseData.HealthValues.Y_Value);
		float ManaValue = float(LinkedEntity->EntityBaseData.ManaValues.X_Value) / float(LinkedEntity->EntityBaseData.ManaValues.Y_Value);
		float HealthPercentValue = FMath::FInterpTo(HealthBar->Percent, HealthValue, DeltaTime, 5.f);
		float ManaPercentValue = FMath::FInterpTo(ManaBar->Percent, ManaValue, DeltaTime, 5.f);
		HealthBar->SetPercent(HealthPercentValue);
		ManaBar->SetPercent(ManaPercentValue);
	}
}