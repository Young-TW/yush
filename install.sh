# build

echo "start Build"

g++ src/main.cpp -o yush -std=c++17

# add to path

echo "set yush binary file to PATH"

cp yush /usr/local/bin/

echo "All tasks done"