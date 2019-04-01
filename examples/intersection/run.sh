DIR=$( dirname $0 )
./build/bin/main.x < ${DIR}/in.txt
mv out/circles.png ${DIR}
