#!/bin/sh
exe="Sylvan"
des="/home/failed/Sylvan"
deplist=$(ldd $exe | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')  
cp $deplist $des


