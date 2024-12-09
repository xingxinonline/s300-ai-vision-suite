import os
import shutil

def process_files_in_directory(directory):
    print("开始处理文件。")
    
    # 首先，将所有.mem后缀文件复制为.cde后缀的文件
    mem_files = [file for file in os.listdir(directory) if file.endswith('.mem')]
    for mem_file in mem_files:
        # 构建新文件名，将后缀从.mem改为.cde
        base_name = os.path.splitext(mem_file)[0]
        new_file = base_name + '.cde'
        src_path = os.path.join(directory, mem_file)
        dest_path = os.path.join(directory, new_file)
        try:
            shutil.copy(src_path, dest_path)
            print(f"已将 {mem_file} 复制为 {new_file}")
        except Exception as e:
            print(f"复制文件 {mem_file} 时出错: {e}")

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
            
        # 创建对应的_cde目录
        cde_directory = os.path.join(new_directory, f"{prefix}_cde")
        os.makedirs(cde_directory, exist_ok=True)
        print(f"创建_cde子目录：{cde_directory}")
        
        # 将.mem文件转换为.cde并移动到_cde目录
        for mem_file in [file for file in mem_files if file.startswith(prefix)]:
            base_name = os.path.splitext(mem_file)[0]
            cde_file_name = f"{base_name}.cde"
            src_path = os.path.join(directory, mem_file)
            cde_temp_path = os.path.join(directory, cde_file_name)  # 临时.cde文件路径

            # 首先复制.mem文件为临时的.cde文件
            shutil.copy(src_path, cde_temp_path)
            print(f"已将 {mem_file} 复制为临时 {cde_file_name}")

            # 然后移动临时的.cde文件到目标_cde子目录
            shutil.move(cde_temp_path, cde_directory)
            print(f"已移动 {cde_file_name} 到 {cde_directory}")

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
