# What is PrimedKeys?
PrimedKeys will be an onscreen configurable hotkey menu with a preset style akin to [Aseprite](https://www.aseprite.org/).
I plan to make specific support for customization, because not only is it fun, why not make it a little artsy considering it's literally meant for artists.

# Why?
It's a project I created from two problems I had.
1. I wanted a way to use hotkeys on a touchscreen laptop without going into the rabbithole of configuring my HP Pen. Or buying another expensive accessory that I probably wouldn't use enough to be worth.
2. The other alternatives did not work well for me, and stopped working or crashed.

In the end I had no other options, so I thought to myself,

> "Hmmmm. I haven't really touched C++ before." - Me

Plus, I was introduced to [Dear ImGui](https://github.com/ocornut/imgui) recently- And I really liked it! So I figured this would be a great opportunity to fix my issues, and learn a new skill!

In my journey of trying to find a software like this. I found [RadialMenu](http://radialmenu.weebly.com/) and [AutoHotPie](https://github.com/dumbeau/AutoHotPie). But in my super specific case it didn't work out. Something about my computer did not want to work with RadialMenu. Also, my HP Pen didn't want to work with AutoHotPie regardless of what I did. Overall I really liked how RadialMenu was a legitamate gui overlay with a top level window holding buttons that replicate keystrokes.

# Setup
1. Clone the repo. Ensure you're using Visual Studio 2022.
2. Check project settings and fix if needed.
   > `General/Platform Toolset` -> `Visual Studio 2022 (v143)`
   >
   > `General/C++ Language Standard` -> `ISO C++ 20 Standard (/std:c++20)`
   >
   > `Advanced/Whole Program Optimization` -> `Use Link Time Code Generation`
   >
   > `Advanced/Character Set` -> `Use Multi-Byte Character Set`
   >
   > `VC++ Directories/Include Directories` -> `lib\SDL2-2.28.3\include;src;include;$(IncludePath)`
   >
   > `VC++ Directories/Library Directories` -> `lib\SDL2-2.28.3\lib\x86;$(LibraryPath)`
   >
   > `Linker::Input/Addictional Dependencies` -> `opengl32.lib;gdi32.lib;imm32.lib;SDL2.lib;SDL2main.lib;%(AdditionalDependencies)`

If you need any help compiling/starting the project DM me on Discord (GudBoiNero#6650) or open an [issue](https://github.com/GudBoiNero/PrimedKeys/issues).

# Contribution Rules
1. For changes you must use a separate branch.
2. You may not push to [`master`](https://github.com/GudBoiNero/PrimedKeys/tree/master). You may only push to [`beta`](https://github.com/GudBoiNero/PrimedKeys/tree/master).
3. Pull requests to main may only be from [`beta`](https://github.com/GudBoiNero/PrimedKeys/tree/master).
4. When making pull requests make sure to state the purpose of your changes, unless the issue the change is derived from clearly explains it.
5. Try to keep commit comments relevant. (Flexible)
