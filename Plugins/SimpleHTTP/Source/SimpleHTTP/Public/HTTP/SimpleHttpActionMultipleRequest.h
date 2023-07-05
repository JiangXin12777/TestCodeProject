// Copyright (C) RenZhai.2020.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "HTTP/Core/SimpleHttpActionRequest.h"

namespace SimpleHTTP
{
	namespace HTTP
	{
		class IHTTPClientRequest;
	}
}

class SIMPLEHTTP_API FSimpleHttpActionMultipleRequest : public FSimpleHttpActionRequest
{
public:
	FSimpleHttpActionMultipleRequest();

	virtual bool Suspend() override;
	virtual bool Cancel() override;

	virtual void GetObjects(const TArray<FString> &URL, const FString &SavePaths) override;
	virtual void GetObjects(const TArray<FString> &URL) override;
	virtual void DeleteObjects(const TArray<FString> &URL) override;
	virtual bool PutObject(const FString &URL, const FString &LocalPaths) override;

protected:
	virtual void HttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully) override;
	virtual void HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived) override;
	virtual void HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue) override;

protected:
	virtual void ExecutionCompleteDelegate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully) override;

private:
	uint32 RequestNumber;
	TArray<TSharedPtr<SimpleHTTP::HTTP::IHTTPClientRequest>> Requests;
};
