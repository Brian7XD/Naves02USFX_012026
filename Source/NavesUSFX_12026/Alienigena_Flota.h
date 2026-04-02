// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "Alienigena.h"
#include "Alienigena_Flota.generated.h"

UCLASS()
class NAVESUSFX_12026_API AAlienigena_Flota : public AAlienigena
{
    GENERATED_BODY()

public:
    AAlienigena_Flota();

protected:
    virtual void Tick(float DeltaTime) override;

private:
    float TiempoOscilacion;
};
