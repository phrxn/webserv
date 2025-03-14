
#set permissions to directories

directory_file_cpp=folder_with_things_to_test_the_class_File-cpp/

directory_str=${directory_file_cpp}directory

chmod 700 $directory_str
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on directory"
    exit 1
fi

#set permissions to Files

file_str=${directory_file_cpp}/file

chmod 700 $file_str
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on directory"
    exit 1
fi

#add read permission to files that will be readed by File.cpp

chmod 700 ${directory_file_cpp}z_file_empty
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on z_file_empty"
    exit 1
fi

chmod 700 ${directory_file_cpp}z_file_10_bytes
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on z_file_10_bytes"
    exit 1
fi

chmod 700 ${directory_file_cpp}z_dir_empty
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on z_dir_empty"
    exit 1
fi

chmod 700 ${directory_file_cpp}z_dir_10_bytes
if [ $? -ne 0 ]; then
    echo "Error: Failed to change permissions on z_dir_10_bytes"
    exit 1
fi