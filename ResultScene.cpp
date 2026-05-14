//リザルトシーン
#include "DxLib.h"
#include "ResultScene.h"
#include"Game.h"
#include "Input.h"

//　---初期化処理:プレイシーンからのデータを受け取る---
void ResultScene::Init(int time, int correctCount, int clickCount)
{
    clearTime = time;       //クリアにかかった時間
    correct = correctCount; //正解クリック数
	totalClick = clickCount;//総クリック数

   // WaitKey();
}

//　--- 更新処理:入力によるシーン遷移の判定 ---
void ResultScene::Update(SceneID& scene)
{
	// --- クリックされた時の処理 ---
    if (!Input::IsMouseTriggered()) return;
    {
        

		if (Game::stage >= 3)   // すべてのステージをクリアしていたら
        {
            //全クリだからタイトルに戻る
            scene = SceneID::TITLE;
           
        }
        else
        {
			//まだ続きがあるなら次のステージへ
            Game::stage++;
            scene = SceneID::PLAY;
            
        }
    }
}

//　--- 描画処理:結果のテキスト表示 ---
void ResultScene::Draw()
{
    //タイトルの表示
    DrawString(800, 200, _T("RESULT"), GetColor(255, 255, 255));

	//クリアタイムの表示
    DrawFormatString(800, 300, GetColor(255, 255, 255),
        _T("Clear Time : %d sec"), clearTime);

	//正解率の表示
    float rate = (float)correct / totalClick * 100.0f;

	// 小数点以下1桁まで表示
    DrawFormatString(800, 350, GetColor(255, 255, 255),
       _T( "Accuracy : %.1f %%"), rate);

    //ステージ数の表示
    DrawFormatString(
        800, 250,
        GetColor(255, 255, 255),
        _T("Stage %d Clear!"), Game::stage);

	// 次へ進むための案内表示
    DrawString(800, 500, _T("Click to Next"), GetColor(255, 255, 0));
}