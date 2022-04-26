# -*- Python -*-
import os
import platform
import re
import subprocess
import tempfile

import lit.formats
import lit.util

from lit.llvm import llvm_config
from lit.llvm.subst import ToolSubst
from lit.llvm.subst import FindTool

# Configuration file for the 'lit' test runner.

# name: The name of this test suite.
config.name = 'TestANA'

# suffixes: A list of file extensions to treat as test files.
config.suffixes = ['.c', '.cpp', '.i', '.cppm', '.m', '.mm', '.cu', '.hip', '.hlsl',
                   '.ll', '.cl', '.clcpp', '.s', '.S', '.modulemap', '.test', '.rs', '.ifs', '.rc']

# excludes: A list of directories to exclude from the testsuite. The 'Inputs'
# subdirectories contain auxiliary inputs for various tests in their parent
# directories.
config.excludes = ['Inputs', 'CMakeLists.txt', 'README.txt', 'LICENSE.txt', 'debuginfo-tests']

config.test_format = lit.formats.ShTest("0")

#set project directory
source_dir = os.path.dirname(os.path.abspath(__file__)) #absolute path to source file

#set exec_path
config.test_exec_root = os.path.join(source_dir + "/../build/TestANA")

#set clang
config.substitutions.append(('%ClangPath',"/Volumes/CODE/llvm-project/build/bin"))

#set pluginPath
config.substitutions.append(('%PluginPath', source_dir+ "/../build/lib/clang-plugin"))