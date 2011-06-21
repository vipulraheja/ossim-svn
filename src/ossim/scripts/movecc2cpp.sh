#!/bin/bash
for i in `find src -name "*.cc"`
do
base=`echo $i | cut -d. -f1`

mv $i $base.cpp
done