#include "AnimationWidget.h"

#include "Components/Image.h"

const FName UAnimationWidget::MaterialParameterFrameRate = TEXT("FrameRate");
const FName UAnimationWidget::MaterialParameterColumnsAmount = TEXT("NumberOfColumns");
const FName UAnimationWidget::MaterialParameterRowsAmount = TEXT("NumberOfRows");
const FName UAnimationWidget::MaterialParameterStaticFrameNumber = TEXT("StaticFrameNumber");
const FName UAnimationWidget::MaterialParameterAnimationTexture = TEXT("AnimationTexture");
const FName UAnimationWidget::MaterialParameterTime = TEXT("InputTime");

void UAnimationWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	InitializeMaterial();
}

void UAnimationWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAnimationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (IsPaused)
		return;

	CurrentTime += InDeltaTime;
	SetTimeInput(CurrentTime);

	UE_LOG(LogTemp, Warning, TEXT("Time: %f"), CurrentTime / GetAnimationDuration());
}

void UAnimationWidget::AnimationPlay()
{
	IsPaused = false;
}

void UAnimationWidget::AnimationPause()
{
	IsPaused = true;
}

void UAnimationWidget::AnimationStop()
{
	IsPaused = true;
	SetFrame(StaticFrameNumber);
}

void UAnimationWidget::SetFrame(int32 InFrame)
{
	float FramesAmount = static_cast<float>(GetFramesAmount());
	if (FramesAmount == 0)
		return;

	float Percent = (1 / FramesAmount) * static_cast<float>(InFrame);
	CurrentTime = (GetAnimationDuration() * Percent);
	SetTimeInput(Percent);
}

void UAnimationWidget::InitializeMaterial()
{
	if (!AnimationMaterialInstance)
		return;

	if (!AnimationTexture)
		return;

	if (!AnimImage)
		return;

	AnimationMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(AnimationMaterialInstance, this);
	if (!AnimationMaterialInstanceDynamic)
		return;

	SetFrameRate(FrameRate);
	SetColumnsAmount(ColumnsAmount);
	SetRowsAmount(RowsAmount);
	SetStaticFrameNumber(StaticFrameNumber);
	SetAnimationTexture(AnimationTexture);

	FSlateBrush AnimatedBrush = AnimImage->GetBrush();
	AnimatedBrush.SetResourceObject(AnimationMaterialInstanceDynamic);
	AnimImage->SetBrush(AnimatedBrush);
}

void UAnimationWidget::SetTimeInput(float InTime)
{
	if (!AnimationMaterialInstanceDynamic)
		return;

	AnimationMaterialInstanceDynamic->SetScalarParameterValue(MaterialParameterTime, InTime);
}

int32 UAnimationWidget::GetCurrentFrame() const
{
	if (CurrentTime == 0.f)
		return 0;

	if (GetFramesAmount() == 0)
		return 0;

	return static_cast<int32>(FMath::FloorToInt(CurrentTime * static_cast<float>(FrameRate))) % GetFramesAmount();
}

void UAnimationWidget::SetFrameRate(int32 InFrameRate)
{
	if (!AnimationMaterialInstanceDynamic)
		return;

	FrameRate = InFrameRate;
	AnimationMaterialInstanceDynamic->SetScalarParameterValue(MaterialParameterFrameRate, static_cast<float>(InFrameRate));
}

void UAnimationWidget::SetColumnsAmount(int32 InColumnsAmount)
{
	if (!AnimationMaterialInstanceDynamic)
		return;

	ColumnsAmount = InColumnsAmount;
	AnimationMaterialInstanceDynamic->SetScalarParameterValue(MaterialParameterColumnsAmount, static_cast<float>(InColumnsAmount));
}

void UAnimationWidget::SetRowsAmount(int32 InRowsAmount)
{
	if (!AnimationMaterialInstanceDynamic)
		return;

	RowsAmount = InRowsAmount;
	AnimationMaterialInstanceDynamic->SetScalarParameterValue(MaterialParameterRowsAmount, static_cast<float>(InRowsAmount));
}

void UAnimationWidget::SetStaticFrameNumber(int32 InStaticFrameNumber)
{
	StaticFrameNumber = InStaticFrameNumber;
}

void UAnimationWidget::SetAnimationTexture(UTexture2D* InAnimationTexture)
{
	if (!InAnimationTexture)
		return;

	if (!AnimationMaterialInstanceDynamic)
		return;

	AnimationTexture = InAnimationTexture;
	AnimationMaterialInstanceDynamic->SetTextureParameterValue(MaterialParameterAnimationTexture, InAnimationTexture);
}
