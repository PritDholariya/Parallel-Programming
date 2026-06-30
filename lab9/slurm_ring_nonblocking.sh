#!/usr/bin/env bash

#SBATCH --job-name="ring_nonblocking"
#SBATCH --partition=all
#SBATCH --time=0-00:05:00

#SBATCH --exclusive
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4

#SBATCH --output=/home/fd0005372/out/ring_nonblocking.out.%j
#SBATCH --error=/home/fd0005372/out/ring_nonblocking.err.%j

cd /home/fd0005372/mySubdir

mpirun ./ring_nonblocking