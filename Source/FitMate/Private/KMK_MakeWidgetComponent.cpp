// Fill out your copyright notice in the Description page of Project Settings.


#include "KMK_MakeWidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "KMK_InteractionActor.h"
#include "KMK_Player.h"
#include "KMK_ReceipWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UKMK_MakeWidgetComponent::UKMK_MakeWidgetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKMK_MakeWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	me = Cast< AKMK_Player>(GetOwner());
}


// Called every frame
void UKMK_MakeWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UKMK_MakeWidgetComponent::SetupInputBinding(class UEnhancedInputComponent* input)
{
	// 키입력 바인딩
	input->BindAction(IA_Interaction, ETriggerEvent::Triggered, this, &UKMK_MakeWidgetComponent::InputInteraction);
}

void UKMK_MakeWidgetComponent::InputInteraction(const struct FInputActionValue& value)
{
	
	// 라인 트레이스를 통해 클릭된 오브젝트를 감지
	FHitResult HitResult;
	me->pc->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	// 히트된 오브젝트가 있는지 확인
	if (HitResult.bBlockingHit)
	{
		// 클릭된 오브젝트의 정보 받아오기
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			FVector ActorLocation = HitActor->GetActorLocation();
			if (HitActor->GetActorLabel().Contains("Media"))
			{
				FVector RandomLocation = FVector(HitActor->GetActorLocation().X,
					FMath::RandRange(-500.f, 500.f),
					FMath::RandRange(-500.f, 500.f));
				GEngine->AddOnScreenDebugMessage(3, 1, FColor::Cyan, FString::Printf(TEXT("alfdjlskf")));
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedParticle, RandomLocation);
				
			}
			count = 0;
			auto* actorClass = Cast<AKMK_InteractionActor>(HitActor);
			if (actorClass)
			{
				widget = CreateWidget(GetWorld(), actorClass->widgetFact);
				if (widget && count < 1)
				{
					SetViewPortLayer(widget, actorClass->layer);
					count++;
					auto* ex = Cast<UKMK_ReceipWidget>(widget);
					if (ex)
					{
						TMap<FString, FString> log;
						log.Add("HI", "1");
						log.Add("He", "2");
						log.Add("HIy", "3");
						ex->SetTextLog(log);
					}
				}
			}
		}
	}
}

// 외부에서 호출
void UKMK_MakeWidgetComponent::SetViewPortLayer(UUserWidget* wid, int num)
{
	wid->AddToViewport(num);
	me->pc->SetPause(true);
}

void UKMK_MakeWidgetComponent::DeleteMyWidget()
{
	widget->RemoveFromParent();
	me->pc->SetPause(false);
}
