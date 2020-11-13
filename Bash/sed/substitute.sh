#!/bin/bash

read foo
echo $foo | sed "s/foo/bars/"
