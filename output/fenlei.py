import os
import shutil

def process_files_in_directory(directory):
    print("开始处理文件。")

    # 查找所有包含特定后缀的文件
    suffix = '_edp_ext_data_blk0_bnk0.mem'
    files_with_suffix = [file for file in os.listdir(directory) if suffix in file]

    # 提取所有独特的前缀
    prefixes = set(file.split('_edp')[0] for file in files_with_suffix)

    # 为每个前缀创建目录并移动文件
    for prefix in prefixes:
        new_directory = os.path.join(directory, prefix)
        if not os.path.exists(new_directory):
            os.makedirs(new_directory)
            print(f"创建目录：{new_directory}")

        # 将所有包含该前缀的文件移动到新目录
        for file in os.listdir(directory):
            if file.startswith(prefix):
                src_path = os.path.join(directory, file)
                dest_path = os.path.join(new_directory, file)
                try:
                    shutil.move(src_path, dest_path)
                    print(f"已将 {file} 移动到 {new_directory}")
                except Exception as e:
                    print(f"移动文件 {file} 时出错: {e}")

    print("文件处理完成。")

def main():
    current_directory = os.getcwd()
    process_files_in_directory(current_directory)

if __name__ == "__main__":
    main()
