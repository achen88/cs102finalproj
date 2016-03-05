g++ -o test2 include\*.cpp test\test2.cpp
test2.exe config.txt
cd results
mogrify -format jpeg *.bmp
convert -delay 4 -loop 0 *.jpeg -scale 512x512 m2v:andrew_chen.mpeg
pause