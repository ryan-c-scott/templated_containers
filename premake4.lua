solution "TemplatedContainers"
configurations { "Debug", "Release" }
location "build"

flags { 
}

configuration "Debug"
flags { "Symbols" }

configuration "Release"
flags { "OptimizeSpeed", "Symbols" }

------------------------------------------------------------------------------------
project "Tests"
kind "ConsoleApp"
language "C++"

targetdir( "bin" );

files { 
   "src/**.h", "src/**.cpp", "src/**.cc",
   "deps/EASTL/src/**.h", "deps/EASTL/src/**.cpp", 
}

includedirs { 
   "src",
   "deps/EASTL/include"
}

links { 
}

libdirs {
}

