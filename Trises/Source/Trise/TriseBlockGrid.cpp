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
	//����ֵΪ0
	for (int x = 0; x < BG_HEIGHT; x++)    //����ȫ��Ϊ0  BG_HEIGHT:y   BG_WIDTH:x
		for (int y = 0; y < BG_WIDTH; y++)
		{
			backGround[x][y] = 0;
		}
	for (int y = 0; y < BG_WIDTH; y++)    //�ײ��߽�Ϊ1
		backGround[0][y] = 1;
	for (int32 x = 1; x < BG_HEIGHT; x++)  	//����Ϊ1
	{
		backGround[x][0] = 1;
		backGround[x][BG_WIDTH - 1] = 1;
	}
	//�Ѿ����õķ������� ��ʼ��
	for (int x = 0; x < BG_HEIGHT; x++)    //����ȫ��Ϊ0  BG_HEIGHT:y   BG_WIDTH:x
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
	CreateBorder();  //�Ȱѱ߽������
	TetrisType = rand() % 6 + 1;
	SpawnPiece();     //���ɴ󷽿�     �����ó�1 �Ȳ��������
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATriseBlockGrid::OnTimer, 1, true);
}



void ATriseBlockGrid::OnTimer()
{
	//for (int i = 0; i < 4; i++)  //ÿ���ж�4��  //�����ƶ���˵���ж����ƶ������ƶ�
	//�ĸ����״̬��һ�µ�
		switch (pBlock[0]->Status)    //���Ӧ����������ж�
		{
		case 0:       //����
		{
			for (int i = 0; i < 4; i++)  //��ÿ��������������Ϊ1
			{
				SetGridArrayPosition(pBlock[i]->GetActorLocation());    //�ѵ�ǰ����ֵ����������Ϊ1
				SetPlacedGround(pBlock[i]->GetActorLocation(),i);          //ֻ��ͣס��ʱ��ż�¼�ѷ��÷����λ�ã�ָ�룩
			}
			LineClear();                //����ʱ�Ƿ����У������Ҫ����ֱ����������Ͳ�����
			for (int i = 0; i < 4; i++)
				pBlock[i] = nullptr;        //�õ�ǰָ��Ϊnullptr����
				//�������һ����  
			TetrisType = rand() % 6 + 1;
			SpawnPiece();          //��������һ��С����   
			break;
		}
		case 1:       //��ʱ��һ��������   ���������ƶ������ƶ�
		{
			int count = 0;
			FVector TempLocation[4];
			for (int i = 0; i < 4; i++)
			{
				FVector OldLocation = pBlock[i]->GetActorLocation();
				const int XOffset = -1 * BlockSpacing;     //XOfferset �ǵ�ͼ��x������
				const int YOffset = 0 * BlockSpacing;     //YOfferset �ǵ�ͼ��y������
				//����λ��
				const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + OldLocation;
				if (IsCheckMove(BlockLocation))
				{
					count++;
				}
				TempLocation[i] = BlockLocation;
			}
			if (count == 4)  //�����ƶ�
			{
				for (int i = 0; i < 4; i++)
				{
					pBlock[i]->Status = 1;  //״̬�ƶ���
					pBlock[i]->SetActorLocation(TempLocation[i]);
				}
			}
			else  //�����ƶ�
			{
				for (int i = 0; i < 4; i++)
					pBlock[i]->Status = 0;  //״ֹ̬ͣ
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
				// ����ש��
				ATriseBlock* NewBlock = GetWorld()->SpawnActor<ATriseBlock>(ArrayToActalLocation(x, y), FRotator(0, 0, 0));

				if (NewBlock != nullptr)
				{
					NewBlock->OwningGrid = this;
				}
			}

		}
	}



}

