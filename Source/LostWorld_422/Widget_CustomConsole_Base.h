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
 * Add types of Custom Console entries
 * Add different colours for text entries
 * Change the name of the function to include 'CustomConsole'.
 * Added Show/Hide function.
 * Create easily accessed instance of this widget for add entries to the console scroll box
 */
};
