// PluginBufWrL.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "BufWrL.hpp"

static InterfaceTable* ft;

namespace BufWrL {

BufWrL::BufWrL() {
    mCalcFunc = make_calc_function<BufWrL, &BufWrL::next>();
    next(1);
}

void BufWrL::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(0);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace BufWrL

PluginLoad(BufWrLUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<BufWrL::BufWrL>(ft, "BufWrL");
}
