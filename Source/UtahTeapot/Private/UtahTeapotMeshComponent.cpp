// Fill out your copyright notice in the Description page of Project Settings.


#include "UtahTeapotMeshComponent.h"
#include <header.h>



UUtahTeapotMeshComponent::UUtahTeapotMeshComponent(const FObjectInitializer& objectInitializer)
    : Super(objectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = TG_PostPhysics;
    
    m_pInstance = create_instance();
}

UUtahTeapotMeshComponent::~UUtahTeapotMeshComponent()
{
    if (m_pInstance != nullptr)
    {
        destroy_instance(m_pInstance);
    }
}

void UUtahTeapotMeshComponent::InitializeComponent()
{
    Super::InitializeComponent();

    PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UUtahTeapotMeshComponent::TickComponent(float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction* pThisFunction)
{
    if (GetNumSections() == 0)
    {
        // 頂点群
        TArray<FVector> vertices;
        // インデックス群
        TArray<int32> indices;
        // 法線群（今回は空っぽのまま）
        TArray<FVector> normals;
        // テクスチャー座標群
        TArray<FVector2D> texcoords0;
        // 頂点カラー群（今回は空っぽのまま）
        TArray<FLinearColor> vertex_colors;
        // 接線群（今回は空っぽのまま）
        TArray<FProcMeshTangent> tangents;

        update(m_pInstance, Div, SubDiv);

        for (auto i = 0; i < get_vertex_count(m_pInstance); ++i)
        {
            const auto actualIndex = i;//get_vertex_count(m_pInstance) - i - 1;
            FVector position;
            get_position(m_pInstance, &position.X, &position.Y, &position.Z, actualIndex);
            vertices.Emplace(position);

            FVector normal;
            get_normal(m_pInstance, &normal.X, &normal.Y, &normal.Z, actualIndex);
            normals.Emplace(normal);
        }

        for (auto i = 0; i < get_index_count(m_pInstance); ++i)
        {
            const auto index = get_index( m_pInstance ,i);
            indices.Emplace(index);
        }
        CreateMeshSection_LinearColor(0, vertices, indices, normals, texcoords0, vertex_colors, tangents, true);
    }
}