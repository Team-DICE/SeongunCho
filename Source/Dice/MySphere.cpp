// Fill out your copyright notice in the Description page of Project Settings.


#include "MySphere.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine.h"
#include "DiceCharacter.h"

// Sets default values
AMySphere::AMySphere()
{
    // Set this actor to call Tick() every frame.  
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach a static mesh component.
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;

    // Set the static mesh to a sphere.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/SM_Cylinder.SM_Cylinder'"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
    }

    // Setup collision to ignore all but allow pawn to pass through.
    SphereMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    SphereMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    float RandomX = FMath::RandRange(-5000.0f, 5000.0f);
    float RandomY = FMath::RandRange(-5000.0f, 5000.0f);

    SphereMesh->SetRelativeLocation(FVector(RandomX, RandomY, -100.0f));
    SphereMesh->SetWorldScale3D(FVector(100.0f, 100.0f, 100.0f));
  
   

}



// Called when the game starts or when spawned
void AMySphere::BeginPlay()
{
	Super::BeginPlay();
    

}

	

// Called every frame
void AMySphere::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ����ƽ �޽��� ũ�� ���� ����
    FVector NewScale = GetActorScale3D() - FVector(DeltaTime, DeltaTime, 0);
    if (NewScale.X > 1.0f)
    {
        SetActorScale3D(NewScale);
    }

    static float ElapsedTime = 0.0f;
    ElapsedTime += DeltaTime;

    // 1�ʰ� ���� ������ health�� ���ҽ�ŵ�ϴ�.
    if (ElapsedTime >= 1.0f)
    {
        CheckCharacterPositionAndReduceHealth(DeltaTime);
        ElapsedTime = 0.0f; // Ÿ�̸Ӹ� �ʱ�ȭ
    }
}

void AMySphere::CheckCharacterPositionAndReduceHealth(float DeltaTime)
{
    for (TActorIterator<ADiceCharacter> It(GetWorld()); It; ++It)
    {
        ADiceCharacter* Character = *It;

        // ����ƽ �޽��� ���� ��ġ
        FVector SphereOrigin = GetActorLocation();

        // ����ƽ �޽��� ���� ������
        float SphereScale = GetActorScale3D().X; // X, Y, Z �������� ��� ����� �� �ֽ��ϴ�.

        // ����ƽ �޽��� �⺻ ũ�� (����: �⺻ ������ 50)
        float BaseRadius = 50.0f;

        // ����ƽ �޽��� ���� ������ ���
        float SphereRadius = SphereScale * BaseRadius;

        // ĳ���Ϳ� ����ƽ �޽��� �Ÿ��� ���
        float Distance = FVector::Dist(Character->GetActorLocation(), SphereOrigin);

        // ���� ĳ���Ͱ� �޽��� ������ �ۿ� �ִٸ�, health�� ���ҽ�ŵ�ϴ�.
        if (Distance > SphereRadius)
        {
            Character->UpdateHealth(-5.0f); // ��Ȯ�ϰ� 5�� ����
        }
    }
}

