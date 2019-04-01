DIR=$( dirname $0 )
./build/bin/main.x < ${DIR}/in.txt
mv out/before.png out/intersection.png out/union.png ${DIR}
