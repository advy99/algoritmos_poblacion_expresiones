from conan import ConanFile
from conan.tools.gnu import PkgConfigDeps
from conan.tools.meson import Meson, MesonToolchain
from conan.tools.layout import basic_layout
from conan.tools.files import copy, collect_libs
import os
import sys

class GPConan(ConanFile):
    name = "GPAlgorithms"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False], 
        "fPIC": [True, False], 
        "target_dir": ["ANY"],  
        "gprof": [True, False], 
        "openmp": [True, False],
        "docs": [True, False]
    }
    default_options = {
        "shared": False, 
        "fPIC": True, 
        "target_dir": "build",  
        "gprof": False, 
        "openmp": True,
        "docs": False
    }
    # generators = "PkgConfigDeps", "MesonToolchain"
    requires = ["argparse/2.9"]
    exports_sources = "src/*", "include/*", "doc/*", "test/*", "meson.build", "meson.options", "README.md"

    def package_id(self):
        self.info.clear()

    def layout(self):
        # the meson file is in this folder

        self.folders.source = "."
        self.folders.build = str(self.options.target_dir)


    def generate(self):
        pkg_conf = PkgConfigDeps(self)
        pkg_conf.generate()

        # generate meson tool chain depending on options passed to conan
        tc = MesonToolchain(self)
        # tc.project_options["shared"] = str(self.options.shared).lower()
        tc.project_options["gprof"] = str(self.options.gprof).lower()
        tc.project_options["openmp"] = str(self.options.openmp).lower()
        tc.project_options["docs"] = str(self.options.docs).lower()
        tc.generate()


    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        meson = Meson(self)
        meson.install()
        build_dir = os.path.join(self.source_folder, self.folders.build)

        copy(self, "*.hpp", src=self.source_folder, dst=os.path.join(self.package_folder, "include"))
        copy(self, "*.lib", src = build_dir, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.dll", src = build_dir, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.dylib*", src = build_dir, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.so", src = build_dir, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.a", src = build_dir, dst=os.path.join(self.package_folder, "lib"), keep_path=False)


    def package_info(self):
        self.cpp_info.libs = collect_libs(self)
        self.cpp_info.includedirs = ["include"]

