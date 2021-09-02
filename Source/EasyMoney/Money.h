//  Copyright © 2015 Sebastián Benítez. All rights reserved.

#pragma once

#include <climits>
#include "Money.generated.h"

/**
 * Implements a basic data type that holds money representation using a 64 bits
 * integer. To hold the decimal part, the entire number is stored as cents.
 */
USTRUCT(BlueprintType)
struct FMoney
{
    GENERATED_USTRUCT_BODY()
public:

    // Constructors

    /**
     * Construct a money value with zero cents.
     */
    FMoney() { Value = 0; }

    /**
     * Constructs a money value with `Credits` cents.
     */
	explicit FMoney(int32 Credits) { Value = Credits * 100; }

    /**
     * Constructs a money value by copying the value from `Other`.
     */
	FMoney(const FMoney& Other) { Value = Other.Value; }


    // Blueprint callable functions.

	void InitWithInt32(int32 Credits) { Value = Credits * 100; }
	void InitWithMillions(int32 Credits) { Value = FMath::Clamp<int64>((int64)Credits * 100 * 1000000, LLONG_MIN, LLONG_MAX); }
	FString ToString() const;
	FString FormatAsNumber() const;

    // Other.

    FORCEINLINE int64 GetValue() const { return Value; }

    // Assignment operators.

    FORCEINLINE FMoney& operator=(const FMoney& Other) {
        Value = Other.Value;
        return *this;
    };

    FORCEINLINE FMoney& operator=(int32 Credits) {
        Value = Credits * 100;
        return *this;
    };

    // Other operators, including conversion.

    FORCEINLINE FMoney& operator+=(const FMoney& Other) {
        Value += Other.Value;
        return *this;
    };

    FORCEINLINE FMoney operator+(const FMoney& Other) const {
        FMoney Result = *this;
        Result.Value += Other.Value;
        return Result;
    };

    FORCEINLINE FMoney& operator-=(const FMoney& Other) {
        Value -= Other.Value;
        return *this;
    };

    FORCEINLINE FMoney operator-(const FMoney& Other) const {
        FMoney Result = *this;
        Result.Value -= Other.Value;
        return Result;
    };

    FORCEINLINE FMoney& operator*=(const FMoney& Other) {
        Value *= Other.Value;
        return *this;
    };

    FORCEINLINE FMoney& operator*=(float Num) {
        Value *= Num;
        return *this;
    };

    FORCEINLINE FMoney operator*(const FMoney& Other) const {
        FMoney Result = *this;
        Result.Value *= Other.Value;
        return Result;
    };

    FORCEINLINE FMoney operator*(float Num) const {
        FMoney Result = *this;
        Result.Value *= Num;
        return Result;
    };

    FORCEINLINE FMoney& operator/=(const FMoney& Other) {
        check(Other.Value != 0);
        Value /= Other.Value;
        return *this;
    };

    FORCEINLINE FMoney operator/(const FMoney& Other) const {
        check(Other.Value != 0);
        FMoney Result = *this;
        Result.Value /= Other.Value;
        return Result;
    };

    FORCEINLINE FMoney operator/(float Num) const {
        check(Num != 0.f);
        FMoney Result = *this;
        Result.Value /= Num;
        return Result;
    };

    FORCEINLINE bool operator==(const FMoney& Other) const {
        return Value == Other.Value;
    };

    FORCEINLINE bool operator!=(const FMoney& Other) const { return !(*this == Other); };

    FORCEINLINE bool operator<(const FMoney& Other) const {
        return Value < Other.Value;
    };

    FORCEINLINE bool operator>(const FMoney& Other) const { return *this < Other; };
    FORCEINLINE bool operator<=(const FMoney& Other) const { return !(*this > Other); };
    FORCEINLINE bool operator>=(const FMoney& Other) const { return !(*this < Other); };

private:
    int64 Value;
};

/**
* Helper class to be used by blueprints.
*/
UCLASS()
class EASYMONEY_API UMoneyHelper : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Money")
    static FMoney& InitWithInt32(UPARAM(Ref) FMoney& Money, int32 Credits);

    UFUNCTION(BlueprintCallable, Category = "Money")
    static FMoney& InitWithMillions(UPARAM(Ref) FMoney& Money, int32 MillionCredits);

    UFUNCTION(BlueprintCallable, Category = "Money")
    static FString ToString(UPARAM(Ref) FMoney& Money);

    UFUNCTION(BlueprintCallable, Category = "Money")
    static FString FormatAsNumber(UPARAM(Ref) FMoney& Money);
};
