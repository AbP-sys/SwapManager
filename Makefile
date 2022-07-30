swap_manager: dashboard.c
	gcc dashboard.c -o "SwapManager" -lm `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0` 

install:
	cp mkswap.sh /usr/bin/
	cp SwapManager /usr/bin/
	mkdir -p  /etc/SwapManager && cp mystyles.css /etc/SwapManager