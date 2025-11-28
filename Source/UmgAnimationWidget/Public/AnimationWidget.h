#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "AnimationWidget.generated.h"

class UImage;
class UTexture2D;
class UMaterialInstance;
class UMaterialInstanceDynamic;

UCLASS(Blueprintable, BlueprintType)
class UMGANIMATIONWIDGET_API UAnimationWidget : public UUserWidget
{
	GENERATED_BODY()

	static const FName MaterialParameterFrameRate;
	static const FName MaterialParameterColumnsAmount;
	static const FName MaterialParameterRowsAmount;
	static const FName MaterialParameterStaticFrameNumber;
	static const FName MaterialParameterAnimationTexture;
	static const FName MaterialParameterTime;

	//private fields
private:

	UPROPERTY(EditDefaultsOnly, Category = "UMG Animated Widget")
	UMaterialInstance* AnimationMaterialInstance{ nullptr };

	UPROPERTY(VisibleDefaultsOnly, Category = "UMG Animated Widget")
	UMaterialInstanceDynamic* AnimationMaterialInstanceDynamic{ nullptr };

	/* Current animation time. Mapped to 0-1 in Tick */
	UPROPERTY(VisibleDefaultsOnly, Category = "UMG Animated Widget")
	float CurrentTime{ 0.f };

	UPROPERTY(VisibleDefaultsOnly, Category = "UMG Animated Widget")
	bool IsPaused{ false };

	UPROPERTY(VisibleDefaultsOnly, Category = "UMG Animated Widget")
	bool IsOnce{ false };

	/* Set your animation sprite sheet */
	UPROPERTY(EditAnywhere, Category = "UMG Animated Widget")
	UTexture2D* AnimationTexture{ nullptr };

	/* Set desired animation frame rate */
	UPROPERTY(EditAnywhere, Category = "UMG Animated Widget")
	int32 FrameRate{ 30 };

	/* Set amount of columns in your animation spreadsheet */
	UPROPERTY(EditAnywhere, Category = "UMG Animated Widget")
	int32 ColumnsAmount{ 0 };

	/* Set amount of rows in your animation spreadsheet */
	UPROPERTY(EditAnywhere, Category = "UMG Animated Widget")
	int32 RowsAmount{ 0 };

	/* Set static frame number (0 based) if you want to display a static frame instead of an animation */
	UPROPERTY(EditAnywhere, Category = "UMG Animated Widget")
	int32 StaticFrameNumber{ 0 };

	/* Image in the UMG control that will display animation */
	UPROPERTY(meta = (BindWidget))
	UImage* AnimImage{ nullptr };

//public methods
public:
	/* Initializes widget in editor */
	void NativePreConstruct() override;

	/* Initializes widget in runtime */
	void NativeConstruct() override;

	/* Tick is used to play, pause and stop animation */
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	/* Plays or resumes animation */
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void AnimationPlay();

	/* Plays animation once from static frame to end */
	void AnimationPlayOnce();

	/* Pauses animation (on current frame) */
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void AnimationPause();

	/* Stops animation (and resets frame to StaticFrameNumber) */
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void AnimationStop();

	/* Sets animation to desired frame */
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void SetFrame(int32 InFrame);

	/* Sets desired frame rate */
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void SetFrameRate(int32 InFrameRate);

	/* Sets amount of columns in the sprite sheet to properly cut it */
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void SetColumnsAmount(int32 InColumnsAmount);

	/* Sets amount of rows in the sprite sheet to properly cut it */
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void SetRowsAmount(int32 InRowsAmount);

	/* Sets frame number, that will be selected on animation stop */
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void SetStaticFrameNumber(int32 InStaticFrameNumber);

	/* Sets animation sprite sheet*/
	UFUNCTION(BlueprintCallable, Category = "UMG Animated Widget")
	void SetAnimationTexture(UTexture2D* InAnimationTexture);

//private methods
private:
	/* Initializes MaterialInstance, sets all the parameters */
	void InitializeMaterial();

	void SetTimeInput(float InTime);

//public getters/setters
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	int32 GetFrameRate() const { return FrameRate; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	int32 GetColumnsAmount() const { return ColumnsAmount; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	int32 GetRowsAmount() const { return RowsAmount; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	int32 GetStaticFrameNumber() const { return StaticFrameNumber; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	int32 GetCurrentFrame() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	int32 GetFramesAmount() const { return ColumnsAmount * RowsAmount;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	float GetAnimationDuration() const { return static_cast<float>(GetFramesAmount()) / static_cast<float>(FrameRate); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	float GetFrameDuration() const { return 1.f / static_cast<float>(FrameRate); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	bool GetIsPaused() const { return IsPaused; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UMG Animated Widget")
	UTexture2D* GetAnimationTexture() const { return AnimationTexture; }
};
