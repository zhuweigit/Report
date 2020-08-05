// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Client.generated.h"

UCLASS()
class CHATROOM_API AClient : public AActor
{
	GENERATED_BODY()
		
public:	
	AClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	////每当将角色从关卡里移除时调用
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "MySocket")   //Socket创建
	bool SocketCreate(FString IPStr, int32 port);     
	
	UFUNCTION(BlueprintPure, Category = "MySocket")       //Socket收
	void SocketReceive(bool& bReceive, FString& recvMessage);

	UFUNCTION(BlueprintCallable, Category = "MySocket")   //Socket发
	void SocketSend(FString meesage);

	FString StringFromBinaryArray(TArray<uint8> BinaryArray);  //把二进制数组改成字符串

	FSocket *SocketClient;                                  //客户端Socket指针

	 FIPv4Address ip;                                       //IP地址




};
