#!/bin/bash

echo "Type in: I love tars"
read foo
var=$(echo $foo | tr "t" "b")
echo $var
