until test-commands
do consequent-commands
done

while test-commands
do consequent-commands
done

for name [ [in [words...] ] ; ]
do commands
done

if test-commands;
	then consequent-commands;
elif more-test-commands;
	then more-consequents;
else alternate consequents;
fi
