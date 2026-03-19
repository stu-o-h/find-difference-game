//入力管理 Input.GetMouseButtonDown()の代わり
#pragma once

// 入力管理クラス
// ゲーム全体で共通して使用する
class Input {
public:

    // 毎フレーム呼ぶ（前フレーム状態更新）
    static void Update();

    // 左クリックが押された瞬間を取得
    static bool IsMouseTriggered();
   
    // マウス座標取得
    static void GetMousePosition(int& x, int& y);

	static bool IsKeyDown(int key);       // ★キーが押されているか
	static bool IsKeyTriggered(int key);   // ★キーが押された瞬間か
};
