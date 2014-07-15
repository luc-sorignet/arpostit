
#Installation
This is a guide for install post-it source code for Epson Moverio BT-100 and a Windows 8 64x Operating system.

##Step 1 : OpenFrameworks
In first step we need to Install OpenFrameworks : http://openframeworks.cc/

####Code Blocks Install
>Download OpenFrameworks for CodeBlocks : [Here](http://www.openframeworks.cc/versions/v0.8.3/of_v0.8.3_win_cb_release.zip)
>Follow [OpenFrameworks Install Guide for CodeBlocks](http://openframeworks.cc/setup/codeblocks/)


####Visual Studio Install
>Download OpenFrameworks for visual studio : [Here](http://www.openframeworks.cc/versions/v0.8.3/of_v0.8.3_vs_release.zip)
>Follow [OpenFrameworks Install Guidefor visual studio](http://openframeworks.cc/setup/vs)

Ok now run some exemples to try OpenFrameworks

##Step 2 : Android SDK and Epson Installation
> Download and unzip Android Bundle for windows it contains Android SDk and eclipse with adt-bundle.
> http://developer.android.com/sdk/index.html#win-bundle
If you want complementary informations about Android Bundle [click here](http://developer.android.com/sdk/installing/index.html)
Install some ADT and run eclipse to test-it

##Step 3 : Epson Moverio Eclipse Install
The main issue to this device is the not recognition... to solve this we need to modify some configuration files.
First we need to install the driver for recognise epson smartglasses as an android device.
> Go to Android SDK Folder and google usb driver path `android-bundle-folder/sdk/extras/google/usb_driver`
> And add some line to `android_winusb.inf` file.
> `[Google.NTamd64]
; BT-100
%SingleAdbInterface% = USB_Install, USB\VID_04B8&PID_0C04
%CompositeAdbInterface% = USB_Install, USB\VID_04B8&PID_0C04&MI_01`


>After go to `%HOMEPATH%/.android` you can copy\paste it in the windows run command `WINDOWS+R` shortcut.
>Modify `adb_usb.ini` and add `0x04B8` 

Ok now we can install the driver for recognize Epson Moverio.
>  Next connect the device with developer mode disabled. Windows will identify it as a USB mass storage device (MSC).


> You need to go into Device Manager and uninstall it. If you have multiple USB-MSDs listed under USB Serial Bus Controllers, you can identify which one is the Moverio by disconnecting it, right clicking on each one that is still present, selecting properties and noting the location value on the general tab. Then reconnect the Moverio and look for the new entry it adds.

> After you've uninstalled the Moverio's USB Mass Storage Device entry, disconnect it and enable Developer mode on the device.

>Then reconnect it. Device Manager will update to show a BT1 entry under Other Devices

>Right click on the BT1 entry, select Update Driver Software, mrowse My Computer for driver software. Provide the path to the USB driver folder from step one. Click Next.

>At this point I get a warning about not being able to verify the publisher of the driver. I believe this is related to my having edited the .inf file. Click install this driver software anyway.

>Windows will report that the driver is successfully installed. Close the update dialog. You should now see an Android Composite ADB Interface entry in device manager. It appeared under Android Phone.

Now the Hardware install is complete
Import the source in your project and enjoy it.

----------


##Optional Step  : OpenFrameworks Addons ofx
To install some ofx like ofxARToolkitPlus copy paste the ofx in the addons Openframeworks folder and include it to your project.
you can search and download some OFX [Here](http://ofxaddons.com/)


----------

> #### Guide Written by [Luc SORIGNET](#)

----------
