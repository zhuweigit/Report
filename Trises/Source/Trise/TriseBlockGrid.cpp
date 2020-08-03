#include "TriseBlockGrid.h"
#include "TriseBlock.h"
#include "Components/TextRenderComponent.h"
#include "Trise.h"
#include "Block.h"
#include "Engine/World.h"


#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATriseBlockGrid::ATriseBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);
	TetrisType = 0;
	Tage1=1;    
	TageT=1;
	TageO=1;
	TageS=1;
	TageZ=1;
	TageL=1;
	//数组值为0
	for (int x = 0; x < BG_HEIGHT; x++)    //所有全设为0  BG_HEIGHT:y   BG_WIDTH:x
		for (int y = 0; y < BG_WIDTH; y++)
		{
			backGround[x][y] = 0;
		}
	for (int y = 0; y < BG_WIDTH; y++)    //底部边界为1
		backGround[0][y] = 1;
	for (int32 x = 1; x < BG_HEIGHT; x++)  	//两边为1
	{
		backGround[x][0] = 1;
		backGround[x][BG_WIDTH - 1] = 1;
	}
	//已经放置的方块数组 初始化
	for (int x = 0; x < BG_HEIGHT; x++)    //所有全设为0  BG_HEIGHT:y   BG_WIDTH:x
		for (int y = 0; y < BG_WIDTH; y++)
		{
			PlacedGround[x][y] = nullptr;
		}
}


void ATriseBlockGrid::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
		GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("MoveLeft", EInputEvent::IE_Pressed, this, &ATriseBlockGrid::HandleLeft);
	if (GetWorld())
		GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("MoveRight", EInputEvent::IE_Pressed, this, &ATriseBlockGrid::HandleRight);
	if (GetWorld())
		GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("MoveDown", EInputEvent::IE_Pressed, this, &ATriseBlockGrid::HandleDown);
	if (GetWorld())
		GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Rotate", EInputEvent::IE_Pressed, this, &ATriseBlockGrid::Rotate);
	CreateBorder();  //先把边界板生成
	TetrisType = rand() % 6 + 1;
	SpawnPiece();     //生成大方块     先设置成1 先不随机产生
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATriseBlockGrid::OnTimer, 1, true);
}



void ATriseBlockGrid::OnTimer()
{
	//for (int i = 0; i < 4; i++)  //每次判断4次  //对于移动来说所有都能移动才能移动
	//四个块的状态是一致的
		switch (pBlock[0]->Status)    //这个应该是整体的判断
		{
		case 0:       //到底
		{
			for (int i = 0; i < 4; i++)  //把每个对象都数组设置为1
			{
				SetGridArrayPosition(pBlock[i]->GetActorLocation());    //把当前下落值的数组设置为1
				SetPlacedGround(pBlock[i]->GetActorLocation(),i);          //只有停住的时候才记录已放置方块的位置（指针）
			}
			LineClear();                //检测此时是否消行，如果需要消就直接消，否则就不操作
			for (int i = 0; i < 4; i++)
				pBlock[i] = nullptr;        //让当前指针为nullptr就行
				//随机生成一个块  
			TetrisType = rand() % 6 + 1;
			SpawnPiece();          //并且生成一个小方块   
			break;
		}
		case 1:       //随时间一格往下移   整体检测能移动才能移动
		{
			int count = 0;
			FVector TempLocation[4];
			for (int i = 0; i < 4; i++)
			{
				FVector OldLocation = pBlock[i]->GetActorLocation();
				const int XOffset = -1 * BlockSpacing;     //XOfferset 是地图上x的坐标
				const int YOffset = 0 * BlockSpacing;     //YOfferset 是地图上y的坐标
				//计算位置
				const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + OldLocation;
				if (IsCheckMove(BlockLocation))
				{
					count++;
				}
				TempLocation[i] = BlockLocation;
			}
			if (count == 4)  //可以移动
			{
				for (int i = 0; i < 4; i++)
				{
					pBlock[i]->Status = 1;  //状态移动中
					pBlock[i]->SetActorLocation(TempLocation[i]);
				}
			}
			else  //不能移动
			{
				for (int i = 0; i < 4; i++)
					pBlock[i]->Status = 0;  //状态停止
			}
			break;
		}
		}
}

