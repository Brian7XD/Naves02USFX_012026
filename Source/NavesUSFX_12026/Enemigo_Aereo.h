#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Enemigo_Aereo.generated.h"

UCLASS()
class NAVESUSFX_12026_API AEnemigo_Aereo : public AEnemigo
{
	GENERATED_BODY()

protected:
	AEnemigo_Aereo(); 
	virtual void ComportamientoParticular(float DeltaTime) override;
};
