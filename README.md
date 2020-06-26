# Template-Coppeliasim-Project
This is simple coppeliasim project in order to just copy and paste simple things. (Visual C++)


In order to set connection:

To use the remote API functionality in your C/C++ application, just include following C-language files in your project:

extApi.h
extApi.c
extApiPlatform.h (contains platform specific code)
extApiPlatform.c (contains platform specific code)
Above files are located in CoppeliaSim's installation directory, under programming/remoteApi. Make sure you have defined NON_MATLAB_PARSING and MAX_EXT_API_CONNECTIONS=255 (and optionally DO_NOT_USE_SHARED_MEMORY) as a preprocessor definition. To enable the remote API on the client side (i.e. your application), call simxStart. See the bubbleRobClient project in the programming directory for an example. This page lists and describes all supported C/C++ remote API functions. CoppeliaSim remote API functions can easily be recognized from their "simx"-prefix.

