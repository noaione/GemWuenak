import argparse
import os
import subprocess
from pathlib import Path

# Need Python3.6 and up

parser = argparse.ArgumentParser(prog="GemWuenak-Compiler")
parser.add_argument("method", help="method to use", choices=["clean", "compile"])
parser.add_argument(
    "-CXX", "--cxx-path", dest="cxx_path", action="store", type=str, required=False, default="g++"
)
parser.add_argument("-fa", "--fallback-ascii", dest="fa_flags", action="store_true", required=False)
parser.add_argument("-d", "--debug-mode", dest="debug_flags", action="store_true", required=False)
args = parser.parse_args()

if args.method == "clean":
    object_files = [str(path) for path in Path('.').rglob('*.o')]
    for obj_f in object_files:
        os.remove(obj_f)
    exit(0)
elif args.method == "compile":
    game_name = "GemWuenak"
    collect_cpp = [str(path) for path in Path('.').rglob('*.cpp')]
    for cppf in collect_cpp:
        print(f"Compiling: {cppf}")
        cppn, _ = os.path.splitext(cppf)
        cmp_args = [args.cxx_path, "-O2", "-c", cppf, "-o", cppn + ".o"]
        if args.fa_flags:
            cmp_args.append("-DFALLBACKASCII")
        if args.debug_flags:
            cmp_args.append("-DDEBUGGAME")
        subprocess.call(cmp_args)

    object_files = [str(path) for path in Path('.').rglob('*.o')]
    cmp_args = [args.cxx_path, "-O2", "-s"]
    cmp_args.extend(object_files)
    if args.fa_flags:
        cmp_args.append("-DFALLBACKASCII")
        game_name += "_fallback"
    if args.debug_flags:
        cmp_args.append("-DDEBUGGAME")
        game_name += "_debugbuild"
    # cmp_args.extend(["-O1"])
    print(f"Compiling binary: {game_name}")
    cmp_args.extend(["-o", game_name])
    subprocess.call(cmp_args)
