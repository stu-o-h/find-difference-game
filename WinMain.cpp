#include "DxLib.h"
#include "Game.h"
#include "Resource.h"
#include "Input.h"

// Windowsアプリのエントリーポイント
// 通常の main() の代わり
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ---------------------------
    // ウィンドウ設定
    // ---------------------------

    
    SetGraphMode(1920, 1080, 32);     // 画面サイズ 1280x720 / 32bitカラー
    ChangeWindowMode(TRUE);          // ウィンドウモードで起動（FALSEならフルスクリーン）
    // ---------------------------
    // DxLib初期化
    // ---------------------------

    if (DxLib_Init() == -1) {        // 初期化失敗なら終了
        return -1;
    }

    // ---------------------------
    // リソース読み込み
    // ---------------------------

    // 画像などを最初にまとめて読み込む
    Resource::Load();

    // ---------------------------
    // ゲーム本体生成
    // ---------------------------

    Game game;   // ゲームクラスのインスタンス作成
    game.Init(); // 初期化（最初のシーン設定など）

    // ---------------------------
    // メインループ
    // ---------------------------

    // ProcessMessage() == 0 の間は実行
    // ウィンドウが閉じられるとループ終了
    while (ProcessMessage() == 0)
    {
        ClearDrawScreen(); // 画面クリア（前フレームの描画を消す）

        // ESCキーで終了
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        game.Update();     // ゲームのロジック更新（シーン制御など）

        game.Draw();       // ゲーム描画

        ScreenFlip();      // バックバッファを表示（画面更新）

        Input::Update();   // 入力情報更新（前フレームとの差分管理）
    }

    // ---------------------------
    // 終了処理
    // ---------------------------

    DxLib_End();   // DxLib終了処理
    return 0;
}
