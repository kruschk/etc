#!/bin/bash

echo "Please enter type of fruit"
read fruit
if [ "$fruit" == "apple" ]
	then echo "Good, I like apples!"
elif [ "$fruit" == "pear" ]
	then echo "Good, I like pears!"
elif [ "$fruit" == "banana" ]
	then echo "Good, I like bananas!"
else 
	echo "Oh no, I hate "$fruit"s!"
fi
