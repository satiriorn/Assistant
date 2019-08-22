// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class ASSISTANT_API APortal : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Portal")
		bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "Portal")
		void SetActive(bool NewActive);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Portal")
		void ClearRTT();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Portal")
		void SetRTT(UTexture* RenderTexture);

	UFUNCTION(BlueprintNativeEvent, Category = "Portal")
		void ForceTick();

	UFUNCTION(BlueprintPure, Category = "Portal")
		AActor* GetTarget();

	UFUNCTION(BlueprintCallable, Category = "Portal")
		void SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, Category = "Portal")
		bool IsPointInFrontOfPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);

	UFUNCTION(BlueprintCallable, Category = "Portal")
		bool IsPointCrossingPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);

	UFUNCTION(BlueprintCallable, Category = "Portal")
		void TeleportActor(AActor* ActorToTeleport);
		
	APortal(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(BlueprintReadOnly)
		USceneComponent* PortalRootComponent;
		
private:
	bool bIsActive;

	AActor* Target;

	FVector LastPosition;
	bool 	LastInFront;
};
