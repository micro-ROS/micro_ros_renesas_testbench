#!/bin/bash

echo $(rfp-cli -device RA -tool e2 -sig | awk '/Device:/ {print $2}')