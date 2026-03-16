#pragma once
#include "Scene.h"

class ResultScene
{
private:

    int clearTime;     //クリアタイム
    int correct;       //正解数
    int totalClick;    //クリック数

public:

    void Init(int time, int correctCount, int clickCount);
    void Update(SceneID& scene);
    void Draw();
};