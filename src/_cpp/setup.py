from setuptools import setup, Extension
import sys
import pybind11

setup(
    name = "__init__",
    version = "1.0",
    ext_modules = [
        Extension(
            "_cpp",
            sources = [
                "_cpp.cpp",
                "core.cpp",
                "gamesR2simple.cpp",
                "KeyCodes.cpp",
                "Combinations.cpp"
            ],
            include_dirs = [
                pybind11.get_include(),
                ".",
                r"C:\Users\MyPrezWappa\Documents\SDL3\SDL-release-3.2.20\out\install\x64-Debug\include"
            ],
            library_dirs = [
                r"C:\Users\MyPrezWappa\Documents\SDL3\SDL-release-3.2.20\out\install\x64-Debug\lib"
            ],
            libraries = [
                "SDL3"
            ],
            language = "c++",
            extra_compile_args = ["/std:c++17"]
        )
    ]
)
