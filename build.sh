if [[ "$(uname)" == "Darwin" ]]; then
	export CC="$(brew --prefix llvm)/bin/clang"
	export CXX="$(brew --prefix llvm)/bin/clang++"
fi

rm -rf build
mkdir build
cd build
cmake .. -DRWMICRO_USE_OPENMP=ON -DRWMICRO_BUILD_APPS=ON -DRWMICRO_BUILD_TESTS=ON
make -j8
