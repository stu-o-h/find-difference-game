//ゲーム本編を管理するシーン
#include "PlayScene.h"
#include "Resource.h"
#include "Input.h"
#include "DxLib.h"
#include "Object.h"
#include "Game.h"
#include "ResultScene.h"

int PlayScene::GetCorrectCount() const
{
    return correctCount;
}

int PlayScene::GetClickCount() const
{
    return clickCount;
}

// ★オブジェクト同士が近すぎないか判定する関数
bool IsTooClose(AnotherPoint a, AnotherPoint b)
{
    int ax = a.x + a.width / 2;
    int ay = a.y + a.height / 2;

    int bx = b.x + b.width / 2;
    int by = b.y + b.height / 2;

    int dx = ax - bx;
    int dy = ay - by;

    int distance2 = dx * dx + dy * dy;

    int minDist = 150;  // この距離以上離す

    return distance2 < minDist * minDist;
}

// ★オブジェクト同士が重なってないか判定する関数
bool IsOverlap(AnotherPoint a, AnotherPoint b)
{
    if (a.x + a.width < b.x) return false;
    if (b.x + b.width < a.x) return false;
    if (a.y + a.height < b.y) return false;
    if (b.y + b.height < a.y) return false;

    return true; // 重なっている
}

void PlayScene::Init()
{
    correctCount = 0;
    clickCount = 0;

    another.x = 600;
    another.y = 350;
    another.width = 120;
    another.height = 40;
    another.isFound = false;

	currentArea = 0;
	totalAnotherCount = 3;
	remainingCount = totalAnotherCount;
	areaCount = 3;

    for (int i = 0; i < areaCount; i++)
    {
        areaClear[i] = false;   // 最初は全部未クリア
    }

	showClick = false;

    font = CreateFontToHandle(NULL, 30, 3);// フォントサイズ30、太さ3のフォントを作成

	gameTimer = 0;

	showMiss = false;

	missTimer = 0;

    bgmVolume = 0;
    bgmFadeIn = true;
    bgmFadeOut = false;

    PlaySoundMem(Resource::bgmPlay, DX_PLAYTYPE_LOOP);
    ChangeVolumeSoundMem(0, Resource::bgmPlay);

    correctCount = 0;
    clickCount = 0;

    // ★ステージごとの設定
    if (Game::stage == 1)
    {
        totalAnotherCount = 3;
    }
    else if (Game::stage == 2)
    {
        totalAnotherCount = 4;
    }
    else if (Game::stage == 3)
    {
        totalAnotherCount = 5;
    }

    remainingCount = totalAnotherCount;


	CreateObjects();
}

void PlayScene::Update(SceneID& scene)
{
    
    CheckClick();
    gameTimer++;

    if (areaClear[0] && areaClear[1] && areaClear[2])
    {
        StopSoundMem(Resource::bgmPlay);  // ★追加
        scene = SceneID::RESULT;
        bgmFadeOut = true;
    }

    if (missTimer > 0)
    {
        missTimer--;
    }
    else
    {
        showMiss = false;
    }

    // フェードイン
    if (bgmFadeIn)
    {
        bgmVolume += 3;

        if (bgmVolume >= 255)
        {
            bgmVolume = 255;
            bgmFadeIn = false;
        }

        ChangeVolumeSoundMem(bgmVolume, Resource::bgmPlay);
    }
	// フェードアウト
    if (bgmFadeOut)
    {
        bgmVolume -= 3;

        if (bgmVolume <= 0)
        {
            bgmVolume = 0;
            StopSoundMem(Resource::bgmPlay);
            scene = SceneID::RESULT;
        }

        ChangeVolumeSoundMem(bgmVolume, Resource::bgmPlay);
    }
}

void PlayScene::CreateObjects()
{
    int objCount = 6;

    for (int area = 0; area < areaCount; area++)
    {
        for (int i = 0; i < objCount; i++)
        {
            objs[area][i].width = 80;
            objs[area][i].height = 80;

            bool overlap;

            do
            {
                overlap = false;

                objs[area][i].x = GetRand(1000) + 300;
                objs[area][i].y = GetRand(500) + 180;

                for (int j = 0; j < i; j++)
                {
                    if (IsTooClose(objs[area][i], objs[area][j]))
                    {
                        overlap = true;
                        break;
                    }
                }

            } while (overlap);

            objs[area][i].isAnother = false;
            objs[area][i].isFound = false;
        }

        // 正解を3つ
        int count = 0;

        while (count < totalAnotherCount)
        {
            int index = GetRand(objCount - 1);

            if (!objs[area][index].isAnother)
            {
                objs[area][index].isAnother = true;
                count++;
            }
        }
    }
}


void PlayScene::FoundAnother()
{
    remainingCount--;   //見つけたら残りを減らす

    if (remainingCount <= 0)
    {
        areaClear[currentArea] = true;  // ★このエリアをクリア
        clearTime = gameTimer;
    }
}

