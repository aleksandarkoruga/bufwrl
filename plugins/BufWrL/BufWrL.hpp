// PluginBufWrL.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace BufWrL {

class BufWrL : public SCUnit {
public:
    BufWrL();

    // Destructor
    // ~BufWrL();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace BufWrL
