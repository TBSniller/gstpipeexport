# Gstreamer .dot pipeline export using ezinject
## Build
```
git clone https://github.com/smx-smx/ezinject.git

# Get FindGstreamer modules
wget https://raw.githubusercontent.com/GStreamer/qt-gstreamer/refs/heads/master/cmake/modules/FindGStreamer.cmake -O ezinject/cmake-modules/FindGStreamer.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/MacroLogFeature.cmake -O ezinject/cmake-modules/MacroLogFeature.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/QtGStreamerConfig.cmake.in -O ezinject/cmake-modules/QtGStreamerConfig.cmake.in
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/QtGStreamerConfigCommon.cmake -O ezinject/cmake-modules/QtGStreamerConfigCommon.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindGLIB2.cmake -O ezinject/cmake-modules/FindGLIB2.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindGObject.cmake -O ezinject/cmake-modules/FindGObject.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindGStreamer.cmake -O ezinject/cmake-modules/FindGStreamer.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindGStreamerPluginsBase.cmake -O ezinject/cmake-modules/FindGStreamerPluginsBase.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindOpenGLES2.cmake -O ezinject/cmake-modules/FindOpenGLES2.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/HandleImportedTargetsInCMakeRequiredLibraries.cmake -O ezinject/cmake-modules/HandleImportedTargetsInCMakeRequiredLibraries.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/MacroFindGStreamerLibrary.cmake -O ezinject/cmake-modules/MacroFindGStreamerLibrary.cmake

# Get this repository and add to ezinject build
cd ezinject/samples
git clone https://github.com/tbsniller/gstpipeexport.git
echo "add_subdirectory(gstpipeexport)" >> CMakeLists.txt

cd ..
# source env script if needed
./build.sh -DUSE_LH=ON
```

## WebOS `starfish-media-pipeline` example usage
- Copy `libgstpipeexport.so` and `ezinject` to target system
- While video is playing:
```
# Get pid (usually more than one available)
ps -ax | grep starfish

./ezinject PID libgstpipeexport.so

# log will be redirected
tail -F /tmp/gstpipeexport.log
```
- Press pause and play
- .dot file will be exported to `/tmp/pipeline_dump.dot`