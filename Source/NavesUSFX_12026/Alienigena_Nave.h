// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Alienigena.h"
#include "Alienigena_Nave.generated.h"

UCLASS()
class NAVESUSFX_12026_API AAlienigena_Nave : public AAlienigena
{
    GENERATED_BODY()

public:
    AAlienigena_Nave();

protected:
    virtual void Tick(float DeltaTime) override;

private:
    float TiempoOscilacion;
};