#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

class Transformation {
public:
    virtual glm::mat4 getTransformedMatrix(const glm::mat4& matrix) = 0;
    virtual bool isDynamic() const { return false; }
    virtual ~Transformation() = default;
};


class Translate : public Transformation {
private:
    glm::vec3 translation;

public:
    Translate(float x, float y, float z) : translation(x, y, z) {}

    glm::mat4 getTransformedMatrix(const glm::mat4& matrix) override {
        return glm::translate(matrix, translation);
    }
};

class Rotate : public Transformation {
private:
    float angle;
    glm::vec3 axis;

public:
    Rotate(float angle, float x, float y, float z) : angle(angle), axis(x, y, z) {}

    glm::mat4 getTransformedMatrix(const glm::mat4& matrix) override {
        return glm::rotate(matrix, glm::radians(angle), axis);
    }
};

class Scale : public Transformation {
private:
    glm::vec3 scale;

public:
    Scale(float x, float y, float z) : scale(x, y, z) {}

    glm::mat4 getTransformedMatrix(const glm::mat4& matrix) override {
        return glm::scale(matrix, scale);
    }
};

class DynamicTranslate : public Transformation {
private:
    glm::vec3 translationStartPoint;
    glm::vec3 translationEndPoint;
    float progress; // Progress factor between 0.0 and 1.0
    float speed;

public:
    DynamicTranslate(float x, float y, float z, float x1, float y1, float z1, float speed = 0.01f)
        : translationStartPoint(x, y, z), translationEndPoint(x1, y1, z1), progress(0.0f), speed(speed) {}

    glm::mat4 getTransformedMatrix(const glm::mat4& matrix) override {
        if (progress < 1.0f) {
            progress += speed;
            if (progress > 1.0f) {
                progress = 1.0f;
            }
        }

        // Interpolate between the start and end points
        glm::vec3 currentPosition = glm::mix(translationStartPoint, translationEndPoint, progress);

        return glm::translate(matrix, currentPosition);
    }

    bool isDynamic() const override { return true; }

    void reset() {
        progress = 0.0f;
    }
};

class BezinCurve : public Transformation {
private:
    glm::mat4 A;              // Bézier basis matrix
    glm::mat4x3 B;            // Control points (4 control points in 3D space)
    float t;                  // Current interpolation parameter
    float delta;              // Step size for updating `t`
    glm::vec3 positionOffset; // Offset to apply to the computed position

public:
    BezinCurve(const glm::mat4& A, const glm::mat4x3& B, float initialT = 0.5f, float deltaStep = 0.01f, glm::vec3 offset = glm::vec3(0.0f))
        : A(A), B(B), t(initialT), delta(deltaStep), positionOffset(offset) {}

    glm::mat4 getTransformedMatrix(const glm::mat4& matrix) override {
        if (t >= 1.0f || t <= 0.0f) delta *= -1;
        t += delta;

        // Compute the Bézier curve position
        glm::vec4 parameters(t * t * t, t * t, t, 1.0f); // Bézier basis vector: [t^3, t^2, t, 1]
        glm::vec3 p = B * (A * parameters);              // Compute position using basis matrix A and control points B

        p += positionOffset;

        return glm::translate(matrix, p);
    }

    bool isDynamic() const override {
        return true;
    }
};



class DynamicRotate : public Transformation {
private:
    float angle;
    glm::vec3 axis;

public:
    DynamicRotate(float angle, float x, float y, float z) : angle(angle), axis(x, y, z) {}

    glm::mat4 getTransformedMatrix(const glm::mat4& matrix) override {
        angle += 10.0f; 
        return glm::rotate(matrix, glm::radians(angle), axis);
    }

    bool isDynamic() const override { return true; }
};

class TransformationGroup : public Transformation {
private:
    std::vector<std::shared_ptr<Transformation>> transformations;;

public:

    void addTransformation(const std::shared_ptr<Transformation>& transformation) {
        transformations.push_back(transformation);
    }

	void clearAllTransformations() {
		transformations.clear();
	}


    Transformation* getTransformedMatrixByIndex(int index) {
        return transformations[index].get();
    }

    // Returns all transformations
    glm::mat4 getTransformedMatrix(const glm::mat4& matrix) override {
        glm::mat4 result = matrix;
        for (const auto& transformation : transformations) {
            result = transformation->getTransformedMatrix(result);
        }
        return result;
    }

    bool isDynamic() const override {
        for (const auto& transformation : transformations) {
            if (transformation->isDynamic()) {
                return true;
            }
        }
        return false;
    }
};





