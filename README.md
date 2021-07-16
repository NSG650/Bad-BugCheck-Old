# Bad-BugCheck-
Bad Apple but its BSOD [Bootvid]

# How does it work???
The driver uses bootvid's ```VidBitBlt``` function to display each frame and in the end it BugChecks. Bootvid is also used by the BSOD for displaying on the screen.
However as it was only made for displaying the BSOD, Bootscreen it flickers alot and is very slow while displaying the bmps quickly

# NOTE
This driver has only been tested on VMware and I had several issues of the graphics driver interfering and the system BugChecking alot.
Incase you want to try it yourself. Get a copy of Windows 10/11 Insider and install it in VMware and disable the graphics driver using `devmgmt.msc`
