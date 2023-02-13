-- premake5.lua
workspace "AutoSplitter"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "AutoSplitter"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "WalnutExternal.lua"
include "AutoSplitter"