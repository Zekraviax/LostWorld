#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ScrollBox.h"

#include "Widget_CustomConsole_Base.generated.h"


UCLASS()
class LOSTWORLD_422_API UWidget_CustomConsole_Base : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* ConsoleScrollBox;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION(BlueprintCallable)
	void AddEntry(FString text);


/* TO-DO:
 * Added types of Custom Console entries
 * Add different colours of entries
 * Change the name of the function to include 'CustomConsole'.
 * Added Show/Hide function.
 */
};
