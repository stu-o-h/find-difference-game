// 結果シーンのヘッダーファイル
#pragma once
#include "Scene.h"

class ResultScene
{
private:

    int clearTime;     //クリアタイム
    int correct;       //正解数
    int totalClick;    //クリック数

public:

	// クリアタイム、正解数、クリック数を受け取り、内部変数に保存する
    void Init(int time, int correctCount, int clickCount);

	// シーン遷移の判定（クリックされたら次のシーンへ）
    void Update(SceneID& scene);
    
	// 結果のテキスト表示
    void Draw();
};