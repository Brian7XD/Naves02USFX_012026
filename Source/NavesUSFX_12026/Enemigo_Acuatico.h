#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Enemigo_Acuatico.generated.h"

UCLASS()
class NAVESUSFX_12026_API AEnemigo_Acuatico : public AEnemigo
{
	GENERATED_BODY()

public:
	AEnemigo_Acuatico();
	virtual void Tick(float DeltaTime) override;
};
