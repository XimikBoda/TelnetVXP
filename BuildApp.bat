REM Build Bat File
REM Precheck the Resource 
"C:\MRE_SDK\tools\ResEditor\CmdShell.exe" save  "D:\MyGitHub\TelnetVXP\TelnetVXP.vcproj"
REM Copmile c file 
"C:\SourceryLite\Bin\arm-none-eabi-gcc" -c -g -fpic -mcpu=arm7tdmi-s -fvisibility=hidden -mthumb -mlittle-endian -O2 -D__MRE_COMPILER_GCC__ -fno-exceptions -fno-non-call-exceptions -o "D:\MyGitHub\TelnetVXP\arm\gccmain.o" -c "C:\MRE_SDK\lib\MRE30\src\gccmain.c"      -D _MINIGUI_LIB_ -D _USE_MINIGUIENTRY -D _NOUNIX_ -D _FOR_WNC -D __MRE_SDK__ -D   __MRE_VENUS_NORMAL__  -D  __MMI_MAINLCD_240X320__ -I "C:\MRE_SDK\include" -I "C:\MRE_SDK\include\service" -I "C:\MRE_SDK\include" -I "C:\MRE_SDK\include\service" -I "D:\MyGitHub\TelnetVXP\include" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\include\component" -I "D:\MyGitHub\TelnetVXP\ResID" -I "D:\MyGitHub\TelnetVXP\src\app\widget" -I "D:\MyGitHub\TelnetVXP\src\app\launcher" -I "D:\MyGitHub\TelnetVXP\src\app\wallpaper" -I "D:\MyGitHub\TelnetVXP\src\app\screen_lock" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\include\component" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\src\framework" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\base" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\mvc" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\pme" -I "D:\MyGitHub\TelnetVXP\src\framework\mmi_core" -I "D:\MyGitHub\TelnetVXP\src\ui_engine\vrt\interface" -I "D:\MyGitHub\TelnetVXP\src\component" -I "D:\MyGitHub\TelnetVXP\src\ui_engine\framework\xml" -I "D:\MyGitHub\TelnetVXP"
REM Copmile c file 
"C:\SourceryLite\Bin\arm-none-eabi-g++" -c -g -fpic -mcpu=arm7tdmi-s -fvisibility=hidden -mthumb -mlittle-endian -O2 -D__MRE_COMPILER_GCC__ -fno-exceptions -fno-non-call-exceptions           -fcheck-new -o "D:\MyGitHub\TelnetVXP\arm\Console.o" -c "d:\MyGitHub\TelnetVXP\Console.cpp"      -D _MINIGUI_LIB_ -D _USE_MINIGUIENTRY -D _NOUNIX_ -D _FOR_WNC -D __MRE_SDK__ -D   __MRE_VENUS_NORMAL__  -D  __MMI_MAINLCD_240X320__ -I "C:\MRE_SDK\include" -I "C:\MRE_SDK\include\service" -I "C:\MRE_SDK\include" -I "C:\MRE_SDK\include\service" -I "D:\MyGitHub\TelnetVXP\include" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\include\component" -I "D:\MyGitHub\TelnetVXP\ResID" -I "D:\MyGitHub\TelnetVXP\src\app\widget" -I "D:\MyGitHub\TelnetVXP\src\app\launcher" -I "D:\MyGitHub\TelnetVXP\src\app\wallpaper" -I "D:\MyGitHub\TelnetVXP\src\app\screen_lock" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\include\component" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\src\framework" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\base" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\mvc" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\pme" -I "D:\MyGitHub\TelnetVXP\src\framework\mmi_core" -I "D:\MyGitHub\TelnetVXP\src\ui_engine\vrt\interface" -I "D:\MyGitHub\TelnetVXP\src\component" -I "D:\MyGitHub\TelnetVXP\src\ui_engine\framework\xml" -I "D:\MyGitHub\TelnetVXP"
REM Copmile c file 
"C:\SourceryLite\Bin\arm-none-eabi-g++" -c -g -fpic -mcpu=arm7tdmi-s -fvisibility=hidden -mthumb -mlittle-endian -O2 -D__MRE_COMPILER_GCC__ -fno-exceptions -fno-non-call-exceptions           -fcheck-new           -fcheck-new -o "D:\MyGitHub\TelnetVXP\arm\main.o" -c "d:\MyGitHub\TelnetVXP\main.cpp"      -D _MINIGUI_LIB_ -D _USE_MINIGUIENTRY -D _NOUNIX_ -D _FOR_WNC -D __MRE_SDK__ -D   __MRE_VENUS_NORMAL__  -D  __MMI_MAINLCD_240X320__ -I "C:\MRE_SDK\include" -I "C:\MRE_SDK\include\service" -I "C:\MRE_SDK\include" -I "C:\MRE_SDK\include\service" -I "D:\MyGitHub\TelnetVXP\include" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\include\component" -I "D:\MyGitHub\TelnetVXP\ResID" -I "D:\MyGitHub\TelnetVXP\src\app\widget" -I "D:\MyGitHub\TelnetVXP\src\app\launcher" -I "D:\MyGitHub\TelnetVXP\src\app\wallpaper" -I "D:\MyGitHub\TelnetVXP\src\app\screen_lock" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\include\component" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\src\framework" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\base" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\mvc" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\pme" -I "D:\MyGitHub\TelnetVXP\src\framework\mmi_core" -I "D:\MyGitHub\TelnetVXP\src\ui_engine\vrt\interface" -I "D:\MyGitHub\TelnetVXP\src\component" -I "D:\MyGitHub\TelnetVXP\src\ui_engine\framework\xml" -I "D:\MyGitHub\TelnetVXP"
REM Copmile c file 
"C:\SourceryLite\Bin\arm-none-eabi-g++" -c -g -fpic -mcpu=arm7tdmi-s -fvisibility=hidden -mthumb -mlittle-endian -O2 -D__MRE_COMPILER_GCC__ -fno-exceptions -fno-non-call-exceptions           -fcheck-new           -fcheck-new           -fcheck-new -o "D:\MyGitHub\TelnetVXP\arm\Telnet.o" -c "d:\MyGitHub\TelnetVXP\Telnet.cpp"      -D _MINIGUI_LIB_ -D _USE_MINIGUIENTRY -D _NOUNIX_ -D _FOR_WNC -D __MRE_SDK__ -D   __MRE_VENUS_NORMAL__  -D  __MMI_MAINLCD_240X320__ -I "C:\MRE_SDK\include" -I "C:\MRE_SDK\include\service" -I "C:\MRE_SDK\include" -I "C:\MRE_SDK\include\service" -I "D:\MyGitHub\TelnetVXP\include" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\include\component" -I "D:\MyGitHub\TelnetVXP\ResID" -I "D:\MyGitHub\TelnetVXP\src\app\widget" -I "D:\MyGitHub\TelnetVXP\src\app\launcher" -I "D:\MyGitHub\TelnetVXP\src\app\wallpaper" -I "D:\MyGitHub\TelnetVXP\src\app\screen_lock" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\include\component" -I "D:\MyGitHub\TelnetVXP\include\service" -I "D:\MyGitHub\TelnetVXP\src\framework" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\base" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\mvc" -I "D:\MyGitHub\TelnetVXP\src\framework\ui_core\pme" -I "D:\MyGitHub\TelnetVXP\src\framework\mmi_core" -I "D:\MyGitHub\TelnetVXP\src\ui_engine\vrt\interface" -I "D:\MyGitHub\TelnetVXP\src\component" -I "D:\MyGitHub\TelnetVXP\src\ui_engine\framework\xml" -I "D:\MyGitHub\TelnetVXP"
REM Link app 
"C:\SourceryLite\Bin\arm-none-eabi-gcc" -o "D:\MyGitHub\TelnetVXP\TelnetVXP.axf"  "D:\MyGitHub\TelnetVXP\arm\gccmain.o"  "D:\MyGitHub\TelnetVXP\arm\Console.o"  "D:\MyGitHub\TelnetVXP\arm\main.o"  "D:\MyGitHub\TelnetVXP\arm\Telnet.o" -fpic -msvr4-struct-return -pie  -T "C:\MRE_SDK\lib\MRE30\armgcc_t\scat.ld" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\percommon.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\pertcp.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\persensor.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\persmsper.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\perbitstream.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\perfile.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\perhttp.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\perpro.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\persec.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\persysstorage.a" -l:"C:\MRE_SDK\lib\MRE30\armgcc_t\perudp.a"
REM Pack resource to app 
"C:\MRE_SDK\tools\ResEditor\CmdShell.exe" pack -silent -resolution 240x320 -o "D:\MyGitHub\TelnetVXP\TelnetVXP.pkd" -e AXF "D:\MyGitHub\TelnetVXP\TelnetVXP.vcproj" "D:\MyGitHub\TelnetVXP\TelnetVXP.axf"
REM Add tag infromation 
"C:\MRE_SDK\tools\PackDigist.exe" "D:\MyGitHub\TelnetVXP\TelnetVXP.vcproj" "TelnetVXP" "0.1.0" "Ximik_Boda" "1500" "NotSupportBg" "Not Support rotate" "TelnetVXP" "TelnetVXP" "TelnetVXP" "1234567890" "content" " TCP Sensor SMS(person) BitStream File HTTP ProMng Sec SysStorage UDP" "vxp" "GCC" "PKD" "UnCompress" "NoVPI" "Adaptable" "15728960" "UnSysMemAble" "
    " "-1" "UNPUSH" "-1" ""  "UnAutoStart"  "UnTransferImg" "NoIdleShortcut"  D:\MyGitHub\TelnetVXP\arm D:\MyGitHub\TelnetVXP\build.log

