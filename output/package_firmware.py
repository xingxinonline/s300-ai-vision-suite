import os
import sys
import zipfile
import subprocess

# 配置
PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BIN_DIR = os.path.join(PROJECT_ROOT, 'Debug')
RELEASE_DIR = os.path.join(PROJECT_ROOT, 'release_pkgs')

# 目标文件列表
BIN_FILES = [
    'model_dtcm_boot.bin',
    'model_psram_boot.bin',
    'model_ptcm_boot.bin',
    'model_sram0_boot.bin',
    'model_sram1_boot.bin'
]

def get_git_tag():
    try:
        # 获取当前 HEAD 指向的 tag，如果不是 tag 则显示 commit hash
        result = subprocess.check_output(
            ['git', '-C', PROJECT_ROOT, 'describe', '--tags', '--exact-match'], 
            stderr=subprocess.STDOUT
        )
        return result.decode('utf-8').strip()
    except subprocess.CalledProcessError:
        try:
            # 如果没有精确匹配的 tag，使用这个命令获取最近的 tag + 距离
            result = subprocess.check_output(
                ['git', '-C', PROJECT_ROOT, 'describe', '--tags', '--always'], 
                stderr=subprocess.STDOUT
            )
            return result.decode('utf-8').strip()
        except subprocess.CalledProcessError:
            return 'snapshot'

def package_binaries(tag):
    if not os.path.exists(RELEASE_DIR):
        os.makedirs(RELEASE_DIR)

    zip_filename = f"dsp_firmware_{tag}.zip"
    zip_path = os.path.join(RELEASE_DIR, zip_filename)

    print(f"正在打包固件版本: {tag} ...")
    
    found_count = 0
    with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for bin_file in BIN_FILES:
            file_path = os.path.join(BIN_DIR, bin_file)
            if os.path.exists(file_path):
                print(f"  [+] 添加: {bin_file}")
                zipf.write(file_path, bin_file)
                found_count += 1
            else:
                print(f"  [!] 警告: 未找到 {bin_file}")

    if found_count == 0:
        print("\n错误: 未找到任何 bin 文件，打包失败。")
        if os.path.exists(zip_path):
            os.remove(zip_path)
    else:
        print(f"\n[v]打包成功！")
        print(f"文件位置: {zip_path}")
        print("请将此文件上传至 Release 附件。")

if __name__ == "__main__":
    current_tag = get_git_tag()
    # 如果用户通过命令行传入了版本号，优先使用
    if len(sys.argv) > 1:
        current_tag = sys.argv[1]
    
    package_binaries(current_tag)
