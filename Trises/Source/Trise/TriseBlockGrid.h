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
	uint8 backGround[BG_HEIGHT][BG_WIDTH];      //板子数组
	ABlock* PlacedGround[BG_HEIGHT][BG_HEIGHT]; //已经放置数组的板子
	class ABlock* pBlock[NUM];                  //俄罗斯大块(由4个子块组成）   拥有它
	TArray<ABlock*> BorderBlocks;               // 门的方块
	TArray<ABlock*> PlacedTetrominoes;          //// 已经放置好的的俄罗斯方块
public:
	bool IsCheckMove(const FVector BlockLocation);                                                                   //普通检查 
	int IsCheckRotateMove(const FVector PreLoc0, const FVector PreLoc1, const FVector PreLoc2, const FVector PreLoc3); //旋转检查
	FVector CheckOnceDownLocation(const FVector BlockLocation);                                //全部放下去能到哪
	FVector ActalToArrayLocation(const FVector BlockLocation);                                 //实际位置转换成板子数组
	FVector ArrayToActalLocation(int x, int y);                                                //实际位置转换成板子数组
	void SetPlacedGround(const FVector BlockLocation,int i);                                   //用此时实际位置设置PlacedGround的值（也就是当前防止块的指针
	void LineClear();                                                                            //在方块停住的时候进行检测 满行时消除
	void Refresh(int backGroundi);                                                               //进行刷新 本行销毁，上面的进行位置下移 并且生成块
public:
	FTimerHandle TimerHandle;	                       //定时器句柄
	void OnTimer();                                   //时间响应函数  下落
protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
public:
	void CreateBorder();                   //创建板子 
	void SpawnPiece();                     	//生成大方块
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
	void SetGridArrayPosition(FVector BlockLocation);

	void HandleLeft();      //向左
	void HandleRight();    //向右
	void HandleDown();    //向下到底
	void Rotate();         //旋转
	//变换相关的全局tag
	int32 Tage1;    //一字型
	int32 TageT;    //T字型
	int32 TageO;    //O字型
	int32 TageS;    //S字型
	int32 TageZ;    //Z字型
	int32 TageL;    //L字型
 
};
