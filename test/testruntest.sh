



cp ../src/buildfile.c copythisback.c
rm ../src/buildfile.c
cp wraptestmax.c ../src/buildfile.c
make 
echo "test complete"
rm ../src/buildfile.c
cp copythisback.c ../src/buildfile.c

