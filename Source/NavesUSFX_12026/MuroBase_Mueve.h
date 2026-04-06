// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "MuroBase.h"
#include "MuroBase_Mueve.generated.h"

UCLASS()
class NAVESUSFX_12026_API AMuroBase_Mueve : public AMuroBase {
    GENERATED_BODY()
protected:
    // Sobrescribimos el método de la clase padre
    virtual void EfectoEspecial(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Muro Movil")
        float Velocidad = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Muro Movil")
        float Amplitud = 300.0f;
};
