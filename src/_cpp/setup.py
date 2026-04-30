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
                "libs/SDL3/include",
                "libs/SDL3_ttf/include"
            ],
            library_dirs = [
                "libs/SDL3/lib",
                "libs/SDL3_ttf/lib"
            ],
            libraries = [
                "SDL3",
                "SDL3_ttf"
            ],
            language = "c++",
            extra_compile_args = ["/std:c++17"]
        )
    ]
)
