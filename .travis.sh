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
        scan-build --status-bugs make -j4
    fi
  else
    generate \
    && cd build && make -j4 && cd bin && ./cppcore_unittest
  fi
fi
