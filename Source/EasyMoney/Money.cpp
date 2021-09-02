//  Copyright © 2015 Sebastián Benítez. All rights reserved.

#include "EasyMoney.h"
#include "Money.h"

FString FMoney::ToString() const
{
	return FString::Printf(TEXT("%d"), FMath::DivideAndRoundDown<int64>(Value, 100));
}

#ifndef _F64d
    #if defined(WIN32)
        #define _F64d L"%I64d"
    #else
        #include <inttypes.h>
        #define _F64d L"%" PRId64
    #endif
#endif

FString FMoney::FormatAsNumber() const
{
	FString Result;
	FString Num = FString::Printf(_F64d, FMath::DivideAndRoundDown<int64>(Value, 100));

	int32 dec = 0;
	for (int32 x = Num.Len() - 1; x > -1; --x)
	{
		Result += Num.Mid(x, 1);

		dec++;
		if (dec == 3 && x > 0)
		{
			Result += TEXT(",");
			dec = 0;
		}
	}

	return Result.Reverse();
}


FMoney& UMoneyHelper::InitWithInt32(FMoney& Money, int32 Credits)
{
    Money.InitWithInt32(Credits);
    return Money;
}

FMoney& UMoneyHelper::InitWithMillions(FMoney& Money, int32 MillionCredits)
{
    Money.InitWithMillions(MillionCredits);
    return Money;
}

FString UMoneyHelper::ToString(FMoney& Money)
{
    return Money.ToString();
}

FString UMoneyHelper::FormatAsNumber(FMoney& Money)
{
    return Money.FormatAsNumber();
}
