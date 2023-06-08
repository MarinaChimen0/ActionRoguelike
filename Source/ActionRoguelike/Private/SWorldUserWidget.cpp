#include "SWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!IsValid(AttachedActor))
	{
		RemoveFromParent();
		UE_LOG(LogTemp, Warning, TEXT("AttachedActor no longer valid, removing Health Widget."));
		return;
	}
	
	FVector2D ScreenPosition;
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition))
	{
		const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		if(ParentSizeBox)
			ParentSizeBox->SetRenderTranslation(ScreenPosition/Scale);
	}
}
