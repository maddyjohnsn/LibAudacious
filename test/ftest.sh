

#Test 1 TTN 
echo "Test of TTN Start.  "
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl  -D IFDEFTEST -D TOOLFOPEN -D TOOLFCLOSE
gcc main.c -o main -ldl -D IFDEFTEST  -D IFDEFTEST 
LD_AUDIT=./comit.so ./main
echo ""
#Test 2 TTR 
echo "Test of TTR Start.  ."
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl  -D IFDEFTEST  -D TOOLFOPEN -D TOOLFCLOSE                       
gcc main.c -o main -ldl -D IFDEFTEST  -D USEGETC
LD_AUDIT=./comit.so ./main
echo ""
#Test 3 TTT
echo "Test of TTT Start.  "
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl  -D IFDEFTEST -D TOOLFOPEN -D TOOLFCLOSE -D TOOLFGETC
gcc main.c -o main -ldl -D IFDEFTEST  -D USEGETC
LD_AUDIT=./comit.so ./main
echo ""

#Test 2 TRN 
echo "Test of TRN Start.  "
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl  -D IFDEFTEST -D TOOLFOPEN
gcc main.c -o main -ldl -D IFDEFTEST 
LD_AUDIT=./comit.so ./main
echo ""
#Test 2 TRR 
echo "Test of TRR Start.  ."
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D IFDEFTEST  -D TOOLFOPEN
gcc main.c -o main -ldl -D IFDEFTEST  -D USEGETC
LD_AUDIT=./comit.so ./main
echo ""
#Test 3 TRT
echo "Test of TRT Start.  "
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D IFDEFTEST  -D TOOLFOPEN -D TOOLFGETC
gcc main.c -o main -ldl -D IFDEFTEST  -D USEGETC
LD_AUDIT=./comit.so ./main
echo ""

#Test 1 TN 
echo "Test of RTN Start. kinda  , mem err of invalid free on fclose"
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D IFDEFTEST   -D TOOLFCLOSE                       
gcc main.c -o main -ldl -D IFDEFTEST 
LD_AUDIT=./comit.so ./main
echo ""
#Test 2 TTR 
echo "Test of RTR Start.   ."
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D IFDEFTEST  -D TOOLFCLOSE                       
gcc main.c -o main -ldl -D IFDEFTEST  -D USEGETC
LD_AUDIT=./comit.so ./main
echo ""
#Test 3 TTT
echo "Test of RTT Start.   "
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D IFDEFTEST  -D TOOLFCLOSE -D TOOLFGETC          
gcc main.c -o main -ldl -D IFDEFTEST  -D USEGETC
LD_AUDIT=./comit.so ./main
echo ""

#Test 1 TN
echo "Test of RRN Start.  " 
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D IFDEFTEST   
gcc main.c -o main -ldl -D IFDEFTEST 
LD_AUDIT=./comit.so ./main
echo ""
#Test 2 TTR
echo "Test of RRR Start.  ."
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D IFDEFTEST  
gcc main.c -o main -ldl -D IFDEFTEST  -D USEGETC
LD_AUDIT=./comit.so ./main
echo ""
#Test 3 TTT
echo "Test of RRT Start.  "
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D IFDEFTEST   -D TOOLFGETC
gcc main.c -o main -ldl -D IFDEFTEST  -D USEGETC
LD_AUDIT=./comit.so ./main
echo ""
