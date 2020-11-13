#!/bin/bash

read foo
var=$(echo $foo | tr "{a-z}" "{A-Z}")
# {a-z} matches a through z
# {A-Z} matches Z through Z
echo $var
