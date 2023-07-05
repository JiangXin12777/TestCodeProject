#pragma once

#include "CoreMinimal.h"
#include "Request/RequestInterface.h"

namespace SimpleHTTP
{
	namespace HTTP
	{
		struct FPutObjectRequest : IHTTPClientRequest
		{
			FPutObjectRequest(const FString &URL, const FString& ContentString);
			FPutObjectRequest(const FString &URL, const TArray<uint8>& ContentPayload);
			FPutObjectRequest(const FString &URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream);
		};

		struct FGetObjectRequest : IHTTPClientRequest
		{
			FGetObjectRequest(const FString &URL);
		};

		struct FDeleteObjectsRequest : IHTTPClientRequest
		{
			FDeleteObjectsRequest(const FString &URL);
		};

		struct FPostObjectsRequest : IHTTPClientRequest
		{
			FPostObjectsRequest(const FString &URL);
		};
	}
}