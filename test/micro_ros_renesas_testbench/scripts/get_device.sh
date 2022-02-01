#!/bin/bash
DEVICE=$(rfp-cli -device RA -tool e2 -sig | awk '/Device:/ {print $2}')
echo ${DEVICE}