#!/bin/bash

echoFunction() {
	echo "echo is called"
}
fooBar() {
	echo "Functions are FUN!"
}

echoFunction;
fooBar;
echoFunction;
# You call functions without (), just the function name then a semicolon.
