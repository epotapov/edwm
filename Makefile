EXE_SRCS = edwm.c
DLL_SRCS = edwmDLL.c

all: release

release: edwm.c
	cl $(EXE_SRCS) /link kernel32.lib user32.lib /out:edwm.exe /subsystem:console
	cl $(DLL_SRCS) /LD /link kernel32.lib user32.lib /out:edwmDLL.dll /subsystem:windows /entry:DllMain

clean:
	del *.obj *.exe *.dll *.lib *.exp *.ilk *.pdb *.res
