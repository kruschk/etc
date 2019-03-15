#!/bin/bash

# This script synchronizes from the flash drive to another computer.
# The flash drive should be mounted at /media/jonah/flash
DEST='/home/jonah/'

cd /media/jonah/flash/sync/ && rsync -aPrtvz * "${DEST}"
