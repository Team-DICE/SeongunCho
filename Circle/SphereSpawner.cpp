// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereSpawner.h"
#include "MySphere.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values
ASphereSpawner::ASphereSpawner()
{
 	// 사용안함
	PrimaryActorTick.bCanEverTick = false;

}


void ASphereSpawner::BeginPlay()
{
	Super::BeginPlay();
    // 10초뒤 SpawnSphere() 실행. 타이머 조정 가능
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASphereSpawner::SpawnSphere, 10.0f, false);
}

void ASphereSpawner::SpawnSphere()
{
    
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // 스폰 위치 설정, MySphere클래서에서 랜덤으로 결정하기에 본 클래스에서는 따로 조정하지 않음.
    FVector SpawnLocation(0.0f, 0.0f, 0.0f); 
    FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

    // MySphere 액터 생성
    AMySphere* SpawnedSphere = GetWorld()->SpawnActor<AMySphere>(AMySphere::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

}
