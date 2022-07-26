swap_manager: dashboard.c
	gcc dashboard.c -o "SwapManager" -lm `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0` 

install:
	sudo cp mkswap.sh /bin/
	sudo cp SwapManager /bin/