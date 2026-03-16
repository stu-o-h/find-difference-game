//押しっぱなし防止
//Unityの GetMouseButtonDown 相当
//入力管理

#include "DxLib.h"
#include "Input.h"

// 前フレームのマウス状態を保持
static int nowMouse;
static int prevMouse; // 現在のマウス状態（初期値は前フレームと同じ）
// 毎フレーム更新（最後に呼ぶのが理想）
void Input::Update() {
    // 現在のマウス状態を保存
	prevMouse = nowMouse; //前フレームの状態を保存
    nowMouse = GetMouseInput();  //現在の入力を取得。
}
// 左クリックが押された瞬間を検出
bool Input::IsMouseTriggered() {

    //(now & MOUSE_INPUT_LEFT)今フレームで左クリックが押されているか？ 
    // !(prevMouse & MOUSE_INPUT_LEFT) 前フレームでは押されていなかったか？
    return (nowMouse & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT);//押された瞬間だけtrue
}
// マウス座標取得
void Input::GetMousePosition(int& x, int& y) {
    GetMousePoint(&x, &y);
}

