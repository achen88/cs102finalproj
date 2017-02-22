g++ -o generate include\*.cpp generate\generate.cpp
generate.exe config.txt
cd results
mogrify -format jpeg *.bmp
convert -delay 4 -loop 0 *.jpeg -scale 512x512 m2v:andrew_chen.mp4
pause