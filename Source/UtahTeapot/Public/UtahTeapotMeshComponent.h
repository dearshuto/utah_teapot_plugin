// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "UtahTeapotMeshComponent.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup=Rendering)
class UTAHTEAPOT_API UUtahTeapotMeshComponent : public UProceduralMeshComponent
{
	GENERATED_UCLASS_BODY()
	
public:
	~UUtahTeapotMeshComponent();

	/** Used when rendering the face mesh (mostly debug reasons) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	class UMaterialInterface* pMaterial;

	/** Used when rendering the face mesh (mostly debug reasons) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material, meta = (ClampMax="255"))
	uint8 Div;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material, meta = (ClampMax="255"))
	uint8 SubDiv;

private:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction* pThisFunction) override;

	virtual class UMaterialInterface* GetMaterial(int32 ElementIndex) const override
	{
		return pMaterial;
	}

	virtual void SetMaterial(int32 ElementIndex, class UMaterialInterface* Material) override
	{
		pMaterial = Material;
	}

	void SetupMesh();

private:
	int32 m_Value;
	void* m_pInstance = nullptr;
};
