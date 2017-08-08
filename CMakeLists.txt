cmake_minimum_required(VERSION 3.3)
project(Utility)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Makefile

        ./include/gda/cli/Command.hpp
        ./include/gda/cli/CommandLineInterface.hpp
        ./include/gda/Color.hpp
        ./include/gda/data_structures/inline_set/InlineSet.hpp
        ./include/gda/FastRandom.hpp
        ./include/gda/fs/File.hpp
        ./include/gda/fs/FileSystem.hpp
        ./include/gda/fs/Folder.hpp
        ./include/gda/hash/MD5Hash.hpp
        ./include/gda/math/Graph.hpp
        ./include/gda/math/Line.hpp
        ./include/gda/math/Math.hpp
        ./include/gda/math/Vector2.hpp
        ./include/gda/math/Vector3.hpp
        ./include/gda/math/Vector4.hpp
        ./include/gda/MemoryRef.hpp
        ./include/gda/Optional.hpp
        ./include/gda/script/Environment.hpp
        ./include/gda/script/Expression.hpp
        ./include/gda/script/ScriptLanguage.hpp
        ./include/gda/String.hpp
        ./include/gda/tcp/Client.hpp
        ./include/gda/tcp/Connection.hpp
        ./include/gda/tcp/NetworkBuffer.hpp
        ./include/gda/tcp/Server.hpp
        ./include/gda/UniqueId.hpp
        ./include/gda/Utility.hpp
        ./src/cli/Command.cpp
        ./src/cli/CommandLineInterface.cpp
        ./src/Color.cpp
        ./src/data_structures/inline_set/InlineSet.cpp
        ./src/FastRandom.cpp
        ./src/fs/File.cpp
        ./src/fs/FileSystem.cpp
        ./src/fs/Folder.cpp
        ./src/hash/MD5Hash.cpp
        ./src/math/Line.cpp
        ./src/math/Math.cpp
        ./src/math/Vector2.cpp
        ./src/math/Vector3.cpp
        ./src/math/Vector4.cpp
        ./src/MemoryRef.cpp
        ./src/script/Environment.cpp
        ./src/script/Expression.cpp
        ./src/script/ScriptLanguage.cpp
        ./src/String.cpp
        ./src/tcp/Client.cpp
        ./src/tcp/Connection.cpp
        ./src/tcp/NetworkBuffer.cpp
        ./src/tcp/Server.cpp
        ./src/UniqueId.cpp
        ./src/Utility.cpp
        ./test/gda/cli/CommandLineInterfaceTest.cpp
        ./test/gda/ColorTest.cpp
        ./test/gda/data_structures/inline_set/InlineSetTest.cpp
        ./test/gda/FastRandomTest.cpp
        ./test/gda/fs/FileSystemTest.cpp
        ./test/gda/MemoryRefTest.cpp
        ./test/gda/OptionalTest.cpp
        ./test/gda/script/ScriptTest.cpp
        ./test/gda/StringTest.cpp
        ./test/gda/UniqueIdTest.cpp
        ./test/tester.cpp)

include_directories(. ./src ./libs/gtest/include ./include)

add_executable(asd ${SOURCE_FILES})
