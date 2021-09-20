#!/bin/bash

rfp-cli -device RA -tool e2 > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "E2 emulator failed, trying with Jlink"
    rfp-cli -device RA -tool jlink > /dev/null 2>&1
fi

exit $?