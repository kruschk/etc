#!/bin/bash
# Change working directory to /home/jonah
DEST='/media/jonah/flash/sync/'

cd /home/jonah && rsync -aPrtvz $(cat lenovo-b575-include.txt) "${DEST}"
