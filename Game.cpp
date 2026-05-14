//メイン信仰管理
#include "Game.h"
#include "DXLib.h"
#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "FadeManager.h"
#include "Input.h"

// --- 静的メンバ変数の定義 ---
static TitleScene title;//タイトル
static PlayScene  play;//プレイシーン
static ResultScene result;//リザルト
static FadeManager fade;//フェード

int Game::stage = 1; // ゲーム全体のステージ番号　
// --- 初期化処理 ---
void Game::Init() {
    fade.Init();                  //フェードを初期化
    currentScene = SceneID::TITLE;//最初のシーンをタイトルに設定
	nextScene = currentScene; // シーン遷移のための変数も同じにしておく
	isChangingScene = false;        //最初はシーン遷移していない状態

	title.Init();           //タイトルシーンの初期化
}

// --- 更新処理 ---
void Game::Update() {

    //前フレームのシーンを記録する変数
    static SceneID prevScene = SceneID::TITLE;

    fade.Update();//毎フレームフェード更新

	//シーン切り替えの実行
	if (!fade.IsFading() && isChangingScene)//フェードが終わっていて、シーン遷移中なら
    {
		currentScene = nextScene;           //シーンを切り替える
		fade.StartFadeIn();                 //新しいシーンにフェードインする
		isChangingScene = false;            //シーン遷移完了
    }

    // --- 現在のシーンに応じた個別更新 ---
    switch (currentScene) {

    case SceneID::TITLE:
    {
        //シーンが切り替わった直後の初回のみ初期化
        if (prevScene != SceneID::TITLE)
        {
            title.Init();
        }

        SceneID requestedScene = currentScene;

        title.Update(requestedScene);//タイトル内の処理

		//タイトル側からシーンを変えたいと要求があったら
        if (requestedScene != currentScene && !isChangingScene)
        {
			nextScene = requestedScene; //次の行先を保存
			fade.StartFadeOut();        //フェードアウト開始
			isChangingScene = true;     //シーン遷移中フラグを立てる
        }
    }
    break;
    case SceneID::PLAY:
    {
        if (prevScene != SceneID::PLAY)
        {
            play.Init();
        }

        SceneID requestedScene = currentScene;

        play.Update(requestedScene);

        if (requestedScene != currentScene && !isChangingScene)
        {
            nextScene = requestedScene;
            fade.StartFadeOut();
            isChangingScene = true;
        }
    }
    break;

    case SceneID::RESULT:
    {   
        //　リザルト開始時には、プレイ中のスコアやタイムを引き渡して初期化
        if (prevScene != SceneID::RESULT)
        {
            result.Init(
                play.GetClearTime(),
                play.GetCorrectCount(),
                play.GetClickCount()
            );
        }

        SceneID requestedScene = currentScene;

        result.Update(requestedScene);

        if (requestedScene != currentScene && !isChangingScene)
        {
            nextScene = requestedScene;
            fade.StartFadeOut();
            isChangingScene = true;
        }
    }
    break;
    }
    
	prevScene = currentScene;//今回のシーンを前回のシートとして保存
	Input::Update();        //キー入力の更新
}

// --- 描画処理 ---
void Game::Draw() {
	//  --- 現在のシーンに応じた個別描画 ---
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
