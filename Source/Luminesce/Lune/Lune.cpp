// Fill out your copyright notice in the Description page of Project Settings.


#include "Lune.h"

#include "Animation/AnimAttributes.h"



// Sets default values
ALune::ALune()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bAbilitiesInitialized = false;

	MainSpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("MainSpringArm"));
	MainSpringArm->SetupAttachment(RootComponent);

	MainCamera = CreateDefaultSubobject<UCameraComponent>(FName("MainCamera"));
	MainCamera->SetupAttachment(MainSpringArm);
	
	HaloSpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("HaloSpringArm"));
	HaloSpringArm->SetupAttachment(MainCamera);

	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	ArmsMesh->SetupAttachment(MainCamera);

	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Legs");
	LegsMesh->SetupAttachment(GetMesh());

	LuneAttributes = CreateDefaultSubobject<ULuneAttributeSet>("LuneAttributes");

	InteractComponent = CreateDefaultSubobject<UInteract>("InteractComponent");
	HaloComponent = CreateDefaultSubobject<UHaloComponent>("HaloComponent");

	//Halo = CreateDefaultSubobject<AHalo>("Halo");
	//Halo->ArmsMesh = ArmsMesh;

	HaloComponent->PlayerCam = MainCamera;
	HaloComponent->HaloSpringArm = HaloSpringArm;

	//AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	//AbilitySystemComponent->SetIsReplicated(true);
	//AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("BaseAttributeSet");
	LuneAttributeSet = CreateDefaultSubobject<ULuneAttributeSet>("LuneAttributeSet");
}

// Called when the game starts or when spawned
void ALune::BeginPlay()
{
	Super::BeginPlay();

	//Halo = GetWorld()->SpawnActor<AHalo>(HaloClass, FVector::ZeroVector, FRotator::ZeroRotator);
	//Halo->AttachToComponent(ArmsMesh,FAttachmentTransformRules::SnapToTargetIncludingScale,"HaloSocket");
	//Halo->PlayerCam = MainCamera;
}

void ALune::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ALune::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

// Called every frame
void ALune::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALune::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	
	// Set up action bindings
	//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	if (UAbilityEnhancedInputComponent* EnhancedInputComponent = Cast<UAbilityEnhancedInputComponent>(PlayerInputComponent))
	{
		checkf(EnhancedInputComponent, TEXT("Ability System Enhanced Input Component is likely not set in project settings"));
		checkf(AbilityInputsDataAsset, TEXT("InputDataAsset INVALID"));

		EnhancedInputComponent->BindAbilityInputs(AbilityInputsDataAsset, this,
			&ALune::OnAbilityInputPressed, &ALune::OnAbilityInputReleased);
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALune::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALune::Look);

		EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Started, this, &ALune::FireStart);
		EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Completed, this, &ALune::FireEnd);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ALune::AimStart);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ALune::AimEnd);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ALune::InteractStart);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ALune::InteractEnd);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ALune::InteractHoldFinished);

		EnhancedInputComponent->BindAction(UpAction, ETriggerEvent::Started, this, &ALune::Up);
		EnhancedInputComponent->BindAction(DownAction, ETriggerEvent::Started, this, &ALune::Down);
	}
	else
	{
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALune::OnAbilityInputPressed(FGameplayTag Tag)
{
	AbilitySystemComponent->AbilityInputPressed(Tag);
}

void ALune::OnAbilityInputReleased(FGameplayTag Tag)
{
	AbilitySystemComponent->AbilityInputReleased(Tag);
}

void ALune::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	/*if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}*/
}

void ALune::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ALune::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALune::FireStart(const FInputActionValue& Value)
{
	// if (UInteract* InteractComponentPtr = InteractComponent.Get())
	// {
	// 	InteractComponentPtr->InteractWith(HaloComponent);
	// }

	//AbilitySystemComponent->TryActivateAbilityByClass(TakeLiteAbility,true);
	//bool testbool = AbilitySystemComponent->TryActivateAbilitiesByTag(TakeLiteTag,true);
	//FFSIwanttoseethevalueplease = testbool;
}

void ALune::FireEnd(const FInputActionValue& Value)
{
}

void ALune::InteractStart(const FInputActionValue& Value)
{
	
}

void ALune::InteractEnd(const FInputActionValue& Value)
{
	
}

void ALune::InteractHoldFinished(const FInputActionValue& Value)
{
	
}

void ALune::AimStart(const FInputActionValue& Value)
{
	if (UHaloComponent* HaloComponentPtr = HaloComponent.Get())
		HaloComponentPtr->StartBeam(MainCamera.Get());
}

void ALune::AimEnd(const FInputActionValue& Value)
{
	if (UHaloComponent* HaloComponentPtr = HaloComponent.Get())
		HaloComponentPtr->EndBeam();
}

void ALune::Up(const FInputActionValue& Value)
{
	if (UHaloComponent* HaloComponentPtr = HaloComponent.Get())
		HaloComponentPtr->LiteIndexUp();
}

void ALune::Down(const FInputActionValue& Value)
{
	if (UHaloComponent* HaloComponentPtr = HaloComponent.Get())
		HaloComponentPtr->LiteIndexDown();
}
