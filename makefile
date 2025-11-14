default: build

build:
	mkdir -p output
	gcc -Iinclude -o output/TurboFire src/TurboFire.c src/Card.c src/Deck.c src/Game.c

clean:
	rm -rf output