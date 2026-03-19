// 画像リソース管理クラス
// Unityでいうと Resources.Load や
// 事前に画像を読み込んで保持しておくマネージャー的な役割

#include "DxLib.h"
#include "Resource.h"
#include <tchar.h>
// 静的メンバ変数（クラス共有の画像ハンドル）
int  Resource::PlayHandle;

int Resource::PlayHandle1;

int Resource::playArea[STAGE_MAX][AREA_MAX];

int Resource::titleHandle = -1;

int Resource::arrowLeft = -1;

int Resource::arrowRight = -1;

int Resource::bgmPlay = -1;

int Resource::tutorialImage[3];

// 画像読み込み関数
void Resource::Load() {
    
    titleHandle = LoadGraph(_T("Resource/Image_fx.png"));
    arrowRight = LoadGraph(_T("Resource/nextButton.png"));
    arrowLeft = LoadGraph(_T("Resource/arrowRight.png"));
   // printfDx(_T("Left:%d Right:%d\n", arrowLeft, arrowRight));

    playArea[0][0] = LoadGraph(_T("Resource/Image/Image_fx (2).png"));
    playArea[0][1] = LoadGraph(_T("Resource/Image/Image_fx.png"));
    playArea[0][2] = LoadGraph(_T("Resource/Image/Image_fx (1).png"));

    playArea[1][0] = LoadGraph(_T("Resource/Image/駅のホーム（夜・照明OFF）.jpg"));
    playArea[1][1] = LoadGraph(_T("Resource/Image/何かの施設２（夜・照明ON）.jpg"));
    playArea[1][2] = LoadGraph(_T("Resource/Image/街中のビル（日中）.jpg"));

    playArea[2][0] = LoadGraph(_T("Resource/Image/住宅街の公園（夕方）.jpg"));
    playArea[2][1] = LoadGraph(_T("Resource/Image/駅のコンコース.jpg"));
    playArea[2][2] = LoadGraph(_T("Resource/Image/ショッピングモール２.jpg"));

    bgmPlay = LoadSoundMem(_T("Resource/maou_game_village07.mp3"));

    tutorialImage[0] = LoadGraph(_T("Resource/スクリーンショット 2026-03-13 111136.png"));
    tutorialImage[1] = LoadGraph(_T("Resource/スクリーンショット 2026-03-13 112245.png"));
    tutorialImage[2] = LoadGraph(_T("Resource/スクリーンショット 2026-03-13 112048.png"));
}
