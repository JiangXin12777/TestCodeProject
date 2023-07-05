// Copyright (C) RenZhai.2020.All Rights Reserved.

#include "HTTP/SimpleHttpActionMultipleRequest.h"
#include "Client/HTTPClient.h"
#include "Core/SimpleHttpMacro.h"
#include "HAL/FileManager.h"
#include "SimpleHTTPLog.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Math/UnrealMathUtility.h"

FSimpleHttpActionMultipleRequest::FSimpleHttpActionMultipleRequest()
	:Super()
	,RequestNumber(0)
{

}

bool FSimpleHttpActionMultipleRequest::Suspend()
{
	return false;
}

bool FSimpleHttpActionMultipleRequest::Cancel()
{
	for (auto &Tmp : Requests)
	{
		if (Tmp.IsValid())
		{
			FHTTPClient().Cancel(Tmp.ToSharedRef());
		}
	}

	return true;
}

void FSimpleHttpActionMultipleRequest::GetObjects(const TArray<FString> &URL, const FString &SavePaths)
{
	SetPaths(SavePaths);

	for (const auto &Tmp : URL)
	{
		Requests.Add(MakeShareable(new FGetObjectRequest(Tmp)));
		TSharedPtr<IHTTPClientRequest> Request = Requests.Last();

		REQUEST_BIND_FUN(FSimpleHttpActionMultipleRequest)

		if (FHTTPClient().Execute(Request.ToSharedRef()))
		{
			RequestNumber++;

			UE_LOG(LogSimpleHTTP, Log, TEXT("Multple get objects request number %d by multple request."), RequestNumber);
		}
		else
		{
			UE_LOG(LogSimpleHTTP, Error, TEXT("Multple get objects request execution failed."));
		}

		UE_LOG(LogSimpleHTTP, Log, TEXT("GetObjects RequestNumber = %i"), RequestNumber);
	}
}

void FSimpleHttpActionMultipleRequest::GetObjects(const TArray<FString> &URL)
{
	bSaveDisk = false;

	for (const auto &Tmp : URL)
	{
		Requests.Add(MakeShareable(new FGetObjectRequest(Tmp)));
		TSharedPtr<IHTTPClientRequest> Request = Requests.Last();

		REQUEST_BIND_FUN(FSimpleHttpActionMultipleRequest)

		if (FHTTPClient().Execute(Request.ToSharedRef()))
		{
			RequestNumber++;
			UE_LOG(LogSimpleHTTP, Log, TEXT("Multple get objects request number %d by multple request."), RequestNumber);
		}
		else
		{
			UE_LOG(LogSimpleHTTP, Error, TEXT("Multple get objects request execution failed."));
		}

		UE_LOG(LogSimpleHTTP, Log, TEXT("GetObjects RequestNumber = %i"), RequestNumber);
	}
}

void FSimpleHttpActionMultipleRequest::DeleteObjects(const TArray<FString> &URL)
{
	for (const auto &Tmp : URL)
	{
		Requests.Add(MakeShareable(new FDeleteObjectsRequest(Tmp)));
		TSharedPtr<IHTTPClientRequest> Request = Requests.Last();

		REQUEST_BIND_FUN(FSimpleHttpActionMultipleRequest)

		if (FHTTPClient().Execute(Request.ToSharedRef()))
		{
			RequestNumber++;

			UE_LOG(LogSimpleHTTP, Log, TEXT("Multple delete request number %d by multple request."), RequestNumber);
		}
		else
		{
			UE_LOG(LogSimpleHTTP, Error, TEXT("Fail to delete object."));
		}

		UE_LOG(LogSimpleHTTP, Log, TEXT("DeleteObjects RequestNumber = %i"), RequestNumber);
	}
}

bool FSimpleHttpActionMultipleRequest::PutObject(const FString &URL, const FString &LocalPaths)
{
	if (LocalPaths.Len())
	{
		UE_LOG(LogSimpleHTTP, Log, TEXT("Set path %s."), *LocalPaths);
	}
	
	SetPaths(LocalPaths);

	//Start filtering path
	TArray<FString> AllPaths;
	IFileManager::Get().FindFilesRecursive(AllPaths, *LocalPaths, TEXT("*"), true, false);
	
	if (AllPaths.Num())
	{
		for (auto &Tmp : AllPaths)
		{
			UE_LOG(LogSimpleHTTP, Log, TEXT("The uploaded resources are[%s]."), *Tmp);
		}
	}
	else
	{
		UE_LOG(LogSimpleHTTP, Error, TEXT("The obtained content is empty. Please check whether there are resources under this path%s.[%s]"), *LocalPaths);
		return false;
	}

	for (const auto &Tmp: AllPaths)
	{
		TArray<uint8> ByteData;
		FFileHelper::LoadFileToArray(ByteData, *Tmp);

		FString ObjectName = FPaths::GetCleanFilename(Tmp);

		Requests.Add(MakeShareable(new FPutObjectRequest(URL / ObjectName, ByteData)));
		TSharedPtr<IHTTPClientRequest> Request = Requests.Last();

		REQUEST_BIND_FUN(FSimpleHttpActionMultipleRequest)

		if (FHTTPClient().Execute(Request.ToSharedRef()))
		{
			RequestNumber++;

			UE_LOG(LogSimpleHTTP, Log, TEXT("Multple put object request number %d by multple request."), RequestNumber);
		}
		else
		{
			UE_LOG(LogSimpleHTTP, Error, TEXT("Fail to put object."));
		}

		UE_LOG(LogSimpleHTTP, Log, TEXT("PutObject RequestNumber = %i"), RequestNumber);
	}

	return RequestNumber > 0;
}

void FSimpleHttpActionMultipleRequest::ExecutionCompleteDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	Super::ExecutionCompleteDelegate(Request, Response, bConnectedSuccessfully);

	if (RequestNumber > 0)
	{
		RequestNumber--;
		if (RequestNumber <= 0)
		{
			AllRequestCompleteDelegate.ExecuteIfBound();
			AllTasksCompletedDelegate.ExecuteIfBound();

			bRequestComplete = true;

			UE_LOG(LogSimpleHTTP, Log, TEXT("The task has been completed."));
		}

		UE_LOG(LogSimpleHTTP, Log, TEXT("ExecutionCompleteDelegate RequestNumber = %i"), RequestNumber);
	}
	else
	{
		UE_LOG(LogSimpleHTTP, Error, TEXT("Request quantity error."));
	}
}

void FSimpleHttpActionMultipleRequest::HttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	Super::HttpRequestComplete(Request, Response, bConnectedSuccessfully);
}

void FSimpleHttpActionMultipleRequest::HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
{
	Super::HttpRequestProgress(Request, BytesSent, BytesReceived);
}

void FSimpleHttpActionMultipleRequest::HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue)
{
	Super::HttpRequestHeaderReceived(Request, HeaderName, NewHeaderValue);
}
