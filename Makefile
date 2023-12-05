#--device /dev/ttyUSB0
#--privileged \
#--mount type=bind,src=/dev/bus/usb,dst=/dev/bus/usb \

.PHONY: dev
dev:
	docker container run \
		-ti \
		--rm \
		--device /dev/ttyUSB0 \
		--mount type=bind,src=$$PWD,dst=/root/xmastree \
		--workdir /root/xmastree \
		--name xmastree \
		juli3nk/dev:arduino

.PHONY: prep
prep:
	arduino-cli core update-index --config-file arduino-cli.yaml
	arduino-cli core install esp32:esp32
	arduino-cli board list
	arduino-cli lib install \
		ArduinoJson \
		FastLED \
		WifiManager

.PHONY: compile
compile:
	arduino-cli \
		compile \
		--fqbn esp32:esp32:esp32 \
		.

.PHONY: upload
upload:
	arduino-cli \
		upload \
		-p /dev/ttyUSB0 \
		--fqbn esp32:esp32:esp32 \
		.

.PHONY: monitor
monitor:
	screen /dev/ttyUSB0 9600