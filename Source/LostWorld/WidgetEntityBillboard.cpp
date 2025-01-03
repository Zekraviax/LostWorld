#include "WidgetEntityBillboard.h"


void UWidgetEntityBillboard::UpdateBillboard(const FEntity& InEntity) const
{
	float HealthAsPercentage = float(InEntity.Stats.CurrentHealthPoints) / float(InEntity.Stats.MaximumHealthPoints);
	HealthBar->SetPercent(HealthAsPercentage);

	float ManaAsPercentage = float(InEntity.Stats.CurrentManaPoints) / float(InEntity.Stats.MaximumManaPoints);
	ManaBar->SetPercent(ManaAsPercentage);

	FString ManaTextAsString = FString::FromInt(InEntity.Stats.CurrentManaPoints) + " / " + FString::FromInt(InEntity.Stats.MaximumManaPoints);
	ManaText->SetText(FText::FromString(ManaTextAsString));

	if (InEntity.Stats.CurrentBarrierPoints > 0) {
		BarrierBar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		FString BarrierTextAsString = FString::FromInt(InEntity.Stats.CurrentBarrierPoints);
		HealthText->SetText(FText::FromString(BarrierTextAsString));
	} else {
		BarrierBar->SetVisibility(ESlateVisibility::Collapsed);

		FString HealthTextAsString = FString::FromInt(InEntity.Stats.CurrentHealthPoints) + " / " + FString::FromInt(InEntity.Stats.MaximumHealthPoints);
		HealthText->SetText(FText::FromString(HealthTextAsString));
	}
}