void ATriseBlockGrid::SpawnPiece()   //����״���ɶ���˹����
{
	//��̬����ש��
	TSubclassOf<ABlock> TS = LoadClass<ABlock>(NULL, TEXT("/Game/Puzzle/BP_Piece.BP_Piece_c"));
	//��ʼ��Ĭ����״��0����״
	switch (TetrisType)
	{
	case 1:             //һ����
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 5 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(21 * BlockSpacing, 8 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));    //������תλ  21 6
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0)); 
		break;
	}
	case 2:             //����
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 5 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(22 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));    //������תλ  21 6
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		 
		break;
	}
	case 3:             //o��
	{                                                                                            //������ת
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
	case 4:             //s��
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(22 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(22 * BlockSpacing, 8 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));           ////������תλ  21 7
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		break;
	}
	case 5:             //z��
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(22 * BlockSpacing, 5 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(22 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));     ////������תλ  21 6
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		break;
	}
	case 6:             //L��
	{
		const FVector BlockLocation1 = FVector(21 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation2 = FVector(21 * BlockSpacing, 7 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation3 = FVector(22 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		const FVector BlockLocation4 = FVector(23 * BlockSpacing, 6 * BlockSpacing, 0.f) + GetActorLocation();
		pBlock[0] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation1, FRotator(0, 0, 0));       ////������תλ  21 6
		pBlock[1] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation2, FRotator(0, 0, 0));
		pBlock[2] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation3, FRotator(0, 0, 0));
		pBlock[3] = GetWorld()->SpawnActor<ABlock>(TS, BlockLocation4, FRotator(0, 0, 0));
		break;
	}
	}
	for (int i = 0; i < 4; i++)
	{
		pBlock[i]->Status = 1;   //������ʱ״̬Ϊ1 �����ƶ�
	}
	ATriseBlockGrid*pCur = this;

}
bool ATriseBlockGrid::IsCheckMove(const FVector BlockLocation)
{
	//ʵ��λ��ת��ɰ�������λ��
	FVector NewLoaction = ActalToArrayLocation(BlockLocation);
	if (backGround[(int)NewLoaction.X][(int)NewLoaction.Y] == 1)
		return false;
	return true;
}
int ATriseBlockGrid::IsCheckRotateMove(const FVector PreLoc0, const FVector PreLoc1, const FVector PreLoc2, const FVector PreLoc3)
{
	//ʵ��λ��ת��ɰ�������λ��
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

FVector ATriseBlockGrid::CheckOnceDownLocation(const FVector BlockLocation)  //BlockLocation���ײ�λ��
{
	FVector NewLoaction = ActalToArrayLocation(BlockLocation);
	int BlockArrayX = (int)NewLoaction.X;
	int BlockAyyayY = (int)NewLoaction.Y;
	for (int i = BlockArrayX; i > 0; i--)
	{
		if (backGround[i][BlockAyyayY] == 1)
		{
			//SetActorLocation();
			return ArrayToActalLocation(i+1, BlockAyyayY);    //�������Ǹ�λ�ø����Ŷ� ���� ��Ҫ������������
		}
	}
	return BlockLocation;   //���û���赲�ͷ���ԭλ����piece�ж������ԭλ�þ����䵽��
}

//ʵ��λ��ת��������λ��
FVector ATriseBlockGrid::ActalToArrayLocation(const FVector BlockLocation)
{
	FVector ArrayLocation = FVector((BlockLocation - GetActorLocation()).X / BlockSpacing, (BlockLocation - GetActorLocation()).Y / BlockSpacing, (BlockLocation - GetActorLocation()).Z);
	return ArrayLocation;
}

FVector ATriseBlockGrid::ArrayToActalLocation(int x, int y)
{
	const int XOffset = x * BlockSpacing;
	const int YOffset = y * BlockSpacing;
	const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();    //����ǰ��ӵ�λ��

	return BlockLocation;
}


void ATriseBlockGrid::LineClear()
{
	//��ͣס��ʱ����м��
	for (int i = 1; i < BG_HEIGHT - 1; i++)  //x ��   
	{
		int count = 0;   //ÿ�м���
		for (int j = 1; j < BG_WIDTH - 1; j++)
		{
			if (backGround[i][j] != 0)    //��1��0 �ʹ�������������һ�м��
			{
				count++;   //����
			}
		}
		//���оͽ�������
		if(count==10)
		Refresh(i);  //��¼Ҫˢ�µ�λ��  �������٣�����Ľ���λ������
		
     }
	 //����Ҫ���

}

void ATriseBlockGrid::Refresh(int backGroundi)
{
	for (int j = 1; j < BG_WIDTH - 1; j++)   //��ǰ��ɾ��  �������������ֵ��ӦҲҪ�ı�
	{
		PlacedGround[backGroundi][j]->Destroy();
		backGround[backGroundi][j] = 0;
		PlacedGround[backGroundi][j] = nullptr;
	}
	for (int x = backGroundi + 1; x < BG_HEIGHT - 4; x++)   //�����ÿ��ÿ���Ѿ����õķ��鶼����һ��
	{
		for (int y = 1; y < BG_WIDTH - 1; y++)      
		{
			if (PlacedGround[x][y] != nullptr)
			{
				backGround[x][y] = 0;                 //�������������ƶ�
				backGround[x-1][y] = 1;

				FVector BlockLocation= ArrayToActalLocation(x - 1, y);
				PlacedGround[x][y]->SetActorLocation(BlockLocation);                    //ʵ�ʿ������ƶ�:   ��ת����λ��Ȼ��ֱ���ƶ�λ��
				                                                                                 //�ٸ����ѷ��ÿ�������λ��
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
	 
		FVector ArrayLocation = ActalToArrayLocation(BlockLocation);  //�õ�����λ��
		PlacedGround[(int)ArrayLocation.X][(int)ArrayLocation.Y] = pBlock[i];
 
	
}



void ATriseBlockGrid::HandleLeft()   //�ƶ�����˹���� ��һ�����ƶ��ĸ��ӿ飩
{
	FVector Location[4];
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
	     FVector OldLocation = pBlock[i]->GetActorLocation();
	     const int XOffset = 0 * BlockSpacing;     //XOfferset �ǵ�ͼ��x������
	     const int YOffset = -1 * BlockSpacing;     //YOfferset �ǵ�ͼ��y������
	     //����λ��
	     const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + OldLocation;
		 Location[i] = BlockLocation;    //��λ�ü�¼һ��
		 if (IsCheckMove(BlockLocation))
		 {
			 count++;
		 }
	}
	if (count == 4)  //˵�����ĸ��ӿ��λ�ö������ƶ�Ҫ��   ������Ͳ�����
	{
		for (int i = 0; i < 4; i++)
		{
			//�ƶ��������λ��
			pBlock[i]->SetActorLocation(Location[i]);
			pBlock[i]->Status = 1;         //�ƶ���
		}
	}
}

void ATriseBlockGrid::HandleRight()           //���ƶ�
{
	FVector Location[4];
	int count = 0;

	for (int i = 0; i < 4; i++)
	{
		FVector OldLocation = pBlock[i]->GetActorLocation();
		const int XOffset = 0 * BlockSpacing;     //XOfferset �ǵ�ͼ��x������
		const int YOffset = 1 * BlockSpacing;     //YOfferset �ǵ�ͼ��y������
		//����λ��
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + OldLocation;

		Location[i] = BlockLocation;    //��λ�ü�¼һ��
		if (IsCheckMove(BlockLocation))
		{
			count++;
		}	 
	}
	if (count == 4)  //˵�����ĸ��ӿ��λ�ö������ƶ�Ҫ��
	{
		for (int i = 0; i < 4; i++)
		{
			//�ƶ��������λ��
			pBlock[i]->SetActorLocation(Location[i]);
			pBlock[i]->Status = 1;         //�ƶ���
		}
	}

}

void ATriseBlockGrid::HandleDown()   
{
	//��¼һ��Ԥ�����
	int PreDistance[4];
	//��¼һ�·��ص�Ԥ��λ��
	FVector PLocation[4];
	for (int i = 0; i < 4; i++)
	{
		FVector OldLocation = pBlock[i]->GetActorLocation();
		FVector PredictedLocation = CheckOnceDownLocation(OldLocation);
		PLocation[i] = PredictedLocation;
		if (PredictedLocation != OldLocation)  //˵�����赲
		{
			PreDistance[i] = OldLocation.X - PredictedLocation.X;
		}
		else         //˵��û���赲
		{
			PreDistance[i] = OldLocation.X - 1 * BlockSpacing;
		}
	}
	//�����ƶ�����Сֵ
	int Lowest = PreDistance[0];
	for (int i = 1; i < 4; i++)
	{
		if (PreDistance[i] < Lowest)
			Lowest = PreDistance[i];    //ˢ��һ����Сֵ
	}

	//��������벻Ϊʱ���������ƶ��������
	if (Lowest)
	{
		for (int i = 0; i < 4; i++)
		{
			FVector NewLocation = FVector(-Lowest, 0, 0) + pBlock[i]->GetActorLocation();
			pBlock[i]->SetActorLocation(NewLocation);  
			pBlock[i]->Status = 0;         //ͣס
		}
	} 
}
void ATriseBlockGrid::Rotate()
{
	//ֻ��Ҫ��λ�þ����������ñ䶯
	// 
	//  Tage1 ��2��
	//	TageT ��4��
	//	TageO ��1��
	//	TageS ����
	//	TageZ ��4��
	//	TageL ��4��

	switch (TetrisType)
	{
	case 1:             //һ����  �Զ���λ��cur�Ŀ�Ϊ��ת����  
	{                    //�Ȼ�ȡ����λ��Ȼ���ٰ��ڼ������˳����аڷ�
		FVector CorLocation = pBlock[1]->GetActorLocation();
		if (Tage1 % 2 == 0)   //0��
		{
			//���һ���Ƿ��ܹ���ת
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
		if (Tage1 % 2 == 1)   //1��
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
	case 2:             //����
	{
		if (TageT % 4 == 0)   //0��
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
		if (TageT % 4 == 1)   //1��
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
		if (TageT % 4 == 2)   //2��
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
		if (TageT % 4 == 3)   //3��
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
	case 3:             //o��
	{

		break;
	}
	case 4:             //s��
	{
		if (TageS % 4 == 0)   //0��
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
		if (TageS % 4 == 1)   //1��
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
		if (TageS % 4 == 2)   //0��
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
		if (TageS % 4 == 3)   //1��
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
	case 5:             //z��
	{
		if (TageZ % 4 == 0)   //0��
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
		if (TageZ % 4 == 1)   //1��
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
		if (TageZ % 4 == 2)   //0��
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
		if (TageZ % 4 == 3)   //1��
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
	case 6:             //L��
	{
		if (TageL % 4 == 0)   //0��
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
		if (TageL % 4 == 1)   //1��
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
		if (TageL % 4 == 2)   //2��
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
		if (TageL % 4 == 3)   //1��
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
		pBlock[i]->Status = 1;   //������ʱ״̬Ϊ1 �����ƶ�
	}	 
}



#undef LOCTEXT_NAMESPACE

