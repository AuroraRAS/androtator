# Androtator
Androtator helps you keep your antenna pointing to the satellite. It run on Android 6 or later, and working with GPredict.

## How to build
1. Please put your NDK path after the "PATH" env, we need `ndk-build` to build Hamlib.

 `PATH=$PATH:<sdk path>/<ndk path>/<ndk version>`

2. Build Hamlib.

 `./build_hamlib.sh`

3. Build Androtaor using your Qt Creator.
4. Open an issue tell me, if you get any errors.