void PlayScene::CheckClick()
{
    if (!Input::IsMouseTriggered()) return;
    clickCount++;   // ←追加

    int mx, my;
    GetMousePoint(&mx, &my);

    int w, h;
    GetGraphSize(Resource::arrowLeft, &w, &h);

    int rightX = 1700;
    int rightY = 450;

    int leftX = 50;
    int leftY = 450;

    // ===== 右矢印 =====
    if (mx > rightX && mx < rightX + w &&
        my > rightY && my < rightY + h)
    {
        currentArea++;
        if (currentArea >= areaCount) currentArea = 0;
        remainingCount = totalAnotherCount;
        return; // ←ここ重要
    }

    // ===== 左矢印 =====
    if (mx > leftX && mx < leftX + w &&
        my > leftY && my < leftY + h)
    {
        currentArea--;
        if (currentArea < 0) currentArea = areaCount - 1;
        remainingCount = totalAnotherCount;
        return; // ←ここ重要
    }

    bool hitObject = false;

    for (int i = 0; i < OBJ_MAX; i++)
    {
        if (objs[currentArea][i].isFound) continue;

        if (mx > objs[currentArea][i].x && mx < objs[currentArea][i].x + objs[currentArea][i].width &&
            my > objs[currentArea][i].y && my < objs[currentArea][i].y + objs[currentArea][i].height)
        {
            hitObject = true;

            if (objs[currentArea][i].isAnother)
            {
                objs[currentArea][i].isFound = true;
                correctCount++;
                FoundAnother();
            }

            break;
        }
    }

    // ===== ミスクリック =====
    if (!hitObject)
    {
        missX = mx;
        missY = my;
        showMiss = true;
        missTimer = 60;
    }
}


int PlayScene::GetClearTime() const
{
    // クリアタイムはフレーム数を60で割って秒数に変換
    return clearTime / 60;
}


void PlayScene::Draw()
{
    DrawFormatString(1700, 50,
        GetColor(255, 255, 255),
        "残り:%d", remainingCount);

    int sec = gameTimer / 60;
    int min = sec / 60;
    sec = sec % 60;

    DrawFormatString(
        1700, 100,
        GetColor(255, 255, 255),
        "TIME %02d:%02d", min, sec
    );
    /*
    DrawStringToHandle(
        100, 50, 
        "文字が表示されない場合がありますその時は別のエリアに移動してもう一回もどると表示されると思います。",
  GetColor(255, 255, 255), font);
  */
  //  DrawStringToHandle(100, 50, "もうひとつ", GetColor(255, 255, 255), font);

    switch (currentArea)
    {
    case 0:
        DrawGraph(280, 150, Resource::playArea[currentArea], TRUE);
        break;
    case 1:
        DrawGraph(280, 150, Resource::playArea[currentArea], TRUE);
        break;
    case 2:
        DrawGraph(280, 150, Resource::playArea[currentArea], TRUE);
        break;
	case 3:
        DrawGraph(280, 150, Resource::playArea[currentArea], TRUE);
		break;
    }

    // ＞ボタン
   // DrawString(1800, 500, ">", GetColor(255, 255, 255));
    DrawGraph(1700, 450, Resource::arrowRight, TRUE);
    DrawGraph(50, 450, Resource::arrowLeft, TRUE);
    

    int w, h;
    GetGraphSize(Resource::arrowLeft, &w, &h);

    DrawBox(1700, 450, 1700 + w, 450 + h, GetColor(255, 0, 0), FALSE); // 右ボタン
    DrawBox(50, 450, 50 + w, 450 + h, GetColor(0, 255, 0), FALSE);   // 左ボタン
    int mx, my;
    GetMousePoint(&mx, &my);

    DrawFormatString(0, 0, GetColor(255, 255, 255),
        "Mouse:%d %d  Area:%d", mx, my, currentArea);

    if (showClick)
    {
        DrawCircle(clickX, clickY, 20, GetColor(0, 255, 0), FALSE);
    }
    if (showMiss)
    {
        DrawLine(missX - 20, missY - 20, missX + 20, missY + 20, GetColor(255, 0, 0), 3);
        DrawLine(missX + 20, missY - 20, missX - 20, missY + 20, GetColor(255, 0, 0), 3);
    }

    int objColor = 6;
    
    for (int i = 0; i < objColor; i++)
    {
        
        if (objs[currentArea][i].isFound) continue;

        int color = objs[currentArea][i].isAnother ?
            GetColor(0, 255, 0):  // 正解
            GetColor(255, 0, 0);    // ダミー

        DrawBox(
            objs[currentArea][i].x,
            objs[currentArea][i].y,
            objs[currentArea][i].x + objs[currentArea][i].width,
            objs[currentArea][i].y + objs[currentArea][i].height,
            color,
            FALSE
        );
        
        // ★正解オブジェクトなら文字を表示
        if (objs[currentArea][i].isAnother && !objs[currentArea][i].isFound)
        {
            int textW = GetDrawStringWidth("もうひとつ", -1);

            DrawString(
                objs[currentArea][i].x + objs[currentArea][i].width / 2 - textW / 2,
                objs[currentArea][i].y + objs[currentArea][i].height / 2 - 8,
                "もうひとつ",
                GetColor(255, 255, 255)
            );
        }
    }
    for (int i = 0; i < OBJ_MAX; i++)
    {
        if (objs[currentArea][i].isFound)
        {
            int cx = objs[currentArea][i].x + objs[currentArea][i].width / 2;
            int cy = objs[currentArea][i].y + objs[currentArea][i].height / 2;

            DrawCircle(cx, cy, 40, GetColor(0, 255, 0), FALSE);
        }
    }
	if (areaClear[currentArea])// ★ クリアしてるエリアなら「CLEAR!」表示
    {
        DrawString(900, 100, "CLEAR!", GetColor(255, 255, 0));
    }
    
}
// DrawGraph(0, 0, Resource::PlayHandle, TRUE);
