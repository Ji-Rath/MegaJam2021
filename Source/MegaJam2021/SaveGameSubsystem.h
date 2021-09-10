#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/InputChord.h"
#include "GameFramework/PlayerInput.h"
#include "SaveGameSubsystem.generated.h"

class USaveGame;
class USettingsSaveGame;
class UPlayerInput;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionKeyChanged, FInputActionKeyMapping, NewKey);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAxisKeyChanged, FInputAxisKeyMapping, NewKey);

UCLASS()
class MEGAJAM2021_API USaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FInputAxisKeyMapping GetAxisKeyMapping(UPlayerInput* PlayerInput, FName AxisName, float Scale);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FInputActionKeyMapping GetActionKeyMapping(UPlayerInput* PlayerInput, FName ActionName);

	USaveGame* GetGameSave(FString SlotName, UClass* SaveType);

	template < class T >
	T* GetGameSave(FString SlotName)
	{
		UClass* ReturnType = T::StaticClass();
		return Cast<T>(GetGameSave(SlotName, ReturnType));
	}

	UFUNCTION(BlueprintCallable)
	void ResetKeyBindings();

	UFUNCTION(BlueprintCallable)
	void RebindAxisMap(FName AxisName, float Scale, FInputChord NewKey);

	UFUNCTION(BlueprintCallable)
	void RebindActionMap(FName ActionName, FInputChord NewKey);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USettingsSaveGame* SaveSettings;

	UPROPERTY(BlueprintAssignable)
	FActionKeyChanged OnActionKeyChanged;

	UPROPERTY(BlueprintAssignable)
	FAxisKeyChanged OnAxisKeyChanged;

	void Initialize(FSubsystemCollectionBase& Collection) override;

};

