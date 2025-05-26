#include <span>
#include <complex>
#include <vector>


using ftype = std::complex<double>;

void fftPrepare(std::span<ftype> a)
{
    size_t len = (size_t)std::bit_width(a.size() - 1);
    for (size_t i = 0; i < a.size(); i++)
    {
        size_t j = 0;
        for (size_t k = 0; k < len; k++) { j |= ((i >> k) & 1) << (len - k - 1); }
        if (i < j) { std::swap(a[i], a[j]); }
    }
}

void fftCalc(std::span<ftype> a, ftype wn)
{
    if (a.size() == 1) { return; }
    fftCalc(a.subspan(0, a.size() / 2), wn * wn);
    fftCalc(a.subspan(a.size() / 2, a.size() / 2), wn * wn);
    ftype w = 1.0;
    for (size_t i = 0; i < a.size() / 2; i++, w *= wn)
    {
        ftype bw = w * a[i + a.size() / 2];
        a[i + a.size() / 2] = a[i] - bw; // w^(i + a.size() / 2) = w^i * w^(a/size() / 2) = -w^i
        a[i] = a[i] + bw;
    }
}

void fft(std::span<ftype> a, bool inv)
{
    ftype w1 = std::polar(1.0, 2.0 * std::numbers::pi / a.size());
    if (inv) { w1 = std::conj(w1); }
    fftPrepare(a);
    fftCalc(a, w1);
}

void mul(std::vector<ftype>& a, std::vector<ftype> b)
{
    size_t n = std::bit_ceil(a.size() + b.size() - 1);
    a.resize(n, 0.0);
    b.resize(n, 0.0);
    fft(a, false);
    fft(b, false);
    for (size_t i = 0; i < n; i++) { a[i] *= b[i]; }
    fft(a, true);
    for (auto& ai : a) { ai /= n; }
}

template<typename T>
void mul(std::vector<T>& a, const std::vector<T>& b)
{
    std::vector<ftype> fa(all(a)), fb(all(b));
    mul(fa, std::move(fb));
    a.resize(fa.size());
    for (size_t i = 0; i < a.size(); i++) { a[i] = (T)std::round(fa[i].real()); }
}
