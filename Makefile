
.PHONY: dev
dev:
	docker container run \
		-ti \
		--rm \
		--mount type=bind,src=$$PWD,dst=/root/xmastree \
		--workdir /root/xmastree \
		--device /dev/ttyUSB0 \
		--name xmastree \
		juli3nk/dev:arduino

.PHONY: prep
prep:
	arduino-cli core update-index --config-file arduino-cli.yaml
	arduino-cli core install esp32:esp32
	arduino-cli board list
	arduino-cli \
		lib \
		install \
			WiFi \
			ArduinoJson \
			FastLED

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
