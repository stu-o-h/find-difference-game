#include "DxLib.h"
#include "ResultScene.h"
#include"Game.h"

void ResultScene::Init(int time, int correctCount, int clickCount)
{
    clearTime = time;
    correct = correctCount;
    totalClick = clickCount;
}

void ResultScene::Update(SceneID& scene)
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        Game::stage++;   // ★次のステージ

        if (Game::stage > 3)   // ★最終ステージ
        {
            Game::stage = 1;
            scene = SceneID::TITLE;
        }
        else
        {
            scene = SceneID::PLAY;
        }
    }
}

void ResultScene::Draw()
{
    DrawString(800, 200, "RESULT", GetColor(255, 255, 255));

    DrawFormatString(800, 300, GetColor(255, 255, 255),
        "Clear Time : %d sec", clearTime);

    float rate = (float)correct / totalClick * 100.0f;

    DrawFormatString(800, 350, GetColor(255, 255, 255),
        "Accuracy : %.1f %%", rate);

    DrawFormatString(
        800, 250,
        GetColor(255, 255, 255),
        "Stage %d Clear!", Game::stage);

    DrawString(800, 500, "Press SPACE to Title", GetColor(255, 255, 0));
}