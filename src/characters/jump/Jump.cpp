#include "Jump.h"

Jump::Jump() {
    this->activeFrame = jumpFrames[0];
    this->activeFrameIndex = 0;
}

void Jump::nextFrame() {
    if (activeFrameIndex < sizeof(jumpFrames) / sizeof(*jumpFrames)) {
        this->activeFrameIndex++;
    } else {
        this->activeFrameIndex = 0;
    }
    this->activeFrame = jumpFrames[activeFrameIndex];
}
