// Fill out your copyright notice in the Description page of Project Settings.


#include "Client.h"
#include "Interfaces/IPv4/IPv4Address.h"

// Sets default values
AClient::AClient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SocketClient = nullptr;                      //初始化   
}

// Called when the game starts or when spawned
void AClient::BeginPlay()
{
	Super::BeginPlay();
	FString IPStr = TEXT("10.81.18.48");
	int32 port = 3030;
	SocketCreate(IPStr, port);
}

bool AClient::SocketCreate(FString IPStr, int32 port)
{
	FIPv4Address::Parse(IPStr, ip);    //将字符串的IPStr地址转换成整数ip
	
   //创建一个Socket
	SocketClient = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);
	////调试
	//TSharedRef<FInternetAddr> b = addr;
	//bool a = SocketClient->Connect(*addr);
	
	if (SocketClient->Connect(*addr))     //连接自己输入的IP地址
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("Connect Succ!"));
		//用于向屏幕输出调试消息 证明网络连接成功  有可能崩溃（viewport要提前设置）
		UE_LOG(LogTemp, Warning, TEXT("Connect Succ!"));
		return true;
	}
	else      //连接失败
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("Connect failed!"));
		UE_LOG(LogTemp, Warning, TEXT("Connect failed!"));
		return false;
	}
}

// Called every frame
void AClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SocketReceive();
}


void AClient::SocketReceive(bool & bReceive, FString & recvMessage)
{
	recvMessage = "";
	bReceive = false;
	if (!SocketClient)
	{
		return;
	}

	TArray<uint8> ReceiveData;
	uint32 size;
	uint8 element = 0;
	while (SocketClient->HasPendingData(size))
	{
		ReceiveData.Init(element, FMath::Min(size, 65507u));

		int32 read = 0;
		SocketClient->Recv(ReceiveData.GetData(), ReceiveData.Num(), read);

	}

	 if (ReceiveData.Num() <= 0)
       {
              return;
       }
       FString log = "Total Data read! num: " + FString::FromInt(ReceiveData.Num() <= 0);

       GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, log);
       UE_LOG(LogTemp, Warning, TEXT("Recv log:   %s"), *log);

       const FString ReceivedUE4String = StringFromBinaryArray(ReceiveData);

       log = "Server:" + ReceivedUE4String;
       GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, log);
       UE_LOG(LogTemp, Warning, TEXT("*** %s"), *log);

       recvMessage = ReceivedUE4String;

       bReceive = true;



}

void AClient::SocketSend(FString meesage)
{
	TCHAR *seriallizedChar = meesage.GetCharArray().GetData();
	int32 size = FCString::Strlen(seriallizedChar) + 1;
	int32 sent = 0;

	if (SocketClient->Send((uint8*)TCHAR_TO_UTF8(seriallizedChar), size, sent))  //发
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("_____Send Succ!"));
		UE_LOG(LogTemp, Warning, TEXT("_____Send Succ!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("_____Send failed!"));
		UE_LOG(LogTemp, Warning, TEXT("_____Send failed!"));
	}
}

FString AClient::StringFromBinaryArray(TArray<uint8> BinaryArray)
{
	return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray.GetData())));
}

