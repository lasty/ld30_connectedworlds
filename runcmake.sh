#!/bin/bash
#Helper script to create different cmake builds/compilers based on directory
#eg: mkdir Clang;  cd Clang; ../runcmake.sh Debug;  ninja
#or use commandline arguments to select configuration eg:  ../runcmake.sh clang release

if [ -f $PWD/$(basename $0) ]; then
    echo "Don't run this from here.  Instead do:  mkdir Clang; cd Clang; ../$(basename $0)"
    exit 1
fi;

 #Default config is Clang with Debug
compiler=clang
config=Debug

parse_arg () {
    case ${1,,} in
        clang) compiler=clang ;;
        gcc) compiler=gcc ;;
        debug) config=Debug ;;
        release) config=Release ;;
        *) 
            echo "Unknown config parameter '$1'"
        ;;
    esac
}

# parse directory name as a command line argument
parse_arg $(basename $PWD)

for arg in "$@"
do
    parse_arg $arg
done


echo "Compiler is ${compiler}, Build Type is ${config}.       Running Cmake Command:"

case ${compiler,,} in
clang)
    lang="CC=clang CXX=clang++ "
    export $lang
;;
gcc)
    lang=""
;;
esac

cmd="cmake -GNinja -DCMAKE_BUILD_TYPE=${config} .."
echo "${lang}$cmd"

$cmd
