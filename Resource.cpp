// 画像リソース管理クラス
// Unityでいうと Resources.Load や
// 事前に画像を読み込んで保持しておくマネージャー的な役割

#include "DxLib.h"
#include "Resource.h"

// 静的メンバ変数（クラス共有の画像ハンドル）
int  Resource::PlayHandle;

int Resource::PlayHandle1;

int Resource::playArea[10];

int Resource::titleHandle = -1;

int Resource::arrowLeft = -1;

int Resource::arrowRight = -1;

int Resource::bgmPlay = -1;

int Resource::tutorialImage[3];

// 画像読み込み関数
void Resource::Load() {

    // 画像ファイルを読み込み、ハンドルを取得
    // LoadGraphは成功すると画像ハンドル（整数）を返す
    // 失敗すると -1 を返す
	titleHandle = LoadGraph("Resource/Image_fx.png");
    arrowLeft = LoadGraph("Resource/名称未設定 2 のコピー.png");
	arrowRight = LoadGraph("Resource/nextButton.png.png");

    playArea[0] = LoadGraph("Resource/Image_fx (2).png");
    playArea[1] = LoadGraph("Resource/Image_fx.png");
    playArea[2] = LoadGraph("Resource/Image_fx (1).png");
    playArea[3] = LoadGraph("Resource/駅のホーム（夜・照明OFF）.jpg");
    playArea[4] = LoadGraph("Resource/何かの施設２（夜・照明ON）.jpg");
    playArea[5] = LoadGraph("Resource/街中のビル（日中）.jpg");
    playArea[6] = LoadGraph("Resource/住宅街の公園（夕方）.jpg");
    playArea[7] = LoadGraph("Resource/駅のコンコース.jpg");
    playArea[8] = LoadGraph("Resource/ショッピングモール２.jpg");
    playArea[9] = LoadGraph("Resource/stage10.png");

	bgmPlay = LoadSoundMem("Resource/maou_game_village07.mp3");

   tutorialImage[0] = LoadGraph("Resource/スクリーンショット 2026-03-13 111136.png");
    tutorialImage[1] = LoadGraph("Resource/スクリーンショット 2026-03-13 112245.png");
    tutorialImage[2] = LoadGraph("Resource/スクリーンショット 2026-03-13 112048.png");

   // PlayHandle = LoadGraph("Resource/Image_fx (2).png");
   // PlayHandle1 = LoadGraph("Resource/Image_fx.png");

    //objNormal = LoadGraph("Resource/Image_fx (2).png");
    //objDiff = LoadGraph("Resource/Image_fx.png");
    // 注意：
    // LoadGraph は失敗すると -1 を返す
    // DrawGraph する前に -1 でないかチェックすると安全
}

