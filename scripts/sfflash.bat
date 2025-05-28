@echo off
title=uart download
set WORK_PATH=%~dp0
set CURR_PATH=%cd%
cd %WORK_PATH%
set param=%1

if "%param%" NEQ "" (
    if /I "%param:~0,3%"=="com" (
        ImgDownUart.exe --func 0 --port %param% --baund 3000000 --loadram 1 --postact 1 --device SF32LB52X_NOR --file .\ImgBurnList.ini --log ImgBurn.log
        if !errorlevel!==0 (
            echo Download Successful
        ) else (
            echo Download Failed
            echo logfile:%WORK_PATH%ImgBurn.log
        )
        cd %CURR_PATH%
        goto:EOF
    ) else (
        echo Illegal parameter, must start with com or COM string.
        cd %CURR_PATH%
        goto:EOF
    )
)
:start
echo,
echo      Uart Download
echo,
set /p input=please input the serial port num:
goto download
:download
echo com%input%
ImgDownUart.exe --func 0 --port com%input% --baund 3000000 --loadram 1 --postact 1 --device SF32LB52X_NOR --file .\ImgBurnList.ini --log ImgBurn.log
if %errorlevel%==0 (
    echo Download Successful
)else (
    echo Download Failed
    echo logfile:%WORK_PATH%ImgBurn.log
)
cd %CURR_PATH%

if "%ENV_ROOT%"=="" pause

