// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TimerManager.h"         
#include "Interfaces/InteractionInterface.h"
#include "ilkCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInventoryComponent;
class UInputMappingContext;
struct FInputActionValue;
class APlayerHUD;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

USTRUCT()
struct FInteractionData
{
   GENERATED_BODY()
    
   FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
    {
    
   };

   UPROPERTY()
   AActor* CurrentInteractable;

   UPROPERTY()
   float LastInteractionCheckTime;

};

UCLASS(config=Game)
class AilkCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* InteractAction;




	

public:

    //PROPERTIES AND VARIABLES

    //FUNCTIONS



    AilkCharacter();

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;


    /** Returns Mesh1P subobject **/
    USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
    /** Returns FirstPersonCameraComponent subobject **/
    UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


    FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };

    FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; };

    void UpdateInteractionWidget() const;

protected:

    //PROPERTIES AND VARIABLES

    UPROPERTY()
    APlayerHUD* HUD;

    UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
    TScriptInterface<IInteractionInterface> TargetInteractable;

    UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
    UInventoryComponent* PlayerInventory;

    float InteractionCheckFrequency;

    float InteractionCheckDistance;

    FTimerHandle TimerHandle_Interaction;

    FInteractionData InteractionData;

    //FUNCTIONS

    void PerformInteractionCheck();
    void FoundInteractable(AActor* NewInteractable);
    void NoInteractableFound();
    void BeginInteract();
    void EndInteract();
    void Interact();

    virtual void BeginPlay();
    virtual void Tick(float DeltaTime) override;



	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


};

