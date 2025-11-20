mkdir build
cd build

cmake ..
cp ../config/settings.json ./settings.json

mkdir ./shader/
cp ../shader/* ./shader/

mkdir ./texture/
cp ../texture/* ./texture/

cmake --build .

./Chess