import os
import sys
import argparse
import requests
import subprocess
import glob

# ================= 配置区域 (请填写) =================
# 1. 内网 GitLab 配置
GITLAB_URL = "http://192.168.199.196:8800" # 去掉 /users/... 等后缀，只留根地址
GITLAB_TOKEN = "1Yo_fbzgmi5z_NxxhKUM"           # <--- 请在此填入内网 GitLab Access Token
GITLAB_PROJECT = "panxinhao/s300-ai-vision-suite" # 格式: 组名/项目名 (URL encoded id 也可以)

# 2. Gitee 配置
GITEE_TOKEN = "e641f2c1b7f75978b54038d4c141676f"             # <--- 请在此填入 Gitee Access Token
GITEE_REPO = "xingxinonline/s300-ai-vision-suite" # 格式: 拥有者/仓库名

# ====================================================

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RELEASE_DIR = os.path.join(PROJECT_ROOT, 'release_pkgs')

def get_current_tag():
    # 1. 尝试从命令行参数获取
    if len(sys.argv) > 1:
        return sys.argv[1]

    # 2. 尝试获取当前精确匹配的 Tag
    try:
        result = subprocess.check_output(
            ['git', '-C', PROJECT_ROOT, 'describe', '--tags', '--exact-match'], 
            stderr=subprocess.STDOUT
        ).decode('utf-8').strip()
        return result
    except subprocess.CalledProcessError:
        pass

    # 3. 尝试获取最近的 Tag
    try:
        print("提示: 当前 HEAD 不是 Tag，尝试使用最近的 Tag...")
        result = subprocess.check_output(
            ['git', '-C', PROJECT_ROOT, 'describe', '--tags', '--abbrev=0'], 
            stderr=subprocess.STDOUT
        ).decode('utf-8').strip()
        return result
    except subprocess.CalledProcessError:
        print("错误: 无法找到任何 Tag")
        sys.exit(1)

def upload_gitlab(tag, file_path, title, description):
    print(f"\n>> [GitLab] 正在发布 {tag} 到 {GITLAB_URL} ...")
    
    # 1. 处理 Project ID (将 / 替换为 %2F)
    project_id_encoded = GITLAB_PROJECT.replace("/", "%2F")
    headers = {"PRIVATE-TOKEN": GITLAB_TOKEN}
    
    # 2. 上传文件
    upload_url = f"{GITLAB_URL}/api/v4/projects/{project_id_encoded}/uploads"
    print(f"   上传文件: {os.path.basename(file_path)}")
    try:
        with open(file_path, 'rb') as f:
            files = {'file': f}
            r = requests.post(upload_url, headers=headers, files=files)
            if r.status_code != 201:
                print(f"   上传失败: {r.text}")
                return
            uploaded_file_info = r.json()
            # Markdown 链接格式
            file_link_markdown = uploaded_file_info.get("markdown")
            # 也可以获取 absolute_url 放到 assets 配置里，这里简单起见，直接追加到 Release Notes 描述里
            description += f"\n\n## 下载\n{file_link_markdown}"
    except Exception as e:
         print(f"   连接 GitLab 失败: {e}")
         return

    # 3. 创建 Release
    release_url = f"{GITLAB_URL}/api/v4/projects/{project_id_encoded}/releases"
    data = {
        "name": title,
        "tag_name": tag,
        "description": description
    }
    
    r = requests.post(release_url, headers=headers, json=data)
    if r.status_code == 201:
        print("   ✅ GitLab 发布成功！")
    elif r.status_code == 409:
        print("   ⚠️ GitLab Release 已存在，跳过。")
    else:
        print(f"   ❌ GitLab 发布失败: {r.text}")

def upload_gitee(tag, file_path, title, description):
    print(f"\n>> [Gitee] 正在发布 {tag} 到 Gitee ...")
    owner, repo = GITEE_REPO.split('/')
    
    # 1. 创建 Release
    create_url = f"https://gitee.com/api/v5/repos/{owner}/{repo}/releases"
    data = {
        "access_token": GITEE_TOKEN,
        "tag_name": tag,
        "name": title,
        "body": description,
        "prerelease": False,
        "target_commitish": "main" 
    }
    
    # Gitee 需要先创建 Release 拿到 ID，然后再上传附件
    # 或者如果 Release 已存在，获取 ID
    r = requests.post(create_url, data=data)
    release_id = None
    
    if r.status_code == 201:
        release_id = r.json()['id']
        print("   Release 创建成功，准备上传附件...")
    elif r.status_code == 409: # Already exists
        print("   Release 已存在，尝试获取 Release ID...")
        # 获取 tag 对应的 release
        get_url = f"https://gitee.com/api/v5/repos/{owner}/{repo}/releases/tags/{tag}"
        r_get = requests.get(get_url, params={"access_token": GITEE_TOKEN})
        if r_get.status_code == 200:
            release_id = r_get.json()['id']
    else:
        print(f"   ❌ Gitee 发布失败: {r.text}")
        return

    if not release_id:
        print("   无法获取 Release ID，跳过附件上传")
        return

    # 2. 上传附件
    # Gitee API 文档说明：POST /repos/{owner}/{repo}/releases/{id}/attach_files
    attach_url = f"https://gitee.com/api/v5/repos/{owner}/{repo}/releases/{release_id}/attach_files"
    
    print(f"   上传文件: {os.path.basename(file_path)}")
    try:
        with open(file_path, 'rb') as f:
            files = {'file': f}
            params = {"access_token": GITEE_TOKEN}
            r_up = requests.post(attach_url, params=params, files=files)
            if r_up.status_code == 201:
                print("   ✅ Gitee 附件上传成功！")
            else:
                print(f"   ❌ Gitee 附件上传失败: {r_up.text}")
    except Exception as e:
        print(f"   Gitee 上传异常: {e}")

def main():
    tag = get_current_tag()
    print(f"当前 Tag: {tag}")
    
    # 查找对应的 zip 包
    zip_pattern = os.path.join(RELEASE_DIR, f"ai_firmware_{tag}.zip")
    if not os.path.exists(zip_pattern):
        print(f"未找到固件包: {zip_pattern}")
        print("请先运行 python output/package_firmware.py 进行打包")
        sys.exit(1)
        
    title = f"Face Detection Firmware {tag}"
    desc = f"Release {tag} for Face Detection DSP firmware."
    
    # 执行 GitHub 发布 (使用 gh cli)
    print(f"\n>> [GitHub] 检查 GitHub 发布状态...")
    # 简单通过 gh release view 检查是否存在，不存在则创建
    try:
        subprocess.check_call(['gh', 'release', 'view', tag], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        print("   GitHub Release 已存在。")
    except subprocess.CalledProcessError:
        print("   GitHub Release 不存在，开始创建...")
        subprocess.call([
            'gh', 'release', 'create', tag, zip_pattern,
            '--title', title,
            '--notes', desc
        ])

    # 执行 GitLab 发布
    if GITLAB_TOKEN != "YOUR_GITLAB_TOKEN":
        upload_gitlab(tag, zip_pattern, title, desc)
    else:
        print("\n>> [GitLab] 未配置 Token，跳过。请编辑脚本填入 GITLAB_TOKEN")

    # 执行 Gitee 发布
    if GITEE_TOKEN != "YOUR_GITEE_TOKEN":
        upload_gitee(tag, zip_pattern, title, desc)
    else:
        print("\n>> [Gitee] 未配置 Token，跳过。请编辑脚本填入 GITEE_TOKEN")

if __name__ == "__main__":
    main()
