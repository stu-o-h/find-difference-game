//Scene遷移は参照渡しで制御
//→ Unityの SceneManager.LoadScene() 的役割
// ゲーム全体管理
#pragma once

// SceneID（TITLE, PLAY, RESULTなど）を使うために必要
#include "Scene.h"          // シーンIDの定義
#include "TitleScene.h"     //タイトルソース
#include "PlayScene.h"      //プレイシーンソース
#include "ResultScene.h"    //リザルトシーンソース
#include "FadeManager.h"    //フェード管理クラスソース

// ゲーム全体を管理するクラス
// Unityでいう SceneManager の役割
class Game {
public:
	// --- 公開メンバ関数 ---

    // 初期化（ゲーム開始時）
    void Init();

    // 毎フレーム更新
    void Update();

    // 毎フレーム描画  プログラムのどこからでも「Game::stage」でアクセス可能
    void Draw();

    static int stage; // 現在のステージ番号

private:
	// --- 非公開メンバ変数 ---

	// --- シーン管理用変数 ---
	SceneID currentScene; //現在のシーン
	SceneID nextScene;    // 次の切り替える予定のシーン
    bool isChangingScene; // 現在フェード中かどうか

	//　--- 各シーンの実態（インスタンス）---
	//　ここにインスタンスを持つことで、シーンを切り替えてもデータが保持される
    TitleScene title;
    PlayScene play;
	ResultScene result;  // リザルトシーンのインスタンス

	// --- フェード管理 ---
	FadeManager fade;   // フェード管理クラス
};