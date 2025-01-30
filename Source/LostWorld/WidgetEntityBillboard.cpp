#include "WidgetEntityBillboard.h"


void UWidgetEntityBillboard::UpdateBillboard(const FEntity& InEntity) const
{
	float HealthAsPercentage = float(InEntity.TotalStats.CurrentHealthPoints) / float(InEntity.TotalStats.MaximumHealthPoints);
	HealthBar->SetPercent(HealthAsPercentage);

	float ManaAsPercentage = float(InEntity.TotalStats.CurrentManaPoints) / float(InEntity.TotalStats.MaximumManaPoints);
	ManaBar->SetPercent(ManaAsPercentage);

	FString ManaTextAsString = FString::FromInt(InEntity.TotalStats.CurrentManaPoints) + " / " + FString::FromInt(InEntity.TotalStats.MaximumManaPoints);
	ManaText->SetText(FText::FromString(ManaTextAsString));

	if (InEntity.TotalStats.CurrentBarrierPoints > 0) {
		BarrierBar->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		float BarrierAsPercentage = float(InEntity.TotalStats.CurrentBarrierPoints) / float(InEntity.TotalStats.MaximumHealthPoints);
		HealthBar->SetPercent(BarrierAsPercentage);

		FString BarrierTextAsString = FString::FromInt(InEntity.TotalStats.CurrentBarrierPoints);
		HealthText->SetText(FText::FromString(BarrierTextAsString));
	} else {
		BarrierBar->SetVisibility(ESlateVisibility::Collapsed);

		FString HealthTextAsString = FString::FromInt(InEntity.TotalStats.CurrentHealthPoints) + " / " + FString::FromInt(InEntity.TotalStats.MaximumHealthPoints);
		HealthText->SetText(FText::FromString(HealthTextAsString));
	}
}
