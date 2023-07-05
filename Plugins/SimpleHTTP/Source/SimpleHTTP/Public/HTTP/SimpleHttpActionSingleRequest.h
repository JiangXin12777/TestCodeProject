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

class SIMPLEHTTP_API FSimpleHttpActionSingleRequest : public FSimpleHttpActionRequest
{
public:
	FSimpleHttpActionSingleRequest();

	virtual bool Suspend() override;
	virtual bool Cancel() override;

	virtual bool GetObject(const FString& URL) override;
	virtual bool GetObject(const FString& URL, const FString& SavePaths) override;
	virtual bool PutObject(const FString& URL, const TArray<uint8>& Data) override;
	virtual bool PutObject(const FString& URL, const FString& LocalPaths) override;
	virtual bool PutObjectByString(const FString& URL, const FString& InBuff) override;
	virtual bool PutObject(const FString& URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream) override;
	virtual bool DeleteObject(const FString& URL) override;
	virtual bool PostObject(const FString& URL) override;
protected:
	virtual void HttpRequestComplete(FHttpRequestPtr InRequest, FHttpResponsePtr Response, bool bConnectedSuccessfully) override;
	virtual void HttpRequestProgress(FHttpRequestPtr InRequest, int32 BytesSent, int32 BytesReceived) override;
	virtual void HttpRequestHeaderReceived(FHttpRequestPtr InRequest, const FString& HeaderName, const FString& NewHeaderValue) override;

protected:
	virtual void ExecutionCompleteDelegate(FHttpRequestPtr InRequest, FHttpResponsePtr Response, bool bConnectedSuccessfully) override;

protected:
	TSharedPtr<SimpleHTTP::HTTP::IHTTPClientRequest> Request;
};
