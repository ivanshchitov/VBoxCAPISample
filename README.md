# VBoxCAPISample


I try to retrieve the virtual machine screen frames to display them inside my other Qt application. For interaction with VirtualBox I use VBox SDK 6.1 (Glue C API) in order to support all target OSes: Linux, macOS and Windows.

I use the following solution to receive the VM's frames. I implemented custom IFramebuffer structure and all its' functions. In particular I implemented get_Capabilities(), NotifyChange(), NotifyUpdate() and NotifyUpdateImage() functions.

Inside get_Capabilities() I set FramebufferCapabilities_UpdateImage, FramebufferCapabilities_RenderCursor, FramebufferCapabilities_MoveCursor capabilities. Inside NotifyUpdateImage() I catch frames and pass them to the Qt part of the application. This Framebuffer is attached to IDisplay instance using AttachFramebuffer() method call.

This solution works correctly on Linux and macOS, it does not under Windows.

Problem is that the NotifyUpdateImage() function is not called. So the application does not receive the frames from the virtual machine.

This example is for debug purposes it runs virtual machine and prints messages from the Framebuffer's functions into console. 
