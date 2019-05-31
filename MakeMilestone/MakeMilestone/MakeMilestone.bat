IF "%~1"=="" GOTO USAGE
echo "%~1"
rd %1
md %1
md %1\Source
copy HAPI_Start\*.cpp %1\Source\
copy HAPI_Start\*.hpp %1\Source\
copy HAPI_Start\*.h %1\Source\
copy HAPI_Start\*.txt %1\
copy *.txt %1\
goto DONE
:USAGE
	echo "usage: MakeMilestone.bat <desired name of milestone folder>"
:DONE
		