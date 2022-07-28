struct JumpFrame {
    float boardRotationAngle;
    float boardHeightIncrement;
};

static JumpFrame jumpFrames[5] = {
        {0,   0},
        {60,  10},
        {180, 10},
        {300, -10},
        {360, -10}
};

class Jump {
public:
    Jump();

    JumpFrame activeFrame;
    int activeFrameIndex;

    void nextFrame();
};
