// Copyright (C) RenZhai.2020.All Rights Reserved.


#include "SimpleHTTPFunctionLibrary.h"
#include "SimpleHttpManage.h"
#include "HTTP/Core/SimpleHttpActionRequest.h"
#include "HTTP/Core/SimpleHTTPHandle.h"

void USimpleHTTPFunctionLibrary::Pause()
{
	SIMPLE_HTTP.Suspend();
}

void USimpleHTTPFunctionLibrary::Awaken()
{
	SIMPLE_HTTP.Awaken();
}

bool USimpleHTTPFunctionLibrary::Cancel()
{
	return SIMPLE_HTTP.Cancel();;
}

bool USimpleHTTPFunctionLibrary::CancelByHandle(const FName& Handle)
{
	return SIMPLE_HTTP.Cancel((FSimpleHTTPHandle)Handle);
}

FName USimpleHTTPFunctionLibrary::GetHandleByLastExecutionRequest()
{
	return SIMPLE_HTTP.GetHandleByLastExecutionRequest();
}

bool USimpleHTTPFunctionLibrary::PostRequest(const FString &InURL, const FString &InParam, const FSimpleHttpBpResponseDelegate &BPResponseDelegate)
{
	return SIMPLE_HTTP.PostRequest(*InURL,*InParam, BPResponseDelegate);
}

void USimpleHTTPFunctionLibrary::Tick(float DeltaTime)
{
	FSimpleHttpManage::Get()->Tick(DeltaTime);
}

bool USimpleHTTPFunctionLibrary::GetObjectToMemory(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL)
{
	return SIMPLE_HTTP.GetObjectToMemory(BPResponseDelegate, URL);
}

bool USimpleHTTPFunctionLibrary::GetObjectToLocal(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &SavePaths)
{
	return SIMPLE_HTTP.GetObjectToLocal(BPResponseDelegate, URL, SavePaths);
}

bool USimpleHTTPFunctionLibrary::PutObjectFromLocal(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &LocalPaths)
{
	return SIMPLE_HTTP.PutObjectFromLocal(BPResponseDelegate, URL, LocalPaths);
}

bool USimpleHTTPFunctionLibrary::PutObjectFromBuffer(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, const TArray<uint8> &Buffer)
{
	return SIMPLE_HTTP.PutObjectFromBuffer(BPResponseDelegate, URL, Buffer);
}

bool USimpleHTTPFunctionLibrary::PutObjectFromString(const FSimpleHttpBpResponseDelegate& BPResponseDelegate, const FString& URL, const FString& InBuffer)
{
	return SIMPLE_HTTP.PutObjectFromString(BPResponseDelegate, URL, InBuffer);
}

bool USimpleHTTPFunctionLibrary::DeleteObject(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL)
{
	return SIMPLE_HTTP.DeleteObject(BPResponseDelegate, URL);
}

bool USimpleHTTPFunctionLibrary::PutObjectsFromLocal(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &LocalPaths)
{
	return SIMPLE_HTTP.PutObjectsFromLocal(BPResponseDelegate, URL,LocalPaths);
}

void USimpleHTTPFunctionLibrary::GetObjectsToLocal(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL, const FString &SavePaths)
{
	SIMPLE_HTTP.GetObjectsToLocal(BPResponseDelegate, URL, SavePaths);
}

void USimpleHTTPFunctionLibrary::GetObjectsToMemory(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL)
{
	SIMPLE_HTTP.GetObjectsToMemory(BPResponseDelegate, URL);
}

void USimpleHTTPFunctionLibrary::DeleteObjects(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL)
{
	SIMPLE_HTTP.DeleteObjects(BPResponseDelegate, URL);
}
