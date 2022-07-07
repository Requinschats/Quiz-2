struct Size {
    float x;
    float y;
    float z;
};

struct Position {
    float x;
    float y;
    float z;
};


class TranslateMatrix {
public:
    TranslateMatrix(float x_position,
                    float y_position,
                    float z_position,
                    float x_size,
                    float y_size,
                    float z_size);

    void bindTranslationMatrix(int *shaderProgram);

    Position position;
    Size size;

};
