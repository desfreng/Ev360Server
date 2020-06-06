#!/usr/bin/env bash

PROJECT_DIR="/home/gabriel/Bureau/Ev360Mover"
DOCKER_CONTAINER="ev360mover"

PROJECT_NAME="$(basename $PROJECT_DIR)"
EXECUTABLE_NAME="$(basename $PROJECT_DIR)"

#CMAKE_OPT="-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON"
CMAKE_OPT=""

BUILD_DIR="$PROJECT_DIR/build"
UPLOAD=0

while getopts "h?u" opt; do
  case "$opt" in
  h | \?)
    show_help
    exit 0
    ;;
  u)
    UPLOAD=1
    ;;
  esac
done

echo "Cleaning build directory..."

if [ -d "$BUILD_DIR" ]; then
  rm -r "$BUILD_DIR"
fi

mkdir -p "$BUILD_DIR"

echo "Generating CMakeList.txt..."

mv "$PROJECT_DIR/CMakeLists.txt" "$PROJECT_DIR/CMakeLists.txt.old"
echo 'include("~/toolchain-armel.cmake")' >"$PROJECT_DIR/CMakeLists.txt"
cat "$PROJECT_DIR/CMakeLists.txt.old" >>"$PROJECT_DIR/CMakeLists.txt"

echo "Starting Docker Container..."

CONTAINER_ID=$(docker run -dit -w "/src/build" -v "$PROJECT_DIR":/src --rm "$DOCKER_CONTAINER")

echo "Container ID : " "$CONTAINER_ID"

echo
echo "Run CMake..."
docker exec "$CONTAINER_ID" cmake .. $CMAKE_OPT

echo
echo "Run Make..."
docker exec "$CONTAINER_ID" make -j 4

echo
echo -e "Stopping Container..."
docker stop "$CONTAINER_ID" >/dev/null

echo "Cleaning..."
mv "$PROJECT_DIR/CMakeLists.txt.old" "$PROJECT_DIR/CMakeLists.txt"

echo
echo "Information on $EXECUTABLE_NAME : "
file -b "$BUILD_DIR/$EXECUTABLE_NAME"

echo
if [ $UPLOAD == 1 ]; then
  echo "Uploading..."

  rsync "$BUILD_DIR/$EXECUTABLE_NAME" "robot@ev3:/home/robot/$PROJECT_NAME/"
  ssh robot@ev3 chmod +x "/home/robot/$PROJECT_NAME/$EXECUTABLE_NAME"

  echo
  echo "Executing..."
  echo
  ssh robot@ev3 brickrun -r "/home/robot/$PROJECT_NAME/$EXECUTABLE_NAME"

  echo
fi

echo "Done !"
