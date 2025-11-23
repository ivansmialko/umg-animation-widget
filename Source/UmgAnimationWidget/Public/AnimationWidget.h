#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "AnimationWidget.generated.h"

class UTexture2D;
class UMaterialInstanceDynamic;

UCLASS(Blueprintable, BlueprintType)
class UAnimationWidget : public UUserWidget
{
    GENERATED_BODY()

//private fields
private:
	/* Set your animation spreadsheet */
	UPROPERTY(EditAnywhere, Category="Animation")
	UTexture2D* AnimationTexture{ nullptr };

	/* Set desired animation frame rate */
	UPROPERTY(EditAnywhere, Category = "Animation")
	uint32 FrameRate{ 30 };

	/* Set amount of columns in your animation spreadsheet */
	UPROPERTY(EditAnywhere, Category = "Animation")
	uint32 ColumnsAmount{ 0 };

	/* Set amount of rows in your animation spreadsheet */
	UPROPERTY(EditAnywhere, Category = "Animation")
	uint32 RowsAmount{ 0 };

	/* Set static frame number (0 based) if you want to display a static frame instead of an animation */
	UPROPERTY(EditAnywhere, Category = "Animation")
	uint32 StaticFrameNumber{ 0 };
};
