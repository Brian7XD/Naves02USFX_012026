// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MuroBase.h"
#include "MuroBase_Divide.generated.h"

UCLASS()
class NAVESUSFX_12026_API AMuroBase_Divide : public AMuroBase {
    GENERATED_BODY()
protected:
    virtual void EfectoEspecial(float DeltaTime) override;

    bool bYaSeDividio = false;
    float Cronometro = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Muro Division")
        TSubclassOf<AMuroBase> ClaseAGenerar; // Clase que se va a spawnear
};
