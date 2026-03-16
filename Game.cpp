#include "Game.h"
#include "DXLib.h"
#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "FadeManager.h"


static TitleScene title;//タイトル
static PlayScene  play;//プレイシーン
static ResultScene result;//リザルト
static FadeManager fade;//フェード

int Game::stage = 1; // ステージ番号の初期化
//フェードを初期化
void Game::Init() {
    fade.Init();                  //フェードを初期化
    currentScene = SceneID::TITLE;//最初のシーンをタイトルに設定
	nextScene = currentScene; // シーン遷移のための変数も同じにしておく
	isChangingScene = false;        //最初はシーン遷移していない状態

    title.Init();
}

//更新処理
void Game::Update() {

    //前フレームのシーンを記録する変数
    static SceneID prevScene = SceneID::TITLE;

    fade.Update();//毎フレームフェード更新

    // フェード完了後にシーン切替
    if (!fade.IsFading() && isChangingScene)
    {
        currentScene = nextScene;
        fade.StartFadeIn();
        isChangingScene = false;
    }

    //現在のシーンごとに処理を分岐
    switch (currentScene) {

    case SceneID::TITLE:
    {
        SceneID requestedScene = currentScene;

        title.Update(requestedScene);

        if (requestedScene != currentScene && !isChangingScene)
        {
            nextScene = requestedScene;
            fade.StartFadeOut();
            isChangingScene = true;
        }
    }
        break;
    case SceneID::PLAY:
        if (prevScene != SceneID::PLAY)

        play.Init();//「今フレームで初めてPLAYになった」なら初期化する。
        
        play.Update(currentScene);
        
        break;
    case SceneID::RESULT:
        if (prevScene != SceneID::RESULT)
        {
            result.Init(
                play.GetClearTime(),
                play.GetCorrectCount(),
                play.GetClickCount()
            );
        }

        result.Update(currentScene);
        break;
    }
    
    prevScene = currentScene;//最後に現在シーンを保存
}

//描画も同様に switch 分岐。
void Game::Draw() {
    switch (currentScene) {
    case SceneID::TITLE:
        title.Draw();
        break;
    case SceneID::PLAY:
        play.Draw();
        break;
    case SceneID::RESULT:
        result.Draw();
        break;
    }
    fade.Draw();//最後に描画することで画面の上に黒がかぶる
}
