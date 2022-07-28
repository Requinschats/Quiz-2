struct JumpFrame {
    float boardRotationAngle;
    float boardHeightIncrement;
};

static JumpFrame jumpFrames[5] = {
        {0,   0},
        {30,  7},
        {0,   7},
        {330, -7},
        {0,   -7}
};

class Jump {
public:
    Jump();

    JumpFrame activeFrame;
    int activeFrameIndex;

    void nextFrame();
};
