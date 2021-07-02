#!/bin/bash

rfp-cli -device RA -tool e2 > /dev/null 2>&1
exit $?