##
## EPITECH PROJECT, 2020
## rtype
## File description:
## Makefile
##

all:
		@mkdir -p build && \
		cd build && \
		cmake .. -G "Unix Makefiles" && \
		cmake --build . && \
		cp bin/r-type_client .. && \
		cp bin/r-type_server ..

install:
	mkdir -p build && cd build && conan install .. --build=missing

add_remotes:
		conan remote add conan-center https://bintray.com/conan/conan-center
		conan remote add epitech https://bintray.com/epitech/public-conan
		conan remote add bincrafters https://bintray.com/bincrafters/public-conan

clean:
	rm  -rf build/CMakeFiles build/CMakeCache.txt

clean_all:
	rm  -rf build

fclean: clean
	rm r-type_client r-type_server

re: fclean all

.PHONY: all install clean fclean clean_all add_remotes
