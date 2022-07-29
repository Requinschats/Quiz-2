#include "Jump.h"

//sets the default values to the first frame
Jump::Jump() {
    this->activeFrame = jumpFrames[0];
    this->activeFrameIndex = 0;
}

//increments the frame index and sets the active frame to the next frame
void Jump::nextFrame() {
    if (activeFrameIndex < sizeof(jumpFrames) / sizeof(*jumpFrames)) {
        this->activeFrameIndex++;
    } else {
        this->activeFrameIndex = 0;
    }
    this->activeFrame = jumpFrames[activeFrameIndex];
}
