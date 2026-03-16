#include "FadeManager.h"
#include "DxLib.h"

/*StartFadeOut() 呼ぶ
    ↓
Update() で alpha 増える
    ↓
Draw() で黒が重なる
    ↓
alpha=255 で終了
*/

// 初期化
void FadeManager::Init()
{
    state = NONE;      // フェードしていない状態
    alpha = 0;         // 完全透明（画面が見える）
    fadeSpeed = 16;     // フェード速度（0.5秒想定）
}

// フェードアウト開始（暗くする）
void FadeManager::StartFadeOut()
{
    state = FADE_OUT;
}

// フェードイン開始（明るくする）
void FadeManager::StartFadeIn()
{
    state = FADE_IN;
}



// 毎フレーム更新
void FadeManager::Update()
{
    if (state == FADE_OUT)
    {
        // 徐々に黒くする
        alpha += fadeSpeed;

        // 最大値で止める
        if (alpha >= 255)
        {
            alpha = 255;
            state = NONE;  // フェード終了
        }
    }
    else if (state == FADE_IN)
    {
        // 徐々に透明にする
        alpha -= fadeSpeed;

        // 最小値で止める
        if (alpha <= 0)
        {
            alpha = 0;
            state = NONE;  // フェード終了
        }
    }
}

// 描画
void FadeManager::Draw()
{
    // 完全透明なら描画しない
    if (alpha <= 0) return;

    // アルファブレンド描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

    // 画面全体を黒で覆う
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);

    // ブレンドモードを戻す（重要）
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// フェード中かどうか
bool FadeManager::IsFading() const
{
    return state != NONE;
}