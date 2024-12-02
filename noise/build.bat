@echo off

IF NOT EXIST bin mkdir bin
pushd bin

set OptFlags= -O2
set CodeGenFlags= -GL
set PreFlags= -DDEBUG#1
set LangFlags= -Z7
set MiscFlags= -nologo -Wall -WX -wd4514 -wd4710 -wd4711 -wd4820 -wd4668 -Fe../bin/noise.exe
set CompilerFlags= %OptFlags% %CodeGenFlags% %PreFlags% %LangFlags% %MiscFlags%
set LinkerFlags= -incremental:no

set FileList= ..\src\noise.cpp

cl %CompilerFlags% %FileList% /link %LinkerFlags%

popd
