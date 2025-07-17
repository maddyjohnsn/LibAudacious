

#Test 1 TTN 
echo "Test of TTN Start. no crash"
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFOPEN -D TOOLFCLOSE
gcc fmain.c -o fmain -ldl 
LD_AUDIT=./comit.so ./fmain
echo ""
#Test 2 TTR 
echo "Test of TTR Start. Crashes."
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFOPEN -D TOOLFCLOSE                       
gcc fmain.c -o fmain -ldl -D USEGETC
LD_AUDIT=./comit.so ./fmain
echo ""
#Test 3 TTT
echo "Test of TTT Start. No crash"
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFOPEN -D TOOLFCLOSE -D TOOLFGETC
gcc fmain.c -o fmain -ldl -D USEGETC
LD_AUDIT=./comit.so ./fmain
echo ""

#Test 2 TRN 
echo "Test of TRN Start. crash"
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFOPEN
gcc fmain.c -o fmain -ldl
LD_AUDIT=./comit.so ./fmain
echo ""
#Test 2 TRR 
echo "Test of TRR Start. Crashes."
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFOPEN
gcc fmain.c -o fmain -ldl -D USEGETC
LD_AUDIT=./comit.so ./fmain
echo ""
#Test 3 TRT
echo "Test of TRT Start. crash"
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFOPEN -D TOOLFGETC
gcc fmain.c -o fmain -ldl -D USEGETC
LD_AUDIT=./comit.so ./fmain
echo ""

#Test 1 TN 
echo "Test of RTN Start. kinda crash, mem err of invalid free on fclose"
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl  -D TOOLFCLOSE                       
gcc fmain.c -o fmain -ldl
LD_AUDIT=./comit.so ./fmain
echo ""
#Test 2 TTR 
echo "Test of RTR Start.  Crashes."
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFCLOSE                       
gcc fmain.c -o fmain -ldl -D USEGETC
LD_AUDIT=./comit.so ./fmain
echo ""
#Test 3 TTT
echo "Test of RTT Start.  crash"
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFCLOSE -D TOOLFGETC          
gcc fmain.c -o fmain -ldl -D USEGETC
LD_AUDIT=./comit.so ./fmain
echo ""

#Test 1 TN
echo "Test of RRN Start. No crash" 
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl  
gcc fmain.c -o fmain -ldl
LD_AUDIT=./comit.so ./fmain
echo ""
#Test 2 TTR
echo "Test of RRR Start. no Crashes."
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl 
gcc fmain.c -o fmain -ldl -D USEGETC
LD_AUDIT=./comit.so ./fmain
echo ""
#Test 3 TTT
echo "Test of RRT Start. No crash"
gcc -shared -fPIC ../src/practice.c -o comit.so -ldl  -D TOOLFGETC
gcc fmain.c -o fmain -ldl -D USEGETC
LD_AUDIT=./comit.so ./fmain
echo ""