void ATriseBlockGrid::CreateBorder()
{
	for (int32 x = 0; x < BG_HEIGHT; x++)
	{
		for (int32 y = 0; y < BG_WIDTH; y++)
		{
			if (backGround[x][y] == 1)
			{
				// 生成砖块
				ATriseBlock* NewBlock = GetWorld()->SpawnActor<ATriseBlock>(ArrayToActalLocation(x, y), FRotator(0, 0, 0));

				if (NewBlock != nullptr)
				{
					NewBlock->OwningGrid = this;
				}
			}

		}
	}



}

void ATriseBlockGrid::SpawnPiece()   //按形状生成俄罗斯方块
{
	//动态生成砖块
	TSubclassOf<ABlock> TS = LoadClass<ABlock>(NULL, TEXT("/Game/Puzzle/BP_Piece.BP_Piece_c"));
	//初始化默认形状是0号形状
	switch (TetrisType)
	{
	case 1:             //一字型
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 5 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(21 * BlockSpacing, 8 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));    //中心旋转位  21 6
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0)); 
		break;
	}
	case 2:             //土型
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 5 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(22 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));    //中心旋转位  21 6
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		 
		break;
	}
	case 3:             //o型
	{                                                                                            //不用旋转
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(22 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(22 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		break;
	}
	case 4:             //s型
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(22 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(22 * BlockSpacing, 8 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));           ////中心旋转位  21 7
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		break;
	}
	case 5:             //z型
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(22 * BlockSpacing, 5 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(22 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));     ////中心旋转位  21 6
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		break;
	}
	case 6:             //L型
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(22 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(23 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));       ////中心旋转位  21 6
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		break;
	}
	}
	for (int i = 0; i < 4; i++)
	{
		pBlock[i]->Status = 1;   //刚生成时状态为1 让它移动
	}
	ATriseBlockGrid*pCur = this;

}
bool ATriseBlockGrid::IsCheckMove(const FVector BlockLocation)
{
	//实际位置转变成板子数组位置
	FVector NewLoaction = ActalToArrayLocation(BlockLocation);
	if (backGround[(int)NewLoaction.X][(int)NewLoaction.Y] == 1)
		return false;
	return true;
}
int ATriseBlockGrid::IsCheckRotateMove(const FVector PreLoc0, const FVector PreLoc1, const FVector PreLoc2, const FVector PreLoc3)
{
	//实际位置转变成板子数组位置
	FVector NewLoaction0 = ActalToArrayLocation(PreLoc0);
	FVector NewLoaction1 = ActalToArrayLocation(PreLoc1);
	FVector NewLoaction2 = ActalToArrayLocation(PreLoc2);
	FVector NewLoaction3 = ActalToArrayLocation(PreLoc3);
	int count = 0;
	if (backGround[(int)NewLoaction0.X][(int)NewLoaction0.Y] == 1)
		count++;
	if (backGround[(int)NewLoaction1.X][(int)NewLoaction1.Y] == 1)
		count++;
	if (backGround[(int)NewLoaction2.X][(int)NewLoaction2.Y] == 1)
		count++;
	if (backGround[(int)NewLoaction3.X][(int)NewLoaction3.Y] == 1)
		count++;
	return count;
}

FVector ATriseBlockGrid::CheckOnceDownLocation(const FVector BlockLocation)  //BlockLocation到底部位置
{
	FVector NewLoaction = ActalToArrayLocation(BlockLocation);
	int BlockArrayX = (int)NewLoaction.X;
	int BlockAyyayY = (int)NewLoaction.Y;
	for (int i = BlockArrayX; i > 0; i--)
	{
		if (backGround[i][BlockAyyayY] == 1)
		{
			//SetActorLocation();
			return ArrayToActalLocation(i+1, BlockAyyayY);    //把上面那个位置给它才对 ！！ 它要放在他的上面
		}
	}
	return BlockLocation;   //如果没有阻挡就返回原位置由piece判断如果是原位置就下落到底
}

//实际位置转换成数组位置
FVector ATriseBlockGrid::ActalToArrayLocation(const FVector BlockLocation)
{
	FVector ArrayLocation = FVector((BlockLocation - GetActorLocation()).X / BlockSpacing, (BlockLocation - GetActorLocation()).Y / BlockSpacing, (BlockLocation - GetActorLocation()).Z);
	return ArrayLocation;
}

FVector ATriseBlockGrid::ArrayToActalLocation(int x, int y)
{
	const int XOffset = x * BlockSpacing;
	const int YOffset = y * BlockSpacing;
	const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();    //这个是板子的位置

	return BlockLocation;
}


