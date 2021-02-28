// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMeshCube.h"
#include "Engine.h"

// Sets default values
AProceduralMeshCube::AProceduralMeshCube()
{
	ThisScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ThisScene;

	ThisMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	ThisMesh->SetupAttachment(RootComponent);
}

void AProceduralMeshCube::PostActorCreated()
{
	Super::PostActorCreated();
	GenerateMesh();
}

void AProceduralMeshCube::PostLoad()
{
	Super::PostLoad();
	GenerateMesh();
}

void AProceduralMeshCube::GenerateMesh()
{
	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();
	Tangents.Reset();
	UVs.Reset();
	Colors.Reset();

	int32 TriangleIndexCount = 0;
	FVector DefinedShape[8];
	FProcMeshTangent TangentSetup;

	DefinedShape[0] = FVector(CubeRaduis.X, CubeRaduis.Y, CubeRaduis.Z); //Forward TopRight
	DefinedShape[1] = FVector(CubeRaduis.X, CubeRaduis.Y, -CubeRaduis.Z); //Forward ButtomRight
	DefinedShape[2] = FVector(CubeRaduis.X, -CubeRaduis.Y, CubeRaduis.Z); // Forward TopLeft
	DefinedShape[3] = FVector(CubeRaduis.X, -CubeRaduis.Y, -CubeRaduis.Z); // Forward ButtomLeft

	DefinedShape[4] = FVector(-CubeRaduis.X, -CubeRaduis.Y, CubeRaduis.Z); //Forward TopRight
	DefinedShape[5] = FVector(-CubeRaduis.X, -CubeRaduis.Y, -CubeRaduis.Z); //Forward ButtomRight
	DefinedShape[6] = FVector(-CubeRaduis.X, CubeRaduis.Y, CubeRaduis.Z); // Forward TopLeft
	DefinedShape[7] = FVector(-CubeRaduis.X, CubeRaduis.Y, -CubeRaduis.Z); // Forward ButtomLeft

	//front
	TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);
	AddQuadMesh(DefinedShape[0], DefinedShape[1], DefinedShape[2], DefinedShape[3], TriangleIndexCount, TangentSetup);

	//left
	TangentSetup = FProcMeshTangent(1.f, 0.f, 0.f);
	AddQuadMesh(DefinedShape[2], DefinedShape[3], DefinedShape[4], DefinedShape[5], TriangleIndexCount, TangentSetup);

	//back
	TangentSetup = FProcMeshTangent(0.f, -1.f, 0.f);
	AddQuadMesh(DefinedShape[4], DefinedShape[5], DefinedShape[6], DefinedShape[7], TriangleIndexCount, TangentSetup);

	//right
	TangentSetup = FProcMeshTangent(-1.f, 0.f, 0.f);
	AddQuadMesh(DefinedShape[6], DefinedShape[7], DefinedShape[0], DefinedShape[1], TriangleIndexCount, TangentSetup);

	//top
	TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);
	AddQuadMesh(DefinedShape[6], DefinedShape[0], DefinedShape[4], DefinedShape[2], TriangleIndexCount, TangentSetup);

	//buttom
	TangentSetup = FProcMeshTangent(0.f, -1.f, 0.f);
	AddQuadMesh(DefinedShape[1], DefinedShape[7], DefinedShape[3], DefinedShape[5], TriangleIndexCount, TangentSetup);

	ThisMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
}

void AProceduralMeshCube::AddTriangleMesh(FVector TopLeft, FVector ButtomLeft, FVector ButtomRight, int32& TriIndex, FProcMeshTangent Tangent)
{
	int32 Point1 = TriIndex++;
	int32 Point2 = TriIndex++;
	int32 Point3 = TriIndex++;

	Vertices.Add(TopLeft);
	Vertices.Add(ButtomLeft);
	Vertices.Add(ButtomRight);

	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	FVector ThisNorm = FVector::CrossProduct(TopLeft, ButtomRight).GetSafeNormal();
	for (int i = 0; i < 3; i++)
	{
		Normals.Add(ThisNorm);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);
	}

	UVs.Add(FVector2D(0.f, 1.f)); //TopLeft
	UVs.Add(FVector2D(0.f, 0.f)); //ButtomLeft
	UVs.Add(FVector2D(1.f, 0.f)); //ButtomRight
}

void AProceduralMeshCube::AddQuadMesh(FVector TopLeft, FVector ButtomLeft, FVector TopRight, FVector ButtomRight, int32& TriIndex, FProcMeshTangent Tangent)
{
	int32 Point1 = TriIndex++;
	int32 Point2 = TriIndex++;
	int32 Point3 = TriIndex++;
	int32 Point4 = TriIndex++;

	Vertices.Add(TopLeft);
	Vertices.Add(ButtomLeft);
	Vertices.Add(TopRight);
	Vertices.Add(ButtomRight);

	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	Triangles.Add(Point2);
	Triangles.Add(Point4);
	Triangles.Add(Point3);

	FVector ThisNorm = FVector::CrossProduct(TopLeft - ButtomRight, ButtomRight - TopRight).GetSafeNormal();
	for (int i = 0; i < 4; i++)
	{
		Normals.Add(ThisNorm);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);
	}

	UVs.Add(FVector2D(0.f, 1.f)); //TopLeft
	UVs.Add(FVector2D(0.f, 0.f)); //ButtomLeft
	UVs.Add(FVector2D(1.f, 1.f)); //TopRight
	UVs.Add(FVector2D(1.f, 0.f)); //ButtomRight

}


