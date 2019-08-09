function generate() {
    OPTIONS=""

    if [ "$ASAN" = "ON" ] ; then
        OPTIONS="$OPTIONS -DCPPCORE_ASAN=ON"
    else
        OPTIONS="$OPTIONS -DCPPCORE_ASAN=OFF"
    fi

    if [ "$UBSAN" = "ON" ] ; then
        OPTIONS="$OPTIONS -DCPPCORE_UBSAN=ON"
    else
        OPTIONS="$OPTIONS -DCPPCORE_UBSAN=OFF"
    fi

    cmake -G "Unix Makefiles" $OPTIONS
}
if [ "$TRAVIS_OS_NAME" = "linux" ]; then
  if [ $ANALYZE = "ON" ] ; then
    if [ "$CC" = "clang" ]; then
        scan-build cmake -G "Unix Makefiles" -DBUILD_SHARED_LIBS=OFF -DASSIMP_BUILD_TESTS=OFF
        scan-build --status-bugs make -j2
    fi
  else
    generate \
    && make -j4 && cd bin && ./cppcore_unittest
  fi
fi