void ATriseBlockGrid::LineClear()
{
	//当停住的时候进行检测
	for (int i = 1; i < BG_HEIGHT - 1; i++)  //x 行   
	{
		int count = 0;   //每行计数
		for (int j = 1; j < BG_WIDTH - 1; j++)
		{
			if (backGround[i][j] != 0)    //有1个0 就代表不满，进行上一行检测
			{
				count++;   //计数
			}
		}
		//满行就进行消行
		if(count==10)
		Refresh(i);  //记录要刷新的位置  本行销毁，上面的进行位置下移
		
     }
	 //不需要检测

}

void ATriseBlockGrid::Refresh(int backGroundi)
{
	for (int j = 1; j < BG_WIDTH - 1; j++)   //当前行删除  另外两个数组的值相应也要改变
	{
		PlacedGround[backGroundi][j]->Destroy();
		backGround[backGroundi][j] = 0;
		PlacedGround[backGroundi][j] = nullptr;
	}
	for (int x = backGroundi + 1; x < BG_HEIGHT - 4; x++)   //上面的每层每个已经放置的方块都下移一格
	{
		for (int y = 1; y < BG_WIDTH - 1; y++)      
		{
			if (PlacedGround[x][y] != nullptr)
			{
				backGround[x][y] = 0;                 //板子数组往下移动
				backGround[x-1][y] = 1;

				FVector BlockLocation= ArrayToActalLocation(x - 1, y);
				PlacedGround[x][y]->SetActorLocation(BlockLocation);                    //实际块往下移动:   先转换成位置然后直接移动位置
				                                                                                 //再更新已放置块的数组的位置
				PlacedGround[x - 1][y] = PlacedGround[x][y];
				PlacedGround[x][y] = nullptr;
			}
		}
	}
}

void ATriseBlockGrid::SetGridArrayPosition(FVector BlockLocation)
{
	FVector ArrayLocation=ActalToArrayLocation(BlockLocation);
	backGround[(int)ArrayLocation.X][(int)ArrayLocation.Y]=1;
}

void ATriseBlockGrid::SetPlacedGround(const FVector BlockLocation, int i)
{
	 
		FVector ArrayLocation = ActalToArrayLocation(BlockLocation);  //得到数组位置
		PlacedGround[(int)ArrayLocation.X][(int)ArrayLocation.Y] = pBlock[i];
 
	
}



void ATriseBlockGrid::HandleLeft()   //移动俄罗斯方块 （一下子移动四个子块）
{
	FVector Location[4];
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
	     FVector OldLocation = pBlock[i]->GetActorLocation();
	     const int XOffset = 0 * BlockSpacing;     //XOfferset 是地图上x的坐标
	     const int YOffset = -1 * BlockSpacing;     //YOfferset 是地图上y的坐标
	     //计算位置
	     const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + OldLocation;
		 Location[i] = BlockLocation;    //把位置记录一下
		 if (IsCheckMove(BlockLocation))
		 {
			 count++;
		 }
	}
	if (count == 4)  //说明这四个子块的位置都符合移动要求   不满足就不更新
	{
		for (int i = 0; i < 4; i++)
		{
			//移动到这个新位置
			pBlock[i]->SetActorLocation(Location[i]);
			pBlock[i]->Status = 1;         //移动中
		}
	}
}

void ATriseBlockGrid::HandleRight()           //右移动
{
	FVector Location[4];
	int count = 0;

	for (int i = 0; i < 4; i++)
	{
		FVector OldLocation = pBlock[i]->GetActorLocation();
		const int XOffset = 0 * BlockSpacing;     //XOfferset 是地图上x的坐标
		const int YOffset = 1 * BlockSpacing;     //YOfferset 是地图上y的坐标
		//计算位置
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + OldLocation;

		Location[i] = BlockLocation;    //把位置记录一下
		if (IsCheckMove(BlockLocation))
		{
			count++;
		}	 
	}
	if (count == 4)  //说明这四个子块的位置都符合移动要求
	{
		for (int i = 0; i < 4; i++)
		{
			//移动到这个新位置
			pBlock[i]->SetActorLocation(Location[i]);
			pBlock[i]->Status = 1;         //移动中
		}
	}

}

