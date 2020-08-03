// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trise.h"
#include "Block.h"
#include "Math/Vector2D.h"
#include "TriseBlockGrid.generated.h"



UCLASS()
class TRISE_API ATriseBlockGrid : public APawn
{
	GENERATED_BODY()
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

public:
	ATriseBlockGrid();
 	int32 Score;
	int32 TetrisType;
	uint8 backGround[BG_HEIGHT][BG_WIDTH];      //��������
	ABlock* PlacedGround[BG_HEIGHT][BG_HEIGHT]; //�Ѿ���������İ���
	class ABlock* pBlock[NUM];                  //����˹���(��4���ӿ���ɣ�   ӵ����
	TArray<ABlock*> BorderBlocks;               // �ŵķ���
	TArray<ABlock*> PlacedTetrominoes;          //// �Ѿ����úõĵĶ���˹����
public:
	bool IsCheckMove(const FVector BlockLocation);                                                                   //��ͨ��� 
	int IsCheckRotateMove(const FVector PreLoc0, const FVector PreLoc1, const FVector PreLoc2, const FVector PreLoc3); //��ת���
	FVector CheckOnceDownLocation(const FVector BlockLocation);                                //ȫ������ȥ�ܵ���
	FVector ActalToArrayLocation(const FVector BlockLocation);                                 //ʵ��λ��ת���ɰ�������
	FVector ArrayToActalLocation(int x, int y);                                                //ʵ��λ��ת���ɰ�������
	void SetPlacedGround(const FVector BlockLocation,int i);                                   //�ô�ʱʵ��λ������PlacedGround��ֵ��Ҳ���ǵ�ǰ��ֹ���ָ��
	void LineClear();                                                                            //�ڷ���ͣס��ʱ����м�� ����ʱ����
	void Refresh(int backGroundi);                                                               //����ˢ�� �������٣�����Ľ���λ������ �������ɿ�
public:
	FTimerHandle TimerHandle;	                       //��ʱ�����
	void OnTimer();                                   //ʱ����Ӧ����  ����
protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
public:
	void CreateBorder();                   //�������� 
	void SpawnPiece();                     	//���ɴ󷽿�
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
	void SetGridArrayPosition(FVector BlockLocation);

	void HandleLeft();      //����
	void HandleRight();    //����
	void HandleDown();    //���µ���
	void Rotate();         //��ת
	//�任��ص�ȫ��tag
	int32 Tage1;    //һ����
	int32 TageT;    //T����
	int32 TageO;    //O����
	int32 TageS;    //S����
	int32 TageZ;    //Z����
	int32 TageL;    //L����
 
};
