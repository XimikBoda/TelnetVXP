"C:\MRE_SDK\tools\DllPackage.exe" "D:\MyGitHub\TelnetVXP\TelnetVXP.vcproj"
if %errorlevel% == 0 (
 echo postbuild OK.
  copy TelnetVXP.vpp ..\..\..\MoDIS_VC9\WIN32FS\DRIVE_E\TelnetVXP.vpp /y
exit 0
)else (
echo postbuild error
  echo error code: %errorlevel%
  exit 1
)

