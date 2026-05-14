//フェード管理クラスのヘッダーファイル
#pragma once//多重インクルード防止
#include "DxLib.h"

//ここからクラス定義
class FadeManager {
    // 【公開機能：Gameクラスなどから呼び出す】
public:
    void Init();//初期化関数
    void Update();//毎フレーム呼ぶ更新処理
    void Draw();//フェード描画処理

    void StartFadeIn();//フェード開始命令
    void StartFadeOut();//フェード開始命令

    bool IsFading() const;//この関数はメンバ変数を変更しません

private:
    // 【内部データ：クラスの外からは直接触れない】
    
    //フェード状態管理
    enum FadeState {
        NONE,//何もしていない
        FADE_IN,//明るくしている
        FADE_OUT//暗くしている
    };

    //現在のフェード状態を保持。
    FadeState state;

    int alpha;          // 透明度　0〜255
    int fadeSpeed;      // 1フレームあたりの変化量

    
};
