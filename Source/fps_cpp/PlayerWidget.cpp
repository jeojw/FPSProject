// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "fps_cppCharacter.h"
#include "Kismet/GameplayStatics.h"

void UPlayerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    Player = Cast<Afps_cppCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    // ���� ���� �ʱ�ȭ
    PlayerHealth = Player->GetHealth();  // ���� ��
    CurItem = Player->GetWeaponType();  // EItemTypeEnum�� �ʱⰪ ����
    CurItemSelection = Player->GetCurrentItemSelection();
    CurPistols = Player->GetInventory()->GetCurBullet(CurItemSelection);

    if (HpBar)
    {
        HpBar->SetPercent(1.0f);  // HP �ٸ� 100%�� �ʱ�ȭ
    }

    if (CurPistolCounts)
    {
        CurPistolCounts->SetText(FText::FromString(FString::FromInt(CurPistols)));  // �ʱ� �Ѿ� ���� ����
    }
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (Player)
    {
        CurPistols = Player->GetInventory()->GetCurBullet(CurItemSelection); // �÷��̾��� �Ѿ� ���� ������Ʈ (����)
        PlayerHealth = Player->GetHealth(); // �÷��̾��� ü�� ������Ʈ (����)

        if (CurPistolCounts)
        {
            CurPistolCounts->SetText(FText::FromString(FString::FromInt(CurPistols)));
        }

        if (HpBar)
        {
            HpBar->SetPercent(FMath::Clamp(PlayerHealth / 100.0f, 0.0f, 1.0f));
        }
    }
}