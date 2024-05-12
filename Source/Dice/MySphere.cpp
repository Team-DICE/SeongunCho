
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

    // ����ƽ �޽� ����
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;

    // ����ƽ �޽� ����
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/SM_Cylinder.SM_Cylinder'"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
    }

    // ����ƽ �޽ÿ� ���� �浹 ����
    SphereMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    SphereMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // ����ƽ �޽� ������ ������ ��ġ ���� , x,y, ��ǥ�� 
    float RandomX = FMath::RandRange(-5000.0f, 5000.0f);
    float RandomY = FMath::RandRange(-5000.0f, 5000.0f);

    // ���� ��ġ, ������ ����. �Ǹ����� ������ locatiion z ���ڴ� -100 ����
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

    // ����ƽ �޽��� ũ�� ���� 
    FVector NewScale = GetActorScale3D() - FVector(DeltaTime, DeltaTime, 0);
    if (NewScale.X > 1.0f)
    {
        SetActorScale3D(NewScale);
    }


    //�ڱ��� �ۿ� ��ġ�� ���� �� ó��
    static float ElapsedTime = 0.0f;
    ElapsedTime += DeltaTime;
    // 1�ʰ� ���� ������ health�� ����
    if (ElapsedTime >= 1.0f)
    {
        CheckCharacterPositionAndReduceHealth(DeltaTime);
        ElapsedTime = 0.0f; // Ÿ�̸Ӹ� �ʱ�ȭ
    }
}

// ĳ������ ��ġ Ȯ�� �� health ���� �Լ�

void AMySphere::CheckCharacterPositionAndReduceHealth(float DeltaTime)
{
    for (TActorIterator<ADiceCharacter> It(GetWorld()); It; ++It)
    {
        ADiceCharacter* Character = *It;

        // ����ƽ �޽��� ���� ��ġ
        FVector SphereOrigin = GetActorLocation();

        // ����ƽ �޽��� ���� ������
        float SphereScale = GetActorScale3D().X; 

        // ����ƽ �޽��� �⺻ ũ�� default = 50
        float BaseRadius = 50.0f;

        // ����ƽ �޽��� ���� ������ ���
        float SphereRadius = SphereScale * BaseRadius;

        // ĳ���Ϳ� ����ƽ �޽��� �Ÿ��� ���
        float Distance = FVector::Dist(Character->GetActorLocation(), SphereOrigin);

        // ���� ĳ���Ͱ� �޽��� ������ �ۿ� �ִٸ�, health�� ����
        if (Distance > SphereRadius)
        {
            Character->UpdateHealth(-5.0f); // ex) 5�� ����
        }
    }
}

