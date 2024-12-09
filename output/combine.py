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

def read_file_to_dict(file_path):
    """Read file content into a dictionary keyed by the address."""
    content_dict = {}
    with open(file_path, 'r') as file:
        for line in file:
            if line.strip():
                address, content = line.strip().split(' ')
                content_dict[address] = content
    return content_dict

def check_for_duplicate_addresses(dict1, dict2):
    """Check for duplicate addresses in two dictionaries."""
    common_addresses = set(dict1.keys()) & set(dict2.keys())
    if common_addresses:
        raise ValueError(f"Duplicate addresses found: {common_addresses}")

def merge_dicts(dict1, dict2):
    """Merge two dictionaries, combining and sorting by keys."""
    merged_dict = {}
    for address in sorted(set(dict1.keys()) | set(dict2.keys())):
        content1 = dict1.get(address, "")
        content2 = dict2.get(address, "")
        merged_content = content2 + content1
        merged_dict[address] = merged_content
    return merged_dict

def write_merged_content(merged_dict, output_path):
    """Write the merged content to a file, replacing addresses."""
    with open(output_path, 'w') as file:
        for address in merged_dict:
            new_address = address.replace("@44", "@00")
            file.write(f"{new_address} {merged_dict[address]}\n")

def fill_missing_addresses(output_path):
    """Fill missing addresses with zeros."""
    temp_path = output_path + ".temp"
    with open(output_path, 'r') as file, open(temp_path, 'w') as temp_file:
        prev_address = None
        for line in file:
            address, content = line.strip().split(' ', 1)
            address_int = int(address.replace('@', ''), 16)

            # If there is a previous address and a gap exists, fill the gap with zeros
            if prev_address is not None and address_int != prev_address + 1:
                for missing_address in range(prev_address + 1, address_int):
                    temp_file.write(f"@{missing_address:07X} {'0'*len(content)}\n")

            temp_file.write(line)
            prev_address = address_int

    # Replace the original file with the temp file
    os.replace(temp_path, output_path) 
            
def write_data_parts_from_file(output_path, directory, base_name):
    """从更新后的文件中读取内容，并将数据四等分逆序写入四个新文件"""
    # 从更新后的文件中读取数据
    with open(output_path, 'r') as file:
        lines = file.readlines()

    # 确保有数据行可供处理
    if not lines:
        print("No data available in the file.")
        return

    # 定义目标文件名，包含base_name前缀
    part_file_names = [
        f'{base_name}_ext_blk0_16k0.mem',
        f'{base_name}_ext_blk0_16k1.mem',
        f'{base_name}_ext_blk0_16k2.mem',
        f'{base_name}_ext_blk0_16k3.mem',
    ]

    # 分割并逆序写入数据
    part_files = [open(os.path.join(directory, name), 'w') for name in part_file_names]
    for line in lines:
        _, data = line.strip().split(' ', 1)
        # 分割数据
        parts = [data[i:i + len(data) // 4] for i in range(0, len(data), len(data) // 4)]
        # 逆序并写入到对应的文件
        for part_file, part_data in zip(part_files, parts[::-1]):  # 注意逆序处理
            part_file.write(f"{part_data}\n")

    # 关闭所有文件
    for file in part_files:
        file.close()

    print(f"Data divided and written to files with base_name prefix: {', '.join(part_file_names)}")

def process_files(base_name, directory, suffixes):
    # Read file contents into dictionaries
    file_dicts = [read_file_to_dict(os.path.join(directory, f'{base_name}_{suffix}.mem')) for suffix in suffixes]

    # Check for duplicate addresses and merge prog and data banks separately
    check_for_duplicate_addresses(file_dicts[0], file_dicts[2]) # prog_blk0 vs data_blk0
    check_for_duplicate_addresses(file_dicts[1], file_dicts[3]) # prog_blk1 vs data_blk1

    merged_bnk0 = merge_dicts(file_dicts[0], file_dicts[2])
    merged_bnk1 = merge_dicts(file_dicts[1], file_dicts[3])

    # Ensure both banks have the same addresses
    final_addresses = sorted(set(merged_bnk0.keys()) | set(merged_bnk1.keys()))
    final_merged = {addr: merged_bnk1.get(addr, "0000000000000000") + merged_bnk0.get(addr, "0000000000000000") for addr in final_addresses}

    # Write final merged content to a file
    output_path = os.path.join(directory, f'{base_name}_ext_blk0.mem')
    write_merged_content(final_merged, output_path)
    
    # Then, fill missing addresses
    fill_missing_addresses(output_path)

    print(f"File merged and saved at: {output_path}")

    # 新增：仅将数据段四等分并写入四个新文件
    write_data_parts_from_file(output_path, directory, base_name)

def main():
    print("Starting the merging process.")
    current_directory = os.getcwd()
    suffixes = ['ext_prog_blk0_bnk0', 'ext_prog_blk0_bnk1', 'edp_ext_data_blk0_bnk0', 'edp_ext_data_blk0_bnk1']
    base_names = set()

    # Identify unique base names based on the suffix
    for file in os.listdir(current_directory):
        for suffix in suffixes:
            if file.endswith(suffix + '.mem'):
                base_name = file[:-len(suffix) - 4].rstrip('_') # 4 for '.mem'
                base_names.add(base_name)
                break

    for base_name in base_names:
        process_files(base_name, current_directory, suffixes)

    print("Merging process complete.")
    


if __name__ == "__main__":
    main()
