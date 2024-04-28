// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereSpawner.h"
#include "MySphere.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values
ASphereSpawner::ASphereSpawner()
{
 	// ������
	PrimaryActorTick.bCanEverTick = false;

}


void ASphereSpawner::BeginPlay()
{
	Super::BeginPlay();
    // 10�ʵ� SpawnSphere() ����. Ÿ�̸� ���� ����
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASphereSpawner::SpawnSphere, 10.0f, false);
}

void ASphereSpawner::SpawnSphere()
{
    
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // ���� ��ġ ����, MySphereŬ�������� �������� �����ϱ⿡ �� Ŭ���������� ���� �������� ����.
    FVector SpawnLocation(0.0f, 0.0f, 0.0f); 
    FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

    // MySphere ���� ����
    AMySphere* SpawnedSphere = GetWorld()->SpawnActor<AMySphere>(AMySphere::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

}
