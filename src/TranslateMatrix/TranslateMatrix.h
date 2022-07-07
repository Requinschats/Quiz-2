struct Scale {
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
                    float x_scale,
                    float y_scale,
                    float z_scale);

    void bindTranslationMatrix();

    Position position;
    Scale scale;

};