void ATriseBlockGrid::HandleDown()   
{
	//记录一下预测距离
	int PreDistance[4];
	//记录一下返回的预测位置
	FVector PLocation[4];
	for (int i = 0; i < 4; i++)
	{
		FVector OldLocation = pBlock[i]->GetActorLocation();
		FVector PredictedLocation = CheckOnceDownLocation(OldLocation);
		PLocation[i] = PredictedLocation;
		if (PredictedLocation != OldLocation)  //说明有阻挡
		{
			PreDistance[i] = OldLocation.X - PredictedLocation.X;
		}
		else         //说明没有阻挡
		{
			PreDistance[i] = OldLocation.X - 1 * BlockSpacing;
		}
	}
	//挑出移动的最小值
	int Lowest = PreDistance[0];
	for (int i = 1; i < 4; i++)
	{
		if (PreDistance[i] < Lowest)
			Lowest = PreDistance[i];    //刷新一下最小值
	}

	//当这个距离不为时，所有人移动这个距离
	if (Lowest)
	{
		for (int i = 0; i < 4; i++)
		{
			FVector NewLocation = FVector(-Lowest, 0, 0) + pBlock[i]->GetActorLocation();
			pBlock[i]->SetActorLocation(NewLocation);  
			pBlock[i]->Status = 0;         //停住
		}
	} 
}
void ATriseBlockGrid::Rotate()
{
	//只需要改位置就行其他不用变动
	// 
	//  Tage1 有2种
	//	TageT 有4种
	//	TageO 有1种
	//	TageS 有种
	//	TageZ 有4种
	//	TageL 有4种

	switch (TetrisType)
	{
	case 1:             //一字型  以二个位置cur的块为旋转中心  
	{                    //先获取中心位置然后再按第几个块的顺序进行摆放
		FVector CorLocation = pBlock[1]->GetActorLocation();
		if (Tage1 % 2 == 0)   //0号
		{
			//检测一下是否能够旋转
			FVector PreLoc0 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(0 * BlockSpacing, 2 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}

		}
		if (Tage1 % 2 == 1)   //1号
		{
			FVector PreLoc0 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(-2 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		Tage1++;
		break;
	}
	case 2:             //土型
	{
		if (TageT % 4 == 0)   //0号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageT % 4 == 1)   //1号
		{
			FVector PreLoc0 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageT % 4 == 2)   //2号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageT % 4 == 3)   //3号
		{
			FVector PreLoc0 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		TageT++;
		break;
	}
	case 3:             //o型
	{

		break;
	}
	case 4:             //s型
	{
		if (TageS % 4 == 0)   //0号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(1 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageS % 4 == 1)   //1号
		{
			FVector PreLoc0 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(-1 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageS % 4 == 2)   //0号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(-1 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageS % 4 == 3)   //1号
		{
			FVector PreLoc0 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc2 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			FVector PreLoc3 = FVector(1 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[1]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		TageS++;
		break;
	}
	case 5:             //z型
	{
		if (TageZ % 4 == 0)   //0号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc2 = FVector(1 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc3 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageZ % 4 == 1)   //1号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc1 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc2 = FVector(1 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc3 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageZ % 4 == 2)   //0号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc2 = FVector(-1 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc3 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageZ % 4 == 3)   //1号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc1 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc2 = FVector(-1 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc3 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		TageZ++;
		break;
	}
	case 6:             //L型
	{
		if (TageL % 4 == 0)   //0号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc2 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc3 = FVector(2 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageL % 4 == 1)   //1号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc1 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc2 = FVector(0 * BlockSpacing, 1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc3 = FVector(0 * BlockSpacing, 2 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageL % 4 == 2)   //2号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc1 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc2 = FVector(-1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc3 = FVector(-2 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		if (TageL % 4 == 3)   //1号
		{
			FVector PreLoc0 = FVector(0 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc1 = FVector(1 * BlockSpacing, 0 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc2 = FVector(0 * BlockSpacing, -1 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			FVector PreLoc3 = FVector(0 * BlockSpacing, -2 * BlockSpacing, 0.f) + pBlock[0]->GetActorLocation();
			if (IsCheckRotateMove(PreLoc0, PreLoc1, PreLoc2, PreLoc3) == 0)
			{
				pBlock[0]->SetActorLocation(PreLoc0);
				pBlock[1]->SetActorLocation(PreLoc1);
				pBlock[2]->SetActorLocation(PreLoc2);
				pBlock[3]->SetActorLocation(PreLoc3);
			}
		}
		TageL++;
		break;
	}
	}
	for (int i = 0; i < 4; i++)
	{
		pBlock[i]->Status = 1;   //刚生成时状态为1 让它移动
	}	 
}



#undef LOCTEXT_NAMESPACE

