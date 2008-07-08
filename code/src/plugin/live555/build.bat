call "C:\Program Files\Microsoft Visual Studio 8\VC\vcvarsall.bat"
cd liveMedia
nmake /B -f liveMedia.mak
cd ../groupsock
nmake /B -f groupsock.mak
cd ../UsageEnvironment
nmake /B -f UsageEnvironment.mak
cd ../BasicUsageEnvironment
nmake /B -f BasicUsageEnvironment.mak
cd ../testProgs
nmake /B -f testProgs.mak
cd ../mediaServer
nmake /B -f mediaServer.mak