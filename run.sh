clear

g++ main.cpp -o bin/raspiiclock

if [ $? -eq 0 ];then
   bin/raspiiclock 
#   echo !$ > asciiclock.pid
else
   echo "There are compilation errors!"
fi

