# Gstreamer .dot pipeline export using ezinject
https://github.com/smx-smx/ezinject (`02b6e26bda46541b59a945d3fa8db53506869aa7`)
## Build
```
git clone https://github.com/smx-smx/ezinject.git
# Module is based on an old commit
cd ezinject/
git checkout 02b6e26bda46541b59a945d3fa8db53506869aa7

# Get FindGstreamer modules
wget https://raw.githubusercontent.com/GStreamer/qt-gstreamer/refs/heads/master/cmake/modules/FindGStreamer.cmake -O cmake-modules/FindGStreamer.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/MacroLogFeature.cmake -O cmake-modules/MacroLogFeature.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/QtGStreamerConfig.cmake.in -O cmake-modules/QtGStreamerConfig.cmake.in
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/QtGStreamerConfigCommon.cmake -O cmake-modules/QtGStreamerConfigCommon.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindGLIB2.cmake -O cmake-modules/FindGLIB2.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindGObject.cmake -O cmake-modules/FindGObject.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindGStreamer.cmake -O cmake-modules/FindGStreamer.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindGStreamerPluginsBase.cmake -O cmake-modules/FindGStreamerPluginsBase.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/FindOpenGLES2.cmake -O cmake-modules/FindOpenGLES2.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/HandleImportedTargetsInCMakeRequiredLibraries.cmake -O cmake-modules/HandleImportedTargetsInCMakeRequiredLibraries.cmake
wget https://github.com/GStreamer/qt-gstreamer/raw/refs/heads/master/cmake/modules/MacroFindGStreamerLibrary.cmake -O cmake-modules/MacroFindGStreamerLibrary.cmake

# Get this repository and add to ezinject build
cd samples/
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
