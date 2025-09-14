#include "Systems/WorldSimSubsystem.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "EngineUtils.h"                      // TActorRange
#include "Engine/DirectionalLight.h"          // ADirectionalLight
#include "Components/LightComponent.h"        // ULightComponent

void UWorldSimSubsystem::Tick(float DeltaTime)
{
    const float DtGameHours = DeltaTime * TimeScale;
    if (DtGameHours > 0.f)
    {
        AdvanceTime(DtGameHours);
    }

    if (!SunActor.IsValid())
    {
        TryAutoBindSun();
    }

    UpdateSun(GameHours);
}

void UWorldSimSubsystem::AdvanceTime(float DtGameHours)
{
    GameHours += DtGameHours;

    if (GameHours >= 24.f || GameHours < 0.f)
    {
        GameHours = FMath::Fmod(GameHours, 24.f);
        if (GameHours < 0.f) GameHours += 24.f;
    }
}

void UWorldSimSubsystem::GetTimeHM(int32& OutHour, int32& OutMinute) const
{
    const float H = FMath::Clamp(GameHours, 0.f, 24.f - KINDA_SMALL_NUMBER);
    OutHour = static_cast<int32>(H);
    OutMinute = FMath::Clamp(static_cast<int32>((H - OutHour) * 60.f), 0, 59);
}

void UWorldSimSubsystem::SetTimeScaleClamped(float NewScale)
{
    TimeScale = FMath::Max(0.f, NewScale);
}

void UWorldSimSubsystem::AddGameHours(float DeltaHours)
{
    AdvanceTime(DeltaHours);
}

//Güneþ ýþýðýný otomatik baðlama
void UWorldSimSubsystem::TryAutoBindSun()
{
    if (!GetWorld()) return;

    for (ADirectionalLight* DL : TActorRange<ADirectionalLight>(GetWorld()))
    {
        if (IsValid(DL) && DL->ActorHasTag(FName("Sun")))
        {
            SunActor = DL;
            break;
        }
    }
}

void UWorldSimSubsystem::UpdateSun(float GameHoursNow)
{
    ADirectionalLight* Sun = SunActor.Get();
    if (!Sun) return;

    ULightComponent* LC = Sun->GetLightComponent();
    if (!LC) return;

    // --- Gün -> Gece yoðunluk geçiþi ---
    const float DawnIn = FMath::SmoothStep(
        DawnStartHour - TransitionHours, DawnStartHour + TransitionHours, GameHoursNow);
    const float DuskOut = 1.f - FMath::SmoothStep(
        DuskStartHour - TransitionHours, DuskStartHour + TransitionHours, GameHoursNow);

    const float DayAlpha = FMath::Clamp(DawnIn * DuskOut, 0.f, 1.f);

    const float TargetIntensity = FMath::Lerp(MinIntensity, MaxIntensity, DayAlpha);
    LC->SetIntensity(TargetIntensity);
}
