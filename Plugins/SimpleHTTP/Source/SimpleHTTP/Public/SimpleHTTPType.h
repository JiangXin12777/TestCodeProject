#pragma once

#include "CoreMinimal.h"
#include "SimpleHTTPType.generated.h"

UCLASS(BlueprintType)
class SIMPLEHTTP_API USimpleHttpContent :public UObject
{
	GENERATED_BODY()

public:
	TArray<uint8> *Content;

	UFUNCTION(BlueprintPure, Category = "SimpleHTTP|HttpContent")
	TArray<uint8> &GetContent();

	UFUNCTION(BlueprintCallable, Category = "SimpleHTTP|HttpContent")
	bool Save(const FString &LocalPath);
};

enum class EHTTPRequestType
{
	SINGLE,
	MULTPLE,
};

UENUM(BlueprintType)
enum class ESimpleHttpStarte :uint8
{
	NotStarted,//ProcessRequest()
	Processing,
	Failed,
	Failed_ConnectionError,
	Succeeded,
};

USTRUCT(BlueprintType)
struct SIMPLEHTTP_API FSimpleHttpBase
{
	GENERATED_USTRUCT_BODY()

	FSimpleHttpBase()
		:ContentLength(INDEX_NONE)
	{}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "SimpleHttpBase|SimpleHttpBase")
	FString URL;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpBase")
	TArray<FString> AllHeaders;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpBase")
	FString ContentType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpBase")
	int32 ContentLength;
};

USTRUCT(BlueprintType)
struct SIMPLEHTTP_API FSimpleHttpRequest :public FSimpleHttpBase
{
	GENERATED_USTRUCT_BODY()

	FSimpleHttpRequest()
		:Super()
		, ElapsedTime(INDEX_NONE)
		, Status(ESimpleHttpStarte::NotStarted)
	{}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpRequest")
	FString Verb;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpRequest")
	float ElapsedTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpRequest")
	ESimpleHttpStarte Status;
};

USTRUCT(BlueprintType)
struct SIMPLEHTTP_API FSimpleHttpResponse :public FSimpleHttpBase
{
	GENERATED_USTRUCT_BODY()

	FSimpleHttpResponse()
		:Super()
		,ResponseCode(INDEX_NONE)
		,Content(NewObject<USimpleHttpContent>())
	{}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpResponse")
	int32 ResponseCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpResponse")
	FString ResponseMessage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHttpBase|SimpleHttpResponse")
	TObjectPtr<USimpleHttpContent> Content;
};

//BP
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FSimpleHttpSingleRequestCompleteDelegate,const FSimpleHttpRequest ,Request,const FSimpleHttpResponse , Response,bool ,bConnectedSuccessfully);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FSimpleHttpSingleRequestProgressDelegate,const FSimpleHttpRequest , Request, int64, BytesSent, int64, BytesReceived);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FSimpleHttpSingleRequestHeaderReceivedDelegate, const FSimpleHttpRequest , Request, const FString , HeaderName, const FString , NewHeaderValue);
DECLARE_DYNAMIC_DELEGATE(FAllRequestCompleteDelegate);

//C++
DECLARE_DELEGATE_ThreeParams(FSimpleSingleCompleteDelegate, const FSimpleHttpRequest &, const FSimpleHttpResponse &, bool);
DECLARE_DELEGATE_ThreeParams(FSimpleSingleRequestProgressDelegate, const FSimpleHttpRequest &, int64, int64);
DECLARE_DELEGATE_ThreeParams(FSimpleSingleRequestHeaderReceivedDelegate, const FSimpleHttpRequest &, const FString &, const FString &);

USTRUCT(BlueprintType)
struct SIMPLEHTTP_API FSimpleHttpBpResponseDelegate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHTTP|HTTPResponseDelegate")
	FSimpleHttpSingleRequestCompleteDelegate			SimpleHttpRequestCompleteDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHTTP|HTTPResponseDelegate")
	FSimpleHttpSingleRequestProgressDelegate			SimpleHttpRequestProgressDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHTTP|HTTPResponseDelegate")
	FSimpleHttpSingleRequestHeaderReceivedDelegate		SimpleHttpRequestHeaderReceivedDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SimpleHTTP|HTTPResponseDelegate")
	FAllRequestCompleteDelegate							AllRequestCompleteDelegate;
};

struct SIMPLEHTTP_API FSimpleHttpResponseDelegate
{
	FSimpleSingleCompleteDelegate						SimpleCompleteDelegate;
	FSimpleSingleRequestProgressDelegate				SimpleSingleRequestProgressDelegate;
	FSimpleSingleRequestHeaderReceivedDelegate			SimpleSingleRequestHeaderReceivedDelegate;
	FSimpleDelegate										AllTasksCompletedDelegate;
};