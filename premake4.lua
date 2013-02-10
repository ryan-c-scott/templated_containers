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
project "VL"
kind "ConsoleApp"
language "C++"

targetdir( "bin" );

files { 
   "src/**.h", "src/**.cpp", "src/**.cc",
}

includedirs { 
   "src",
}

links { 
}

libdirs {
}

