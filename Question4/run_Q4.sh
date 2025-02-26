#!/bin/bash
#SBATCH -J BlasSimple                            # Job name
#SBATCH -N 1                                # Number of nodes
#SBATCH -n 1                               # Number of tasks
#SBATCH -o output_%j.txt                    # Standard output file
#SBATCH -e error_%j.txt                     # Standard error file
#SBATCH --mail-user=tarallo.n@northeastern.edu  # Email
#SBATCH --mail-type=ALL                     # Type of email notifications

# Your program/command here

module load OpenBLAS/0.3.29
gcc -lm -lopenblas Q4.c -o Q4
./Q4
