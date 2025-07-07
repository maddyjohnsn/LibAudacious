



cp ../src/buildfile.c copythisback.c
rm ../src/buildfile.c
cp wraptest1.c ../src/buildfile.c
make
echo "test complete"
rm ../src/buildfile.c
cp wraptest3.c ../src/buildfile.c
make
echo "test complete"
rm ../src/buildfile.c
cp nothingtest.c ../src/buildfile.c
make
echo "test complete"
rm ../src/buildfile.c
cp copythisback.c ../src/buildfile.c

