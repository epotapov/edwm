EXE_SRCS = edwm.c
DLL_SRCS = edwmDLL.c

all: debug

build_all: debug build

debug: edwm.c
	cl $(EXE_SRCS) /link kernel32.lib user32.lib /out:edwm.exe /subsystem:console
	cl $(DLL_SRCS) /LD /link kernel32.lib user32.lib /out:edwmDLL.dll /subsystem:windows /entry:DllMain

build: directory edwm.c
	cl $(EXE_SRCS) /link kernel32.lib user32.lib /out:build/edwm.exe /subsystem:console
	cl $(DLL_SRCS) /LD /link kernel32.lib user32.lib /out:build/edwmDLL.dll /subsystem:windows /entry:DllMain
	del *.obj *.lib *.exp *.ilk *.pdb *.res

directory:
	cmd /c IF NOT EXIST build mkdir build

clean:
	del *.obj *.exe *.dll *.lib *.exp *.ilk *.pdb *.res

clean_all:
	del *.obj *.exe *.dll *.lib *.exp *.ilk *.pdb *.res
	cmd /c IF EXIST build rmdir /S /Q build
