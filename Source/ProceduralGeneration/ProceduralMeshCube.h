// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralMeshCube.generated.h"

UCLASS()
class PROCEDURALGENERATION_API AProceduralMeshCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralMeshCube();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Parameters")
		FVector CubeRaduis = FVector(100.f, 100.f, 100.f);


protected:

	UPROPERTY(VisibleAnywhere)
		USceneComponent* ThisScene;

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* ThisMesh;

	virtual void PostActorCreated() override;
	virtual void PostLoad() override;

	void GenerateMesh();

private:
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;


	void AddTriangleMesh(FVector TopLeft, FVector ButtomLeft, FVector ButtomRight, int32& TriIndex, FProcMeshTangent Tangent);
	void AddQuadMesh(FVector TopLeft, FVector ButtomLeft, FVector TopRight, FVector ButtomRight, int32& TriIndex, FProcMeshTangent Tangent);





};
