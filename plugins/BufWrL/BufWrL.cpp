// PluginBufWrL.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "BufWrL.hpp"

static InterfaceTable* ft;

namespace BufWrL {

	BufWrL::BufWrL() :prevPhase(-1), prevSamp(0.0f), m_fbufnum(-1.0f) {


		mCalcFunc = make_calc_function<BufWrL, &BufWrL::next>();
		next(1);


	}

	void BufWrL::next(int nSamples) {

		auto* unit = this;

		GET_BUF;

		const float* input0 = in(0);
		const float* phase = in(1);
		const float* samp = in(2);

		float* outbuf = out(0);

		// simple gain function
		if (buf) {
			for (int i = 0; i < nSamples; ++i) {
				int ph;
				int delta;
				{
					LOCK_SNDBUF(buf);
					ph = (static_cast<int>((phase[i]) * buf->samples) % (buf->samples));
					delta = (ph >= prevPhase ? (ph - prevPhase) : (((buf->samples - 1) - prevPhase) + ph));
				}

				if (delta > 0 && prevPhase >= 0)
				{
					auto iDelta = 1.0f / static_cast<float>(delta);


					for (auto j = 0; j < delta; ++j)
					{
						ACQUIRE_SNDBUF(buf);
						bufData[((int)prevPhase + j) % buf->samples] = lininterp(iDelta * static_cast<float>(j), bufData[(int)prevPhase % (buf->samples)], samp[i]);
						RELEASE_SNDBUF(buf);
					}
				}


				{
					LOCK_SNDBUF(buf);
					bufData[ph] = samp[i];
				}

				outbuf[i] = samp[i];

				prevSamp = samp[i];
				prevPhase = ph;


			}


		}
		else {
			for (int i = 0; i < nSamples; ++i) {
				outbuf[i] = samp[i];
			}
		}
	}
} // namespace BufWrL

PluginLoad(BufWrLUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<BufWrL::BufWrL>(ft, "BufWrL");
}
