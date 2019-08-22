#include "Portal.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "BunAssistant.h"

APortal::APortal(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	bIsActive = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->Mobility = EComponentMobility::Static;

	PortalRootComponent	= CreateDefaultSubobject<USceneComponent>(TEXT("PortalRootComponent"));
	PortalRootComponent->SetupAttachment(GetRootComponent());
	PortalRootComponent->SetRelativeLocation( FVector(0.0f, 0.0f, 0.0f) );
	PortalRootComponent->SetRelativeRotation( FRotator(0.0f, 0.0f, 0.0f) );
	PortalRootComponent->Mobility = EComponentMobility::Movable;
}
void APortal::TeleportActor( AActor* ActorToTeleport )
{
	if( ActorToTeleport == nullptr || Target == nullptr )
	{
		return;
	}

	FVector SavedVelocity 	= FVector::ZeroVector;
	ABunAssistant* AC 	= nullptr;

	if( ActorToTeleport->IsA( ABunAssistant::StaticClass() ) )
	{
		AC = Cast<ABunAssistant>( ActorToTeleport );

		SavedVelocity = AC->GetCharMovementComponent()->GetCurrentVelocity();
	}

	FHitResult HitResult;
	FVector NewLocation = UTool::ConvertLocationToActorSpace( ActorToTeleport->GetActorLocation(), this, Target );

	ActorToTeleport->SetActorLocation( 	NewLocation, false, &HitResult, ETeleportType::TeleportPhysics );

	FRotator NewRotation = UTool::ConvertRotationToActorSpace(ActorToTeleport->GetActorRotation(), this, Target);

	ActorToTeleport->SetActorRotation( NewRotation );
	
	auto PC =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if( ActorToTeleport->IsA( ABunAssistant::StaticClass() ) )
	{
		if( PC != nullptr )
		{
			NewRotation = UTool::ConvertRotationToActorSpace(	PC->GetControlRotation(), this, Target );
			PC->SetControlRotation( NewRotation );
		}
		{
			FVector Dots;
			Dots.X 	= FVector::DotProduct( SavedVelocity, GetActorForwardVector() );
			Dots.Y 	= FVector::DotProduct( SavedVelocity, GetActorRightVector() );
			Dots.Z 	= FVector::DotProduct( SavedVelocity, GetActorUpVector() );

			FVector NewVelocity 	= Dots.X * Target->GetActorForwardVector()
									+ Dots.Y * Target->GetActorRightVector()
									+ Dots.Z * Target->GetActorUpVector();

			AC->GetCharMovementComponent()->Velocity = NewVelocity;
		}
	}

	LastPosition = NewLocation;
}

bool APortal::IsPointCrossingPortal( FVector Point, FVector PortalLocation, FVector PortalNormal )
{
	FVector IntersectionPoint;
	FPlane PortalPlane 	= FPlane( PortalLocation, PortalNormal );
	float PortalDot 	= PortalPlane.PlaneDot( Point );
	bool IsCrossing 	= false;
	bool IsInFront 		= PortalDot >= 0;

	bool IsIntersect 	= FMath::SegmentPlaneIntersection( 	LastPosition,
															Point,
															PortalPlane,
															IntersectionPoint );
	
	if( IsIntersect && !IsInFront && LastInFront )
	{
		IsCrossing 	= true;
	}
	
	//Store values for Next check
	LastInFront 	= IsInFront;
	LastPosition 	= Point;

	return IsCrossing;
}

bool APortal::IsPointInFrontOfPortal( FVector Point, FVector PortalLocation, FVector PortalNormal )
{
	FPlane PortalPlane 	= FPlane( PortalLocation, PortalNormal );
	float PortalDot 	= PortalPlane.PlaneDot( Point );
	return ( PortalDot >= 0 );
}

bool APortal::IsActive()
{
	return bIsActive;
}

void APortal::SetActive( bool NewActive )
{
	bIsActive = NewActive;
}


AActor* APortal::GetTarget()
{
	return Target;
}

void APortal::SetTarget( AActor* NewTarget )
{
	Target = NewTarget;
}

void APortal::ClearRTT_Implementation()
{

}

void APortal::SetRTT_Implementation( UTexture* RenderTexture )
{

}

void APortal::ForceTick_Implementation()
{

}
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


