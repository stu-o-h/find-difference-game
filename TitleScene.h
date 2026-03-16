// タイトル画面クラス
// ゲーム開始時に表示されるシーンを管理する

#pragma once

#include "Scene.h"
#include "FadeManager.h"

// タイトル画面クラス
class TitleScene {
public:
    // 初期化処理（必要なら追加）
    void Init();

    // 更新処理（毎フレーム呼ばれる）
    void Update(SceneID& scene);

    // 描画処理（毎フレーム呼ばれる）
    void Draw();
private:
	FadeManager fade; // フェード管理クラスのインスタンス
	bool isChanging = false; // シーン遷移中かどうかのフラグ

    int fontHandle;
    int fontHandle2;

    int tutorialPage;
    bool showTutorial;
    int width;
};

