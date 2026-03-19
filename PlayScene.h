//PlayScene設計（ゲームの心臓）
// 探すパート
#pragma once
#include "Scene.h"  //SceneID を使うため
#include "Object.h" //FindObject 構造体を使うため

#define OBJ_MAX 6
//オブジェクト生成
//クリック判定
//正解管理
//クリア判定
//シーン遷移
class PlayScene
{
public:
    void Init();                //ゲーム開始時の初期化
    void Update(SceneID& scene);//SceneManager.LoadScene()的役割。
    void Draw();                //描画専用。
    
	int GetClearTime() const;    //クリアタイムを取得するゲッター


    int correctCount;   // 正解クリック数
    int clickCount;     // 総クリック数
    int GetCorrectCount() const;
    int GetClickCount() const;

private:
   // static const int OBJ_MAX = 16; // 4x4
    AnotherPoint another;  // ★ 正解エリア
    AnotherPoint objs[10][OBJ_MAX];

    bool areaClear[10] = {}; // 各エリアのクリア状態
    int areaAnotherCount[10];

	int stage;         //ステージ番号
    int totalAnotherCount;          //全問題数
    int remainingCount;             //残り問題数

    bool isClear;                   //クリア状態かどうか
    

	int gameTimer;      // ゲーム全体のフレーム数カウント
    int clearTimer;   // フレーム管理（60fps想定）
    int clearTime;      // クリア時の時間
    
    int currentArea;   // 今表示してるエリア
    int areaCount;     // そのステージのエリア数

    int clickX;
    int clickY;
    bool showClick;

    void CreateObjects();
    void CheckClick();
    void FoundAnother();
    //void CheckAreaChange();

    int font;
    int missX;
    int missY;
    bool showMiss;
	int missTimer;

    int bgmVolume;
    bool bgmFadeIn;
    bool bgmFadeOut;

   

    struct Rect { int x, y, w, h; };
    inline bool InRect(const Rect& r, int mx, int my) {
        return (mx >= r.x && mx < r.x + r.w && my >= r.y && my < r.y + r.h);
    }


    enum PlayState
    {
        STATE_FIND,     // 探す画面
        STATE_DETAIL,   // クリック後の別場面
        STATE_CLEAR     // ステージクリア
    };

    PlayState state;   // ★ 現在の状態
};