// Fill out your copyright notice in the Description page of Project Settings.


#include "Vida.h"

AVida* AVida::instance = nullptr;

// Sets default values
AVida::AVida()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AVida* AVida::getInstance() {
	if (instance == 0) {
		//instance = new AVida();
	}
	return instance;
}

// Called when the game starts or when spawned
void AVida::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVida::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

