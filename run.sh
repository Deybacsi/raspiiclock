clear

g++ -v main.cpp -o bin/raspiiclock

if [ $? -eq 0 ];then
   bin/raspiiclock 
#   echo !$ > raspiiclock.pid
else
   echo "There are compilation errors!"
fi

