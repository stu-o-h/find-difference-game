// リソース管理クラス
// ゲーム全体で使う画像や音などをまとめて管理する
// Unityでいうと Resources や Addressables 的な役割

#pragma once   // 多重インクルード防止（同じヘッダを何回も読み込まない）

class Resource {
public:

    // 画像などをまとめて読み込む関数
    // ゲーム開始時に1回だけ呼ぶ想定
    
  
    static int titleHandle;

    static const int STAGE_MAX = 3;
    static const int AREA_MAX = 3;

    static int playArea[STAGE_MAX][AREA_MAX];   // ★10枚分の画像


    static int PlayHandle;

	static int PlayHandle1;

    static int arrowLeft;   // 左向き（元画像）;    // ＞ボタンの画像ID
    static int arrowRight;  // 右向き（MakeTurnGraphで生成）

	static int bgmPlay;     // BGMのハンドル

    static int seCorrect;
    static int seMiss;

    static int tutorialImage[3];

    static void Load();
    //static void Unload(); // 後始末（任意）

    // 通常オブジェクトの画像ハンドル
    // LoadGraphで取得した値が入る
    //static int objNormal;

    // 「もうひとつ（違い）」の画像ハンドル
    //static int objDiff;
};