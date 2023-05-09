#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MenuLevel.generated.h"

/**
 * 
 */
UCLASS()
class U_TO_API AMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void Test();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	TSubclassOf<UClass> WidgetClass;

//private:
	//class UMenuUI* MenuWidget{ nullptr };
};
