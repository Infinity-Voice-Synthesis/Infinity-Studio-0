mkdir ..\Pb
mkdir ..\Pb\utils
del ..\Pb\utils\* /s /q /f
del ..\Pb\* /s /q /f
protoc --cpp_out=..\Pb utils\pair.proto
protoc --cpp_out=..\Pb nparam.proto
protoc --cpp_out=..\Pb note.proto
protoc --cpp_out=..\Pb point.proto
protoc --cpp_out=..\Pb ppatt.proto
protoc --cpp_out=..\Pb tparam.proto
protoc --cpp_out=..\Pb wave.proto
protoc --cpp_out=..\Pb effect.proto
protoc --cpp_out=..\Pb track.proto
protoc --cpp_out=..\Pb project.proto