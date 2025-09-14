#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldSimSubsystem.generated.h"

class ADirectionalLight;

UCLASS()
class ILK_API UWorldSimSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()

public:
    // 0..24 arasýnda saat (örnek: 8 = sabah 08:00)
    UPROPERTY(BlueprintReadOnly, Category = "WorldSim|Time")
    float GameHours = 8.f;

    // 1.0 => 1 saniye = 1 oyun saati
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldSim|Time", meta = (ClampMin = "0.0"))
    float TimeScale = 0.1f;

    // --- Tickable ---
    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UWorldSimSubsystem, STATGROUP_Tickables); }
    virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }
    virtual bool IsTickable() const override { return true; }

    // BP yardýmcýlarý
    UFUNCTION(BlueprintPure, Category = "WorldSim|Time")
    void GetTimeHM(int32& OutHour, int32& OutMinute) const;

    UFUNCTION(BlueprintCallable, Category = "WorldSim|Time")
    void SetTimeScaleClamped(float NewScale);

    UFUNCTION(BlueprintCallable, Category = "WorldSim|Time")
    void AddGameHours(float DeltaHours);

    // Sahnedeki Directional Light referansý
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldSim|Sun")
    TSoftObjectPtr<ADirectionalLight> SunActor;

    // --- Intensity ayarlarý ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldSim|Sun")
    float MinIntensity = 0.02f; // gece

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldSim|Sun")
    float MaxIntensity = 3.0f;  // gündüz

    // --- Gündüz/gece zamanlarý ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldSim|Sun")
    float DawnStartHour = 7.0f;      // aydýnlanma baþý

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldSim|Sun")
    float DuskStartHour = 20.0f;     // kararma baþý

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WorldSim|Sun", meta = (ClampMin = "0.1", ClampMax = "3.0"))
    float TransitionHours = 4.0f;    // geçiþin yumuþaklýðý

private:
    void AdvanceTime(float DtGameHours);
    void UpdateSun(float GameHoursNow);
    void TryAutoBindSun();
};
