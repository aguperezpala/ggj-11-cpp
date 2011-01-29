#!/bin/sh
RESULT="0"
for i in `find ./ -name *.d` 
	do echo "archivo: $i"
	rm $i
done
echo "Cleaner done"
