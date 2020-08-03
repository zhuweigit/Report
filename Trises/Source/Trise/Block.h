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

	//���� 
	UPROPERTY()
		class UMaterial* BaseMaterial;
	UPROPERTY()
		class UMaterialInstance* BlueMaterial;
	UPROPERTY()
		class UMaterialInstance* OrangeMaterial;

	//���  
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* BlockRoot;
	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BlockMesh;


	ABlock* Tetrominoes[4];  //����˹���
	uint8 BlockGround[HEIGHT][WIDTH];  //����˹��������

	int Status;    //����˹�����ʱ��״̬

	class ATriseBlockGrid*pTriseBlockGrid;   

	//����ש�����״  ������״
	void SetShape(UWorld *world, TSubclassOf<AActor> BlockClass, int type);
	//���ò���
	void SetMaterial(int32 ElementIndex, UMaterialInterface* Material);
	//���ö���˹�����λ�ã������������ ���м�ֱ�ӻ����ʵ��λ�ò�����λ�ã�
	void  SetPosition(int X, int Y);


	 
};
