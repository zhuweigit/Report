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

	////ÿ������ɫ�ӹؿ����Ƴ�ʱ����
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "MySocket")   //Socket����
	bool SocketCreate(FString IPStr, int32 port);     
	
	UFUNCTION(BlueprintPure, Category = "MySocket")       //Socket��
	void SocketReceive(bool& bReceive, FString& recvMessage);

	UFUNCTION(BlueprintCallable, Category = "MySocket")   //Socket��
	void SocketSend(FString meesage);

	FString StringFromBinaryArray(TArray<uint8> BinaryArray);  //�Ѷ���������ĳ��ַ���

	FSocket *SocketClient;                                  //�ͻ���Socketָ��

	 FIPv4Address ip;                                       //IP��ַ




};
