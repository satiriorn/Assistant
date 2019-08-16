// Fill out your copyright notice in the Description page of Project Settings.


#include "AssistantGameModeBase.h"
#include "BunAssistant.h"

AAssistantGameModeBase::AAssistantGameModeBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<ABunAssistant>Assist(TEXT("/Game/Blueprints/Character/AssistantBP"));
	DefaultPawnClass = Assist.Class;	
}
