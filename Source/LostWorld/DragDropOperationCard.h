#pragma once


#include "CoreMinimal.h"
#include "Variables.h"
#include "Blueprint/DragDropOperation.h"
#include "DragDropOperationCard.generated.h"


UCLASS()
class LOSTWORLD_API UDragDropOperationCard : public UDragDropOperation
{
	GENERATED_BODY()

// ---------------------------------------- Variables ---------------------------------------- //
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCard DraggedCardData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D CursorPositionAsPercentage;
	

// ---------------------------------------- Functions ---------------------------------------- //
	virtual void Dragged_Implementation(const FPointerEvent& PointerEvent) override;
};
