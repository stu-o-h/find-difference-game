//タイトルの時に使うシーン
#include "TitleScene.h"
#include "Input.h"
#include "DxLib.h"
#include"Game.h"
#include "Resource.h"
void TitleScene::Init()
{
    fade.Init(); // フェードの初期化
	fade.StartFadeIn(); // タイトル画面が最初にフェードインするようにする

    fontHandle = CreateFontToHandle("Arial", 40, 3);
    fontHandle2 = CreateFontToHandle("Arial", 20, 3);

    //DrawString(0, 200, "INIT CALLED", GetColor(255, 0, 0));

    tutorialPage = 0;
    showTutorial = false;

    if (fontHandle == -1)
    {
        printfDx("fontHandle FAILED\n");
    }
}

void TitleScene::Update(SceneID& scene)
{
  //  if (GetMouseInput() & MOUSE_INPUT_LEFT)
    //{
      //  scene = SceneID::PLAY;
    //}
    if (!Input::IsMouseTriggered()) return;
    if (Input::IsMouseTriggered())
    {
        if (!showTutorial)
        {
            showTutorial = true;
        }
        else
        {
            tutorialPage++;

            if (tutorialPage >= 3)
            {
                scene = SceneID::PLAY;
            }
        }
    }
}

void TitleScene::Draw()
{
    // 背景色
    //DrawBox(0, 0, 1280, 720, GetColor(30, 30, 50), TRUE);

    //int handle = LoadGraph("Image_fx.png");
    /*
    if (handle == -1)
    {
        DrawString(0, 0, "FAILED", GetColor(255, 0, 0));
    }
    else
    {
        DrawGraph(0, 0, handle, TRUE);
    }
    char path[256];
    GetCurrentDirectoryA(256, path);

    DrawString(0, 100, path, GetColor(255, 255, 0));
    */

    // タイトル
  // DrawGraph(150, 150, Resource::titleHandle, TRUE);
    if (!showTutorial)
    {
        DrawGraph(150, 150, Resource::titleHandle, TRUE);

        int width = GetDrawStringWidthToHandle(
            "Click to Start",
            strlen("Click to Start"),
            fontHandle2);

        DrawStringToHandle(380, 260,
            "Find Another One",
            GetColor(255, 255, 255),
            fontHandle);

        DrawStringToHandle(
            640 - width / 2,
            500,
            "Click to Start",
            GetColor(255, 255, 255),
            fontHandle2);
    }
    else
    {
        DrawGraph(0, 0, Resource::tutorialImage[tutorialPage], TRUE);
    }
   //GetDrawStringWidthToHandle("Click to Start", strlen("Click to Start"), fontHandle2);

  // DrawStringToHandle(640 - width / 2, 500, "Click to Start", GetColor(255, 255, 255), fontHandle2);

  // DrawStringToHandle(380, 260, "Find Another One", GetColor(255, 255, 255), fontHandle);

   
   
    fade.Draw();
}
