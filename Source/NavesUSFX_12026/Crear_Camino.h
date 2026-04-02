#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Lista_Template.h" // 🔥 IMPORTANTE
#include "Crear_Camino.generated.h"

UCLASS()
class NAVESUSFX_12026_API ACrear_Camino : public AActor
{
	GENERATED_BODY()

public:
	ACrear_Camino();

protected:
	virtual void BeginPlay() override;

private:

	// 🔹 Lista de bloques
	Lista_Template<AActor*> ListaBloques;

	UStaticMesh* MallaBloque = nullptr;

};
