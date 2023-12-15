# -*- coding:utf-8 -*-
'''
Author       : panxinhao
Date         : 2023-11-17 14:14:45
LastEditors  : panxinhao
LastEditTime : 2023-11-17 14:22:52
FilePath     : \\mem\\combine.py
Description  : 

Copyright (c) 2023 by xinhao.pan@pimchip.cn, All Rights Reserved. 
'''

import os

def read_file(file_path):
    """Function to read file content."""
    with open(file_path, 'r') as file:
        return file.readlines()

def merge_lines_adjusted(line_bnk0, line_bnk1):
    """Function to merge two lines with bnk1 as high bits, handling empty lines."""
    try:
        address_bnk0, content_bnk0 = line_bnk0.strip().split(' ')
    except ValueError:
        address_bnk0, content_bnk0 = line_bnk0.strip(), "0000000000000000"  # Default content for empty lines

    try:
        _, content_bnk1 = line_bnk1.strip().split(' ')
    except ValueError:
        content_bnk1 = "0000000000000000"  # Default content for empty lines

    # Replace @44 with @00 in the address
    address_bnk0 = address_bnk0.replace("@44", "@00")

    merged_content = content_bnk1 + content_bnk0
    return address_bnk0 + ' ' + merged_content + '\n'

# Function to check if required files exist in a directory
def required_files_exist(directory, base_name):
    required_files = [
        f'{base_name}_ext_prog_blk0_bnk0.mem',
        f'{base_name}_ext_prog_blk0_bnk1.mem',
        f'{base_name}_edp_ext_data_blk0_bnk0.mem',
        f'{base_name}_edp_ext_data_blk0_bnk1.mem'
    ]
    exists = all(os.path.exists(os.path.join(directory, file)) for file in required_files)
    if not exists:
        print(f"Required files for {base_name} are not all present in {directory}")
    return exists

# Function to merge files in a given directory
def merge_files_in_directory(directory, base_name):
    print(f"Processing project: {base_name} in directory: {directory}")

    prog_bnk0_path = os.path.join(directory, f'{base_name}_ext_prog_blk0_bnk0.mem')
    prog_bnk1_path = os.path.join(directory, f'{base_name}_ext_prog_blk0_bnk1.mem')
    data_bnk0_path = os.path.join(directory, f'{base_name}_edp_ext_data_blk0_bnk0.mem')
    data_bnk1_path = os.path.join(directory, f'{base_name}_edp_ext_data_blk0_bnk1.mem')

    # Read and merge contents
    prog_bnk0_content = read_file(prog_bnk0_path)
    prog_bnk1_content = read_file(prog_bnk1_path)
    data_bnk0_content = read_file(data_bnk0_path)
    data_bnk1_content = read_file(data_bnk1_path)

    if len(data_bnk0_content) > len(data_bnk1_content):
        data_bnk1_content.append('\n')

    merged_prog = [merge_lines_adjusted(bnk0, bnk1) for bnk0, bnk1 in zip(prog_bnk0_content, prog_bnk1_content)]
    merged_data = [merge_lines_adjusted(bnk0, bnk1) for bnk0, bnk1 in zip(data_bnk0_content, data_bnk1_content)]

    combined_content = merged_prog + merged_data

    combined_file_path = os.path.join(directory, f'{base_name}_ext_blk0.mem')

    with open(combined_file_path, 'w') as file:
        file.writelines(combined_content)
    print(f"Merging complete for {base_name}. Combined file saved at: {combined_file_path}")

# Main function to iterate through subdirectories and merge files
def main():
    print("Starting the merging process.")
    current_directory = os.getcwd()
    for item in os.listdir(current_directory):
        subdirectory = os.path.join(current_directory, item)
        if os.path.isdir(subdirectory):
            base_name = os.path.basename(subdirectory)
            if required_files_exist(subdirectory, base_name):
                merge_files_in_directory(subdirectory, base_name)
    print("Merging process complete.")

if __name__ == "__main__":
    main()
