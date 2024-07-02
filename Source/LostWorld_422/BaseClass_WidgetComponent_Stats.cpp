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
		float BarrierValue = float(LinkedEntity->EntityBaseData.Barrier) / float(LinkedEntity->EntityBaseData.HealthValues.Y_Value);

		float HealthPercentValue = FMath::FInterpTo(HealthBar->Percent, HealthValue, DeltaTime, 4.f);
		float ManaPercentValue = FMath::FInterpTo(ManaBar->Percent, ManaValue, DeltaTime, 4.f);
		float BarrierPercentValue = FMath::FInterpTo(BarrierBar->Percent, BarrierValue, DeltaTime, 4.f);

		//if (Barrier <= 0) {
		//	BarrierPercentValue = 0;
		//}

		HealthBar->SetPercent(HealthPercentValue);
		ManaBar->SetPercent(ManaPercentValue);
		BarrierBar->SetPercent(BarrierPercentValue);

		if (NameText->GetText().ToString() != LinkedEntity->EntityBaseData.DisplayName) {
			NameText->SetText(FText::FromString(LinkedEntity->EntityBaseData.DisplayName));
		}
	}
}