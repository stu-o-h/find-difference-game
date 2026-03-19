#include "DxLib.h"
#include "ResultScene.h"
#include"Game.h"
#include "Input.h"
void ResultScene::Init(int time, int correctCount, int clickCount)
{
    clearTime = time;
    correct = correctCount;
    totalClick = clickCount;

   // WaitKey();   // ←追加
}

void ResultScene::Update(SceneID& scene)
{
    if (!Input::IsMouseTriggered()) return;
    {
        

        if (Game::stage >= 3)   // ★最終ステージ
        {
            
            scene = SceneID::TITLE;
           
        }
        else
        {
            Game::stage++;      // 次のステージ
            scene = SceneID::PLAY;
            
        }
    }
}

void ResultScene::Draw()
{
    DrawString(800, 200, _T("RESULT"), GetColor(255, 255, 255));

    DrawFormatString(800, 300, GetColor(255, 255, 255),
        _T("Clear Time : %d sec"), clearTime);

    float rate = (float)correct / totalClick * 100.0f;

    DrawFormatString(800, 350, GetColor(255, 255, 255),
       _T( "Accuracy : %.1f %%"), rate);

    DrawFormatString(
        800, 250,
        GetColor(255, 255, 255),
        _T("Stage %d Clear!"), Game::stage);

    DrawString(800, 500, _T("Click to Next"), GetColor(255, 255, 0));
}