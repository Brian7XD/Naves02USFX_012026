// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MuroBase.h"
#include "MuroBase_Desaparece.generated.h"

UCLASS()
class NAVESUSFX_12026_API AMuroBase_Desaparece : public AMuroBase {
    GENERATED_BODY()
protected:
    virtual void EfectoEspecial(float DeltaTime) override;

    float TiempoAcumulado = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Muro Intermitente")
        float Intervalo = 3.0f; // Segundos entre cambios
};
