#!/bin/bash

echo "Testing find testdir" > output.log
./find1 testdir >> output.log
echo "" >> output.log

echo "Testing find testdir name " >> output.log
./find2 testdir -name test5 >> output.log
echo "" >> output.log

echo "Testing find files made over 10 minutes ago" >> output.log
./find2 testdir -m +10 >> output.log
echo "" >> output.log

echo "Testing find test2 using inum" >> output.log
./find2 testdir -i 144123965210624079 >> output.log
echo "" >> output.log

echo "adding new file test9" >> output.log
mkdir testdir/test9 >> output.log

echo "Testing find testdir -m -10" >> output.log
./find2 testdir -m -10 >> output.log
echo "" >> output.log

echo "Testing remove test9" >> output.log
./find3testdir -n test9 -d >> output.log
echo "" >> output.log

echo "Displaying files to see if file was removed" >> output.log
./find1 testdir >> output.log
echo "" >> output.log




