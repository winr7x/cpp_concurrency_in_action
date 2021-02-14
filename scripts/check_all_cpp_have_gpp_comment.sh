#!/bin/bash

find listings -type f -name "*cpp" -exec \
bash -c '! grep -q "^//\s*g++" $0 && echo "This file does not have //g++ comment: $0"' {} \;

echo "Script completed. If no any messages above then all cpp files have //g++ comment"
