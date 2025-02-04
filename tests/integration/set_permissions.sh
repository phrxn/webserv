
#set permissions to directories

directory_file_cpp=folder_with_things_to_test_the_class_File-cpp/

directory_str=${directory_file_cpp}directory

chmod 000 $directory_str
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on directory"
    exit 1
fi

#set permissions to Files

file_str=${directory_file_cpp}file

chmod 000 $file_str
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on directory"
    exit 1
fi

#add read permission to files that will be readed by File.cpp

chmod 444 ${directory_file_cpp}z_file_empty
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on z_file_empty"
    exit 1
fi

chmod 444 ${directory_file_cpp}z_file_10_bytes
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on z_file_10_bytes"
    exit 1
fi

chmod 444 ${directory_file_cpp}z_dir_empty
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on z_dir_empty"
    exit 1
fi

chmod 444 ${directory_file_cpp}z_dir_10_bytes
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on z_dir_10_bytes"
    exit 1
fi

# ------------ add permission to files/directory to directoryListing ----------

directoryListing=folder_with_things_to_test_the_class_DirectoryListing-cpp/

chmod 777 ${directoryListing}dir1
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on dir1"
    exit 1
fi

chmod 777 ${directoryListing}dir2
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on dir2"
    exit 1
fi

chmod 777 ${directoryListing}file1
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on file1"
    exit 1
fi

chmod 777 ${directoryListing}file2
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on file2"
    exit 1
fi

touch -m -t "$(date -d @1738379045 +%Y%m%d%H%M.%S)" modification_time.txt
if [ $? -ne 0 ]; then
    echo "Error: Couldn't create the date to file modification_time.txt"
    exit 1
fi