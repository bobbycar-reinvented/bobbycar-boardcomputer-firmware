#!/usr/bin/env python3
import os
import subprocess

# execute './switchconf.sh --list' to get the list of available configurations
output = subprocess.check_output(['bash', './switchconf.sh', '--list']).decode('utf-8').splitlines()

if len(output) == 0:
    print('No configurations found!')
    exit(1)

# check if PATH (env) contains 'bobbycar-boardcomputer-firmware
if 'bobbycar-boardcomputer-firmware' not in os.environ['PATH']:
    print('Please execute ". export.sh"')
    exit(1)

for config in output:
    print('Switching to configuration: ' + config)
    subprocess.check_call(['bash', './switchconf.sh', config])
    # execute idf.py menuconfig and wait for user to close again
    subprocess.check_call(['idf.py', 'menuconfig'])