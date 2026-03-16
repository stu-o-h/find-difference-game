//Scene遷移は参照渡しで制御
//→ Unityの SceneManager.LoadScene() 的役割
// ゲーム全体管理
#pragma once

// SceneID（TITLE, PLAY, RESULTなど）を使うために必要
#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
//#include "ResultScene.h"   // ★これを追加
#include "FadeManager.h"

// ゲーム全体を管理するクラス
// Unityでいう SceneManager の役割
class Game {
public:

    // 初期化（ゲーム開始時）
    void Init();

    // 毎フレーム更新
    void Update();

    // 毎フレーム描画
    void Draw();

    static int stage; // 現在のステージ番号

private:

    // 現在のシーンを保持
    SceneID currentScene;
	SceneID nextScene; // シーン遷移のための変数

	bool isChangingScene; // シーン遷移中かどうか
    TitleScene title;
    PlayScene play;
   // ResultScene result;  // ★ここに書く
	FadeManager fade;   // フェード管理クラス
};