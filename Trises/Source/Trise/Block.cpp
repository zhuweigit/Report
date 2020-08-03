// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "Trise.h"
#include "TriseBlockGrid.h"
#include "TriseBlock.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstance.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Status = 1;    //刚开始的时候为1
	////静态加载 （非蓝图资源）
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;         //形状（七种）
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;           //材质1  白色
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;   //材质2  蓝色
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial; //材质3  黄色
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))//  Game / Puzzle / Meshes / BaseMaterial.BaseMaterial
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	BlockRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Block0"));
	RootComponent = BlockRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0, 0, 0));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());   //材质设置
	BlockMesh->SetupAttachment(BlockRoot);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();


	//俄罗斯方块的二维数组
	for (int x = 0; x < HEIGHT; x++)    //所有全设为0  BG_HEIGHT:y   BG_WIDTH:x
		for (int y = 0; y < WIDTH; y++)
		{
			BlockGround[x][y] = 0;
		}

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::SetShape(UWorld * world, TSubclassOf<AActor> BlockClass, int type)
{
	
}

void ABlock::SetMaterial(int32 ElementIndex, UMaterialInterface * Material)
{
}

void ABlock::SetPosition(int X, int Y)
{
}
 
