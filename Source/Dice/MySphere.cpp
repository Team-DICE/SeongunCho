
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

    // 스태틱 메시 생성
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    RootComponent = SphereMesh;

    // 스태틱 메시 설정
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/SM_Cylinder.SM_Cylinder'"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
    }

    // 스테틱 메시에 대한 충돌 설정
    SphereMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    SphereMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // 스테틱 메시 생성시 랜덤한 위치 설정 , x,y, 좌표만 
    float RandomX = FMath::RandRange(-5000.0f, 5000.0f);
    float RandomY = FMath::RandRange(-5000.0f, 5000.0f);

    // 생성 위치, 스케일 조정. 실린더로 생성시 locatiion z 인자는 -100 고정
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

    // 스태틱 메시의 크기 감소 
    FVector NewScale = GetActorScale3D() - FVector(DeltaTime, DeltaTime, 0);
    if (NewScale.X > 1.0f)
    {
        SetActorScale3D(NewScale);
    }


    //자기장 밖에 위치해 있을 시 처리
    static float ElapsedTime = 0.0f;
    ElapsedTime += DeltaTime;
    // 1초가 지날 때마다 health를 감소
    if (ElapsedTime >= 1.0f)
    {
        CheckCharacterPositionAndReduceHealth(DeltaTime);
        ElapsedTime = 0.0f; // 타이머를 초기화
    }
}

// 캐릭터의 위치 확인 및 health 감소 함수

void AMySphere::CheckCharacterPositionAndReduceHealth(float DeltaTime)
{
    for (TActorIterator<ADiceCharacter> It(GetWorld()); It; ++It)
    {
        ADiceCharacter* Character = *It;

        // 스태틱 메시의 월드 위치
        FVector SphereOrigin = GetActorLocation();

        // 스태틱 메시의 현재 스케일
        float SphereScale = GetActorScale3D().X; 

        // 스태틱 메시의 기본 크기 default = 50
        float BaseRadius = 50.0f;

        // 스태틱 메시의 현재 반지름 계산
        float SphereRadius = SphereScale * BaseRadius;

        // 캐릭터와 스태틱 메시의 거리를 계산
        float Distance = FVector::Dist(Character->GetActorLocation(), SphereOrigin);

        // 만약 캐릭터가 메시의 반지름 밖에 있다면, health를 감소
        if (Distance > SphereRadius)
        {
            Character->UpdateHealth(-5.0f); // ex) 5씩 감소
        }
    }
}

