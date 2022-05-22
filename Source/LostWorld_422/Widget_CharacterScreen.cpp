#include "Widget_CharacterScreen.h"


void UWidget_CharacterScreen::SetVariables(FEntityBase PlayerStats)
{
	HealthText->SetText(FText::FromString("HP: " + FString::FromInt(PlayerStats.HealthValues.X_Value) + " / " + FString::FromInt(PlayerStats.HealthValues.Y_Value)));
	ManaText->SetText(FText::FromString("MP: " + FString::FromInt(PlayerStats.ManaValues.X_Value) + " / " + FString::FromInt(PlayerStats.ManaValues.Y_Value)));

	StrengthText->SetText(FText::FromString("Strength: " + FString::FromInt(PlayerStats.CoreStats.Strength)));
	ConstitutionText->SetText(FText::FromString("Constitution: " + FString::FromInt(PlayerStats.CoreStats.Constitution)));
	IntelligenceText->SetText(FText::FromString("Intelligence: " + FString::FromInt(PlayerStats.CoreStats.Intelligence)));
	WisdomText->SetText(FText::FromString("Wisdom: " + FString::FromInt(PlayerStats.CoreStats.Wisdom)));
	DexterityText->SetText(FText::FromString("Dexterity: " + FString::FromInt(PlayerStats.CoreStats.Dexterity)));
}