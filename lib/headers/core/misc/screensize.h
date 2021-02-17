#ifndef SCREENSIZE_H
#define SCREENSIZE_H

#include <cstdint>
#include <utility>


class ScreenSize final {
private:
    int32_t m_width;
    int32_t m_height;

public:
    friend void swap(ScreenSize&, ScreenSize&);

public:
    ScreenSize();
    ~ScreenSize() = default;
    ScreenSize(const ScreenSize& other);
    ScreenSize(ScreenSize&& other) noexcept;

    ScreenSize& operator=(const ScreenSize& other);
    ScreenSize& operator=(ScreenSize&& other) noexcept;

    explicit ScreenSize(int32_t size);
    explicit ScreenSize(int32_t width, int32_t height);

public:
    void Update(int32_t width, int32_t height);
    void Update(ScreenSize other);

    int32_t GetWidth() const;
    void SetWidth(const int32_t width);

    int32_t GetHeight() const;
    void SetHeight(const int32_t height);
};

void swap(ScreenSize& lhs, ScreenSize& rhs);

#endif // SCREENSIZE_H
