# BufWrL

Author: Aleksandar Koruga

Linearly Interpolated BufWr

### Requirements

- CMake >= 3.5
- SuperCollider source code

### Building

Clone the project:

    git clone https://aleksandarkoruga/bufwrl
    cd bufwrl
    mkdir build
    cd build

Then, use CMake to configure and build it:

    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
    cmake --build . --config Release --target install

You may want to manually specify the install location in the first step to point it at your
SuperCollider extensions directory: add the option `-DCMAKE_INSTALL_PREFIX=/path/to/extensions`.

It's expected that the SuperCollider repo is cloned at `../supercollider` relative to this repo. If
it's not: add the option `-DSC_PATH=/path/to/sc/source`.

### Developing

Use the command in `regenerate` to update CMakeLists.txt when you add or remove files from the
project. You don't need to run it if you only change the contents of existing files. You may need to
edit the command if you add, remove, or rename plugins, to match the new plugin paths. Run the
script with `--help` to see all available options.

### Ugen

Variable rate buffer writing is useful in situations such as granular synthesis or evading to reallocate buffers for changing bpms.
This solution doesn't limit the "skip" so be weary of CPU consumption at very high writing speeds to "large" buffers.
To see the difference with BufWr.ar try:
(
{
var sig=SinOsc.ar(MouseY.kr(0.2, 15000, 1));
var buf1= LocalBuf.new(9600);
var buf2= LocalBuf.new(9600);
var rate=MouseX.kr(0.2, 2000.0, 1);
var readRate=8.0;
var scPhase=Phasor.ar(0, BufRateScale.kr(buf2) * rate, 0, BufFrames.kr(buf2));

var readPhase= ((0.5*BufFrames.kr(buf2))+Phasor.ar(0, BufRateScale.kr(buf2) * readRate, 0, BufFrames.kr(buf2))).wrap(BufFrames.kr(buf2));

BufWrL.ar(buf1, scPhase/BufFrames.kr(buf2),sig);
BufWr.ar(sig,buf2,scPhase);

Sanitize.ar([BufRd.ar(1,buf1,readPhase,interpolation:4),BufRd.ar(1,buf2,readPhase,interpolation:4)]).scope
}.play
)
