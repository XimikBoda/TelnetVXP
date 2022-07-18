# TelnetVXP

## What the heck is this?
You probably know what telnet is. If not, please [read the wiki](https://en.wikipedia.org/wiki/Telnet) :)

This is a simple *telnet client* on the [MRE platform](https://web.archive.org/web/20150922183623/http://mre.mediatek.com/). It is also portable enough to extract the terminal itself (without the Telnet things) and put it on your application as an terminal emulator, see [`Console_io.cpp`](https://github.com/XimikBoda/TelnetVXP/blob/main/Console_io.cpp)

[Demo on Youtube](https://www.youtube.com/watch?v=Yvj6gi3ijYE)

## What does it run on?
[MRE platform](https://web.archive.org/web/20150922183623/http://mre.mediatek.com/), for example [Nokia S30+](https://en.wikipedia.org/wiki/Series_30%2B) phones like Nokia 220 (tested), Nokia 225 (tested),... and some other (mostly Chinese) phones. If your (cell / feature) phone can run `.vxp` apps, it's likely to be able to run this app.

## How does it work?
TelnetVXP = Telnet Client + Terminal emulator

## What are the source files in this repo about?

Files in this repo (as the writting time):

|File(s)|Descriptions|
|-|-|
|[`Console.cpp`](https://github.com/XimikBoda/TelnetVXP/blob/main/Console.cpp) and [`Console.h`](https://github.com/XimikBoda/TelnetVXP/blob/main/Console.h)|Terminal emulator|
|[`Console_io.cpp`](https://github.com/XimikBoda/TelnetVXP/blob/main/Console_io.cpp) and [`Console_io.h`](https://github.com/XimikBoda/TelnetVXP/blob/main/Console_io.h)|Console APIs in case you want to use the terminal emulator for your own project|
|[`Profont6x11.h`](https://github.com/XimikBoda/TelnetVXP/blob/main/Profont6x11.h)|Font for the terminal emulator (because MRE's default one is not really suitable for a terminal)|
|[`T2Input.cpp`](https://github.com/XimikBoda/TelnetVXP/blob/main/T2Input.cpp) and [`T2Input.h`](https://github.com/XimikBoda/TelnetVXP/blob/main/T2Input.h)|Virtual keyboard implementation (we will talk about this later)|
|[`main.cpp`](https://github.com/XimikBoda/TelnetVXP/blob/main/main.cpp) and [`main.h`](https://github.com/XimikBoda/TelnetVXP/blob/main/main.h)|Main file contain `vm_main` function and basic MRE events registerer|

## How to build?

**Read `How to use` first before reading this!!!**

You should have [Visual Studio 2008](https://download.microsoft.com/download/8/1/d/81d3f35e-fa03-485b-953b-ff952e402520/VS2008ProEdition90dayTrialENUX1435622.iso) (I don't think newer versions will work) and [MRE SDK](https://github.com/raspiduino/mre-sdk) and a compiler among ADS1.2 (I made a video about cr@cking it [here](https://www.youtube.com/watch?v=b4sNvcwwmeI), RVDS (cr@cking is even easier than ADS1.2) and [GCC](https://sourcery-g-for-arm-eabi.software.informer.com/download/) (I recommend GCC). You might need to fix path problems when using GCC.

- Step 1: Clone this repo:
```
git clone https://github.com/XimikBoda/TelnetVXP
```

**Note**: If you load this project and build it directly, it might not work. Why? Because paths are stored in `.bat` and project config file, and you are likely to have different path of the project and SDK than the authors :). That's why there is step 2:

- Step 2: Open `MRELauncher.exe` and create new project:

![image](https://user-images.githubusercontent.com/68118236/179532798-1d2ce425-90b0-4d0d-8299-da59fc31fb06.png)

![image](https://user-images.githubusercontent.com/68118236/179533160-f9ffa1f4-173b-46d7-b89f-ac38f33ef411.png)

**REMEMBER** to choose the `MRE application project (.vxp)` and your phone's resolution.

Any other things is up to you.

- Step 3: Open the project it Visual Studio 2008, add all the `.h` and `.cpp` files in this repo to the project by Left click at the `Header files` and `Source files` on the left, then select Add -> Existing item

[image](https://user-images.githubusercontent.com/68118236/179534561-8f491ad0-d82c-4259-900e-e2535a55b288.png)

Then save your VS2008 project (<kbd>CTRL</kbd> + <kbd>Shift</kbd> + <kbd>S</kbd>)

- Step 4: Load your project to MRELauncher:
Click on the `Open project` button, browse to your newly created project and select the `.vcproj` files

![image](https://user-images.githubusercontent.com/68118236/179535252-bb3a2a4c-1148-4cf9-9c51-571a795e8f4e.png)

- Step 5: Change project settings:
Click on `Options` button:

![image](https://user-images.githubusercontent.com/68118236/179535525-aabe31e1-db41-4672-8731-6dc3eb110ba8.png)

Select your compiler type and click `Thumb Command`

![image](https://user-images.githubusercontent.com/68118236/179535670-4c41f3e7-2723-417f-a99d-baff5219297b.png)

Press Ok

- Step 6: Click the make button

![image](https://user-images.githubusercontent.com/68118236/179536075-0c24ab4d-94a9-4e20-b498-87a4942e05d8.png)

Your VXP file should be at `arm/`. If there are two VXP files there, choose the one has the bigger size (Ximik Boda added another config)

- Step 7: Sign the VXP
Refer to [this](https://4pda.to/forum/index.php?showtopic=1041371&st=0) or [this](https://reverseengineering.stackexchange.com/a/30573/40846) to do it.

- Step 8: Copy the VXP file to the phone (by using USB cable or SD card is up to you). Then open the file manager, find the signed VXP app and press open to run.

## How to use?
(Prompt for host and port is being added, please wait)

You can see in [`main.cpp`](https://github.com/XimikBoda/TelnetVXP/blob/main/main.cpp) there was:

```cpp
#ifdef WIN32
	telnet.connect_to("127.0.0.1", 23);
#else
	telnet.connect_to("ximik.mooo.com", 25565);
#endif
```

Change this to the telnet host & port you want to connect to. For example `telnet.connect_to("telehack.com", 23);` and `telnet.connect_to("sdf.org", 23);` usually a good start

## Virtual keyboard

It's designed by Ximik Boda to type 1 key just by pressing 2 times (much quicker than default cellphone typing method)

To know the keyboard layout, press the right soft key (the key that above the call key), it will print the keyboard layout to you.

For typing, look at the phone's physical keyboard: the key 1 has some special characters, the key 2 has some letter a, b, c,...

If you want to type key `a`, for example, press key 2, then look at the small virtual keyboard appear on the screen, you will find the key `a` at the location of key 1 now. Press key 1 to finally send the key `a`

Special keys are at key 1 and key *

The enter button (`\r\n`) is the OK key.

Up / Down / Left / Right key is the D-Pad keys.

You might want to watch the demo video at the top of this Readme file. A picture worth thousands words :)

## Author
[Ximik Boda](https://4pda.to/forum/index.php?showuser=6288932)
