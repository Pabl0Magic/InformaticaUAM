#!/bin/bash
#
#$ -S /bin/bash
#$ -cwd

ssh compute 0-7
cat /proc/cpuinfo.txt > cpuinfo.txt