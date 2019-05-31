del /s /q Demo\*.*
rd Demo
md Demo
md Demo\Licenses
md Demo\Licenses\ffmpeg
md Demo\Data

copy HAPI_Start\HAPI\Libs64 Demo\
copy HAPI_Start\HAPI\Licenses Demo\Licenses
copy HAPI_Start\HAPI\Licenses\ffmpeg Demo\Licenses\ffmpeg
copy HAPI_Start\Data Demo\Data\
copy x64\Release\HAPI_Start.exe Demo\Demo64.exe