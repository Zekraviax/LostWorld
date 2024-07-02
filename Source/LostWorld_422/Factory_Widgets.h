#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Widget_Inventory_Base.h"

#include "Factory_Widgets.generated.h"


UCLASS()
class LOSTWORLD_422_API AFactory_Widgets : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFactory_Widgets();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Inventory
// --------------------------------------------------
	TSubclassOf<UWidget_Inventory_Base> Inventory_Class;
};
