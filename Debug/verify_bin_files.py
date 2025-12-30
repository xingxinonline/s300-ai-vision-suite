#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
验证bin文件与ELF文件的一致性
"""

import os
import sys
import struct
from collections import defaultdict

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    print("Error: pyelftools not installed. Install with: pip install pyelftools")
    sys.exit(1)

# 定义bin文件与段的映射关系
BIN_SECTION_MAPPING = {
    'dsp_ptcm_boot.bin': ['.inttbl', '.text.internal'],
    'dsp_dtcm_boot.bin': ['.data.internal', '.cst.call', '.cst.mov', '.bss', '__MALLOC_SECT'],
    'dsp_sram0_boot.bin': ['.text.external', '__STACK_SECT', '.bss1', '__ARG_SECT', '.data.external', '.interrupt.external'],
    'dsp_sram1_boot.bin': ['.sram1.data'],
    'dsp_psram_boot.bin': ['.npu.inst.external', '.npu.data.external'],
}

class BinVerifier:
    def __init__(self, elf_path, debug_dir):
        self.elf_path = elf_path
        self.debug_dir = debug_dir
        self.sections_data = {}
        self.load_elf()
    
    def load_elf(self):
        """从ELF文件中加载所有段的信息"""
        if not os.path.exists(self.elf_path):
            print(f"Error: ELF file not found: {self.elf_path}")
            sys.exit(1)
        
        with open(self.elf_path, 'rb') as f:
            elffile = ELFFile(f)
            
            print("=" * 80)
            print("ELF文件段信息:")
            print("=" * 80)
            print(f"{'段名':<20} {'地址':<12} {'大小':<10} {'文件偏移':<12}")
            print("-" * 80)
            
            for section in elffile.iter_sections():
                # 跳过某些特殊段
                if section['sh_type'] == 'SHT_NOBITS':
                    self.sections_data[section.name] = {
                        'data': b'',
                        'addr': section['sh_addr'],
                        'size': section['sh_size'],
                        'offset': section['sh_offset'],
                        'type': 'NOBITS'
                    }
                else:
                    section_data = section.data()
                    self.sections_data[section.name] = {
                        'data': section_data,
                        'addr': section['sh_addr'],
                        'size': len(section_data),
                        'offset': section['sh_offset'],
                        'type': 'PROGBITS'
                    }
                
                # 只打印映射表中存在的段
                for bin_file, sections in BIN_SECTION_MAPPING.items():
                    if section.name in sections:
                        size = self.sections_data[section.name]['size']
                        addr = hex(section['sh_addr'])
                        sec_type = self.sections_data[section.name]['type']
                        print(f"{section.name:<20} {addr:<12} {size:<10} {sec_type:<12}")
            
            print()
    
    def verify_bin_files(self):
        """验证bin文件"""
        print("=" * 80)
        print("验证bin文件内容:")
        print("=" * 80)
        
        results = {}
        
        for bin_file, section_names in BIN_SECTION_MAPPING.items():
            bin_path = os.path.join(self.debug_dir, bin_file)
            
            if not os.path.exists(bin_path):
                print(f"\n❌ {bin_file}: 文件不存在")
                results[bin_file] = False
                continue
            
            # 读取bin文件
            with open(bin_path, 'rb') as f:
                bin_data = f.read()
            
            bin_size = len(bin_data)
            
            # 计算应该包含的段的总大小
            expected_size = 0
            section_info = []
            
            for section_name in section_names:
                if section_name in self.sections_data:
                    sec_data = self.sections_data[section_name]['data']
                    sec_size = self.sections_data[section_name]['size']
                    expected_size += sec_size
                    section_info.append((section_name, sec_size))
                else:
                    print(f"  ⚠️  Warning: 段 {section_name} 在ELF中不存在")
            
            # 验证大小
            print(f"\n✓ {bin_file}:")
            print(f"  文件大小: {bin_size} bytes ({bin_size/1024:.2f} KB)")
            print(f"  预期大小: {expected_size} bytes ({expected_size/1024:.2f} KB)")
            
            # 显示包含的段
            print(f"  包含的段:")
            for sec_name, sec_size in section_info:
                print(f"    - {sec_name}: {sec_size} bytes")
            
            # 检查内容匹配
            offset = 0
            content_match = True
            
            for section_name in section_names:
                if section_name not in self.sections_data:
                    continue
                    
                sec_data = self.sections_data[section_name]['data']
                sec_size = len(sec_data)
                
                # 比较数据（仅当两者大小相同时才有意义）
                if offset + sec_size <= bin_size:
                    bin_section_data = bin_data[offset:offset + sec_size]
                    if bin_section_data == sec_data:
                        print(f"    ✓ {section_name} 内容一致")
                    else:
                        print(f"    ❌ {section_name} 内容不一致!")
                        content_match = False
                    offset += sec_size
                else:
                    print(f"    ⚠️  {section_name} 越界")
                    content_match = False
            
            results[bin_file] = content_match
        
        print()
        return results
    
    def generate_report(self, results):
        """生成验证报告"""
        print("=" * 80)
        print("验证报告:")
        print("=" * 80)
        
        passed = sum(1 for v in results.values() if v)
        total = len(results)
        
        for bin_file, result in results.items():
            status = "✓ PASS" if result else "❌ FAIL"
            print(f"{status}: {bin_file}")
        
        print(f"\n总计: {passed}/{total} 通过")
        
        if passed == total:
            print("\n✅ 所有bin文件验证通过！")
        else:
            print(f"\n❌ 有 {total - passed} 个bin文件验证失败")
        
        return passed == total

def main():
    # 获取当前目录（Debug目录）
    debug_dir = os.getcwd()
    elf_file = os.path.join(debug_dir, 'testbench_dsp.elf')
    
    print(f"工作目录: {debug_dir}")
    print(f"ELF文件: {elf_file}")
    print()
    
    # 创建验证器
    verifier = BinVerifier(elf_file, debug_dir)
    
    # 验证bin文件
    results = verifier.verify_bin_files()
    
    # 生成报告
    success = verifier.generate_report(results)
    
    return 0 if success else 1

if __name__ == '__main__':
    sys.exit(main())
