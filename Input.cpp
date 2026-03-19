//押しっぱなし防止
//Unityの GetMouseButtonDown 相当
//入力管理

#include "DxLib.h"
#include "Input.h"

// マウス
static int nowMouse;
static int prevMouse;

// キーボード
static char nowKey[256];
static char prevKey[256];

// 毎フレーム更新
void Input::Update()
{
    // --- マウス ---
    prevMouse = nowMouse;
    nowMouse = GetMouseInput();

    // --- キーボード ---
    memcpy(prevKey, nowKey, 256);
    GetHitKeyStateAll(nowKey);
}

// 左クリックが押された瞬間
bool Input::IsMouseTriggered()
{
    return (nowMouse & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT);
}

// マウス座標
void Input::GetMousePosition(int& x, int& y)
{
    GetMousePoint(&x, &y);
}

// ★キー押しっぱなし
bool Input::IsKeyDown(int key)
{
    return nowKey[key];
}

// ★キー押した瞬間
bool Input::IsKeyTriggered(int key)
{
    return nowKey[key] && !prevKey[key];
}