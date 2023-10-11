#!/bin/bash

# Check if correct number of arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filesize in GB> <partitions>"
    exit 1
fi

input_file="file"
filesize=$1
partition=$2

#Creating master file:
rm "${input_file}"*
python3 create.py $input_file $filesize

echo "Done writing master file"

# Delete all folders starting with "testfilefolder"
for folder in testfilefolder*; do
    if [ -d "$folder" ]; then
        rm -r "$folder"
    fi
done




# Calculate size based on filesize and partition
#size=$((( $filesize / $partition )))
split -n $partition $input_file $input_file -d


# Create required number of folders and run the python command
for (( i=0; i<$partition; i++ )); do
    foldername="testfilefolder$i"
    mkdir "$foldername"
    mv file0$i "${foldername}/file$i"
    #python3 create.py "$foldername/file$i" "$size"
done
