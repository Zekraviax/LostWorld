#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LostWorld_422GameModeBase.h"
#include "Lostworld_422GameStateBase.h"

#include "BaseClass_CardUserWidget.generated.h"

// Forward Declarations
class ABaseClass_PlayerController;


UCLASS()
class LOSTWORLD_422_API UBaseClass_CardUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// NativeTick override
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	FCardBase CardData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	int32 IndexInZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	bool IsDragging;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical")
	ABaseClass_PlayerController* LocalPlayerControllerRef;

// ------------------------- References
	UPROPERTY()
	ALostWorld_422GameModeBase* GameModeRef;

	UPROPERTY()
	ALostWorld_422GameStateBase* GameStateRef;

// Base Variables
// --------------------------------------------------

// ------------------------- Mouse
	UFUNCTION(BlueprintCallable)
	void OnMouseButtonDownEvent(UBaseClass_CardUserWidget* CardDragWidgetInstance);

	UFUNCTION()
	void CastCard();
};
