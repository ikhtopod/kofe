#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>


class Color final {
public:
    using color_type = float;

public: /* Standard colors */
    static const Color BLACK, WHITE, RED, GREEN, BLUE;

private:
    float m_r, m_g, m_b, m_a;

public:
    Color();
    Color(const Color& other);
    Color(Color&& other) noexcept;
    Color& operator=(const Color& other);
    Color& operator=(Color&& other) noexcept;
    ~Color() = default;

public:
    explicit Color(const glm::vec3& rgb);
    explicit Color(const glm::vec3& rgb, color_type a);
    explicit Color(const glm::vec4& rgba);
    explicit Color(color_type r, color_type g, color_type b);
    explicit Color(color_type r, color_type g, color_type b, color_type a);

public:
    friend void swap(Color&, Color&);

private:
    static float Clamp(color_type value);

public:
    color_type Red() const;
    color_type Green() const;
    color_type Blue() const;
    color_type Alpha() const;

    void Red(color_type r);
    void Green(color_type g);
    void Blue(color_type b);
    void Alpha(color_type a);

    void RGBA(color_type r, color_type g, color_type b, color_type a);

public:
    explicit operator glm::vec3() const;
    explicit operator glm::vec4() const;
};


void swap(Color& lhs, Color& rhs);

#endif // COLOR_H
