#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MenuLevel.generated.h"

/**
 *
 */
UCLASS()
class U_TO2_API AMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UClass* WidgetClass{ nullptr };
	class UMenuUI* menuWidget{ nullptr };
};
