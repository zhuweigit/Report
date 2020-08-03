// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trise.h"
#include "Block.generated.h"

UCLASS()
class TRISE_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//材质 
	UPROPERTY()
		class UMaterial* BaseMaterial;
	UPROPERTY()
		class UMaterialInstance* BlueMaterial;
	UPROPERTY()
		class UMaterialInstance* OrangeMaterial;

	//组件  
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* BlockRoot;
	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BlockMesh;


	ABlock* Tetrominoes[4];  //俄罗斯大块
	uint8 BlockGround[HEIGHT][WIDTH];  //俄罗斯大块的数组

	int Status;    //俄罗斯方块此时的状态

	class ATriseBlockGrid*pTriseBlockGrid;   

	//设置砖块的形状  七种形状
	void SetShape(UWorld *world, TSubclassOf<AActor> BlockClass, int type);
	//设置材质
	void SetMaterial(int32 ElementIndex, UMaterialInterface* Material);
	//设置俄罗斯方块的位置（输入数组就行 ，中间直接换算成实际位置并设置位置）
	void  SetPosition(int X, int Y);


	 
};
