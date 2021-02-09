#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>

#include <cstdint>


class Color final {
private:
    static const uint8_t RED, GREEN, BLUE, ALPHA;

private:
    union {
        uint32_t m_id;
        uint8_t m_chanel;
    };

public:
    Color();
    Color(const Color& other);
    Color(Color&& other) noexcept;
    Color& operator=(const Color& other);
    Color& operator=(Color&& other) noexcept;
    ~Color() = default;

public:
    explicit Color(uint32_t id);
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

public:
    friend void swap(Color&, Color&);

public:
    uint32_t Id() const;
    void Id(uint32_t id);

    uint8_t Red() const;
    uint8_t Green() const;
    uint8_t Blue() const;
    uint8_t Alpha() const;

    void Red(uint8_t r);
    void Green(uint8_t g);
    void Blue(uint8_t b);
    void Alpha(uint8_t a);

    void RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

public:
    explicit operator glm::vec3() const;
    explicit operator glm::vec4() const;
};


void swap(Color& lhs, Color& rhs);

#endif // COLOR_H
